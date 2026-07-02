// ============================================
// Address:  0x00694d80
// Original: FUN_00694d80
// Status:   unreviewed
// ============================================

int FUN_00694d80(undefined4 param_1, undefined4 param_2)

{
    int iVar1;
    int *local_8;

    iVar1 = FUN_00694b70(&local_8);
    if (-1 < iVar1)
    {
        iVar1 = (**(code **)(*local_8 + 0x1c))(local_8, param_2);
        (**(code **)(*local_8 + 8))(local_8);
    }
    return iVar1;
}
