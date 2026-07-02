// ============================================
// Address:  0x006936e0
// Original: FUN_006936e0
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_006936e0(undefined4 param_1, int *param_2)

{
    undefined4 uVar1;
    int iVar2;

    if (*param_2 == 0)
    {
        uVar1 = 0;
    }
    else
    {
        iVar2    = FUN_0068dc80(param_1, *param_2);
        *param_2 = iVar2;
        uVar1    = FUN_00699fc0();
    }
    return uVar1;
}
