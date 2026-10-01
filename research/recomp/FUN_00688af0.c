// ============================================
// Address:  0x00688af0
// Original: FUN_00688af0
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_00688af0(undefined4 param_1, int param_2, uint param_3)

{
    int iVar1;
    undefined4 uVar2;

    iVar1 = FUN_0068dae0(param_1);
    if (iVar1 == 1)
    {
        uVar2 = 0x80040203;
    }
    else if ((uint)(*(int *)(param_2 + 8) - *(int *)(param_2 + 4)) < param_3)
    {
        uVar2 = 1;
    }
    else
    {
        *(uint *)(param_2 + 4) = *(int *)(param_2 + 4) + param_3;
        uVar2                  = 0;
    }
    return uVar2;
}
