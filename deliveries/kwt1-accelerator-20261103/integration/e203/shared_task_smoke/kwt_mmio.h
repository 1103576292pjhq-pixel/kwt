#ifndef KWT_MMIO_H
#define KWT_MMIO_H
/* Current project ABI, not an E203-defined peripheral register map. */
#define KWT_BASE       0x11000000u
#define KWT_STATUS     0x00u
#define KWT_TASK       0x04u
#define KWT_LAYER      0x08u
#define KWT_TILE       0x0cu
#define KWT_INDEX      0x10u
#define KWT_DATA       0x14u
#define KWT_ERROR      0x1cu
#define KWT_ACK_TASK   0x34u
#define KWT_ACK_SEQ    0x38u
#define KWT_ACK_COUNT  0x3cu

_Static_assert(sizeof(unsigned int) == 4, "32-bit unsigned int required");
unsigned int kwt_read32(unsigned int offset);
void kwt_write32(unsigned int offset, unsigned int value);
unsigned int kwt_mmio_test(void);
#endif
