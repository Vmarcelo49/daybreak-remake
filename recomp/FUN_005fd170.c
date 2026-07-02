// ============================================
// Address:  0x005fd170
// Original: FUN_005fd170
// Status:   unreviewed
// ============================================

void __fastcall FUN_005fd170(int param_1)

{
    char cVar1;
    short sVar2;
    uint uVar3;
    float10 fVar4;

    uVar3 = FUN_0042c7b0();
    if ((uVar3 & 0x100) != 0)
    {
        switch (*(undefined4 *)(param_1 + 0x150))
        {
        case 0:
        case 0x14:
        case 0x1e:
        case 0x28:
        case 0x32:
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
            *(undefined4 *)(param_1 + 0x54) = 0x42340000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
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
            FUN_0042db10(0, 0x3dcccccd);
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.1;
            }
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.1;
            }
        }
        if ((0xf0 < *(int *)(param_1 + 0x154)) ||
            (((sVar2 = FUN_0042c7b0(), sVar2 != 0 && (sVar2 = FUN_0042c7b0(), sVar2 != 1)) ||
              (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 10:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0;
            FUN_005f6880(0);
            *(undefined4 *)(param_1 + 0x40) = 0x41700000;
        }
        *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 1.75;
        if (0x12 < *(int *)(param_1 + 0x154))
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
            *(undefined4 *)(param_1 + 0x54) = 0x42480000;
            FUN_0042c840(1);
            FUN_005f7450(0, 0x42a00000, 0x1e, 1, 0);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0x3f266666;
            *(undefined4 *)(param_1 + 0x74) = 0x3f266666;
            *(undefined4 *)(param_1 + 0x78) = 0x3f266666;
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
        if (0x5a < *(int *)(param_1 + 0xec))
        {
            *(undefined4 *)(param_1 + 0xec) = 0x5a;
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            FUN_0042db10(0, (float)*(int *)(param_1 + 0xec) * 0.0075);
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10)1.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) =
                    *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.0025;
            }
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0)
            {
                *(float *)(param_1 + 0x6c) =
                    (float)*(int *)(param_1 + 0xec) * 0.0025 + *(float *)(param_1 + 0x6c);
            }
        }
        if (*(int *)(param_1 + 0x154) == 10)
        {
            *(undefined4 *)(param_1 + 0x154) = 1;
            return;
        }
        if ((0x1e0 < *(int *)(param_1 + 0x154)) ||
            (((sVar2 = FUN_0042c7b0(), sVar2 != 0 && (sVar2 = FUN_0042c7b0(), sVar2 != 1)) ||
              (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))))
        {
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
            *(undefined4 *)(param_1 + 0x54) = 0x425c0000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            FUN_005f7450(0, 0x42700000, 0xf, 1, 0);
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
        if (0x78 < *(int *)(param_1 + 0xec))
        {
            *(undefined4 *)(param_1 + 0xec) = 0x78;
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            FUN_0042db10(0, 0x3eb33333);
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.25;
            }
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.25;
            }
        }
        if ((0xf0 < *(int *)(param_1 + 0x154)) ||
            (((sVar2 = FUN_0042c7b0(), sVar2 != 0 && (sVar2 = FUN_0042c7b0(), sVar2 != 1)) ||
              (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x28:
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
            *(undefined4 *)(param_1 + 0x54) = 0x42480000;
            FUN_0042c840(1);
            FUN_005f7450(1, 0x42f00000, 0x1e, 1, 0);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0x3f4ccccd;
            *(undefined4 *)(param_1 + 0x74) = 0x3f4ccccd;
            *(undefined4 *)(param_1 + 0x78) = 0x3f4ccccd;
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
        if (*(int *)(param_1 + 0x154) % 5 == 0)
        {
            FUN_005f6fd0(8, 0, 0, 0);
        }
        if (0x5a < *(int *)(param_1 + 0xec))
        {
            *(undefined4 *)(param_1 + 0xec) = 0x5a;
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            FUN_0042db10(0, (float)*(int *)(param_1 + 0xec) * 0.015);
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10)1.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) =
                    *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.0025;
            }
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0)
            {
                *(float *)(param_1 + 0x6c) =
                    (float)*(int *)(param_1 + 0xec) * 0.0025 + *(float *)(param_1 + 0x6c);
            }
        }
        if (*(int *)(param_1 + 0x154) == 10)
        {
            *(undefined4 *)(param_1 + 0x154) = 1;
            return;
        }
        if ((0x1e0 < *(int *)(param_1 + 0x154)) ||
            (((sVar2 = FUN_0042c7b0(), sVar2 != 0 && (sVar2 = FUN_0042c7b0(), sVar2 != 1)) ||
              (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x32:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x42520000;
            FUN_0042c840(3);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_005f7450(0, 0x43480000, 0x3c, 1, 0);
            FUN_005f6fd0(9, 0, 0, 0);
        }
        if (*(int *)(param_1 + 0x154) % 5 == 0)
        {
            FUN_005f6fd0(7, 0, 0, 0);
        }
        FUN_0042c800(0);
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            FUN_0042db10(0, 0x3ba3d70a);
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10)1.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.005;
            }
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.005;
            }
        }
        if ((0x1e0 < *(int *)(param_1 + 0x154)) ||
            (((sVar2 = FUN_0042c7b0(), sVar2 != 0 && (sVar2 = FUN_0042c7b0(), sVar2 != 1)) ||
              (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x46:
        if (0xf < *(int *)(param_1 + 0x154))
        {
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
            if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 0x50:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f333333;
            *(undefined4 *)(param_1 + 0x74) = 0x3f333333;
            *(undefined4 *)(param_1 + 0x78) = 0x3f333333;
            uVar3                           = FUN_0065d150();
            *(float *)(param_1 + 0x34)      = (float)(uVar3 % 0x1e) - 15.0;
            uVar3                           = FUN_0065d150();
            *(float *)(param_1 + 0x30)      = (float)(uVar3 % 0x1e) - 15.0;
            uVar3                           = FUN_0065d150();
            *(float *)(param_1 + 0x2c)      = (float)(uVar3 % 0x168);
        }
        if (0xe < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x5a:
        if (0xc < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
    }
    *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
    FUN_005f75a0();
    return;
}
