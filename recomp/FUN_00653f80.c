// ============================================
// Address:  0x00653f80
// Original: FUN_00653f80
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_00653f80(int param_1, uint param_2)

{
    uint uVar1;
    undefined4 uVar2;

    *(undefined4 *)(param_1 + 4)   = 0;
    *(undefined4 *)(param_1 + 8)   = 0;
    *(undefined4 *)(param_1 + 0xc) = 0;
    if (param_2 == 0)
    {
        uVar2 = 0;
    }
    else
    {
        uVar1 = FUN_0065a6b0();
        if (uVar1 < param_2)
        {
            FUN_00654190();
        }
        else
        {
            uVar2                        = FUN_004107e0(param_2);
            *(undefined4 *)(param_1 + 4) = uVar2;
            *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_1 + 4);
            *(uint *)(param_1 + 0xc)     = *(int *)(param_1 + 4) + param_2 * 4;
        }
        uVar2 = 1;
    }
    return uVar2;
}
