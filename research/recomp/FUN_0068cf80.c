// ============================================
// Address:  0x0068cf80
// Original: FUN_0068cf80
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_0068cf80(int param_1)

{
    undefined4 uVar1;

    if (((*(int *)(param_1 + 0x38) < 1) || (*(int *)(param_1 + 0x40) < 1)) ||
        (*(int *)(param_1 + 0x44) < 1))
    {
        uVar1 = 0x80040212;
    }
    else if (*(int *)(param_1 + 0x4c) == 0)
    {
        uVar1 = 1;
    }
    else
    {
        uVar1 = 0;
    }
    return uVar1;
}
