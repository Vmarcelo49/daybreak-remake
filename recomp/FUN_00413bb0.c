// ============================================
// Address:  0x00413bb0
// Original: FUN_00413bb0
// Status:   unreviewed
// ============================================

/* WARNING: Removing unreachable block (ram,0x00414416) */
/* WARNING: Removing unreachable block (ram,0x00413e90) */

undefined4 __fastcall FUN_00413bb0(int param_1)

{
    char cVar1;
    undefined4 local_2c;
    undefined4 local_28;
    int local_1c;
    undefined4 local_10;
    int local_8;

    cVar1 = FUN_00650f70();
    if (cVar1 != '\0')
    {
        FUN_00650f40();
        (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 7, 0);
        if (*(int *)(param_1 + 0x1088) == 7)
        {
            FUN_004082f0(0xffffffff);
            FUN_00655d60(0, 0);
            FUN_00655830(0x43c80000, 0x43960000, 0, 0);
        }
        else if (*(int *)(param_1 + 0x1088) == 8)
        {
            FUN_004082f0(0xffffffff);
            FUN_00655d60(0, 0);
            FUN_00655830(0x43c80000, 0x43960000, 0, 1);
        }
        else if (*(int *)(param_1 + 0x1088) == 2)
        {
            FUN_004082f0(0xff808080);
            FUN_00655d60(0, 0);
            FUN_00655d60(0x43980000, 0x41800000);
            FUN_00655d60(0x43100000, 0x42800000);
            FUN_00655830(0x442c0000, 0x42800000, 0, 0);
            FUN_00655830(0x442c0000, 0x42c00000, 0, 1);
            FUN_00655830(0x442c0000, 0x43000000, 0, 2);
            FUN_00655830(0x442c0000, 0x43200000, 0, 3);
            FUN_00655830(0x442c0000, 0x43400000, 0, 4);
            if (*(int *)(param_1 + 0x107c) == 0x10)
            {
                FUN_00655d60(0x44300000, (float)*(int *)(param_1 + 0x1080) * 32.0 + 80.0);
            }
            else
            {
                FUN_00655d60((float)*(int *)(param_1 + 0x107c) * 32.0 + 160.0,
                             (float)*(int *)(param_1 + 0x1080) * 32.0 + 80.0);
            }
            FUN_00655d60((float)*(int *)(param_1 + 0x1074) * 24.0 + 320.0, 0x42000000);
            for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1)
            {
                FUN_00655830((float)local_8 * 24.0 + 320.0,
                             0x42000000,
                             (&DAT_006cfdb8)[local_8] & 0xf,
                             (int)(uint)(byte)(&DAT_006cfdb8)[local_8] >> 4);
            }
        }
        else
        {
            FUN_004082f0(0xffffffff);
            FUN_00655d60(0, 0);
            FUN_00655830(0x43200000, 0x43000000, *(int *)(param_1 + 0x1070) != 0, 0);
            FUN_00655830(0x43200000, 0x43400000, *(int *)(param_1 + 0x1070) != 1, 2);
            if ((*(int *)(param_1 + 0x1074) == 0) && (*(int *)(param_1 + 0x1088) == 1))
            {
                local_28 = 0;
            }
            else
            {
                local_28 = 1;
            }
            FUN_00655830(0x43200000, 0x43600000, local_28, 3);
            if ((*(int *)(param_1 + 0x1074) == 1) && (*(int *)(param_1 + 0x1088) == 1))
            {
                local_2c = 0;
            }
            else
            {
                local_2c = 1;
            }
            FUN_00655830(0x43200000, 0x43800000, local_2c, 4);
            FUN_00655830(0x43200000, 0x43a00000, *(int *)(param_1 + 0x1070) != 2, 6);
            FUN_00655830(0x43200000, 0x43c00000, *(int *)(param_1 + 0x1070) != 3, 8);
            FUN_00655830(0x43200000, 0x43d00000, *(int *)(param_1 + 0x1070) != 4, 9);
            FUN_00655830(0x43200000, 0x43e00000, *(int *)(param_1 + 0x1070) != 5, 10);
            if (*(int *)(param_1 + 0x1088) != 5)
            {
                FUN_00414700(0xff808080);
            }
            FUN_00431b20(DAT_006cfdc1, 0x43c80000, 0x43600000, 0x3f800000, 3);
            FUN_00431ce0(0x43c60000, 0x43600000, 0x3f800000, 3, 1);
            FUN_00431b20(DAT_006cfdc2, 0x43f00000, 0x43600000, 0x3f800000, 3);
            FUN_00431ce0(0x43ee0000, 0x43600000, 0x3f800000, 3, 1);
            FUN_00431b20(DAT_006cfdc3, 0x440c0000, 0x43600000, 0x3f800000, 3);
            FUN_00431ce0(0x440b0000, 0x43600000, 0x3f800000, 3, 1);
            FUN_00431b20(DAT_006cfdc4, 0x44200000, 0x43600000, 0x3f800000, 3);
            FUN_00414700(0xffffffff);
            if (*(int *)(param_1 + 0x1088) == 5)
            {
                FUN_00655d60((((float)(*(int *)(param_1 + 0x1078) / 3) * 80.0 + 400.0) - 16.0) -
                                 (float)(2 - *(int *)(param_1 + 0x1078) % 3) * 22.0,
                             0x43700000);
            }
            if ('\0' < *(char *)(param_1 + 0x18b4))
            {
                FUN_004082f0(0xff000000);
                FUN_00655830(0x43b40000, 0x43858000, 0, (int)*(char *)(param_1 + 0x18b5));
                FUN_00655830(0x43b58000, 0x43840000, 0, (int)*(char *)(param_1 + 0x18b5));
                FUN_00655830(0x43b40000, 0x43828000, 0, (int)*(char *)(param_1 + 0x18b5));
                FUN_00655830(0x43b28000, 0x43840000, 0, (int)*(char *)(param_1 + 0x18b5));
                FUN_00655830(0x43b50000, 0x43850000, 0, (int)*(char *)(param_1 + 0x18b5));
                FUN_00655830(0x43b30000, 0x43850000, 0, (int)*(char *)(param_1 + 0x18b5));
                FUN_00655830(0x43b50000, 0x43830000, 0, (int)*(char *)(param_1 + 0x18b5));
                FUN_00655830(0x43b30000, 0x43830000, 0, (int)*(char *)(param_1 + 0x18b5));
                if (*(int *)(param_1 + 0x1088) == 6)
                {
                    FUN_004082f0(0xffffffff);
                }
                else
                {
                    FUN_004082f0(0xff808080);
                }
                FUN_00655830(0x43b40000, 0x43840000, 0, (int)*(char *)(param_1 + 0x18b5));
            }
            for (local_1c = 0; local_1c < 8; local_1c = local_1c + 1)
            {
                FUN_00655830((float)local_1c * 24.0 + 368.0,
                             0x43a80000,
                             (&DAT_006cfdb8)[local_1c] & 0xf,
                             (int)(uint)(byte)(&DAT_006cfdb8)[local_1c] >> 4);
            }
            FUN_00431b20(DAT_006cfdc5, 0x43ea0000, 0x43c00000, 0x3f800000, 1);
            if (*(int *)(param_1 + 0x1088) == 3)
            {
                FUN_00655d60(0x43e20000, 0x43c80000);
            }
            FUN_00431b20(DAT_006cfdc6, 0x44000000, 0x43d00000, 0x3f800000, 5);
            if (*(int *)(param_1 + 0x1088) == 4)
            {
                FUN_00655d60(496.0 - (float)(4 - *(int *)(param_1 + 0x1074)) * 22.0, 0x43d80000);
            }
            FUN_00655830(0x43d20000, 0x43e00000, 0, DAT_006cfdc8 + 0xe);
            if (*(int *)(param_1 + 0x1088) == 9)
            {
                FUN_00655d60(0x43e20000, 0x43e80000);
            }
            switch (*(undefined4 *)(param_1 + 0x1070))
            {
            case 0:
                local_10 = 0;
                break;
            case 1:
                if (((*(int *)(param_1 + 0x1088) == 1) && (*(int *)(param_1 + 0x1074) == 0)) ||
                    (*(int *)(param_1 + 0x1088) == 5))
                {
                    local_10 = 1;
                }
                else if (((*(int *)(param_1 + 0x1088) == 1) && (*(int *)(param_1 + 0x1074) == 1)) ||
                         (*(int *)(param_1 + 0x1088) == 6))
                {
                    local_10 = 2;
                }
                else
                {
                    local_10 = 6;
                }
                break;
            case 2:
                local_10 = 3;
                break;
            case 3:
                local_10 = 4;
                break;
            case 4:
                local_10 = 5;
                break;
            case 5:
                local_10 = 7;
            }
            FUN_00655830(0x43c80000, 0x44000000, 0, local_10);
        }
        FUN_00650fd0();
    }
    return 1;
}
