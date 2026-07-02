// ============================================
// Address:  0x0061d920
// Original: FUN_0061d920
// Status:   unreviewed
// ============================================

void __fastcall FUN_0061d920(int param_1)

{
    char cVar1;
    short sVar2;
    uint uVar3;
    float10 fVar4;

    uVar3 = FUN_0042c7b0();
    if (((uVar3 & 0x100) != 0) &&
        ((*(int *)(param_1 + 0x150) == 0 || (*(int *)(param_1 + 0x150) == 0x1e))))
    {
        FUN_005f72c0(0x43340000, -*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
        FUN_0042c800(0);
        FUN_0042c840(1);
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
            *(undefined4 *)(param_1 + 0x54) = 0x422a0000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0;
            FUN_005f7450(0, 0x42700000, 10, 1, 0);
            FUN_005f6fd0(7, 0, 0, 0);
        }
        *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
        if (0x3c < *(int *)(param_1 + 0xf0))
        {
            *(undefined4 *)(param_1 + 0xf0) = 0x3c;
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            FUN_0042db10(0, (float)*(int *)(param_1 + 0xf0) * 0.01);
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10)1.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) =
                    *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xf0) * 0.01;
            }
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0)
            {
                *(float *)(param_1 + 0x6c) =
                    (float)*(int *)(param_1 + 0xf0) * 0.01 + *(float *)(param_1 + 0x6c);
            }
        }
        sVar2 = FUN_0042c7b0();
        if (sVar2 != 0)
        {
            FUN_0042c8b0(0xd6);
            FUN_005f5e00();
            return;
        }
        if ((0xf0 < *(int *)(param_1 + 0x154)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 10:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x422a0000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0x78) = 0x40000000;
            *(undefined4 *)(param_1 + 0x74) = 0x40000000;
            *(undefined4 *)(param_1 + 0x70) = 0x40000000;
        }
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0;
        if (*(float *)(param_1 + 0x54) < 3.0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x40400000;
        }
        if (0x5a < *(int *)(param_1 + 0x154))
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
            if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 0x14:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x422a0000;
            FUN_0042c840(1);
        }
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0;
        if (*(float *)(param_1 + 0x54) < 3.0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x40400000;
        }
        if (0x5a < *(int *)(param_1 + 0x154))
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
            if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
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
            *(undefined4 *)(param_1 + 0x54) = 0x42700000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0;
            FUN_005f7450(2, 0x42700000, 10, 1, 0);
            FUN_005f6fd0(7, 0, 0, 0);
        }
        *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
        if (0x3c < *(int *)(param_1 + 0xf0))
        {
            *(undefined4 *)(param_1 + 0xf0) = 0x3c;
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            FUN_0042db10(0, (float)*(int *)(param_1 + 0xf0) * 0.02);
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10)1.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) =
                    *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xf0) * 0.02;
            }
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0)
            {
                *(float *)(param_1 + 0x6c) =
                    (float)*(int *)(param_1 + 0xf0) * 0.02 + *(float *)(param_1 + 0x6c);
            }
        }
        sVar2 = FUN_0042c7b0();
        if (sVar2 != 0)
        {
            FUN_0042c8b0(0xd6);
            FUN_005f5e00();
            return;
        }
        if ((0xf0 < *(int *)(param_1 + 0x154)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x28:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x422a0000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0x78) = 0x40000000;
            *(undefined4 *)(param_1 + 0x74) = 0x40000000;
            *(undefined4 *)(param_1 + 0x70) = 0x40000000;
        }
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0;
        if (*(float *)(param_1 + 0x54) < 3.0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x40400000;
        }
        if (0x5a < *(int *)(param_1 + 0x154))
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
            if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 0x32:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x422a0000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0x78) = 0x40000000;
            *(undefined4 *)(param_1 + 0x74) = 0x40000000;
            *(undefined4 *)(param_1 + 0x70) = 0x40000000;
        }
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0;
        if (*(float *)(param_1 + 0x54) < 3.0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x40400000;
        }
        if (0x5a < *(int *)(param_1 + 0x154))
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
            if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 0x3c:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xff;
            uVar3                           = FUN_0065d150();
            *(float *)(param_1 + 0x30)      = (float)(uVar3 % 0x168);
            *(undefined4 *)(param_1 + 0x70) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x74) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x78) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x54) = 0;
        }
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x70) =
            (float)(fVar4 * (float10)0.025 + (float10) * (float *)(param_1 + 0x70));
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x74) =
            (float)(fVar4 * (float10)0.025 + (float10) * (float *)(param_1 + 0x74));
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x78) =
            (float)(fVar4 * (float10)0.025 + (float10) * (float *)(param_1 + 0x78));
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
    case 0x46:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xff;
            uVar3                           = FUN_0065d150();
            *(float *)(param_1 + 0x30)      = (float)(uVar3 % 0x168);
            *(undefined4 *)(param_1 + 0x70) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x74) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x78) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x54) = 0;
        }
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x70) =
            (float)(fVar4 * (float10)0.025 + (float10) * (float *)(param_1 + 0x70));
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x74) =
            (float)(fVar4 * (float10)0.025 + (float10) * (float *)(param_1 + 0x74));
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x78) =
            (float)(fVar4 * (float10)0.025 + (float10) * (float *)(param_1 + 0x78));
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
    case 0x50:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0xe8) = 0xff;
        }
        if ((10 < *(int *)(param_1 + 0x154)) &&
            (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0x28,
             *(int *)(param_1 + 0xe8) < 0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0;
        }
        FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8), 0xff, 0xff, 0xff);
        if (0xf < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
    }
    *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
    FUN_005f75a0();
    return;
}
