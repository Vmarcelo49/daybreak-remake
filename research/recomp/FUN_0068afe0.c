// ============================================
// Address:  0x0068afe0
// Original: FUN_0068afe0
// Status:   unreviewed
// ============================================

undefined4 FUN_0068afe0(int param_1, undefined4 *param_2, int *param_3)

{
    uint uVar1;
    int iVar2;
    undefined4 uVar3;

    if ((*(uint *)(param_1 + 4) & 0x100) == 0)
    {
        if ((*(uint *)(param_1 + 4) & 0x10) == 0)
        {
            uVar3 = 0x80040249;
        }
        else
        {
            *param_2   = *(undefined4 *)(param_1 + 0x20);
            param_2[1] = *(undefined4 *)(param_1 + 0x24);
            uVar1      = *(uint *)(param_1 + 0x20);
            iVar2      = *(int *)(param_1 + 0x24);
            *param_3   = uVar1 + 1;
            param_3[1] = iVar2 + (uint)(0xfffffffe < uVar1);
            uVar3      = 0x40270;
        }
    }
    else
    {
        *param_2   = *(undefined4 *)(param_1 + 0x20);
        param_2[1] = *(undefined4 *)(param_1 + 0x24);
        *param_3   = *(int *)(param_1 + 0x28);
        param_3[1] = *(int *)(param_1 + 0x2c);
        uVar3      = 0;
    }
    return uVar3;
}
