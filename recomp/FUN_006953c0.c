// ============================================
// Address:  0x006953c0
// Original: FUN_006953c0
// Status:   unreviewed
// ============================================

int FUN_006953c0(undefined4 param_1, double param_2)

{
    int iVar1;
    undefined4 local_c;

    if (param_2 == 0.0)
    {
        iVar1 = -0x7ff8ffa9;
    }
    else
    {
        iVar1 = FUN_00694af0();
        if (-1 < iVar1)
        {
            iVar1 = (**(code **)(*local_c + 0x38))(local_c, param_2);
            (**(code **)(*local_c + 8))(local_c);
        }
    }
    return iVar1;
}
