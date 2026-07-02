// ============================================
// Address:  0x0061b8e0
// Original: FUN_0061b8e0
// Status:   unreviewed
// ============================================

void __fastcall FUN_0061b8e0(int param_1)

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
        case 10:
        case 0x14:
        case 0x1e:
        case 0x28:
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
            *(undefined4 *)(param_1 + 0x54) = 0x423c0000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
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
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
        if (0x4b < *(int *)(param_1 + 0xec))
        {
            *(undefined4 *)(param_1 + 0xec) = 0x4b;
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
            FUN_005f5e00();
            return;
        }
        break;
    case 0x14:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x42340000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
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
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
        if (0x4b < *(int *)(param_1 + 0xec))
        {
            *(undefined4 *)(param_1 + 0xec) = 0x4b;
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            FUN_0042db10(0, 0x3d4ccccd);
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.05;
            }
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.05;
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
            FUN_005f7450(0, 0x41200000, 0x14, 1, 0);
            *(undefined4 *)(param_1 + 0x54) = 0x425c0000;
            FUN_0042c840(1);
        }
        if (((0xf0 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
            (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
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
            FUN_005f7450(0, 0x41200000, 0x14, 1, 0);
            *(undefined4 *)(param_1 + 0x54) = 0x425c0000;
            FUN_0042c840(1);
        }
        if (((0xf0 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
            (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x32:
        *(undefined4 *)(param_1 + 0x54) = 0;
        *(undefined4 *)(param_1 + 0x40) = 0;
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xff;
        }
        if ((0 < *(int *)(param_1 + 0x154)) &&
            (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -10,
             *(int *)(param_1 + 0xe8) < 0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_005f5e00();
            return;
        }
        FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8), 0xff, 0xff, 0xff);
        break;
    case 0x3c:
        *(undefined4 *)(param_1 + 0x54) = 0;
        *(undefined4 *)(param_1 + 0x40) = 0;
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xff;
        }
        if ((0 < *(int *)(param_1 + 0x154)) &&
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
        break;
    case 0x50:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x40e00000;
            *(undefined4 *)(param_1 + 0xe8) = 0xff;
            *(undefined4 *)(param_1 + 0xf8) = 0;
        }
        if (*(int *)(param_1 + 0x154) == 1)
        {
            FUN_005f6880(0);
        }
        *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.4;
        cVar1                      = FUN_005f6a90();
        if (cVar1 == '\x01')
        {
            *(undefined4 *)(param_1 + 0xf8) = 1;
        }
        if ((0x3c < *(int *)(param_1 + 0x154)) || (0 < *(int *)(param_1 + 0xf8)))
        {
            FUN_0042c840(0);
            *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xd;
            if (*(int *)(param_1 + 0xe8) < 0)
            {
                *(undefined4 *)(param_1 + 0xe8) = 0;
                FUN_005f5e00();
                return;
            }
            FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8), 0xff, 0xff, 0xff);
        }
        break;
    case 0x5a:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x40a00000;
            *(undefined4 *)(param_1 + 0xe8) = 0xff;
            *(undefined4 *)(param_1 + 0xf8) = 0;
        }
        if (*(int *)(param_1 + 0x154) == 1)
        {
            FUN_005f6880(0);
        }
        *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.4;
        cVar1                      = FUN_005f6a90();
        if (cVar1 == '\x01')
        {
            *(undefined4 *)(param_1 + 0xf8) = 1;
        }
        if ((0x3c < *(int *)(param_1 + 0x154)) || (0 < *(int *)(param_1 + 0xf8)))
        {
            FUN_0042c840(0);
            *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xd;
            if (*(int *)(param_1 + 0xe8) < 0)
            {
                *(undefined4 *)(param_1 + 0xe8) = 0;
                FUN_005f5e00();
                return;
            }
            FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8), 0xff, 0xff, 0xff);
        }
    }
    *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
    FUN_005f75a0();
    return;
}
