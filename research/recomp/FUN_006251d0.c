// ============================================
// Address:  0x006251d0
// Original: FUN_006251d0
// Status:   unreviewed
// ============================================

void __fastcall FUN_006251d0(int param_1)

{
    int iVar1;
    int iVar2;
    int iVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    char cVar7;
    short sVar8;
    uint uVar9;
    undefined4 uVar10;
    float10 fVar11;
    float10 fVar12;
    float10 fVar13;
    float10 fVar14;
    float10 fVar15;
    int local_30;

    uVar9 = FUN_0042c7b0();
    if ((uVar9 & 0x100) != 0)
    {
        switch (*(undefined4 *)(param_1 + 0x150))
        {
        case 0x1e:
        case 0x28:
        case 0x32:
        case 0x3c:
        case 0x46:
        case 0x5a:
            FUN_005f72c0(0x43340000, -*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
            FUN_0042c800(0);
            FUN_0042c840(1);
        }
    }
    switch (*(undefined4 *)(param_1 + 0x150))
    {
    case 0:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0xb4;
        }
        if ((((0x67 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
              (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 200)) ||
             ((0xcb < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) &&
               (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 300)))) ||
            (300 < *(int *)(param_1 + 0x154)))
        {
            FUN_005f6fd0(0xd, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        if ((*(int *)(param_1 + 0x154) < 0x1e) &&
            (*(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 2.0,
             *(float *)(param_1 + 0x54) < 2.0))
        {
            *(undefined4 *)(param_1 + 0x54) = 0x40000000;
        }
        if (0x1d < *(int *)(param_1 + 0x154))
        {
            if (*(int *)(param_1 + 0x154) == 0x3c)
            {
                FUN_005f7450(0, 0x41f00000, 0x3c, 1, 0);
            }
            *(undefined4 *)(param_1 + 0x54) = 0x42700000;
            FUN_0042db10(0, 0x43340000);
            fVar11                     = (float10)FUN_0042dac0(2);
            *(float *)(param_1 + 0x6c) = (float)fVar11;
            if (*(int *)(param_1 + 0x154) % 0x28 == 0)
            {
                FUN_0042c8b0(99);
            }
            fVar11 = (float10)FUN_0042d980();
            if (((float10) * (float *)(param_1 + 0x18) -
                 (float10) * (float *)(*(int *)(param_1 + 0x38) + 0x18)) *
                        ((float10) * (float *)(param_1 + 0x18) -
                         (float10) * (float *)(*(int *)(param_1 + 0x38) + 0x18)) +
                    fVar11 <
                (float10)360000.0)
            {
                FUN_005f6db0(0xc, 0, 0, 0);
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 10:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0xb4;
        }
        if ((((0x67 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
              (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 200)) ||
             ((0xcb < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) &&
               (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 300)))) ||
            (300 < *(int *)(param_1 + 0x154)))
        {
            FUN_005f6fd0(0xd, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        if ((*(int *)(param_1 + 0x154) < 0x1e) &&
            (*(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 2.0,
             *(float *)(param_1 + 0x54) < 2.0))
        {
            *(undefined4 *)(param_1 + 0x54) = 0x40000000;
        }
        if (0x1d < *(int *)(param_1 + 0x154))
        {
            if (*(int *)(param_1 + 0x154) == 0x3c)
            {
                FUN_005f7450(0, 0x41f00000, 0x3c, 1, 0);
            }
            *(undefined4 *)(param_1 + 0x54) = 0x42700000;
            FUN_0042db10(0xc2340000, 0x43340000);
            fVar11                     = (float10)FUN_0042dac0(2);
            *(float *)(param_1 + 0x6c) = (float)fVar11;
            if (*(int *)(param_1 + 0x154) % 0x28 == 0)
            {
                FUN_0042c8b0(99);
            }
            fVar11 = (float10)FUN_0042d980();
            if (((float10) * (float *)(param_1 + 0x18) -
                 (float10) * (float *)(*(int *)(param_1 + 0x38) + 0x18)) *
                        ((float10) * (float *)(param_1 + 0x18) -
                         (float10) * (float *)(*(int *)(param_1 + 0x38) + 0x18)) +
                    fVar11 <
                (float10)360000.0)
            {
                FUN_005f6db0(0xc, 0, 0, 0);
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 0x14:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0xb4;
        }
        if ((((0x67 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
              (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 200)) ||
             ((0xcb < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) &&
               (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 300)))) ||
            (300 < *(int *)(param_1 + 0x154)))
        {
            FUN_005f6fd0(0xd, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        if ((*(int *)(param_1 + 0x154) < 0x1e) &&
            (*(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 2.0,
             *(float *)(param_1 + 0x54) < 2.0))
        {
            *(undefined4 *)(param_1 + 0x54) = 0x40000000;
        }
        if (0x1d < *(int *)(param_1 + 0x154))
        {
            if (*(int *)(param_1 + 0x154) == 0x3c)
            {
                FUN_005f7450(0, 0x41f00000, 0x3c, 1, 0);
            }
            *(undefined4 *)(param_1 + 0x54) = 0x42700000;
            FUN_0042db10(0x42340000, 0x43340000);
            fVar11                     = (float10)FUN_0042dac0(2);
            *(float *)(param_1 + 0x6c) = (float)fVar11;
            if (*(int *)(param_1 + 0x154) % 0x28 == 0)
            {
                FUN_0042c8b0(99);
            }
            fVar11 = (float10)FUN_0042d980();
            if (((float10) * (float *)(param_1 + 0x18) -
                 (float10) * (float *)(*(int *)(param_1 + 0x38) + 0x18)) *
                        ((float10) * (float *)(param_1 + 0x18) -
                         (float10) * (float *)(*(int *)(param_1 + 0x38) + 0x18)) +
                    fVar11 <
                (float10)360000.0)
            {
                FUN_005f6db0(0xc, 0, 0, 0);
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 0x1e:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            FUN_005f6fd0(10, 0, 0, 0);
            *(undefined4 *)(param_1 + 0x54) = 0x42200000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0;
        }
        sVar8 = FUN_0042c7b0();
        if (((sVar8 != 0) || (cVar7 = FUN_005f6a90(), cVar7 == '\x01')) &&
            ((uVar9 = FUN_0042c7b0(),
              (uVar9 & 2) != 0 || (cVar7 = FUN_005f6a90(), cVar7 == '\x01'))))
        {
            *(undefined4 *)(param_1 + 0xf0) = 1;
        }
        if (*(int *)(param_1 + 0xf0) == 1)
        {
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(float *)(param_1 + 0x70)      = *(float *)(param_1 + 0x70) - 0.1;
            *(float *)(param_1 + 0x74)      = *(float *)(param_1 + 0x74) - 0.1;
            *(float *)(param_1 + 0x78)      = *(float *)(param_1 + 0x78) - 0.1;
            if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
        if (100 < *(int *)(param_1 + 0xec))
        {
            *(undefined4 *)(param_1 + 0xec) = 100;
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154)))
        {
            FUN_0042db10(0, (float)*(int *)(param_1 + 0xec) * 0.0025);
        }
        if (*(int *)(param_1 + 0x154) == 0x1e)
        {
            *(undefined4 *)(param_1 + 0x154) = 0x14;
            return;
        }
        if (0xf0 < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x28:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
            FUN_0042c840(1);
        }
        if (*(int *)(param_1 + 0x154) == 0)
        {
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar11 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar11 < (float10)10.0)
                {
                    fVar11                     = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar11;
                }
                fVar11 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar11)
                {
                    fVar11                     = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar11;
                }
            }
            *(undefined4 *)(param_1 + 0x54) = 0x422a0000;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0x78;
            *(undefined4 *)(param_1 + 0xf0) = 0;
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + -1;
        if (*(int *)(param_1 + 0xec) < 0)
        {
            *(undefined4 *)(param_1 + 0xec) = 0;
        }
        *(float *)(param_1 + 0x5c) =
            (float)*(int *)(param_1 + 0xec) * 0.01 + *(float *)(param_1 + 0x5c);
        if ((0xf0 < *(int *)(param_1 + 0x154)) || (cVar7 = FUN_005f6a90(), cVar7 == '\x01'))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x32:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
            FUN_0042c840(1);
        }
        if (*(int *)(param_1 + 0x154) == 0)
        {
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar11 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar11 < (float10)10.0)
                {
                    fVar11                     = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar11;
                }
                fVar11 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar11)
                {
                    fVar11                     = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar11;
                }
            }
            *(undefined4 *)(param_1 + 0x54) = 0x422a0000;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0x78;
            *(undefined4 *)(param_1 + 0xf0) = 0;
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + -1;
        if (*(int *)(param_1 + 0xec) < 0)
        {
            *(undefined4 *)(param_1 + 0xec) = 0;
        }
        *(float *)(param_1 + 0x5c) =
            *(float *)(param_1 + 0x5c) - (float)*(int *)(param_1 + 0xec) * 0.01;
        if ((0xf0 < *(int *)(param_1 + 0x154)) || (cVar7 = FUN_005f6a90(), cVar7 == '\x01'))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x3c:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
            FUN_0042c840(1);
        }
        if (*(int *)(param_1 + 0x154) == 0)
        {
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar11 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar11 < (float10)10.0)
                {
                    fVar11                     = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar11;
                }
                fVar11 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar11)
                {
                    fVar11                     = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar11;
                }
            }
            *(undefined4 *)(param_1 + 0x54) = 0x422a0000;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0x78;
            *(undefined4 *)(param_1 + 0xf0) = 0;
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + -1;
        if (*(int *)(param_1 + 0xec) < 0)
        {
            *(undefined4 *)(param_1 + 0xec) = 0;
        }
        *(float *)(param_1 + 0x5c) =
            (float)*(int *)(param_1 + 0xec) * 0.01 + *(float *)(param_1 + 0x5c);
        if ((0xf0 < *(int *)(param_1 + 0x154)) || (cVar7 = FUN_005f6a90(), cVar7 == '\x01'))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x46:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
            FUN_0042c840(1);
        }
        if (*(int *)(param_1 + 0x154) == 0)
        {
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar11 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar11 < (float10)10.0)
                {
                    fVar11                     = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar11;
                }
                fVar11 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar11)
                {
                    fVar11                     = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar11;
                }
            }
            *(undefined4 *)(param_1 + 0x54) = 0x422a0000;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0x78;
            *(undefined4 *)(param_1 + 0xf0) = 0;
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + -1;
        if (*(int *)(param_1 + 0xec) < 0)
        {
            *(undefined4 *)(param_1 + 0xec) = 0;
        }
        *(float *)(param_1 + 0x5c) =
            *(float *)(param_1 + 0x5c) - (float)*(int *)(param_1 + 0xec) * 0.01;
        if ((0xf0 < *(int *)(param_1 + 0x154)) || (cVar7 = FUN_005f6a90(), cVar7 == '\x01'))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x50:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(float *)(param_1 + 0x104)     = *(float *)(param_1 + 0x6c) + 90.0;
            *(float *)(param_1 + 0x10c)     = 90.0 - *(float *)(param_1 + 0x6c);
            *(undefined4 *)(param_1 + 0xf8) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0;
        }
        if (*(int *)(param_1 + 0xec) == 0)
        {
            *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 7;
            if (0x5a < *(int *)(param_1 + 0xe8))
            {
                *(undefined4 *)(param_1 + 0xe8) = 0x5a;
            }
            fVar11                      = (float10)FUN_0065d010((float)*(int *)(param_1 + 0xe8));
            *(float *)(param_1 + 0x108) = (float)(fVar11 * (float10)150.0);
            fVar6  = *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c) - 90.0;
            fVar11 = (float10)FUN_0065d050(fVar6);
            fVar4  = *(float *)(param_1 + 0x108);
            fVar12 = (float10)FUN_0065d050(*(undefined4 *)(param_1 + 0x104));
            fVar13 = (float10)FUN_0065d010(*(undefined4 *)(param_1 + 0x104));
            fVar5  = *(float *)(param_1 + 0x108);
            fVar14 = (float10)FUN_0065d010(fVar6);
            fVar6  = *(float *)(param_1 + 0x108);
            fVar15 = (float10)FUN_0065d050(*(undefined4 *)(param_1 + 0x104));
            *(float *)(param_1 + 0x14) =
                (float)(fVar12 * (float10)(float)(fVar11 * (float10)fVar4)) +
                *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x14);
            *(float *)(param_1 + 0x18) =
                (float)(fVar13 * (float10)fVar5) +
                *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 75.0;
            *(float *)(param_1 + 0x1c) =
                (float)(fVar15 * (float10)(float)(fVar14 * (float10)fVar6)) +
                *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x1c);
            *(undefined4 *)(param_1 + 0x38) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x38);
            *(undefined4 *)(param_1 + 0x5c) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c);
            *(undefined4 *)(param_1 + 100) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 100);
            fVar11                     = (float10)FUN_0042dac0(2);
            *(float *)(param_1 + 0x6c) = (float)fVar11;
            if (30.0 < *(float *)(param_1 + 0x6c))
            {
                *(undefined4 *)(param_1 + 0x6c) = 0x41f00000;
            }
            if (*(float *)(param_1 + 0x6c) < -30.0)
            {
                *(undefined4 *)(param_1 + 0x6c) = 0xc1f00000;
            }
            if ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xf4) == 1) &&
                (*(int *)(param_1 + 0xf8) == 0))
            {
                FUN_005f6db0(9, 0, 0, 0);
                *(undefined4 *)(param_1 + 0xf8) = 1;
            }
            if (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xf4) == 2)
            {
                *(undefined4 *)(param_1 + 0xec) = 2;
            }
        }
        if (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xf4) == 2)
        {
            FUN_005f7430();
            FUN_005f6fd0(0xd, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        if ((99 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
            (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 300))
        {
            FUN_005f7430();
            FUN_005f6fd0(0xd, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        break;
    case 0x5a:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            FUN_0042db10(0, 0x41200000);
            FUN_005f6fd0(0xb, 0, 0, 0);
            *(undefined4 *)(param_1 + 0x54) = 0x42700000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0;
            *(undefined4 *)(param_1 + 0xf4) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
        }
        cVar7 = FUN_005f6a90();
        if ((cVar7 == '\x01') && (cVar7 = FUN_005f6a90(), cVar7 == '\x01'))
        {
            *(undefined4 *)(param_1 + 0xf0) = 1;
        }
        if (*(int *)(param_1 + 0xf0) == 1)
        {
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(float *)(param_1 + 0x70)      = *(float *)(param_1 + 0x70) - 0.05;
            *(float *)(param_1 + 0x74)      = *(float *)(param_1 + 0x74) - 0.05;
            *(float *)(param_1 + 0x78)      = *(float *)(param_1 + 0x78) - 0.05;
            if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
        *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + 1;
        if (100 < *(int *)(param_1 + 0xec))
        {
            *(undefined4 *)(param_1 + 0xec) = 100;
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (*(int *)(param_1 + 0x154) == 0x3c)
        {
            *(undefined4 *)(param_1 + 0x154) = 0x28;
            return;
        }
        if (0xb4 < *(int *)(param_1 + 0xf4))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 100:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xff;
            uVar9                           = FUN_0065d150();
            *(float *)(param_1 + 0x30)      = (float)(uVar9 % 0x168);
            *(undefined4 *)(param_1 + 0x70) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x74) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x78) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x54) = 0;
        }
        fVar11 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x70) =
            (float)(fVar11 * (float10)0.025 + (float10) * (float *)(param_1 + 0x70));
        fVar11 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x74) =
            (float)(fVar11 * (float10)0.025 + (float10) * (float *)(param_1 + 0x74));
        fVar11 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x78) =
            (float)(fVar11 * (float10)0.025 + (float10) * (float *)(param_1 + 0x78));
        if ((6 < *(int *)(param_1 + 0x154)) &&
            (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -10,
             *(int *)(param_1 + 0xe8) < 0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_005f5e00();
            return;
        }
        FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8), 0xff, 0xff, 0xff);
        break;
    case 0x6e:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xff;
            uVar9                           = FUN_0065d150();
            *(float *)(param_1 + 0x30)      = (float)(uVar9 % 0x168);
            *(undefined4 *)(param_1 + 0x70) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x74) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x78) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x54) = 0;
        }
        fVar11 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x70) =
            (float)(fVar11 * (float10)0.025 + (float10) * (float *)(param_1 + 0x70));
        fVar11 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x74) =
            (float)(fVar11 * (float10)0.025 + (float10) * (float *)(param_1 + 0x74));
        fVar11 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x78) =
            (float)(fVar11 * (float10)0.025 + (float10) * (float *)(param_1 + 0x78));
        if ((6 < *(int *)(param_1 + 0x154)) &&
            (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -10,
             *(int *)(param_1 + 0xe8) < 0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_005f5e00();
            return;
        }
        FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8), 0xff, 0xff, 0xff);
        break;
    case 0x78:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0xb4;
        }
        if (((0x67 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
             (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 200)) ||
            ((0xcb < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) &&
              (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 300))))
        {
            FUN_005f6fd0(0xd, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        if (*(int *)(param_1 + 0x154) < 0xf)
        {
            FUN_0042db10(0, 0x43340000);
            fVar11                     = (float10)FUN_0042dac0(2);
            *(float *)(param_1 + 0x6c) = (float)fVar11;
        }
        if (*(int *)(param_1 + 0x154) == 0xf)
        {
            FUN_0042c8b0(0x50);
            FUN_005f6db0(3, 0, 0, 0);
        }
        if (*(int *)(param_1 + 0x154) == 0x78)
        {
            FUN_005f7430();
            FUN_005f6fd0(0xd, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        break;
    case 0x82:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0xb4;
        }
        FUN_0042db10(0, 0x43340000);
        fVar11                          = (float10)FUN_0042dac0(2);
        *(float *)(param_1 + 0x6c)      = (float)fVar11;
        *(undefined4 *)(param_1 + 0x54) = 0x42a00000;
        fVar11                          = (float10)FUN_0042d980();
        if (((float10) * (float *)(param_1 + 0x18) -
             (float10) * (float *)(*(int *)(param_1 + 0x38) + 0x18)) *
                    ((float10) * (float *)(param_1 + 0x18) -
                     (float10) * (float *)(*(int *)(param_1 + 0x38) + 0x18)) +
                fVar11 <
            (float10)10000.0)
        {
            for (local_30 = 0; local_30 < 3; local_30 = local_30 + 1)
            {
                FUN_005f6fd0(0xe, 0, 0, 0);
            }
            FUN_005f5e00();
            return;
        }
        break;
    case 0x8c:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            uVar9                      = FUN_0065d150();
            *(float *)(param_1 + 0x6c) = (float)(uVar9 % 0x168);
            uVar9                      = FUN_0065d150();
            *(float *)(param_1 + 100)  = (float)(uVar9 % 0x168);
            uVar9                      = FUN_0065d150();
            *(float *)(param_1 + 0x54) = (float)(uVar9 % 0x14) + 2.0;
            uVar9                      = FUN_0065d150();
            *(float *)(param_1 + 0x30) = (float)(uVar9 % 0x168);
        }
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) * 0.95;
        if (0x3b < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x96:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(float *)(param_1 + 0x104)     = *(float *)(param_1 + 0x6c) + 90.0;
            *(float *)(param_1 + 0x10c)     = 90.0 - *(float *)(param_1 + 0x6c);
            *(undefined4 *)(param_1 + 0xf8) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0;
        }
        *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0x154) * 7;
        if (0x5a < *(int *)(param_1 + 0xe8))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0x5a;
        }
        FUN_0065d010((float)*(int *)(param_1 + 0xe8));
        uVar10                          = FUN_0066b668();
        *(undefined4 *)(param_1 + 0xf0) = uVar10;
        fVar4  = *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c) - 90.0;
        iVar1  = *(int *)(param_1 + 0xf0);
        fVar11 = (float10)FUN_0065d050(fVar4);
        fVar12 = (float10)FUN_0065d050(*(undefined4 *)(param_1 + 0x104));
        iVar2  = *(int *)(param_1 + 0xf0);
        fVar13 = (float10)FUN_0065d010(*(undefined4 *)(param_1 + 0x104));
        iVar3  = *(int *)(param_1 + 0xf0);
        fVar14 = (float10)FUN_0065d010(fVar4);
        fVar15 = (float10)FUN_0065d050(*(undefined4 *)(param_1 + 0x104));
        *(float *)(param_1 + 0x14) = (float)(fVar12 * (float10)(float)(fVar11 * (float10)iVar1)) +
                                     *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x14);
        *(float *)(param_1 + 0x18) = (float)(fVar13 * (float10)iVar2) +
                                     *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) +
                                     75.0;
        *(float *)(param_1 + 0x1c) = (float)(fVar15 * (float10)(float)(fVar14 * (float10)iVar3)) +
                                     *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x1c);
        *(undefined4 *)(param_1 + 0x38) =
            *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x38);
        *(undefined4 *)(param_1 + 0x5c) =
            *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c);
        *(undefined4 *)(param_1 + 100) =
            *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 100);
        fVar11                     = (float10)FUN_0042dac0(2);
        *(float *)(param_1 + 0x6c) = (float)fVar11;
        if (30.0 < *(float *)(param_1 + 0x6c))
        {
            *(undefined4 *)(param_1 + 0x6c) = 0x41f00000;
        }
        if (*(float *)(param_1 + 0x6c) < -30.0)
        {
            *(undefined4 *)(param_1 + 0x6c) = 0xc1f00000;
        }
        if ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xf4) == 1) &&
            (*(int *)(param_1 + 0xf8) == 0))
        {
            FUN_005f6db0(9, 0, 0, 0);
            *(undefined4 *)(param_1 + 0xf8) = 1;
        }
        if (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xf4) == 2)
        {
            FUN_005f6fd0(0xd, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        if (((0x67 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
             (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 200)) ||
            ((0xcb < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) &&
              (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 300))))
        {
            FUN_005f7430();
            FUN_005f6fd0(0xd, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
    }
    *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
    FUN_005f75a0();
    return;
}
