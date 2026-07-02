// ============================================
// Address:  0x00635d40
// Original: FUN_00635d40
// Status:   unreviewed
// ============================================

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __fastcall FUN_00635d40(int param_1)

{
    char cVar1;
    undefined4 *puVar2;
    undefined4 uVar3;
    uint uVar4;
    int iVar5;
    float10 fVar6;
    int local_6d8;
    int local_6d4;
    undefined1 local_6c4[4];
    undefined1 local_6c0[4];
    undefined1 local_6bc[4];
    undefined1 local_6b8[4];
    int local_6b4;
    int local_6b0;
    int local_6ac;
    undefined1 local_6a8[8];
    undefined1 local_6a0;
    undefined1 local_69c[8];
    undefined4 local_694;
    int local_690;
    int local_68c;
    CHAR local_688[264];
    int local_580;
    int local_57c;
    int local_578;
    int local_574;
    int local_570;
    int local_56c;
    undefined1 local_568[1031];
    char local_161;
    int local_160;
    int local_15c;
    CHAR local_158[268];
    undefined4 local_4c;
    undefined4 local_28;
    int local_24;
    char local_20[4];
    uint local_1c;
    int local_18;
    int local_14;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8   = 0xffffffff;
    puStack_c = &LAB_0069e76e;
    local_10  = ExceptionList;
    local_4c  = DAT_006b77f4;
    switch (*(undefined4 *)(param_1 + 0x4a3c))
    {
    case 1:
        if (*(int *)(param_1 + 0x43e4) == 0)
        {
            if (*(int *)(param_1 + 0x41e0) == 0)
            {
                if (DAT_006cfce9 == '\x01')
                {
                    ExceptionList = &local_10;
                    wsprintfA(
                        local_688, "data/bgm/%02d.ogg", (int)(char)(&DAT_006cfbdf)[DAT_006cfbc4]);
                }
                else
                {
                    ExceptionList = &local_10;
                    wsprintfA(local_688, "data/bgm/%02d.ogg", DAT_006cfaf4);
                }
                FUN_0065b870(local_688);
            }
            else if (*(int *)(param_1 + 0x41e0) == 3)
            {
                *(undefined4 *)(param_1 + 0x4a3c) = 2;
            }
            *(int *)(param_1 + 0x41e0) = *(int *)(param_1 + 0x41e0) + 1;
        }
        for (local_68c = 0; local_68c < 4; local_68c = local_68c + 1)
        {
            if (*(int *)(param_1 + 0x43e4 + local_68c * 4) == 0)
            {
                *(int *)(param_1 + 0x43f4 + local_68c * 4)        = *(int *)(param_1 + 0x41e0) + 2;
                *(undefined4 *)(param_1 + 0x43e4 + local_68c * 4) = 0x3c;
                *(undefined4 *)(param_1 + 0x4404 + local_68c * 4) = 0x40c00000;
            }
        }
        break;
    case 2:
        ExceptionList = &local_10;
        for (local_690 = 0; local_690 < 4; local_690 = local_690 + 1)
        {
            iVar5 = *(int *)(param_1 + 0x129c + local_690 * 4);
            fVar6 = (float10)FUN_0042d9d0(0);
            fVar6 = (float10)FUN_0042de80((float)fVar6);
            *(float *)(*(int *)(param_1 + 0x129c + local_690 * 4) + 0xaf40) =
                (float)(fVar6 + (float10) * (float *)(iVar5 + 0xaf40));
            iVar5 = *(int *)(param_1 + 0x129c + local_690 * 4);
            fVar6 = (float10)FUN_0042da30();
            *(float *)(*(int *)(param_1 + 0x129c + local_690 * 4) + 0xaf44) =
                (float)(fVar6 + (float10) * (float *)(iVar5 + 0xaf44));
            *(int *)(*(int *)(param_1 + 0x129c + local_690 * 4) + 0xaf58) =
                *(int *)(*(int *)(param_1 + 0x129c + local_690 * 4) + 0xaf58) + 1;
            if (*(char *)(*(int *)(param_1 + 0x129c + local_690 * 4) + 0x84) == '\0')
            {
                *(int *)(*(int *)(param_1 + 0x129c + local_690 * 4) + 0xaf5c) =
                    *(int *)(*(int *)(param_1 + 0x129c + local_690 * 4) + 0xaf5c) + 1;
            }
        }
        if (*(int *)(param_1 + 0x43d4) != 0)
        {
            if (*(int *)(param_1 + 0x43d8) == 0)
            {
                if (*(int *)(param_1 + 0x12b0) < *(int *)(param_1 + 0x12bc))
                {
                    *(undefined4 *)(param_1 + 0x442c) = 0;
                }
                else if (*(int *)(param_1 + 0x12bc) < *(int *)(param_1 + 0x12b0))
                {
                    *(undefined4 *)(param_1 + 0x442c) = 1;
                }
                else if (*(int *)(*(int *)(param_1 + 0x12a4) + 0x7a4) +
                             *(int *)(*(int *)(param_1 + 0x12a8) + 0x7a4) <
                         *(int *)(*(int *)(param_1 + 0x129c) + 0x7a4) +
                             *(int *)(*(int *)(param_1 + 0x12a0) + 0x7a4))
                {
                    *(undefined4 *)(param_1 + 0x442c) = 0;
                }
                else if (*(int *)(*(int *)(param_1 + 0x129c) + 0x7a4) +
                             *(int *)(*(int *)(param_1 + 0x12a0) + 0x7a4) <
                         *(int *)(*(int *)(param_1 + 0x12a4) + 0x7a4) +
                             *(int *)(*(int *)(param_1 + 0x12a8) + 0x7a4))
                {
                    *(undefined4 *)(param_1 + 0x442c) = 1;
                }
                else
                {
                    uVar4                       = FUN_0065d150();
                    *(uint *)(param_1 + 0x442c) = uVar4 % 2;
                }
                *(int *)(param_1 + 0x4424) = *(int *)(param_1 + 0x442c) << 1;
                *(int *)(param_1 + 0x4428) = *(int *)(param_1 + 0x442c) * 2 + 1;
                if (DAT_006cfdb0 == '\x01')
                {
                    FUN_0063b900();
                    local_6a0 = *(undefined1 *)(param_1 + 0x442c);
                    FUN_00415d30(0, local_6a8, 0, 8);
                }
                if (DAT_006cfdb0 != '\x02')
                {
                    *(undefined4 *)(param_1 + 0x4414) = 0xb4;
                    *(undefined4 *)(param_1 + 0x441c) = 0x41000000;
                    *(undefined4 *)(param_1 + 0x4a3c) = 3;
                }
                break;
            }
            if ((DAT_006cfdb0 == '\x01') && (*(int *)(param_1 + 0x43d8) % 0x78 == 0x3c))
            {
                FUN_0063b8a0();
                local_694 = *(undefined4 *)(param_1 + 0x43d8);
                FUN_00415d30(0, local_69c, 0, 2);
            }
            *(int *)(param_1 + 0x43d8) = *(int *)(param_1 + 0x43d8) + -1;
        }
        for (local_6ac = 0; local_6ac < 4; local_6ac = local_6ac + 1)
        {
            if (*(char *)(*(int *)(param_1 + 0x129c + local_6ac * 4) + 0xaeca) == '\0')
            {
                if (*(char *)(*(int *)(param_1 + 0x129c + local_6ac * 4) + 0xaec9) != '\0')
                {
                    FUN_0064af20(local_6ac, 8);
                    *(undefined4 *)(param_1 + 0x43f4 + local_6ac * 4) = 0;
                    *(undefined4 *)(param_1 + 0x43e4 + local_6ac * 4) = 0x5a;
                    *(undefined4 *)(param_1 + 0x4404 + local_6ac * 4) = 0x41000000;
                }
            }
            else
            {
                iVar5 = FUN_00421930();
                if (iVar5 < 1)
                {
                    *(int *)(param_1 + 0x4424)        = local_6ac;
                    *(undefined4 *)(param_1 + 0x4a3c) = 3;
                    FUN_0064aed0(0xb);
                    if (*(int *)(param_1 + 0x4414) == 0)
                    {
                        *(undefined4 *)(param_1 + 0x4414) = 0xb4;
                        *(undefined4 *)(param_1 + 0x441c) = 0x41000000;
                    }
                    if (local_6ac < 2)
                    {
                        *(undefined4 *)(param_1 + 0x442c) = 1;
                    }
                    else
                    {
                        *(undefined4 *)(param_1 + 0x442c) = 0;
                    }
                }
                else
                {
                    *(undefined4 *)(param_1 + 0x43e4 + local_6ac * 4) = 0x78;
                    *(undefined4 *)(param_1 + 0x4404 + local_6ac * 4) = 0x41000000;
                    *(undefined4 *)(param_1 + 0x43f4 + local_6ac * 4) = 1;
                }
            }
        }
        break;
    case 3:
        ExceptionList = &local_10;
        for (local_6b0 = 0; local_6b0 < 2; local_6b0 = local_6b0 + 1)
        {
            if (0 < *(int *)(param_1 + 0x4414 + local_6b0 * 4))
            {
                *(int *)(param_1 + 0x4414 + local_6b0 * 4) =
                    *(int *)(param_1 + 0x4414 + local_6b0 * 4) + -1;
            }
            if (1.0 < *(float *)(param_1 + 0x441c + local_6b0 * 4))
            {
                *(float *)(param_1 + 0x441c + local_6b0 * 4) =
                    *(float *)(param_1 + 0x441c + local_6b0 * 4) - 0.5;
            }
            if (*(float *)(param_1 + 0x441c + local_6b0 * 4) < 1.0)
            {
                *(undefined4 *)(param_1 + 0x441c + local_6b0 * 4) = 0x3f800000;
            }
        }
        if (*(int *)(param_1 + 0x4414) == 0x78)
        {
            *(undefined4 *)(param_1 + 0x4418) = 0x78;
            *(undefined4 *)(param_1 + 0x4420) = 0x41000000;
            FUN_0064aed0(0xc);
        }
        if (*(int *)(param_1 + 0x4414) == 0)
        {
            if (DAT_006cfce9 == '\x01')
            {
                if (*(int *)(param_1 + 0x442c) == 0)
                {
                    *(undefined4 *)(param_1 + 0x4414) = 1;
                    *(undefined4 *)(param_1 + 0x4418) = 1;
                    *(undefined1 *)(param_1 + 0x4a40) = 1;
                }
                else
                {
                    FUN_0065b870("data/bgm/lose.ogg");
                    FUN_0065ba70(10000);
                    *(undefined4 *)(param_1 + 0x4418) = 0;
                    *(undefined4 *)(param_1 + 0x41dc) = 0x420;
                    *(undefined4 *)(param_1 + 0x41e0) = 0;
                    *(undefined4 *)(param_1 + 0x4a3c) = 5;
                }
            }
            else
            {
                *(undefined4 *)(param_1 + 0x4418) = 0;
                *(undefined4 *)(param_1 + 0x41dc) = 0x420;
                *(undefined4 *)(param_1 + 0x41e0) = 0;
                *(undefined4 *)(param_1 + 0x4a3c) = 4;
                if ((DAT_006cfdb0 == '\0') || ((char)(&DAT_006cfde1)[DAT_006cfdb4] < '\0'))
                {
                    FUN_0065b870("data/bgm/win.ogg");
                }
                else if (((&DAT_006cfaf8)[*(int *)(param_1 + 0x442c) * -2 + 2] ==
                          (int)(char)(&DAT_006cfde1)[DAT_006cfdb4]) ||
                         ((&DAT_006cfaf8)[*(int *)(param_1 + 0x442c) * -2 + 3] ==
                          (int)(char)(&DAT_006cfde1)[DAT_006cfdb4]))
                {
                    FUN_0065b870("data/bgm/lose.ogg");
                }
                else
                {
                    FUN_0065b870("data/bgm/win.ogg");
                }
                FUN_0065ba70(10000);
            }
        }
        else if (*(int *)(param_1 + 0x4414) < 0x1e)
        {
            FUN_0065ba70(*(int *)(param_1 + 0x4414) * 100 + 7000);
        }
        break;
    case 4:
    case 5:
        switch (*(undefined4 *)(param_1 + 0x41e0))
        {
        case 0:
            if (*(int *)(param_1 + 0x41dc) < 1)
            {
                ExceptionList = &local_10;
                for (local_15c = 0; local_15c < 2; local_15c = local_15c + 1)
                {
                    if (((&DAT_006cfb28)[local_15c + *(int *)(param_1 + 0x442c) * 2] == 0) &&
                        (*(int *)(&DAT_006cfb38 +
                                  (local_15c + *(int *)(param_1 + 0x442c) * 2) * 4) == 2))
                    {
                        local_20[local_15c] = '\x10';
                    }
                    else if (((&DAT_006cfb28)[local_15c + *(int *)(param_1 + 0x442c) * 2] == 4) &&
                             (*(int *)(&DAT_006cfb38 +
                                       (local_15c + *(int *)(param_1 + 0x442c) * 2) * 4) == 2))
                    {
                        local_20[local_15c] = '\x11';
                    }
                    else
                    {
                        local_20[local_15c] = '\0';
                    }
                    FUN_00656200(*(undefined4 *)(param_1 + 0x4484 + local_15c * 4));
                    if (local_20[local_15c] == '\0')
                    {
                        wsprintfA(local_158,
                                  "data/win/%02da.bmp",
                                  (&DAT_006cfb28)[local_15c + *(int *)(param_1 + 0x442c) * 2]);
                    }
                    else
                    {
                        wsprintfA(local_158,
                                  "data/win/%02db.bmp",
                                  (&DAT_006cfb28)[local_15c + *(int *)(param_1 + 0x442c) * 2]);
                    }
                    puVar2 = (undefined4 *)FUN_006560c0(local_6b8, local_158);
                    *(undefined4 *)(param_1 + 0x4484 + local_15c * 4) = *puVar2;
                    FUN_00655af0(
                        *(undefined4 *)(param_1 + 0x4484 + local_15c * 4), 0, 0, 0x200, 0x200);
                }
                local_14 = (&DAT_006cfb28)[*(int *)(param_1 + 0x442c) * 2];
                local_24 = (&DAT_006cfb2c)[*(int *)(param_1 + 0x442c) * 2];
                if (local_20[0] != '\0')
                {
                    local_14 = (int)local_20[0];
                }
                iVar5 = local_14;
                if (local_20[1] != '\0')
                {
                    local_24 = (int)local_20[1];
                }
                if (local_24 < local_14)
                {
                    local_160 = local_14;
                    local_14  = local_24;
                    local_24  = iVar5;
                }
                if (*(int *)(param_1 + 0x43c4 + *(int *)(param_1 + 0x442c) * 4) <
                    *(int *)(param_1 + 0x12b0 + (1 - *(int *)(param_1 + 0x442c)) * 0xc))
                {
                    local_6d4 = *(int *)(param_1 + 0x43c4 + *(int *)(param_1 + 0x442c) * 4);
                }
                else
                {
                    local_6d4 = *(int *)(param_1 + 0x12b0 + (1 - *(int *)(param_1 + 0x442c)) * 0xc);
                }
                if (local_6d4 - *(int *)(param_1 + 0x12b0 + *(int *)(param_1 + 0x442c) * 0xc) <
                    0x1e)
                {
                    if ((*(int *)(*(int *)(param_1 + 0x129c + *(int *)(param_1 + 0x442c) * 8) +
                                  0x7a4) < 5000) &&
                        (*(int *)(*(int *)(param_1 + 0x12a0 + *(int *)(param_1 + 0x442c) * 8) +
                                  0x7a4) < 5000))
                    {
                        local_28 = 4;
                    }
                    else
                    {
                        local_28 = 3;
                    }
                }
                else
                {
                    if (*(int *)(param_1 + 0x43c4 + *(int *)(param_1 + 0x442c) * 4) <
                        *(int *)(param_1 + 0x12b0 + (1 - *(int *)(param_1 + 0x442c)) * 0xc))
                    {
                        local_6d8 = *(int *)(param_1 + 0x43c4 + *(int *)(param_1 + 0x442c) * 4);
                    }
                    else
                    {
                        local_6d8 =
                            *(int *)(param_1 + 0x12b0 + (1 - *(int *)(param_1 + 0x442c)) * 0xc);
                    }
                    if (local_6d8 - *(int *)(param_1 + 0x12b0 + *(int *)(param_1 + 0x442c) * 0xc) <
                        0x32)
                    {
                        local_28 = 2;
                    }
                    else
                    {
                        local_28 = 1;
                    }
                }
                wsprintfA(
                    local_158, "data/scenario/win/%02d-%02d-%d.txt", local_14, local_24, local_28);
                FUN_0040fa90();
                local_8 = 0;
                cVar1   = FUN_0065e500(local_158, 0);
                if (cVar1 == '\0')
                {
                    if (local_14 < 0x10)
                    {
                        if (local_24 == 0x10)
                        {
                            local_161 = '\x10';
                        }
                        else
                        {
                            local_161 = '\x11';
                        }
                    }
                    else if (local_14 == 0x11)
                    {
                        local_161 = '\x11';
                    }
                    else if (local_24 == 0x10)
                    {
                        local_161 = '\x10';
                    }
                    else
                    {
                        uVar4     = FUN_0065d150();
                        local_161 = (char)((ulonglong)uVar4 % 2) + '\x10';
                    }
                    wsprintfA(local_158, "data/scenario/win/%02d.txt", (int)local_161);
                    FUN_0065e500(local_158, 0);
                }
                iVar5    = FUN_0063b840();
                local_1c = iVar5 / 2;
                uVar4    = FUN_0065d150();
                FUN_0063b860(uVar4 % local_1c << 1);
                FUN_0040fb40(&local_18);
                FUN_0065b1d0(*(undefined4 *)(param_1 + 0x4494));
                wsprintfA(local_158, "data/voice/win/%s", local_18 + 4);
                puVar2 = (undefined4 *)FUN_0065b0d0(local_6bc, local_158);
                *(undefined4 *)(param_1 + 0x4494) = *puVar2;
                FUN_0065b330(*(undefined4 *)(param_1 + 0x4494), 0);
                FUN_0040fb40(&local_18);
                FUN_00656200(*(undefined4 *)(param_1 + 0x448c));
                puVar2 = (undefined4 *)FUN_00656190(
                    local_6c0, *(undefined4 *)(local_18 + 4), *(undefined4 *)(param_1 + 0xf78));
                *(undefined4 *)(param_1 + 0x448c) = *puVar2;
                FUN_00655af0(*(undefined4 *)(param_1 + 0x448c), 0, 0, 800, 200);
                *(int *)(*(int *)(param_1 + 0x129c + *(int *)(param_1 + 0x442c) * 8) + 0xaee8) =
                    *(int *)(param_1 + 0x43c4 + *(int *)(param_1 + 0x442c) * 4) -
                    *(int *)(param_1 + 0x12b0 + *(int *)(param_1 + 0x442c) * 0xc);
                *(int *)(*(int *)(param_1 + 0x12a0 + *(int *)(param_1 + 0x442c) * 8) + 0xaee8) =
                    *(int *)(param_1 + 0x43c4 + *(int *)(param_1 + 0x442c) * 4) -
                    *(int *)(param_1 + 0x12b0 + *(int *)(param_1 + 0x442c) * 0xc);
                if (DAT_006cfdb0 != '\x02')
                {
                    FUN_00656200(*(undefined4 *)(param_1 + 0x4490));
                    local_568[0] = 0;
                    for (local_56c = 0; local_56c < 4; local_56c = local_56c + 1)
                    {
                        local_570 = FUN_00430880();
                        if (((local_570 == 0x28) && ((int)(&DAT_006cfaf8)[local_56c] < 4)) &&
                            ((&DAT_006cfdd1)[(&DAT_006cfb18)[(&DAT_006cfaf8)[local_56c]]] != '\0'))
                        {
                            (&DAT_006cfdf1)[(&DAT_006cfb18)[(&DAT_006cfaf8)[local_56c]]] = 1;
                        }
                        *(int *)(param_1 + 0x7d8 + local_56c * 4) = local_570;
                        if (0 < local_56c)
                        {
                            FUN_0066b870(local_568, &DAT_006a4a64);
                        }
                        uVar3 = FUN_00430860(local_570);
                        FUN_0066b870(local_568, uVar3);
                    }
                    puVar2 = (undefined4 *)FUN_00656190(
                        local_6c4, local_568, *(undefined4 *)(param_1 + 0xf78));
                    *(undefined4 *)(param_1 + 0x4490) = *puVar2;
                    FUN_00655690(*(undefined4 *)(param_1 + 0x4490), 0, 0, 0x200, 0x25);
                    DAT_006cfe1f = *(undefined1 *)(param_1 + 0x442c);
                }
                if (*(int *)(param_1 + 0x4a3c) == 5)
                {
                    *(undefined4 *)(param_1 + 0x41e0) = 2;
                }
                else
                {
                    *(undefined4 *)(param_1 + 0x41e0) = 1;
                }
                *(undefined4 *)(param_1 + 0x41dc) = 0x200;
                local_8                           = 0xffffffff;
                ~<>();
            }
            else
            {
                *(int *)(param_1 + 0x41dc) = *(int *)(param_1 + 0x41dc) + -8;
            }
            break;
        case 1:
            if (*(int *)(param_1 + 0x41dc) < 1)
            {
                if (DAT_006cfdb0 != '\x02')
                {
                    ExceptionList = &local_10;
                    for (local_574 = 0; local_574 < 4; local_574 = local_574 + 1)
                    {
                        FUN_00657390();
                        for (local_578 = 0; local_578 < 7; local_578 = local_578 + 1)
                        {
                            if ((&DAT_006cae9c)[local_574 * 0x19 + local_578] == 1)
                            {
                                *(undefined4 *)(param_1 + 0x41dc) = 0;
                                *(undefined4 *)(param_1 + 0x41e0) = 5;
                            }
                        }
                    }
                }
            }
            else
            {
                *(int *)(param_1 + 0x41dc) = *(int *)(param_1 + 0x41dc) + -0x10;
            }
            break;
        case 2:
            if (*(int *)(param_1 + 0x41dc) < 1)
            {
                ExceptionList = &local_10;
                FUN_00657390();
                if (DAT_006cae9c == 1)
                {
                    *(undefined4 *)(param_1 + 0x41dc) = 0xff;
                    *(undefined4 *)(param_1 + 0x41e0) = 3;
                }
            }
            else
            {
                *(int *)(param_1 + 0x41dc) = *(int *)(param_1 + 0x41dc) + -0x10;
            }
            break;
        case 3:
            if (*(char *)(param_1 + 0x4a40) == '\0')
            {
                ExceptionList = &local_10;
                if (0 < *(int *)(param_1 + 0x41dc))
                {
                    ExceptionList              = &local_10;
                    *(int *)(param_1 + 0x41dc) = *(int *)(param_1 + 0x41dc) + -5;
                }
                FUN_00657390();
                iVar5 = FUN_00403aa0(DAT_006cae94);
                if (iVar5 == 1)
                {
                    FUN_0064aed0(2);
                    *(int *)(param_1 + 0x1408) = 1 - *(int *)(param_1 + 0x1408);
                }
                else if (DAT_006cae9c == 1)
                {
                    FUN_0064aed0(0);
                    if (*(int *)(param_1 + 0x1408) == 0)
                    {
                        *(undefined4 *)(param_1 + 0x41e0) = 4;
                        *(undefined4 *)(param_1 + 0x41dc) = 0xff;
                    }
                    else
                    {
                        *(undefined1 *)(param_1 + 0x4a40) = 1;
                    }
                }
            }
            break;
        case 4:
            if (*(int *)(param_1 + 0x41dc) < 1)
            {
                ExceptionList                     = &local_10;
                *(undefined4 *)(param_1 + 0x41dc) = 0;
                FUN_0065d670();
                if (0x46 < *(int *)(param_1 + 0x43c8))
                {
                    *(int *)(param_1 + 0x43c8) = *(int *)(param_1 + 0x43c8) + -5;
                }
                FUN_00634760();
                FUN_00634920();
                FUN_0041dcb0();
                FUN_0041dcb0();
                FUN_0041dcb0();
                FUN_0041dcb0();
                FUN_006348b0();
                FUN_00634980();
                FUN_0065d6a0();
                *(undefined4 *)(param_1 + 0x4a3c) = 1;
            }
            else
            {
                *(int *)(param_1 + 0x41dc) = *(int *)(param_1 + 0x41dc) + -5;
            }
            break;
        case 5:
            ExceptionList = &local_10;
            if (*(int *)(param_1 + 0x41dc) == 0)
            {
                ExceptionList = &local_10;
                if (DAT_006cfdb0 == '\x01')
                {
                    ExceptionList = &local_10;
                    FUN_00415d30(0, param_1 + 2000, 0, 0x88);
                }
                FUN_0064aed0(0x16);
            }
            *(int *)(param_1 + 0x41dc) = *(int *)(param_1 + 0x41dc) + 1;
            if (((*(int *)(param_1 + 0x41dc) % 0x1e == 0) && (*(int *)(param_1 + 0x41dc) < 0x97)) &&
                (0x3b < *(int *)(param_1 + 0x41dc)))
            {
                FUN_0064aed0(0x15);
            }
            for (local_57c = 0; local_57c < 4; local_57c = local_57c + 1)
            {
                FUN_00657390();
                if (-1 < *(int *)(&DAT_006cfb08 + local_57c * 4))
                {
                    for (local_580 = 0; local_580 < 7; local_580 = local_580 + 1)
                    {
                        if ((&DAT_006cae9c)[local_57c * 0x19 + local_580] == 1)
                        {
                            if (*(int *)(param_1 + 0x41dc) < 0x96)
                            {
                                FUN_0064aed0(0x15);
                                *(undefined4 *)(param_1 + 0x41dc) = 0x96;
                            }
                            else
                            {
                                *(undefined1 *)(param_1 + 0x4a40) = 1;
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
    for (local_6b4 = 0; local_6b4 < 4; local_6b4 = local_6b4 + 1)
    {
        if (0 < *(int *)(param_1 + 0x43e4 + local_6b4 * 4))
        {
            *(int *)(param_1 + 0x43e4 + local_6b4 * 4) =
                *(int *)(param_1 + 0x43e4 + local_6b4 * 4) + -1;
        }
        if (1.0 < *(float *)(param_1 + 0x4404 + local_6b4 * 4))
        {
            *(float *)(param_1 + 0x4404 + local_6b4 * 4) =
                *(float *)(param_1 + 0x4404 + local_6b4 * 4) - 0.5;
        }
        if (*(float *)(param_1 + 0x4404 + local_6b4 * 4) < 1.0)
        {
            *(undefined4 *)(param_1 + 0x4404 + local_6b4 * 4) = 0x3f800000;
        }
    }
    ExceptionList = local_10;
    return;
}
