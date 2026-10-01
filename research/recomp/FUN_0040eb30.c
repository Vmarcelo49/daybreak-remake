// ============================================
// Address:  0x0040eb30
// Original: FUN_0040eb30
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_0040eb30(int param_1)

{
    char cVar1;
    undefined4 uVar2;
    undefined4 *puVar3;
    int iVar4;
    float *pfVar5;
    undefined1 local_c[4];
    int local_8;

    FUN_006584e0();
    FUN_006585f0();
    FUN_00657390();
    FUN_00657390();
    cVar1 = FUN_006586d0(1);
    if (cVar1 == '\0')
    {
        if (*(char *)(param_1 + 0x76b) == '\0')
        {
            if (*(char *)(param_1 + 0x76c) == '\0')
            {
                if ((*(char *)(param_1 + 0x769) != '\0') &&
                    (*(char *)(param_1 + 0x769) = *(char *)(param_1 + 0x769) + -0xf,
                     *(byte *)(param_1 + 0x769) < 0xf))
                {
                    *(undefined1 *)(param_1 + 0x769) = 0;
                }
                if ((*(char *)(param_1 + 0x76a) != '\0') &&
                    (*(char *)(param_1 + 0x76a) = *(char *)(param_1 + 0x76a) + -5,
                     *(byte *)(param_1 + 0x76a) < 5))
                {
                    *(undefined1 *)(param_1 + 0x76a) = 0;
                }
                if ((*(int *)(param_1 + 0x878) != 0) &&
                    (*(int *)(param_1 + 0x878) = *(int *)(param_1 + 0x878) + -1,
                     *(int *)(param_1 + 0x878) == 0))
                {
                    FUN_0065b330(*(undefined4 *)(param_1 + 0x44), 0);
                }
                *(undefined1 *)(param_1 + 0x759) = 0;
                for (local_8 = 0; local_8 < 6; local_8 = local_8 + 1)
                {
                    iVar4 = FUN_0063bf40();
                    if (iVar4 != 0)
                    {
                        iVar4               = FUN_0040fc30();
                        *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + -1;
                        pfVar5              = (float *)FUN_0040fc30();
                        *(float *)(param_1 + 0x6ac + local_8 * 4) =
                            *(float *)(param_1 + 0x6ac + local_8 * 4) + *pfVar5;
                        iVar4 = FUN_0040fc30();
                        if (*(int *)(iVar4 + 4) == 0)
                        {
                            FUN_0040fc50();
                        }
                        *(undefined1 *)(param_1 + 0x759) = 1;
                    }
                }
                if (*(int *)(param_1 + 0x878) == 0)
                {
                    *(int *)(param_1 + 0x75c) = *(int *)(param_1 + 0x75c) + 1;
                }
                if ((((*(char *)(param_1 + 0x758) == '\0') || (DAT_006cae9c == 1)) ||
                     (DAT_006caf00 == 1)) &&
                    (*(char *)(param_1 + 0x759) == '\0'))
                {
                    if (*(int *)(param_1 + 0x75c) < *(int *)(param_1 + 0x760))
                    {
                        *(undefined4 *)(param_1 + 0x75c) = *(undefined4 *)(param_1 + 0x760);
                    }
                    else
                    {
                        *(undefined1 *)(param_1 + 0x758) = 0;
                        cVar1                            = FUN_0040f4c0();
                        if (cVar1 != '\0')
                        {
                            if (DAT_006cfbc4 == -1)
                            {
                                return 5;
                            }
                            if (DAT_006cfbc5 != '\x01')
                            {
                                DAT_006cfaf4 = (int)(char)(&DAT_006cfbd9)[DAT_006cfbc4];
                                DAT_006cfb30 = (int)(char)(&DAT_006cfbcd)[DAT_006cfbc4 * 2];
                                DAT_006cfb34 = (int)(char)(&DAT_006cfbce)[DAT_006cfbc4 * 2];
                                DAT_006cfbc5 = 1;
                                return 9;
                            }
                            DAT_006cfbc5                     = '\0';
                            DAT_006cfbc4                     = DAT_006cfbc4 + '\x01';
                            *(undefined4 *)(param_1 + 0x770) = 0;
                            *(undefined1 *)(param_1 + 0x76c) = 1;
                        }
                    }
                }
                if ((DAT_006caeb8 == 1) || (DAT_006caf1c == 1))
                {
                    if (DAT_006cfbc4 == -1)
                    {
                        return 5;
                    }
                    if (DAT_006cfbc5 != '\x01')
                    {
                        DAT_006cfaf4 = (int)(char)(&DAT_006cfbd9)[DAT_006cfbc4];
                        DAT_006cfb30 = (int)(char)(&DAT_006cfbcd)[DAT_006cfbc4 * 2];
                        DAT_006cfb34 = (int)(char)(&DAT_006cfbce)[DAT_006cfbc4 * 2];
                        DAT_006cfbc5 = 1;
                        return 9;
                    }
                    DAT_006cfbc5                     = '\0';
                    DAT_006cfbc4                     = DAT_006cfbc4 + '\x01';
                    *(undefined4 *)(param_1 + 0x770) = 0;
                    *(undefined1 *)(param_1 + 0x76c) = 1;
                }
                uVar2 = 8;
            }
            else
            {
                if (*(byte *)(param_1 + 0x76a) < 0xfe)
                {
                    FUN_0065ba70((uint) * (byte *)(param_1 + 0x76a) * -10 + 10000);
                    FUN_0065b2c0((uint) * (byte *)(param_1 + 0x76a) * -10 + 10000);
                    *(char *)(param_1 + 0x76a) = *(char *)(param_1 + 0x76a) + '\x02';
                }
                else
                {
                    *(undefined1 *)(param_1 + 0x76a) = 0xff;
                    if (*(int *)(param_1 + 0x770) == 0)
                    {
                        FUN_0065b9b0();
                        FUN_0065ba70(10000);
                        FUN_0065b520();
                        FUN_0065b2c0(10000);
                    }
                    *(int *)(param_1 + 0x770) = *(int *)(param_1 + 0x770) + 1;
                    if ((DAT_006cae9c == 1) || (*(int *)(param_1 + 0x770) == 300))
                    {
                        if (DAT_006cfbc4 == '\x06')
                        {
                            FUN_0065b520();
                            FUN_0065b9b0();
                            if (DAT_006cfbc6 == '\x01')
                            {
                                return 0x15;
                            }
                            return 2;
                        }
                        FUN_0040f970();
                        *(undefined1 *)(param_1 + 0x76c) = 0;
                    }
                }
                uVar2 = 8;
            }
        }
        else
        {
            if (*(byte *)(param_1 + 0x769) < 0xf1)
            {
                *(char *)(param_1 + 0x769) = *(char *)(param_1 + 0x769) + '\x0f';
            }
            else
            {
                FUN_0065d670();
                FUN_00656200(*(undefined4 *)(param_1 + 0x48));
                puVar3 = (undefined4 *)FUN_006560c0(local_c, param_1 + 0x774);
                *(undefined4 *)(param_1 + 0x48) = *puVar3;
                FUN_00655af0(*(undefined4 *)(param_1 + 0x48), 0, 0, 800, 600);
                FUN_0065d6a0();
                *(undefined1 *)(param_1 + 0x76b) = 0;
            }
            uVar2 = 8;
        }
    }
    else
    {
        FUN_0065b870("data/bgm/title.ogg");
        DAT_006cf3b4 = 100;
        uVar2        = 1;
    }
    return uVar2;
}
