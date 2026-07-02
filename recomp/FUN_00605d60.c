// ============================================
// Address:  0x00605d60
// Original: FUN_00605d60
// Status:   unreviewed
// ============================================

void __fastcall FUN_00605d60(int param_1)

{
    char cVar1;
    short sVar2;
    uint uVar3;
    float10 fVar4;
    undefined4 uVar5;
    float fVar6;

    uVar3 = FUN_0042c7b0();
    if ((uVar3 & 0x100) != 0)
    {
        switch (*(undefined4 *)(param_1 + 0x150))
        {
        case 0:
        case 10:
        case 0x5a:
        case 100:
        case 0xa0:
        case 0xaa:
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
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar4 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)10.0)
                {
                    fVar4                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar4;
                }
                fVar4 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
                {
                    fVar4                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar4;
                }
            }
            *(undefined4 *)(param_1 + 0x54) = 0x420c0000;
            FUN_0042c840(1);
        }
        if (((0xb4 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
            (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            uVar3 = FUN_0042c7b0();
            if ((uVar3 & 0x80) != 0)
            {
                FUN_005f6db0(0xe, 0, 0, 0);
                FUN_0042c8b0(0xa0);
            }
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
                fVar4 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)10.0)
                {
                    fVar4                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar4;
                }
                fVar4 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
                {
                    fVar4                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar4;
                }
            }
            FUN_005f7450(0, 0x41200000, 0x14, 1, 0);
            *(undefined4 *)(param_1 + 0x54) = 0x425c0000;
            FUN_0042c840(1);
        }
        uVar3 = FUN_0042c7b0();
        if ((uVar3 & 0x80) != 0)
        {
            FUN_005f6db0(0xe, 0, 0, 0);
            FUN_0042c8b0(0xa0);
        }
        if (((0xf0 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
            (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x14:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar4 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)10.0)
                {
                    fVar4                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar4;
                }
                fVar4 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
                {
                    fVar4                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar4;
                }
            }
            FUN_005f6fd0(0xf, 0, 0, 0);
            FUN_0042db10(0, 0x40a00000);
            *(undefined4 *)(param_1 + 0x70) = 0x40800000;
            *(undefined4 *)(param_1 + 0x74) = 0x40800000;
            *(undefined4 *)(param_1 + 0x78) = 0x40800000;
            *(undefined4 *)(param_1 + 0x54) = 0x42340000;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0x28;
            FUN_0042c840(1);
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
        if (100 < *(int *)(param_1 + 0xec))
        {
            *(undefined4 *)(param_1 + 0xec) = 100;
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            FUN_0042db10(0, (float)*(int *)(param_1 + 0xec) * 0.0035);
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) =
                    *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.005;
            }
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) =
                    (float)*(int *)(param_1 + 0xec) * 0.005 + *(float *)(param_1 + 0x6c);
            }
        }
        if (((0xf0 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
            (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            FUN_0042c8b0(0xa0);
            FUN_005f6db0(6, 0, 0, 0);
            if (*(int *)(param_1 + 0x154) < 0xf1)
            {
                FUN_005f6db0(7, 0, 0, 0);
            }
            FUN_005f5e00();
            return;
        }
        break;
    case 0x1e:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar4 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)10.0)
                {
                    fVar4                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar4;
                }
                fVar4 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
                {
                    fVar4                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar4;
                }
            }
            *(undefined4 *)(param_1 + 0x70) = 0x40800000;
            *(undefined4 *)(param_1 + 0x74) = 0x40800000;
            *(undefined4 *)(param_1 + 0x78) = 0x40800000;
            *(undefined4 *)(param_1 + 0x54) = 0x42340000;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0x3c;
            FUN_0042c840(1);
            FUN_005f7450(0, 0x41f00000, 0x1e, 1, 0);
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
        if (0x78 < *(int *)(param_1 + 0xec))
        {
            *(undefined4 *)(param_1 + 0xec) = 0x78;
        }
        if (*(int *)(param_1 + 0x154) % 5 == 0)
        {
            FUN_005f6fd0(0xf, 0, 0, 0);
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            FUN_0042db10(0, (float)*(int *)(param_1 + 0xec) * 0.006);
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) =
                    *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.005;
            }
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) =
                    (float)*(int *)(param_1 + 0xec) * 0.005 + *(float *)(param_1 + 0x6c);
            }
        }
        if (((0xf0 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
            (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            FUN_0042c8b0(0xa0);
            FUN_005f6db0(6, 0, 0, 0);
            if (*(int *)(param_1 + 0x154) < 0xf1)
            {
                FUN_005f6db0(7, 0, 0, 0);
            }
            FUN_005f5e00();
            return;
        }
        break;
    case 0x32:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x41200000;
            uVar3                           = FUN_0065d150();
            *(float *)(param_1 + 100)       = (float)(int)(short)((ulonglong)uVar3 % 0x168);
            uVar3                           = FUN_0065d150();
            *(float *)(param_1 + 0x6c)      = (float)(int)(short)((ulonglong)uVar3 % 0x168);
        }
        *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
        *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
        *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
        if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x3c:
        if (0x33 < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x46:
        *(undefined4 *)(param_1 + 0x6c) = 0;
        *(float *)(param_1 + 0x2c)      = *(float *)(param_1 + 0x2c) + 1.0;
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x78) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0;
        }
        if (6.0 <= *(float *)(param_1 + 0x78))
        {
            *(undefined4 *)(param_1 + 0x78) = 0x40c00000;
            *(undefined4 *)(param_1 + 0x70) = 0x40c00000;
        }
        else
        {
            fVar4 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 3));
            *(float *)(param_1 + 0x78) =
                (float)(fVar4 * (float10)0.4 + (float10) * (float *)(param_1 + 0x78));
            fVar4 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 3));
            *(float *)(param_1 + 0x70) =
                (float)(fVar4 * (float10)0.4 + (float10) * (float *)(param_1 + 0x70));
        }
        if (*(int *)(param_1 + 0x154) % 5 == 0)
        {
            FUN_0042c840(1);
            FUN_0042c800(0);
        }
        if (*(int *)(param_1 + 0x154) % 10 == 0)
        {
            uVar3 = FUN_0065d150();
            fVar6 = (float)(uVar3 % 800) - 400.0;
            uVar5 = 0;
            uVar3 = FUN_0065d150(0, fVar6);
            FUN_005f6fd0(8, (float)(uVar3 % 800) - 400.0, uVar5, fVar6);
        }
        if (*(int *)(param_1 + 0x154) < 0xf1)
        {
            fVar4 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 6));
            *(float *)(param_1 + 0x74) = (float)(fVar4 * (float10)0.25 + (float10)0.75);
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
        break;
    case 0x50:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
            uVar3                           = FUN_0065d150();
            *(float *)(param_1 + 0x54)      = (float)(uVar3 % 0x14) * 0.1 + 2.0;
            uVar3                           = FUN_0065d150();
            *(float *)(param_1 + 0x30)      = (float)(uVar3 % 0x168);
            *(undefined4 *)(param_1 + 0x6c) = 0x42b40000;
        }
        *(float *)(param_1 + 0x30) = *(float *)(param_1 + 0x30) + 2.0;
        if (0x3b < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x5a:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            FUN_005f7450(0, 0x41200000, 0x14, 1, 0);
            *(undefined4 *)(param_1 + 0x54) = 0x42200000;
            FUN_0042c840(1);
        }
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + 0.5;
        if (70.0 < *(float *)(param_1 + 0x54))
        {
            *(undefined4 *)(param_1 + 0x54) = 0x428c0000;
        }
        if (((0xf0 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
            (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            uVar3 = FUN_0042c7b0();
            if ((uVar3 & 0x80) != 0)
            {
                FUN_005f6db0(0xe, 0, 0, 0);
                FUN_0042c8b0(0xa0);
            }
            FUN_005f5e00();
            return;
        }
        break;
    case 100:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x40800000;
            *(undefined4 *)(param_1 + 0x74) = 0x40800000;
            *(undefined4 *)(param_1 + 0x78) = 0x40800000;
            *(undefined4 *)(param_1 + 0x54) = 0x422a0000;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0x28;
            FUN_0042c840(1);
            FUN_005f7450(0, 0x41f00000, 10, 1, 0);
        }
        *(int *)(param_1 + 0xec)   = *(int *)(param_1 + 0xec) + 1;
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + 0.5;
        if (70.0 < *(float *)(param_1 + 0x54))
        {
            *(undefined4 *)(param_1 + 0x54) = 0x428c0000;
        }
        if (100 < *(int *)(param_1 + 0xec))
        {
            *(undefined4 *)(param_1 + 0xec) = 100;
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            FUN_0042db10(0, (float)*(int *)(param_1 + 0xec) * 0.003);
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) =
                    *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.003;
            }
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) =
                    (float)*(int *)(param_1 + 0xec) * 0.003 + *(float *)(param_1 + 0x6c);
            }
        }
        if (((0xf0 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
            (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            FUN_005f6db0(0xb, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        break;
    case 0x6e:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            FUN_0042c840(1);
        }
        if (0x33 < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x78:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
            *(undefined4 *)(param_1 + 0xe8) = 0xff;
        }
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x78) =
            (float)(fVar4 * (float10)0.1 + (float10) * (float *)(param_1 + 0x78));
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x74) =
            (float)(fVar4 * (float10)0.1 + (float10) * (float *)(param_1 + 0x74));
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x70) =
            (float)(fVar4 * (float10)0.1 + (float10) * (float *)(param_1 + 0x70));
        if (*(int *)(param_1 + 0x154) == 6)
        {
            FUN_0042c840(0);
        }
        if ((2 < *(int *)(param_1 + 0x154)) &&
            (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xd,
             *(int *)(param_1 + 0xe8) < 0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0;
        }
        FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8), 0xff, 0xff, 0xff);
        if (*(int *)(param_1 + 0x154) % 5 == 0)
        {
            uVar3 = FUN_0065d150();
            fVar6 = (float)(uVar3 % 200) - 100.0;
            uVar5 = 0;
            uVar3 = FUN_0065d150(0, fVar6);
            FUN_005f6fd0(8, (float)(uVar3 % 200) - 100.0, uVar5, fVar6);
        }
        if (0x1e < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x82:
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
        if (6.0 <= *(float *)(param_1 + 0x78))
        {
            *(undefined4 *)(param_1 + 0x78) = 0x40c00000;
            *(undefined4 *)(param_1 + 0x70) = 0x40c00000;
        }
        else
        {
            fVar4 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 3));
            *(float *)(param_1 + 0x78) =
                (float)(fVar4 * (float10)0.4 + (float10) * (float *)(param_1 + 0x78));
            fVar4 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 3));
            *(float *)(param_1 + 0x70) =
                (float)(fVar4 * (float10)0.4 + (float10) * (float *)(param_1 + 0x70));
        }
        if (*(int *)(param_1 + 0x154) % 5 == 0)
        {
            FUN_0042c840(1);
            FUN_0042c800(0);
        }
        if (*(int *)(param_1 + 0x154) % 10 == 0)
        {
            uVar3 = FUN_0065d150();
            fVar6 = (float)(uVar3 % 800) - 400.0;
            uVar5 = 0;
            uVar3 = FUN_0065d150(0, fVar6);
            FUN_005f6fd0(8, (float)(uVar3 % 800) - 400.0, uVar5, fVar6);
        }
        if ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0x172) &&
            (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xae04) == 0))
        {
            *(undefined4 *)(param_1 + 0xf8) = 1;
        }
        if ((*(int *)(param_1 + 0x154) < 0x12d) && (*(int *)(param_1 + 0xf8) < 1))
        {
            fVar4 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 6));
            *(float *)(param_1 + 0x74) = (float)(fVar4 * (float10)0.25 + (float10)0.75);
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
        break;
    case 0x8c:
        *(undefined4 *)(param_1 + 0x6c) = 0;
        *(float *)(param_1 + 0x2c)      = *(float *)(param_1 + 0x2c) + 1.0;
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
        }
        if (*(int *)(param_1 + 0x154) % 5 == 0)
        {
            uVar3 = FUN_0065d150();
            fVar6 = (float)(uVar3 % 200) - 100.0;
            uVar5 = 0;
            uVar3 = FUN_0065d150(0, fVar6);
            FUN_005f6fd0(8, (float)(uVar3 % 200) - 100.0, uVar5, fVar6);
        }
        if (0 < *(int *)(param_1 + 0x154))
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.025;
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.05;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.05;
            if (*(float *)(param_1 + 0x74) < 0.0 != (*(float *)(param_1 + 0x74) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 0x96:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3e19999a;
            *(undefined4 *)(param_1 + 0x74) = 0x3e19999a;
            *(undefined4 *)(param_1 + 0x78) = 0x3e19999a;
        }
        *(undefined4 *)(param_1 + 0x54) = 0;
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x70) =
            (float)(fVar4 * (float10)0.05 + (float10) * (float *)(param_1 + 0x70));
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x74) =
            (float)(fVar4 * (float10)0.05 + (float10) * (float *)(param_1 + 0x74));
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x78) =
            (float)(fVar4 * (float10)0.05 + (float10) * (float *)(param_1 + 0x78));
        if (0x1c < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0xa0:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar4 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)10.0)
                {
                    fVar4                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar4;
                }
                fVar4 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
                {
                    fVar4                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar4;
                }
            }
            *(undefined4 *)(param_1 + 0x54) = 0x42200000;
            FUN_0042c840(1);
        }
        if (((0xb4 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
            (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            uVar3 = FUN_0042c7b0();
            if ((uVar3 & 0x80) != 0)
            {
                FUN_005f6db0(0xe, 0, 0, 0);
                FUN_0042c8b0(0xa0);
            }
            FUN_005f5e00();
            return;
        }
        break;
    case 0xaa:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar4 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)10.0)
                {
                    fVar4                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar4;
                }
                fVar4 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
                {
                    fVar4                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar4;
                }
            }
            FUN_005f7450(0, 0x41200000, 0x14, 1, 0);
            *(undefined4 *)(param_1 + 0x54) = 0x42700000;
            FUN_0042c840(1);
        }
        uVar3 = FUN_0042c7b0();
        if ((uVar3 & 0x80) != 0)
        {
            FUN_005f6db0(0xe, 0, 0, 0);
            FUN_0042c8b0(0xa0);
        }
        if (((0xf0 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
            (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0xb4:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar4 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)10.0)
                {
                    fVar4                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar4;
                }
                fVar4 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
                {
                    fVar4                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar4;
                }
            }
            FUN_005f6fd0(0xf, 0, 0, 0);
            FUN_0042db10(0, 0x40a00000);
            *(undefined4 *)(param_1 + 0x70) = 0x40800000;
            *(undefined4 *)(param_1 + 0x74) = 0x40800000;
            *(undefined4 *)(param_1 + 0x78) = 0x40800000;
            *(undefined4 *)(param_1 + 0x54) = 0x42340000;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0x28;
            FUN_0042c840(1);
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
        if (100 < *(int *)(param_1 + 0xec))
        {
            *(undefined4 *)(param_1 + 0xec) = 100;
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            FUN_0042db10(0, (float)*(int *)(param_1 + 0xec) * 0.065);
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) =
                    *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.075;
            }
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) =
                    (float)*(int *)(param_1 + 0xec) * 0.075 + *(float *)(param_1 + 0x6c);
            }
        }
        if (((0xf0 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
            (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            FUN_0042c8b0(0xa0);
            FUN_005f6db0(6, 0, 0, 0);
            if (*(int *)(param_1 + 0x154) < 0xf1)
            {
                FUN_005f6db0(7, 0, 0, 0);
            }
            FUN_005f5e00();
            return;
        }
        break;
    case 0xbe:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar4 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)10.0)
                {
                    fVar4                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar4;
                }
                fVar4 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
                {
                    fVar4                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar4;
                }
            }
            *(undefined4 *)(param_1 + 0x70) = 0x40800000;
            *(undefined4 *)(param_1 + 0x74) = 0x40800000;
            *(undefined4 *)(param_1 + 0x78) = 0x40800000;
            *(undefined4 *)(param_1 + 0x54) = 0x42340000;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0x3c;
            FUN_0042c840(1);
            FUN_005f7450(0, 0x41f00000, 0x1e, 1, 0);
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
        if (0x78 < *(int *)(param_1 + 0xec))
        {
            *(undefined4 *)(param_1 + 0xec) = 0x78;
        }
        if (*(int *)(param_1 + 0x154) % 5 == 0)
        {
            FUN_005f6fd0(0xf, 0, 0, 0);
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            FUN_0042db10(0, (float)*(int *)(param_1 + 0xec) * 0.075);
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) =
                    *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.01;
            }
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) =
                    (float)*(int *)(param_1 + 0xec) * 0.01 + *(float *)(param_1 + 0x6c);
            }
        }
        if (((0xf0 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
            (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            FUN_0042c8b0(0xa0);
            FUN_005f6db0(6, 0, 0, 0);
            if (*(int *)(param_1 + 0x154) < 0xf1)
            {
                FUN_005f6db0(7, 0, 0, 0);
            }
            FUN_005f5e00();
            return;
        }
    }
    *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
    FUN_005f75a0();
    return;
}
