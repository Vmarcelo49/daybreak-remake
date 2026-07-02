// ============================================
// Address:  0x00401e80
// Original: FUN_00401e80
// Status:   unreviewed
// ============================================

void __fastcall FUN_00401e80(int param_1)

{
    FUN_00651110(6);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x1c, 1);
    (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8, 0, 5, 1);
    (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8, 0, 6, 1);
    (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8, 0, 7, 1);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0xf, 1);
    if (*(int *)(param_1 + 0x18) != 0)
    {
        FUN_0064e1a0();
    }
    (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8, 0, 5, 2);
    (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8, 0, 6, 2);
    (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8, 0, 7, 2);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0xf, 0);
    FUN_00651110(5);
    if (*(int *)(param_1 + 0x14) != 0)
    {
        FUN_0064e1a0();
    }
    FUN_00651110(9);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0xe, 0);
    if (*(int *)(param_1 + 0x1c) != 0)
    {
        FUN_0064e1a0();
    }
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0xe, 1);
    return;
}
