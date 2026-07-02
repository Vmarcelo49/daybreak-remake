// ============================================
// Address:  0x004090a0
// Original: FUN_004090a0
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_004090a0(int param_1)

{
    char cVar1;
    undefined4 uVar2;
    int local_c;
    int local_8;

    *(int *)(param_1 + 0x3c3c) = *(int *)(param_1 + 0x3c3c) + 1;
    FUN_006584e0();
    FUN_006585f0();
    cVar1 = FUN_006586d0(0x1c);
    if ((cVar1 != '\0') && ((cVar1 = FUN_006586d0(0xb8),
                             cVar1 != '\0' || (cVar1 = FUN_006586d0(0x38), cVar1 != '\0'))))
    {
        FUN_0064ad70();
    }
    for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1)
    {
        if ((*(float *)(param_1 + 0x3d50 + local_8 * 4) < 1.0) &&
            (local_8 + 5 < *(int *)(param_1 + 0x3c3c)))
        {
            *(float *)(param_1 + 0x3d50 + local_8 * 4) =
                *(float *)(param_1 + 0x3d50 + local_8 * 4) + 0.1;
        }
    }
    if (*(int *)(param_1 + 0x3c3c) < 0x1e)
    {
        uVar2 = 3;
    }
    else
    {
        if (*(char *)(param_1 + 0x3c40) == *(char *)(param_1 + 0x3c41))
        {
            if (*(char *)(param_1 + 0x3c42) != '\0')
            {
                *(char *)(param_1 + 0x3c42) = *(char *)(param_1 + 0x3c42) + -0xf;
            }
        }
        else
        {
            *(char *)(param_1 + 0x3c42) = *(char *)(param_1 + 0x3c42) + '\x0f';
            if (*(char *)(param_1 + 0x3c42) == -1)
            {
                *(undefined1 *)(param_1 + 0x3c41) = *(undefined1 *)(param_1 + 0x3c40);
            }
        }
        if ((DAT_006cfdb0 == '\x01') && (DAT_006cfde1 == -1))
        {
            FUN_00645e10();
        }
        if (*(char *)(param_1 + 0x3c40) == '\0')
        {
            if (DAT_006cfdb0 == '\x01')
            {
                FUN_0040da20(-1 < DAT_006cfde1);
            }
            for (local_c = 0; local_c < 4; local_c = local_c + 1)
            {
                FUN_00409340(local_c);
            }
            if ((((DAT_006caeb8 == 1) && (*(int *)(param_1 + 0x3c90) == 0)) &&
                 (*(int *)(param_1 + 0x3c94) == 0)) &&
                ((*(int *)(param_1 + 0x3c98) == 0 && (*(int *)(param_1 + 0x3c9c) == 0))))
            {
                FUN_0040d7b0();
            }
        }
        else
        {
            if (DAT_006cfdb0 == '\x01')
            {
                FUN_0040da20(0);
            }
            FUN_0040acb0();
            if (*(char *)(param_1 + 0x3c44) != '\0')
            {
                FUN_0040d130();
                return 9;
            }
        }
        if (*(char *)(param_1 + 0x3c43) == '\0')
        {
            uVar2 = 3;
        }
        else
        {
            FUN_0065b870("data/bgm/title.ogg");
            uVar2 = 1;
        }
    }
    return uVar2;
}
