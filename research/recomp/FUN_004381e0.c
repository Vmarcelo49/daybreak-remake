// ============================================
// Address:  0x004381e0
// Original: FUN_004381e0
// Status:   unreviewed
// ============================================

void FUN_004381e0(void)

{
    undefined4 *puVar1;
    char cVar2;
    undefined4 *puVar3;
    undefined4 *in_stack_00000014;

    while (true)
    {
        cVar2  = FUN_00433b00(&stack0x0000000c);
        puVar1 = in_stack_00000014;
        if (cVar2 == '\0')
            break;
        puVar3    = (undefined4 *)FUN_00437250();
        *puVar3   = *puVar1;
        puVar3[1] = puVar1[1];
        puVar3[2] = puVar1[2];
        puVar3[3] = puVar1[3];
        iterator__operator__();
    }
    return;
}
