"""Small specification models: ownership/credit/scoreboard, NOT RTL timing."""
from __future__ import annotations
from dataclasses import dataclass


class ProtocolError(ValueError):
    pass


@dataclass
class Slot:
    state: str = "EMPTY"
    tile: int | None = None
    weights: int = 0
    biases: int = 0
    pending_writes: int = 0
    remaining_bias_users: int = 0


class WeightSlots:
    """Physical slot selection is internal. Logical tile IDs must be ordered."""
    def __init__(self, count: int = 2, weight_words: int = 1024, bias_words: int = 16):
        if count not in (1, 2):
            raise ValueError("one or two slots")
        self.slots = [Slot() for _ in range(count)]
        self.next_open = 0
        self.next_active = 0
        self.weight_words, self.bias_words = weight_words, bias_words

    def open(self, tile: int) -> int:
        if tile != self.next_open:
            raise ProtocolError("unexpected tile identity")
        if any(s.state == "FILLING" for s in self.slots):
            raise ProtocolError("only one ingress tile can be filling")
        for i, slot in enumerate(self.slots):
            if slot.state == "EMPTY":
                self.slots[i] = Slot("FILLING", tile)
                self.next_open += 1
                return i
        raise BlockingIOError("legal OPEN waits for an EMPTY slot")

    def write(self, index: int, kind: str, element: int) -> None:
        slot = self.slots[index]
        if slot.state != "FILLING":
            raise ProtocolError("cannot write a non-FILLING slot")
        if kind == "W":
            if slot.biases or element != slot.weights or element >= self.weight_words:
                raise ProtocolError("duplicate/out-of-order W")
            slot.weights += 1
        elif kind == "B":
            if slot.weights != self.weight_words or element != slot.biases or element >= self.bias_words:
                raise ProtocolError("invalid bias sequence")
            slot.biases += 1
        else:
            raise ProtocolError("unknown load kind")
        slot.pending_writes += 1

    def acknowledge_write(self, index: int) -> None:
        slot = self.slots[index]
        if slot.pending_writes <= 0:
            raise ProtocolError("no pending write")
        slot.pending_writes -= 1

    def commit(self, index: int) -> None:
        slot = self.slots[index]
        if slot.state != "FILLING" or slot.weights != self.weight_words or slot.biases != self.bias_words:
            raise ProtocolError("incomplete tile")
        if slot.pending_writes:
            raise BlockingIOError("COMMIT is a barrier: wait for real RAM writes")
        slot.state = "READY"

    def activate(self, index: int) -> None:
        slot = self.slots[index]
        if slot.state != "READY" or slot.tile != self.next_active:
            raise ProtocolError("tile not ready or out of order")
        if any(s.state == "ACTIVE" for s in self.slots):
            raise ProtocolError("only one ACTIVE tile")
        slot.state = "ACTIVE"
        slot.remaining_bias_users = 1
        self.next_active += 1

    def finish_bias_use(self, index: int) -> None:
        if self.slots[index].state != "ACTIVE":
            raise ProtocolError("no ACTIVE tile")
        self.slots[index].remaining_bias_users = 0

    def release(self, index: int) -> None:
        slot = self.slots[index]
        if slot.state != "ACTIVE" or slot.remaining_bias_users or slot.pending_writes:
            raise ProtocolError("cannot release a live tile")
        self.slots[index] = Slot()

    def reset(self) -> None:
        self.slots = [Slot() for _ in self.slots]
        self.next_open = self.next_active = 0


class ReadCredits:
    """Capacity covers already-returned data AND all non-cancellable reads."""
    def __init__(self, capacity: int):
        if capacity < 1:
            raise ValueError("positive capacity required")
        self.capacity = capacity
        self.inflight = self.buffered = 0

    @property
    def can_issue(self) -> bool:
        return self.inflight + self.buffered < self.capacity

    def issue(self) -> None:
        if not self.can_issue:
            raise BlockingIOError("no credit for inevitable RAM return")
        self.inflight += 1

    def returned(self) -> None:
        if not self.inflight:
            raise ProtocolError("unsolicited RAM return")
        self.inflight -= 1
        self.buffered += 1

    def consume(self) -> None:
        if not self.buffered:
            raise ProtocolError("empty buffer")
        self.buffered -= 1


class StableChannel:
    """Observed payload must remain valid and unchanged until handshake."""
    def __init__(self):
        self.held = None

    def observe(self, valid: bool, ready: bool, payload: tuple, reset: bool = False) -> None:
        if reset:
            self.held = None
            return
        if self.held is not None and (not valid or payload != self.held):
            raise ProtocolError("valid/payload changed under backpressure")
        self.held = payload if valid and not ready else None
