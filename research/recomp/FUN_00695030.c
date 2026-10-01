// ============================================
// Address:  0x00695030
// Original: FUN_00695030
// Status:   unreviewed
// ============================================

int FUN_00695030(undefined4 param_1, undefined4 param_2, undefined4 param_3)

{
    int iVar1;
    int *local_8;

    iVar1 = FUN_00694b70(&local_8);
    if (-1 < iVar1)
    {
        iVar1 = (**(code **)(*local_8 + 0x40))(local_8, param_2, param_3);
        (**(code **)(*local_8 + 8))(local_8);
    }
    return iVar1;
}
