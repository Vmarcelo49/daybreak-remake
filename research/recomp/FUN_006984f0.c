// ============================================
// Address:  0x006984f0
// Original: FUN_006984f0
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_006984f0(int param_1, int param_2, int param_3)

{
    undefined4 uVar1;

    if (param_2 < 0)
    {
        uVar1 = 0x80070057;
    }
    else if (param_2 < 1)
    {
        if (param_3 == 0)
        {
            uVar1 = 0x80004003;
        }
        else if (*(int *)(param_1 + 0x98) == 0)
        {
            uVar1 = 0x8000ffff;
        }
        else
        {
            uVar1 = FUN_00698fb0();
            FUN_00686900(uVar1);
            uVar1 = 0;
        }
    }
    else
    {
        uVar1 = 0x40103;
    }
    return uVar1;
}
