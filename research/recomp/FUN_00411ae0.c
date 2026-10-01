// ============================================
// Address:  0x00411ae0
// Original: FUN_00411ae0
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_00411ae0(int param_1)

{
    undefined4 uVar1;
    int local_8;

    if (*(char *)(param_1 + 0x5cc) == '\0')
    {
        *(float *)(param_1 + 0x5d0) = *(float *)(param_1 + 0x5d0) - 30.0;
        *(float *)(param_1 + 0x5d4) = *(float *)(param_1 + 0x5d4) - 20.0;
        *(float *)(param_1 + 0x5d8) = *(float *)(param_1 + 0x5d8) - 20.0;
        *(float *)(param_1 + 0x5dc) = *(float *)(param_1 + 0x5dc) - 30.0;
        for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1)
        {
            if (*(float *)(param_1 + 0x5d0 + local_8 * 4) < 0.0)
            {
                *(undefined4 *)(param_1 + 0x5d0 + local_8 * 4) = 0;
            }
        }
        if (0x5a < *(int *)(param_1 + 0x5c4))
        {
            if (*(float *)(param_1 + 0x5e0) <= 1.0)
            {
                *(undefined4 *)(param_1 + 0x5e0) = 0x3f800000;
                FUN_0065d670();
                *(undefined1 *)(param_1 + 0x5cc) = 1;
                FUN_0065d6a0();
            }
            else
            {
                *(float *)(param_1 + 0x5e0) = *(float *)(param_1 + 0x5e0) - 0.25;
            }
            FUN_00408250(*(undefined4 *)(param_1 + 0x5e0));
            FUN_004120f0((*(float *)(param_1 + 0x5e0) - 1.0) * 42.0);
        }
        if (*(int *)(param_1 + 0x5c4) == 0)
        {
            FUN_0065b870("data/bgm/vs.ogg");
        }
        *(int *)(param_1 + 0x5c4) = *(int *)(param_1 + 0x5c4) + 1;
        uVar1                     = 9;
    }
    else
    {
        if (DAT_006cfce9 == '\x01')
        {
            FUN_006492f0();
        }
        else
        {
            FUN_00648ad0();
        }
        uVar1 = 10;
    }
    return uVar1;
}
