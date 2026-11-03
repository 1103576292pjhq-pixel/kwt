#include <stdint.h>

/* 开发窗口，与本包的新SoC顶层一致；不是赛方最终地址。 */
#define SHARED_BASE ((uintptr_t)0xa0000000u)
volatile uint32_t diagnostic_index, diagnostic_expected, diagnostic_actual;

static inline void barrier(void) { __asm__ volatile("fence iorw,iorw" ::: "memory"); }
static uint32_t pattern(uint32_t word) { return (word * 0x00010003u) ^ 0x5ac36917u; }
static int check(uint32_t word, uint32_t want) {
    volatile uint32_t *p = (volatile uint32_t *)(SHARED_BASE + 4u * word);
    uint32_t value = *p;
    diagnostic_index=word; diagnostic_expected=want; diagnostic_actual=value;
    return value == want;
}

int main(void) {
    volatile uint32_t *ram = (volatile uint32_t *)SHARED_BASE;
    /* 先写完32组首尾，再回读，捕捉组选别名，不能写完一项立即读就算通过。 */
    for (uint32_t b=0;b<32;b++) {
        uint32_t first=b*4096u, last=first+4095u;
        ram[first]=pattern(first); ram[last]=pattern(last);
    }
    barrier();
    for (uint32_t b=0;b<32;b++) {
        uint32_t first=b*4096u, last=first+4095u;
        if (!check(first,pattern(first)) || !check(last,pattern(last))) return 0x61;
    }
    /* 同一字内逐字节store与半字store，由真实CPU LSU完成通路摆放。 */
    volatile uint8_t *bytes=(volatile uint8_t *)SHARED_BASE;
    volatile uint16_t *halves=(volatile uint16_t *)SHARED_BASE;
    ram[0]=0x11223344u;
    bytes[0]=0xa5u; bytes[1]=0x5au; bytes[2]=0xc3u; bytes[3]=0x3cu;
    barrier();if(!check(0,0x3cc35aa5u))return 0x62;
    halves[0]=0x7654u;halves[1]=0xfedcu;
    barrier();if(!check(0,0xfedc7654u))return 0x63;
    ram[131071]=0x89abcdefu;
    barrier();if(!check(131071,0x89abcdefu))return 0x64;
    return 1;
}
