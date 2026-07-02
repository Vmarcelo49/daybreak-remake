// ============================================
// Address:  0x00694f80
// Original: FUN_00694f80
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_00694f80(undefined4 param_1, int *param_2, undefined4 param_3)

{
    int iVar1;
    undefined4 uVar2;

    iVar1 = (**(code **)(*param_2 + 0x50))(param_3, 0, param_1);
    if (iVar1 < 0)
    {
        uVar2 = FUN_00694f30(&LAB_006982a0, param_3);
    }
    else
    {
        uVar2 = 0;
    }
    return uVar2;
}
