// ============================================
// Address:  0x00417c20
// Original: FUN_00417c20
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_00417c20(int param_1)

{
    char cVar1;
    undefined4 uVar2;
    int local_28;
    int local_24;
    int local_20;
    int local_1c;
    undefined1 local_18[8];
    int local_10;
    int local_c;
    int local_8;

    FUN_00416180();
    if (*(int *)(param_1 + 0x4070) == 1)
    {
        uVar2 = FUN_00416350(0xe, 0xc);
    }
    else
    {
        FUN_00416280(0xe);
        local_c = 0;
        for (local_10 = 0; local_10 < 8; local_10 = local_10 + 1)
        {
            if (-1 < (char)(&DAT_006cfde1)[local_10])
            {
                local_c = local_c + 1;
            }
        }
        if (local_c == 0)
        {
            FUN_0065b870("data/bgm/title.ogg");
            *(undefined4 *)(param_1 + 0x4070) = 1;
        }
        local_8 = FUN_004090a0();
        if ((local_8 == 1) && (cVar1 = FUN_00416330(), cVar1 != '\0'))
        {
            *(undefined4 *)(param_1 + 0x4070) = 1;
            return 0xe;
        }
        if ((local_8 == 9) && (cVar1 = FUN_00416330(), cVar1 != '\0'))
        {
            DAT_006cfba0                      = 1;
            *(undefined1 *)(param_1 + 0x3f08) = *(undefined1 *)(param_1 + 0x3c40);
            for (local_1c = 0; local_1c < 4; local_1c = local_1c + 1)
            {
                if ((&DAT_006cfaf8)[local_1c] == 0)
                {
                    DAT_006cfba4 = local_1c;
                }
                *(undefined4 *)(param_1 + 0x3f80 + local_1c * 4) = (&DAT_006cfb28)[local_1c];
                *(undefined4 *)(param_1 + 0x3f70 + local_1c * 4) = (&DAT_006cfaf8)[local_1c];
                *(undefined4 *)(param_1 + 0x3f0c + local_1c * 4) =
                    *(undefined4 *)(param_1 + 0x3c48 + local_1c * 4);
                *(undefined4 *)(param_1 + 0x3f1c + local_1c * 4) =
                    *(undefined4 *)(param_1 + 0x3c58 + local_1c * 4);
                *(undefined4 *)(param_1 + 0x3f2c + local_1c * 4) =
                    *(undefined4 *)(param_1 + 0x3c68 + local_1c * 4);
                *(undefined4 *)(param_1 + 0x3f3c + local_1c * 4) =
                    *(undefined4 *)(param_1 + 0x3c80 + local_1c * 4);
                *(undefined4 *)(param_1 + 0x3f5c + local_1c * 4) =
                    *(undefined4 *)(param_1 + 0x3ca0 + local_1c * 4);
                *(undefined1 *)(param_1 + local_1c + 0x3f6c) =
                    *(undefined1 *)(param_1 + local_1c + 0x3cb0);
                *(undefined4 *)(param_1 + 0x3f4c + local_1c * 4) =
                    *(undefined4 *)(param_1 + 0x3c90 + local_1c * 4);
                *(undefined4 *)(param_1 + 0x3f90 + local_1c * 4) =
                    *(undefined4 *)(&DAT_006cfb38 + local_1c * 4);
                *(int *)(param_1 + 0x3fa0 + local_1c * 4) = (int)(char)(&DAT_006cfb48)[local_1c];
                *(int *)(param_1 + 0x3fb0 + local_1c * 4) = (int)(char)(&DAT_006cfb4c)[local_1c];
                *(int *)(param_1 + 0x3fc0 + local_1c * 4) = (int)(char)(&DAT_006cfb54)[local_1c];
            }
            FUN_00419370(0, param_1 + 0x3f00, 0, 8);
            *(undefined1 *)(param_1 + 0x3fd8) = *(undefined1 *)(param_1 + 0x3c40);
            *(undefined4 *)(param_1 + 0x3fdc) = *(undefined4 *)(param_1 + 0x3d48);
            *(undefined4 *)(param_1 + 0x3fe0) = *(undefined4 *)(param_1 + 0x3d4c);
            *(undefined1 *)(param_1 + 0x3fe4) = *(undefined1 *)(param_1 + 0x3c78);
            *(undefined1 *)(param_1 + 0x3fe5) = *(undefined1 *)(param_1 + 0x3c7c);
            *(undefined4 *)(param_1 + 0x3fe8) = DAT_006cf3c0;
            *(undefined4 *)(param_1 + 0x3fec) = DAT_006cf3b8;
            *(undefined4 *)(param_1 + 0x3ff0) = DAT_006cf3bc;
            *(undefined4 *)(param_1 + 0x3ff4) = DAT_006cf3b0;
            *(undefined4 *)(param_1 + 0x3ff8) = DAT_006cf3b4;
            FUN_00419370(0, param_1 + 0x3fd0, 0, 8);
            FUN_004167c0();
            FUN_00415d30(0, local_18, 0, 8);
            return 0x10;
        }
        *(int *)(param_1 + 0x4074) = *(int *)(param_1 + 0x4074) + 1;
        if (*(int *)(param_1 + 0x4074) == 1)
        {
            *(undefined4 *)(param_1 + 0x4074) = 0;
            for (local_20 = 0; local_20 < 8; local_20 = local_20 + 1)
            {
                *(undefined1 *)(param_1 + local_20 + 0x4060) = (&DAT_006cfde1)[local_20];
            }
            for (local_24 = 0; local_24 < 4; local_24 = local_24 + 1)
            {
                *(undefined1 *)(param_1 + local_24 + 0x4068) =
                    *(undefined1 *)(&DAT_006cfb18 + local_24);
            }
            FUN_00419370(0, param_1 + 0x4058, 0x1e, 2);
            if (*(char *)(param_1 + 0x3c40) == '\0')
            {
                *(undefined1 *)(param_1 + 0x3f08) = *(undefined1 *)(param_1 + 0x3c40);
                for (local_28 = 0; local_28 < 4; local_28 = local_28 + 1)
                {
                    *(undefined4 *)(param_1 + 0x3f80 + local_28 * 4) =
                        *(undefined4 *)(param_1 + 0x3d08 + local_28 * 4);
                    *(undefined4 *)(param_1 + 0x3f70 + local_28 * 4) =
                        *(undefined4 *)(param_1 + 0x3cf8 + local_28 * 4);
                    *(undefined4 *)(param_1 + 0x3f0c + local_28 * 4) =
                        *(undefined4 *)(param_1 + 0x3c48 + local_28 * 4);
                    *(undefined4 *)(param_1 + 0x3f1c + local_28 * 4) =
                        *(undefined4 *)(param_1 + 0x3c58 + local_28 * 4);
                    *(undefined4 *)(param_1 + 0x3f2c + local_28 * 4) =
                        *(undefined4 *)(param_1 + 0x3c68 + local_28 * 4);
                    *(undefined4 *)(param_1 + 0x3f3c + local_28 * 4) =
                        *(undefined4 *)(param_1 + 0x3c80 + local_28 * 4);
                    *(undefined4 *)(param_1 + 0x3f5c + local_28 * 4) =
                        *(undefined4 *)(param_1 + 0x3ca0 + local_28 * 4);
                    *(undefined1 *)(param_1 + local_28 + 0x3f6c) =
                        *(undefined1 *)(param_1 + local_28 + 0x3cb0);
                    *(undefined4 *)(param_1 + 0x3f4c + local_28 * 4) =
                        *(undefined4 *)(param_1 + 0x3c90 + local_28 * 4);
                    *(undefined4 *)(param_1 + 0x3f90 + local_28 * 4) =
                        *(undefined4 *)(param_1 + 0x3d18 + local_28 * 4);
                    *(undefined4 *)(param_1 + 0x3fa0 + local_28 * 4) =
                        *(undefined4 *)(param_1 + 0x3d28 + local_28 * 4);
                    *(undefined4 *)(param_1 + 0x3fb0 + local_28 * 4) =
                        *(undefined4 *)(param_1 + 0x3d38 + local_28 * 4);
                    *(int *)(param_1 + 0x3fc0 + local_28 * 4) =
                        (int)*(char *)(param_1 + local_28 + 0x3cd4);
                    if ((*(float *)(param_1 + 0x4004 + local_28 * 0x14) !=
                         *(float *)(param_1 + 0x3cd8 + local_28 * 4)) ||
                        (*(float *)(param_1 + 0x4008 + local_28 * 0x14) !=
                         *(float *)(param_1 + 0x3ce8 + local_28 * 4)))
                    {
                        *(undefined4 *)(param_1 + 0x4004 + local_28 * 0x14) =
                            *(undefined4 *)(param_1 + 0x3cd8 + local_28 * 4);
                        *(undefined4 *)(param_1 + 0x4008 + local_28 * 0x14) =
                            *(undefined4 *)(param_1 + 0x3ce8 + local_28 * 4);
                        *(undefined1 *)(param_1 + 0x400c + local_28 * 0x14) = (undefined1)local_28;
                        FUN_00419370(0, param_1 + 0x3ffc + local_28 * 0x14, 0x14, 2);
                    }
                }
                FUN_00419370(0, param_1 + 0x3f00, 0x1e, 2);
            }
            else
            {
                *(undefined1 *)(param_1 + 0x3fd8) = *(undefined1 *)(param_1 + 0x3c40);
                *(undefined4 *)(param_1 + 0x3fdc) = *(undefined4 *)(param_1 + 0x3d48);
                *(undefined4 *)(param_1 + 0x3fe0) = *(undefined4 *)(param_1 + 0x3d4c);
                *(undefined1 *)(param_1 + 0x3fe4) = *(undefined1 *)(param_1 + 0x3c78);
                *(undefined1 *)(param_1 + 0x3fe5) = *(undefined1 *)(param_1 + 0x3c7c);
                *(undefined4 *)(param_1 + 0x3fe8) = DAT_006cf3c0;
                *(undefined4 *)(param_1 + 0x3fec) = DAT_006cf3b8;
                *(undefined4 *)(param_1 + 0x3ff0) = DAT_006cf3bc;
                *(undefined4 *)(param_1 + 0x3ff4) = DAT_006cf3b0;
                *(undefined4 *)(param_1 + 0x3ff8) = DAT_006cf3b4;
                FUN_00419370(0, param_1 + 0x3fd0, 0x1e, 2);
            }
            uVar2 = 0xe;
        }
        else
        {
            uVar2 = 0xe;
        }
    }
    return uVar2;
}
