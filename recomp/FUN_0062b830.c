// ============================================
// Address:  0x0062b830
// Original: FUN_0062b830
// Status:   unreviewed
// ============================================

void __fastcall FUN_0062b830(int param_1)

{
    int iVar1;
    char cVar2;
    short sVar3;
    uint uVar4;
    float10 fVar5;
    float10 fVar6;
    undefined4 uVar7;
    undefined4 uVar8;
    undefined4 uVar9;
    float fVar10;
    float fVar11;
    undefined4 uVar12;

    uVar4 = FUN_0042c7b0();
    if ((uVar4 & 0x100) != 0)
    {
        switch (*(undefined4 *)(param_1 + 0x150))
        {
        case 0:
        case 10:
        case 0x28:
        case 0x8c:
            FUN_005f72c0(0x43340000, -*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
            FUN_0042c800(0);
            FUN_0042c840(1);
        }
    }
    iVar1 = *(int *)(param_1 + 0x150);
    if (iVar1 < 0xe7)
    {
        if (iVar1 == 0xe6)
        {
            *(undefined4 *)(param_1 + 0x14) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x14);
            *(undefined4 *)(param_1 + 0x18) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18);
            *(undefined4 *)(param_1 + 0x1c) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x1c);
            *(undefined4 *)(param_1 + 0x6c) = 0;
            *(float *)(param_1 + 0x2c)      = *(float *)(param_1 + 0x2c) + 1.0;
            if (*(int *)(param_1 + 0x154) == 0)
            {
                *(undefined4 *)(param_1 + 0x78) = 0;
                *(undefined4 *)(param_1 + 0x70) = 0;
                *(undefined4 *)(param_1 + 0xf8) = 0;
            }
            if (2.0 <= *(float *)(param_1 + 0x78))
            {
                *(undefined4 *)(param_1 + 0x78) = 0x40400000;
                *(undefined4 *)(param_1 + 0x70) = 0x40400000;
            }
            else
            {
                fVar5 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 3));
                *(float *)(param_1 + 0x78) =
                    (float)(fVar5 * (float10)0.15 + (float10) * (float *)(param_1 + 0x78));
                fVar5 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 3));
                *(float *)(param_1 + 0x70) =
                    (float)(fVar5 * (float10)0.15 + (float10) * (float *)(param_1 + 0x70));
            }
            if (*(int *)(param_1 + 0x154) % 5 == 0)
            {
                FUN_0042c840(1);
                FUN_0042c800(0);
            }
            if (*(int *)(param_1 + 0x154) % 10 == 0)
            {
                uVar4  = FUN_0065d150();
                fVar11 = (float)(uVar4 % 300) - 150.0;
                uVar8  = 0;
                uVar4  = FUN_0065d150(0, fVar11);
                FUN_005f6fd0(0x18, (float)(uVar4 % 300) - 150.0, uVar8, fVar11);
            }
            if ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0x172) &&
                (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadf4) == 0))
            {
                *(undefined4 *)(param_1 + 0xf8) = 1;
            }
            if ((*(int *)(param_1 + 0x154) < 0x12d) && (*(int *)(param_1 + 0xf8) < 1))
            {
                fVar5 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 6));
                *(float *)(param_1 + 0x74) = (float)(fVar5 * (float10)0.25 + (float10)0.75);
            }
            else
            {
                FUN_0042c840(0);
                *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
                if (*(float *)(param_1 + 0x74) < 0.0 != (*(float *)(param_1 + 0x74) == 0.0))
                {
                    FUN_005f5e00();
                    return;
                }
            }
        }
        else
        {
            switch (iVar1)
            {
            case 0:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                         (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                        (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
                    {
                        fVar5 = (float10)FUN_0042dac0(2);
                        if ((float10) * (float *)(param_1 + 0x6c) - fVar5 < (float10)10.0)
                        {
                            fVar5                      = (float10)FUN_0042dac0(2);
                            *(float *)(param_1 + 0x6c) = (float)fVar5;
                        }
                        fVar5 = (float10)FUN_0042dac0(2);
                        if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar5)
                        {
                            fVar5                      = (float10)FUN_0042dac0(2);
                            *(float *)(param_1 + 0x6c) = (float)fVar5;
                        }
                    }
                    *(undefined4 *)(param_1 + 0x54) = 0x42820000;
                    *(undefined4 *)(param_1 + 0xe8) = 0;
                    *(undefined4 *)(param_1 + 0xec) = 0x28;
                    *(undefined4 *)(param_1 + 0xf0) = 0;
                    *(undefined4 *)(param_1 + 0xf4) = 0;
                    *(undefined4 *)(param_1 + 0xf8) = 0;
                    FUN_0042c840(1);
                }
                if (*(int *)(param_1 + 0x154) == 1)
                {
                    FUN_005f6880(0);
                    *(undefined4 *)(param_1 + 0x6c) = 0;
                }
                *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.1;
                FUN_0042db10(0, 0x3dcccccd);
                sVar3 = FUN_0042c7b0();
                if (sVar3 != 0)
                {
                    if (*(short *)(param_1 + 0x88 + *(int *)(*(int *)(param_1 + 0x38) + 8) * 2) ==
                        0)
                    {
                        FUN_005f71f0();
                    }
                    FUN_0042c840(0);
                    FUN_005f6db0(0x11, 0, 0, 0);
                    FUN_005f5e00();
                    return;
                }
                cVar2 = FUN_005f6a90();
                if (cVar2 == '\x01')
                {
                    FUN_005f6db0(0x10, 0, 0, 0);
                    FUN_005f5e00();
                    return;
                }
                if (0xb4 < *(int *)(param_1 + 0x154))
                {
                    FUN_005f5e00();
                    return;
                }
                break;
            case 10:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                         (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                        (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
                    {
                        fVar5 = (float10)FUN_0042dac0(2);
                        if ((float10) * (float *)(param_1 + 0x6c) - fVar5 < (float10)10.0)
                        {
                            fVar5                      = (float10)FUN_0042dac0(2);
                            *(float *)(param_1 + 0x6c) = (float)fVar5;
                        }
                        fVar5 = (float10)FUN_0042dac0(2);
                        if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar5)
                        {
                            fVar5                      = (float10)FUN_0042dac0(2);
                            *(float *)(param_1 + 0x6c) = (float)fVar5;
                        }
                    }
                    *(undefined4 *)(param_1 + 0x54) = 0x42960000;
                    *(undefined4 *)(param_1 + 0xe8) = 0;
                    *(undefined4 *)(param_1 + 0xec) = 0x28;
                    *(undefined4 *)(param_1 + 0xf0) = 0;
                    *(undefined4 *)(param_1 + 0xf4) = 0;
                    *(undefined4 *)(param_1 + 0xf8) = 0;
                    FUN_0042c840(1);
                }
                if (*(int *)(param_1 + 0x154) == 1)
                {
                    FUN_005f6880(0);
                    *(undefined4 *)(param_1 + 0x6c) = 0;
                }
                if (*(int *)(param_1 + 0xf8) == 0)
                {
                    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.1;
                    FUN_0042db10(0, 0x3e4ccccd);
                    sVar3 = FUN_0042c7b0();
                    if (sVar3 != 0)
                    {
                        if (*(short *)(param_1 + 0x88 +
                                       *(int *)(*(int *)(param_1 + 0x38) + 8) * 2) == 0)
                        {
                            FUN_005f71f0();
                        }
                        FUN_005f6db0(0x13, 0, 0, 0);
                        FUN_005f5e00();
                        return;
                    }
                    cVar2 = FUN_005f6a90();
                    if (cVar2 == '\x01')
                    {
                        FUN_005f6db0(0x12, 0, 0, 0);
                        FUN_005f5e00();
                        return;
                    }
                }
                if (0xb4 < *(int *)(param_1 + 0x154))
                {
                    FUN_005f5e00();
                    return;
                }
                break;
            case 0x14:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    FUN_0042c840(1);
                }
                *(undefined4 *)(param_1 + 0x54) = 0;
                if (0xe < *(int *)(param_1 + 0x154))
                {
                    FUN_005f5e00();
                    return;
                }
                break;
            case 0x1e:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    *(undefined4 *)(param_1 + 0x54) = 0x42f00000;
                    FUN_0042c840(1);
                    if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                         (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                        (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
                    {
                        fVar5 = (float10)FUN_0042dac0(2);
                        if ((float10) * (float *)(param_1 + 0x6c) - fVar5 < (float10)10.0)
                        {
                            fVar5                      = (float10)FUN_0042dac0(2);
                            *(float *)(param_1 + 0x6c) = (float)fVar5;
                        }
                        fVar5 = (float10)FUN_0042dac0(2);
                        if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar5)
                        {
                            fVar5                      = (float10)FUN_0042dac0(2);
                            *(float *)(param_1 + 0x6c) = (float)fVar5;
                        }
                    }
                }
                sVar3 = FUN_0042c7b0();
                if ((sVar3 != 0) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01'))
                {
                    FUN_005f6db0(2, 0, 0, 0);
                    FUN_005f5e00();
                    return;
                }
                if (0xf0 < *(int *)(param_1 + 0x154))
                {
                    FUN_005f5e00();
                    return;
                }
                break;
            case 0x28:
            case 0x8c:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                         (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                        (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
                    {
                        fVar5 = (float10)FUN_0042dac0(2);
                        if ((float10) * (float *)(param_1 + 0x6c) - fVar5 < (float10)10.0)
                        {
                            fVar5                      = (float10)FUN_0042dac0(2);
                            *(float *)(param_1 + 0x6c) = (float)fVar5;
                        }
                        fVar5 = (float10)FUN_0042dac0(2);
                        if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar5)
                        {
                            fVar5                      = (float10)FUN_0042dac0(2);
                            *(float *)(param_1 + 0x6c) = (float)fVar5;
                        }
                    }
                    *(undefined4 *)(param_1 + 0x54) = 0x42700000;
                    *(undefined4 *)(param_1 + 0xe8) = 0;
                    *(undefined4 *)(param_1 + 0xec) = 0x28;
                    *(undefined4 *)(param_1 + 0xf0) = 0;
                    *(undefined4 *)(param_1 + 0xf4) = 0;
                    *(undefined4 *)(param_1 + 0xf8) = 0;
                    FUN_0042c840(1);
                }
                if (*(int *)(param_1 + 0xf8) == 0)
                {
                    sVar3 = FUN_0042c7b0();
                    if (sVar3 != 0)
                    {
                        if (*(short *)(param_1 + 0x88 +
                                       *(int *)(*(int *)(param_1 + 0x38) + 8) * 2) == 0)
                        {
                            FUN_005f71f0();
                        }
                        FUN_005f6db0(0x15, 0, 0, 0);
                        FUN_005f5e00();
                        return;
                    }
                    cVar2 = FUN_005f6a90();
                    if (cVar2 == '\x01')
                    {
                        FUN_005f6db0(0x14, 0, 0, 0);
                        FUN_005f5e00();
                        return;
                    }
                }
                if (0x96 < *(int *)(param_1 + 0x154))
                {
                    FUN_005f5e00();
                    return;
                }
                break;
            case 0x32:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    *(undefined4 *)(param_1 + 0x54) = 0x42200000;
                    FUN_0042c840(1);
                    *(undefined4 *)(param_1 + 0xe8) = 0;
                    *(undefined4 *)(param_1 + 0xec) = 0;
                }
                *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 3;
                if (0x3c < *(int *)(param_1 + 0xec))
                {
                    *(undefined4 *)(param_1 + 0xec) = 0x3c;
                }
                uVar4 = *(uint *)(param_1 + 0x154) & 0x80000001;
                if ((int)uVar4 < 0)
                {
                    uVar4 = (uVar4 - 1 | 0xfffffffe) + 1;
                }
                if (uVar4 == 0)
                {
                    FUN_005f6fd0(7, 0, 0, 0);
                }
                if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
                {
                    *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
                }
                if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154)))
                {
                    FUN_0042db10(0, (float)*(int *)(param_1 + 0xec) * 0.0075);
                    fVar5 = (float10)FUN_0042dac0(2);
                    if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar5)
                    {
                        *(float *)(param_1 + 0x6c) =
                            *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.0075;
                    }
                    fVar5 = (float10)FUN_0042dac0(2);
                    if ((float10) * (float *)(param_1 + 0x6c) - fVar5 < (float10)-3.0)
                    {
                        *(float *)(param_1 + 0x6c) =
                            (float)*(int *)(param_1 + 0xec) * 0.0075 + *(float *)(param_1 + 0x6c);
                    }
                }
                if (((0x1e0 < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
                    (cVar2 = FUN_005f6a90(), cVar2 != '\0'))
                {
                    FUN_005f6db0(6, 0, 0, 0);
                    FUN_0042c8b0(0x4a);
                    FUN_005f5e00();
                    return;
                }
                break;
            case 0x3c:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    *(undefined4 *)(param_1 + 0x54) = 0;
                    *(undefined4 *)(param_1 + 0x40) = 0;
                    *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
                    *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
                    *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
                    FUN_0042c840(1);
                }
                if (0x33 < *(int *)(param_1 + 0x154))
                {
                    FUN_005f5e00();
                    return;
                }
                break;
            case 0x46:
                if (0x1d < *(int *)(param_1 + 0x154))
                {
                    FUN_005f5e00();
                    return;
                }
                break;
            case 0x50:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                         (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                        (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
                    {
                        fVar5 = (float10)FUN_0042dac0(2);
                        if ((float10) * (float *)(param_1 + 0x6c) - fVar5 < (float10)10.0)
                        {
                            fVar5                      = (float10)FUN_0042dac0(2);
                            *(float *)(param_1 + 0x6c) = (float)fVar5;
                        }
                        fVar5 = (float10)FUN_0042dac0(2);
                        if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar5)
                        {
                            fVar5                      = (float10)FUN_0042dac0(2);
                            *(float *)(param_1 + 0x6c) = (float)fVar5;
                        }
                    }
                    *(undefined4 *)(param_1 + 0x54) = 0x42700000;
                    *(undefined4 *)(param_1 + 0xe8) = 0;
                    *(undefined4 *)(param_1 + 0xec) = 0x28;
                    *(undefined4 *)(param_1 + 0xf0) = 0;
                    *(undefined4 *)(param_1 + 0xf4) = 0;
                    *(undefined4 *)(param_1 + 0xf8) = 0;
                    FUN_0042c840(1);
                    FUN_005f6880(0);
                }
                *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.4;
                cVar2                      = FUN_005f6a90();
                if (cVar2 == '\x01')
                {
                    FUN_005f6db0(0x16, 0, 0, 0);
                    FUN_005f5e00();
                    return;
                }
                if (0x96 < *(int *)(param_1 + 0x154))
                {
                    FUN_005f5e00();
                    return;
                }
                break;
            case 0x5a:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
                    *(undefined4 *)(param_1 + 0x74) = 0x40400000;
                    *(undefined4 *)(param_1 + 0x78) = 0x40400000;
                    *(undefined4 *)(param_1 + 0x54) = 0x3c23d70a;
                    *(undefined4 *)(param_1 + 0xe8) = 0;
                    *(undefined4 *)(param_1 + 0xec) = 0;
                    FUN_0042c840(1);
                }
                *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
                *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
                if (*(int *)(param_1 + 0x154) == 0x29)
                {
                    FUN_005f5e00();
                    return;
                }
                break;
            case 0x6e:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    *(undefined4 *)(param_1 + 0x54) = 0x437a0000;
                    FUN_0042c840(1);
                    *(undefined4 *)(param_1 + 0xe8) = 0;
                    *(undefined4 *)(param_1 + 0xec) = 0;
                    *(undefined4 *)(param_1 + 0xf0) = 0;
                    *(undefined4 *)(param_1 + 0xf4) = 0;
                }
                FUN_0042db10(0, 0x3dcccccd);
                fVar5 = (float10)FUN_0042dac0(2);
                if ((float10)1.0 < (float10) * (float *)(param_1 + 0x6c) - fVar5)
                {
                    *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.1;
                }
                fVar5 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar5 < (float10)-1.0)
                {
                    *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.1;
                }
                sVar3 = FUN_0042c7b0();
                if ((sVar3 != 0) || (cVar2 = FUN_005f6a90(), cVar2 != '\0'))
                {
                    FUN_005f6fd0(0xc, 0, 0, 0);
                    FUN_005f5e00();
                    return;
                }
                if (*(int *)(param_1 + 0x154) == 0x78)
                {
                    FUN_005f5e00();
                    return;
                }
                break;
            case 0x78:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    *(undefined4 *)(param_1 + 0x70) = 0x3d4ccccd;
                    *(undefined4 *)(param_1 + 0x74) = 0x3d4ccccd;
                    *(undefined4 *)(param_1 + 0x78) = 0x3d4ccccd;
                }
                *(undefined4 *)(param_1 + 0x54) = 0;
                fVar5 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
                *(float *)(param_1 + 0x70) =
                    (float)(fVar5 * (float10)0.5 + (float10) * (float *)(param_1 + 0x70));
                fVar5 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
                *(float *)(param_1 + 0x74) =
                    (float)(fVar5 * (float10)0.5 + (float10) * (float *)(param_1 + 0x74));
                fVar5 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
                *(float *)(param_1 + 0x78) =
                    (float)(fVar5 * (float10)0.5 + (float10) * (float *)(param_1 + 0x78));
                if (0x1c < *(int *)(param_1 + 0x154))
                {
                    FUN_005f5e00();
                    return;
                }
                break;
            case 0x82:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    *(undefined4 *)(param_1 + 0x54) = 0x42200000;
                    FUN_0042c840(1);
                    *(undefined4 *)(param_1 + 0xe8) = 0;
                    *(undefined4 *)(param_1 + 0xec) = 0;
                }
                *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
                if (100 < *(int *)(param_1 + 0xec))
                {
                    *(undefined4 *)(param_1 + 0xec) = 100;
                }
                uVar4 = *(uint *)(param_1 + 0x154) & 0x80000001;
                if ((int)uVar4 < 0)
                {
                    uVar4 = (uVar4 - 1 | 0xfffffffe) + 1;
                }
                if (uVar4 == 0)
                {
                    FUN_005f6fd0(7, 0, 0, 0);
                }
                if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
                {
                    *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
                }
                if (((0x1e0 < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
                    (cVar2 = FUN_005f6a90(), cVar2 != '\0'))
                {
                    FUN_005f6db0(6, 0, 0, 0);
                    FUN_0042c8b0(0x4a);
                    FUN_005f5e00();
                    return;
                }
                break;
            case 0x96:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    *(undefined4 *)(param_1 + 0x54) = 0x437a0000;
                    FUN_0042c840(1);
                    *(undefined4 *)(param_1 + 0xe8) = 0;
                    *(undefined4 *)(param_1 + 0xec) = 0;
                    *(undefined4 *)(param_1 + 0xf0) = 0;
                    *(undefined4 *)(param_1 + 0xf4) = 0;
                }
                sVar3 = FUN_0042c7b0();
                if ((sVar3 != 0) || (cVar2 = FUN_005f6a90(), cVar2 != '\0'))
                {
                    FUN_005f6fd0(0xc, 0, 0, 0);
                    FUN_005f5e00();
                    return;
                }
                if (*(int *)(param_1 + 0x154) == 0x78)
                {
                    FUN_005f5e00();
                    return;
                }
                break;
            case 0xa0:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    *(undefined4 *)(param_1 + 0xf4) = 0;
                    *(undefined4 *)(param_1 + 0xf8) = 0;
                    *(undefined4 *)(param_1 + 0x54) = 0;
                }
                if (*(int *)(param_1 + 0xf4) % 0x3c == 0)
                {
                    FUN_0042c8b0(0xc3);
                }
                uVar4 = *(uint *)(param_1 + 0xf4) & 0x80000001;
                if ((int)uVar4 < 0)
                {
                    uVar4 = (uVar4 - 1 | 0xfffffffe) + 1;
                }
                if (((uVar4 == 0) && (*(int *)(param_1 + 0xf4) < 0x38)) &&
                    (-1 < *(int *)(param_1 + 0xf4)))
                {
                    fVar5 = (float10)FUN_0040da40(
                        *(float *)(param_1 + 0x14) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                        2);
                    fVar6 = (float10)FUN_0040da40(
                        *(float *)(param_1 + 0x1c) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68),
                        2);
                    fVar5 = (float10)FUN_0042de80((float)(fVar6 + (float10)(float)fVar5));
                    *(float *)(param_1 + 0x100) = (float)fVar5;
                    fVar5                       = (float10)FUN_00423580(
                        *(float *)(param_1 + 0x18) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64),
                        *(undefined4 *)(param_1 + 0x100));
                    *(float *)(param_1 + 0x104) =
                        (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
                    fVar5 = (float10)FUN_00423580(
                        *(float *)(param_1 + 0x14) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                        *(float *)(param_1 + 0x1c) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68));
                    *(float *)(param_1 + 0x108) =
                        (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
                    uVar4  = FUN_0065d150();
                    fVar10 = ((float)(uVar4 % 0x10) + *(float *)(param_1 + 0x104)) - 8.0;
                    fVar11 = *(float *)(param_1 + 0x108);
                    uVar4  = FUN_0065d150(fVar10);
                    FUN_00435450(
                        3,
                        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64),
                        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68),
                        ((float)(uVar4 % 0x10) + -fVar11 + 90.0) - 8.0,
                        fVar10);
                }
                if (*(int *)(param_1 + 0xf4) == 0x3c)
                {
                    *(undefined4 *)(param_1 + 0xf8) = 4;
                }
                *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + 1;
                if (*(int *)(param_1 + 0xf8) == 4)
                {
                    FUN_005f5e00();
                    return;
                }
                break;
            case 0xaa:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    *(undefined4 *)(param_1 + 0xf4) = 0;
                    *(undefined4 *)(param_1 + 0xf8) = 0;
                    *(undefined4 *)(param_1 + 0x54) = 0;
                }
                *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + 5.0;
                if (*(float *)(param_1 + 0x70) <= 0.5)
                {
                    *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
                    *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
                    *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
                }
                else
                {
                    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.5;
                    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.5;
                    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.5;
                }
                *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(*(int *)(param_1 + 0x38) + 0x14);
                *(float *)(param_1 + 0x18) = *(float *)(*(int *)(param_1 + 0x38) + 0x18) + 85.0;
                *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(*(int *)(param_1 + 0x38) + 0x1c);
                if (*(int *)(param_1 + 0xf4) % 0x3c == 0)
                {
                    FUN_0042c8b0(0xc3);
                }
                if (*(int *)(param_1 + 0xf4) == 0xb4)
                {
                    fVar5 = (float10)FUN_0040da40(
                        *(float *)(param_1 + 0x14) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                        2);
                    fVar6 = (float10)FUN_0040da40(
                        *(float *)(param_1 + 0x1c) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68),
                        2);
                    fVar5 = (float10)FUN_0042de80((float)(fVar6 + (float10)(float)fVar5));
                    *(float *)(param_1 + 0x100) = (float)fVar5;
                    fVar5                       = (float10)FUN_00423580(
                        *(float *)(param_1 + 0x18) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64),
                        *(undefined4 *)(param_1 + 0x100));
                    *(float *)(param_1 + 0x104) =
                        (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
                    fVar5 = (float10)FUN_00423580(
                        *(float *)(param_1 + 0x14) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                        *(float *)(param_1 + 0x1c) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68));
                    *(float *)(param_1 + 0x108) =
                        (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
                    FUN_00435450(
                        0xb,
                        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64),
                        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68),
                        -*(float *)(param_1 + 0x108) + 90.0,
                        *(undefined4 *)(param_1 + 0x104));
                }
                if (*(int *)(param_1 + 0xf4) == 0xb4)
                {
                    *(undefined4 *)(param_1 + 0xf8) = 4;
                }
                *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + 1;
                if (*(int *)(param_1 + 0xf8) == 4)
                {
                    FUN_005f5e00();
                    return;
                }
                break;
            case 0xb4:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    *(undefined4 *)(param_1 + 0xf4) = 0;
                    *(undefined4 *)(param_1 + 0xf8) = 0;
                    *(undefined4 *)(param_1 + 0x54) = 0;
                }
                if (*(int *)(param_1 + 0xf4) % 0x1e == 0)
                {
                    FUN_0042c8b0(0xc3);
                }
                uVar4 = *(uint *)(param_1 + 0xf4) & 0x80000001;
                if ((int)uVar4 < 0)
                {
                    uVar4 = (uVar4 - 1 | 0xfffffffe) + 1;
                }
                if (((uVar4 == 0) && (*(int *)(param_1 + 0xf4) < 0x3d)) &&
                    (-1 < *(int *)(param_1 + 0xf4)))
                {
                    fVar5 = (float10)FUN_0040da40(
                        *(float *)(param_1 + 0x14) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                        2);
                    fVar6 = (float10)FUN_0040da40(
                        *(float *)(param_1 + 0x1c) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68),
                        2);
                    fVar5 = (float10)FUN_0042de80((float)(fVar6 + (float10)(float)fVar5));
                    *(float *)(param_1 + 0x100) = (float)fVar5;
                    fVar5                       = (float10)FUN_00423580(
                        *(float *)(param_1 + 0x18) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64),
                        *(undefined4 *)(param_1 + 0x100));
                    *(float *)(param_1 + 0x104) =
                        (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
                    fVar5 = (float10)FUN_00423580(
                        *(float *)(param_1 + 0x14) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                        *(float *)(param_1 + 0x1c) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68));
                    *(float *)(param_1 + 0x108) =
                        (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
                    uVar4  = FUN_0065d150();
                    fVar10 = ((float)(uVar4 % 4) + *(float *)(param_1 + 0x104)) - 2.0;
                    fVar11 = *(float *)(param_1 + 0x108);
                    iVar1  = *(int *)(param_1 + 0xf4);
                    uVar4  = FUN_0065d150(fVar10);
                    FUN_00435450(
                        3,
                        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64),
                        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68),
                        ((float)(uVar4 % 4) +
                         (((float)(iVar1 + -0x3c) * 1.0 + -fVar11 + 90.0) - 30.0)) -
                            2.0,
                        fVar10);
                }
                if (*(int *)(param_1 + 0xf4) == 0x3c)
                {
                    *(undefined4 *)(param_1 + 0xf8) = 4;
                }
                *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + 1;
                if (*(int *)(param_1 + 0xf8) == 4)
                {
                    FUN_005f5e00();
                    return;
                }
                break;
            case 0xbe:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    *(undefined4 *)(param_1 + 0xf4) = 0;
                    *(undefined4 *)(param_1 + 0xf8) = 0;
                    *(undefined4 *)(param_1 + 0x54) = 0;
                }
                *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + 5.0;
                if (*(float *)(param_1 + 0x70) <= 0.5)
                {
                    *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
                    *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
                    *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
                }
                else
                {
                    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.5;
                    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.5;
                    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.5;
                }
                *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(*(int *)(param_1 + 0x38) + 0x14);
                *(float *)(param_1 + 0x18) = *(float *)(*(int *)(param_1 + 0x38) + 0x18) + 85.0;
                *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(*(int *)(param_1 + 0x38) + 0x1c);
                if (*(int *)(param_1 + 0xf4) % 0x1e == 0)
                {
                    FUN_0042c8b0(0xc3);
                }
                if (*(int *)(param_1 + 0xf4) == 0xb4)
                {
                    fVar5 = (float10)FUN_0040da40(
                        *(float *)(param_1 + 0x14) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                        2);
                    fVar6 = (float10)FUN_0040da40(
                        *(float *)(param_1 + 0x1c) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68),
                        2);
                    fVar5 = (float10)FUN_0042de80((float)(fVar6 + (float10)(float)fVar5));
                    *(float *)(param_1 + 0x100) = (float)fVar5;
                    fVar5                       = (float10)FUN_00423580(
                        *(float *)(param_1 + 0x18) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64),
                        *(undefined4 *)(param_1 + 0x100));
                    *(float *)(param_1 + 0x104) =
                        (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
                    fVar5 = (float10)FUN_00423580(
                        *(float *)(param_1 + 0x14) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                        *(float *)(param_1 + 0x1c) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68));
                    *(float *)(param_1 + 0x108) =
                        (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
                    FUN_00435450(
                        0xf,
                        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64),
                        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68),
                        -*(float *)(param_1 + 0x108) + 90.0,
                        *(undefined4 *)(param_1 + 0x104));
                }
                if (*(int *)(param_1 + 0xf4) == 0xb4)
                {
                    *(undefined4 *)(param_1 + 0xf8) = 4;
                }
                *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + 1;
                if (*(int *)(param_1 + 0xf8) == 4)
                {
                    FUN_005f5e00();
                    return;
                }
                break;
            case 200:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    *(undefined4 *)(param_1 + 0xf4) = 0;
                    *(undefined4 *)(param_1 + 0xf8) = 0;
                    *(undefined4 *)(param_1 + 0x54) = 0;
                    *(undefined4 *)(param_1 + 0x6c) = 0;
                }
                if (*(int *)(param_1 + 0xf4) % 0x3c == 0)
                {
                    FUN_0042c8b0(0xc3);
                }
                if (*(int *)(param_1 + 0xf4) == 0x3c)
                {
                    fVar5 = (float10)FUN_0040da40(
                        *(float *)(param_1 + 0x14) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                        2);
                    fVar6 = (float10)FUN_0040da40(
                        *(float *)(param_1 + 0x1c) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68),
                        2);
                    fVar5 = (float10)FUN_0042de80((float)(fVar6 + (float10)(float)fVar5));
                    *(float *)(param_1 + 0x100) = (float)fVar5;
                    fVar5                       = (float10)FUN_00423580(
                        *(float *)(param_1 + 0x18) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64),
                        *(undefined4 *)(param_1 + 0x100));
                    *(float *)(param_1 + 0x104) =
                        (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
                    fVar5 = (float10)FUN_00423580(
                        *(float *)(param_1 + 0x14) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                        *(float *)(param_1 + 0x1c) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68));
                    *(float *)(param_1 + 0x108) =
                        (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
                    FUN_00435450(
                        0xd,
                        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64),
                        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68),
                        -*(float *)(param_1 + 0x108) + 90.0,
                        *(undefined4 *)(param_1 + 0x104));
                }
                if (*(int *)(param_1 + 0xf4) == 0x3c)
                {
                    *(undefined4 *)(param_1 + 0xf8) = 4;
                }
                *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + 1;
                if (*(int *)(param_1 + 0xf8) == 4)
                {
                    FUN_005f5e00();
                    return;
                }
                break;
            case 0xd2:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    *(undefined4 *)(param_1 + 0xf4) = 0;
                    *(undefined4 *)(param_1 + 0xf8) = 0;
                    *(undefined4 *)(param_1 + 0x54) = 0;
                    *(undefined4 *)(param_1 + 0x6c) = 0;
                }
                *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + 5.0;
                if (*(float *)(param_1 + 0x70) <= 0.5)
                {
                    *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
                    *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
                    *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
                }
                else
                {
                    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.5;
                    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.5;
                    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.5;
                }
                *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(*(int *)(param_1 + 0x38) + 0x14);
                *(float *)(param_1 + 0x18) = *(float *)(*(int *)(param_1 + 0x38) + 0x18) + 85.0;
                *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(*(int *)(param_1 + 0x38) + 0x1c);
                if (*(int *)(param_1 + 0xf4) % 0x3c == 0)
                {
                    FUN_0042c8b0(0xc3);
                }
                if ((*(int *)(param_1 + 0xf4) == 0xb4) && (*(int *)(param_1 + 0xf4) == 0xb4))
                {
                    fVar5 = (float10)FUN_0040da40(
                        *(float *)(param_1 + 0x14) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                        2);
                    fVar6 = (float10)FUN_0040da40(
                        *(float *)(param_1 + 0x1c) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68),
                        2);
                    fVar5 = (float10)FUN_0042de80((float)(fVar6 + (float10)(float)fVar5));
                    *(float *)(param_1 + 0x100) = (float)fVar5;
                    fVar5                       = (float10)FUN_00423580(
                        *(float *)(param_1 + 0x18) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64),
                        *(undefined4 *)(param_1 + 0x100));
                    *(float *)(param_1 + 0x104) =
                        (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
                    fVar5 = (float10)FUN_00423580(
                        *(float *)(param_1 + 0x14) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                        *(float *)(param_1 + 0x1c) -
                            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68));
                    *(float *)(param_1 + 0x108) =
                        (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
                    FUN_00435450(
                        5,
                        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64),
                        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68),
                        -*(float *)(param_1 + 0x108) + 90.0,
                        *(undefined4 *)(param_1 + 0x104));
                }
                if (*(int *)(param_1 + 0xf4) == 0xb4)
                {
                    *(undefined4 *)(param_1 + 0xf8) = 4;
                }
                *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + 1;
                if (*(int *)(param_1 + 0xf8) == 4)
                {
                    FUN_005f5e00();
                    return;
                }
                break;
            case 0xdc:
                if (*(int *)(param_1 + 0x154) == 0)
                {
                    *(undefined4 *)(param_1 + 0xe8) = 0;
                    *(undefined4 *)(param_1 + 0xec) = 0x28;
                    *(undefined4 *)(param_1 + 0xf0) = 0;
                    *(undefined4 *)(param_1 + 0xf4) = 0;
                    *(undefined4 *)(param_1 + 0xf8) = 0;
                    *(undefined4 *)(param_1 + 0x54) = 0;
                    *(undefined4 *)(param_1 + 0x6c) = 0;
                }
                if (*(int *)(param_1 + 0xf4) % 0x3c == 0)
                {
                    FUN_0042c8b0(0xc3);
                }
                if ((0x3b < *(int *)(param_1 + 0xf4)) && (*(int *)(param_1 + 0xf4) % 10 == 0))
                {
                    FUN_005f6ef0(9, 0, 0x461c4000, 0, 0, -*(float *)(param_1 + 0x6c) - 90.0);
                }
                if (0x78 < *(int *)(param_1 + 0xf4))
                {
                    FUN_005f5e00();
                    return;
                }
                *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + 1;
            }
        }
        goto switchD_0062b8dc_caseD_1;
    }
    if (0x1ae < iVar1)
    {
        switch (iVar1)
        {
        case 0x1b8:
        case 0x1c2:
        case 0x1cc:
            goto switchD_0062b91c_caseD_190;
        case 500:
        case 0x1fe:
        case 0x208:
        case 0x212:
        case 0x21c:
        case 0x226:
        case 0x230:
            if (*(int *)(param_1 + 0x154) == 0)
            {
                *(undefined4 *)(param_1 + 0xf4) = 0;
                *(undefined4 *)(param_1 + 0xf8) = 0;
                *(undefined4 *)(param_1 + 0x54) = 0;
                *(undefined4 *)(param_1 + 0x6c) = 0;
            }
            *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + 5.0;
            if (*(float *)(param_1 + 0x70) <= 0.5)
            {
                *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
                *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
                *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
            }
            else
            {
                *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.5;
                *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.5;
                *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.5;
            }
            *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(*(int *)(param_1 + 0x38) + 0x14);
            *(float *)(param_1 + 0x18)      = *(float *)(*(int *)(param_1 + 0x38) + 0x18) + 85.0;
            *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(*(int *)(param_1 + 0x38) + 0x1c);
            if (*(int *)(param_1 + 0xf4) % 0x3c == 0)
            {
                FUN_0042c8b0(0xc3);
            }
            if (*(int *)(param_1 + 0xf4) == *(int *)(param_1 + 0x150) * 2 + -0x334)
            {
                fVar5 = (float10)FUN_0040da40(
                    *(float *)(param_1 + 0x14) -
                        *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                    2);
                fVar11 = (float)fVar5;
                fVar5  = (float10)FUN_0040da40(
                    *(float *)(param_1 + 0x1c) -
                        *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68),
                    2,
                    fVar11);
                fVar5 = (float10)FUN_0042de80((float)(fVar5 + (float10)fVar11));
                *(float *)(param_1 + 0x100) = (float)fVar5;
                fVar5                       = (float10)FUN_00423580(
                    *(float *)(param_1 + 0x18) -
                        *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64),
                    *(undefined4 *)(param_1 + 0x100));
                *(float *)(param_1 + 0x104) =
                    (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
                fVar5 = (float10)FUN_00423580(
                    *(float *)(param_1 + 0x14) -
                        *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                    *(float *)(param_1 + 0x1c) -
                        *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68));
                *(float *)(param_1 + 0x108) =
                    (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
                FUN_00435450(5,
                             *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                             *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64),
                             *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68),
                             -*(float *)(param_1 + 0x108) + 90.0,
                             *(undefined4 *)(param_1 + 0x104));
                *(undefined4 *)(param_1 + 0xf8) = 4;
            }
            *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + 1;
            if (*(int *)(param_1 + 0xf8) == 4)
            {
                FUN_005f5e00();
                return;
            }
        }
        goto switchD_0062b8dc_caseD_1;
    }
    if (iVar1 == 0x1ae)
    {
    switchD_0062b91c_caseD_190:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0xf4) = 0;
            *(undefined4 *)(param_1 + 0xf8) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0x6c) = 0;
        }
        if (*(int *)(param_1 + 0xf4) % 0x3c == 0)
        {
            FUN_0042c8b0(0xc3);
        }
        if (*(int *)(param_1 + 0xf4) == *(int *)(param_1 + 0x150) + -400)
        {
            fVar5 = (float10)FUN_0040da40(
                *(float *)(param_1 + 0x14) -
                    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                2);
            fVar6 = (float10)FUN_0040da40(
                *(float *)(param_1 + 0x1c) -
                    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68),
                2);
            fVar5 = (float10)FUN_0042de80((float)(fVar6 + (float10)(float)fVar5));
            *(float *)(param_1 + 0x100) = (float)fVar5;
            fVar5                       = (float10)FUN_00423580(
                *(float *)(param_1 + 0x18) -
                    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64),
                *(undefined4 *)(param_1 + 0x100));
            *(float *)(param_1 + 0x104) = (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
            fVar5                       = (float10)FUN_00423580(
                *(float *)(param_1 + 0x14) -
                    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                *(float *)(param_1 + 0x1c) -
                    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68));
            *(float *)(param_1 + 0x108) = (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
            FUN_00435450(0xd,
                         *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60),
                         *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64),
                         *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68),
                         -*(float *)(param_1 + 0x108) + 90.0,
                         *(undefined4 *)(param_1 + 0x104));
        }
        *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + 1;
        if (0x3b < *(int *)(param_1 + 0xf4))
        {
            FUN_005f5e00();
            return;
        }
    }
    else
    {
        switch (iVar1)
        {
        case 0xf0:
            if (*(int *)(param_1 + 0x154) == 0)
            {
                uVar4                           = FUN_0065d150();
                *(float *)(param_1 + 0x54)      = (float)(uVar4 % 0x14) * 0.1 + 2.0;
                *(undefined4 *)(param_1 + 0x6c) = 0x42b40000;
            }
            if (0x3b < *(int *)(param_1 + 0x154))
            {
                FUN_005f5e00();
                return;
            }
            break;
        case 300:
        case 0x136:
        case 0x140:
        case 0x14a:
        case 0x154:
        case 0x15e:
        case 0x168:
            if (*(int *)(param_1 + 0x154) == 0)
            {
                if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                     (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                    (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
                {
                    fVar5 = (float10)FUN_0042dac0(2);
                    if ((float10) * (float *)(param_1 + 0x6c) - fVar5 < (float10)10.0)
                    {
                        fVar5                      = (float10)FUN_0042dac0(2);
                        *(float *)(param_1 + 0x6c) = (float)fVar5;
                    }
                    fVar5 = (float10)FUN_0042dac0(2);
                    if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar5)
                    {
                        fVar5                      = (float10)FUN_0042dac0(2);
                        *(float *)(param_1 + 0x6c) = (float)fVar5;
                    }
                }
                *(undefined4 *)(param_1 + 0x54) = 0x42700000;
                *(undefined4 *)(param_1 + 0xe8) = 0;
                *(undefined4 *)(param_1 + 0xec) = 0x28;
                *(undefined4 *)(param_1 + 0xf0) = 0;
                *(undefined4 *)(param_1 + 0xf4) = 0;
                *(undefined4 *)(param_1 + 0xf8) = 0;
                FUN_0042c840(1);
                FUN_005f6880(0);
            }
            *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.1;
            if (*(int *)(param_1 + 0xf8) == 0)
            {
                sVar3 = FUN_0042c7b0();
                if (sVar3 != 0)
                {
                    if (*(short *)(param_1 + 0x88 + *(int *)(*(int *)(param_1 + 0x38) + 8) * 2) ==
                        0)
                    {
                        FUN_005f71f0();
                    }
                    uVar12 = 0;
                    uVar9  = 0;
                    uVar7  = 0;
                    uVar8  = FUN_0066b668(0, 0, 0);
                    FUN_005f6db0(uVar8, uVar7, uVar9, uVar12);
                    FUN_005f5e00();
                    return;
                }
                cVar2 = FUN_005f6a90();
                if (cVar2 == '\x01')
                {
                    uVar12 = 0;
                    uVar9  = 0;
                    uVar7  = 0;
                    uVar8  = FUN_0066b668(0, 0, 0);
                    FUN_005f6db0(uVar8, uVar7, uVar9, uVar12);
                    FUN_005f5e00();
                    return;
                }
            }
            if (0x78 < *(int *)(param_1 + 0x154))
            {
                FUN_005f5e00();
                return;
            }
            break;
        case 400:
        case 0x19a:
        case 0x1a4:
            goto switchD_0062b91c_caseD_190;
        }
    }
switchD_0062b8dc_caseD_1:
    *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
    FUN_005f75a0();
    return;
}
