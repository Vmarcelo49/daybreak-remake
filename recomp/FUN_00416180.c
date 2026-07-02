// ============================================
// Address:  0x00416180
// Original: FUN_00416180
// Status:   unreviewed
// ============================================

void __fastcall FUN_00416180(int *param_1)

{
    char cVar1;
    int local_c;
    int local_8;

    local_8 = 0;
    for (local_c = 1; local_c < 8; local_c = local_c + 1)
    {
        cVar1 = FUN_00416230(local_c);
        if (cVar1 != '\0')
        {
            FUN_00660310(local_c);
            (**(code **)(*param_1 + 0x10))(local_c);
        }
        if ((&DAT_006cfdd1)[local_c] == '\0')
        {
            param_1[local_c + 0x48] = 0;
            param_1[local_c + 0x50] = 0;
        }
        else
        {
            local_8 = local_8 + 1;
        }
    }
    DAT_006cfdcc = local_8;
    return;
}
