/* Only the I/O backend differs; task_test.c is the actual firmware driver. */
#include <stdio.h>
#include <stdlib.h>
#include "../task_test.h"

static FILE *requests, *responses;
static unsigned int transactions;

static unsigned int transact(unsigned int read, unsigned int offset, unsigned int value)
{
    unsigned int result, err;
    if (fprintf(requests, "%u %x %x\n", read, offset, value) < 0 || fflush(requests)) exit(5);
    if (fscanf(responses, "%x %u", &result, &err) != 2) exit(6);
    ++transactions;
    if (err) { fprintf(stderr, "ICB_ERROR offset=%x read=%u\n", offset, read); exit(7); }
    return result;
}

unsigned int kwt_read32(unsigned int offset) { return transact(1, offset, 0); }
void kwt_write32(unsigned int offset, unsigned int value) { (void)transact(0, offset, value); }

int main(int argc, char **argv)
{
    if (argc != 3) return 4;
    requests = fopen(argv[1], "w");
    responses = fopen(argv[2], "r");
    if (!requests || !responses) return 4;
    unsigned int code = kwt_task_test();
    printf("C_TASK code=%x blocks=%u outputs=%u position=%u expected=%x actual=%x status=%x error=%x transactions=%u\n",
           code, kwt_diag.blocks, kwt_diag.outputs, kwt_diag.position,
           kwt_diag.expected, kwt_diag.actual, kwt_diag.status, kwt_diag.error, transactions);
    fprintf(requests, "2 0 0\n");
    fflush(requests);
    fclose(requests); fclose(responses);
    return code == 1 ? 0 : 1;
}
