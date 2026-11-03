/* Compiler check only: this has no reset entry or pass/fail termination.
 * Do not upload this probe as an E203 test program.
 */
unsigned int kwt_toolchain_probe(volatile unsigned int *p)
{
    unsigned int value = *p;
    *p = value ^ 0x13579bdfu;
    return *p;
}
