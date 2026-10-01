// ============================================
// Address:  0x006533f0
// Original: FUN_006533f0
// Status:   unreviewed
// ============================================

void __thiscall FUN_006533f0(int param_1, undefined4 param_2)

{
    char cVar1;
    int *piVar2;

    cVar1 = FUN_0064d6e0();
    if (cVar1 == '\0')
    {
        piVar2 = (int *)FUN_006543d0(param_2);
        if (*(int *)(param_1 + 0x7c) == *piVar2)
        {
            *(undefined4 *)(param_1 + 0x7c) = 0;
        }
        if (*piVar2 != 0)
        {
            FUN_00653b00(1);
        }
        FUN_0065a7f0(param_2);
    }
    return;
}
