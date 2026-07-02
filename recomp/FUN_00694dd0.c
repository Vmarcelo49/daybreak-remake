// ============================================
// Address:  0x00694dd0
// Original: FUN_00694dd0
// Status:   unreviewed
// ============================================

int FUN_00694dd0(undefined4 param_1, undefined4 param_2)

{
    int iVar1;
    int *local_8;

    iVar1 = FUN_00694b70(&local_8);
    if (-1 < iVar1)
    {
        iVar1 = (**(code **)(*local_8 + 0x20))(local_8, param_2);
        (**(code **)(*local_8 + 8))(local_8);
    }
    return iVar1;
}
