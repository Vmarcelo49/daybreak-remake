// ============================================
// Address:  0x0068b320
// Original: FUN_0068b320
// Status:   unreviewed
// ============================================

undefined4 FUN_0068b320(int param_1, int param_2)

{
    undefined4 uVar1;

    if (*(int *)(param_1 + 0x3c) != 0)
    {
        FUN_00686ea0(*(undefined4 *)(param_1 + 0x3c));
        *(undefined4 *)(param_1 + 0x3c) = 0;
    }
    if (param_2 == 0)
    {
        *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) & 0xfffffff7;
        uVar1                  = 0;
    }
    else
    {
        uVar1                           = FUN_00686ed0(param_2);
        *(undefined4 *)(param_1 + 0x3c) = uVar1;
        if (*(int *)(param_1 + 0x3c) == 0)
        {
            *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) & 0xfffffff7;
            uVar1                  = 0x8007000e;
        }
        else
        {
            *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | 8;
            uVar1                  = 0;
        }
    }
    return uVar1;
}
