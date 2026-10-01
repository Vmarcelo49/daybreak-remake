// ============================================
// Address:  0x006095c0
// Original: FUN_006095c0
// Status:   unreviewed
// ============================================

void __fastcall FUN_006095c0(int param_1)

{
    char cVar1;
    uint uVar2;
    float10 fVar3;

    uVar2 = FUN_0042c7b0();
    if ((uVar2 & 0x100) != 0)
    {
        switch (*(undefined4 *)(param_1 + 0x150))
        {
        case 0:
        case 10:
        case 0x14:
        case 0x1e:
        case 0x28:
        case 0x32:
        case 0x3c:
        case 0x46:
        case 0x50:
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
                fVar3 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar3 < (float10)10.0)
                {
                    fVar3                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar3;
                }
                fVar3 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar3)
                {
                    fVar3                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar3;
                }
            }
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0x420c0000;
            FUN_0042c840(1);
        }
        cVar1 = FUN_005f6a90();
        if ((cVar1 == '\x01') || (0x1e < *(int *)(param_1 + 0x154)))
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
            if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154)))
        {
            FUN_0042db10(0, 0x3e800000);
            fVar3 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar3)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.1;
            }
            fVar3 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar3 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.1;
            }
        }
        break;
    case 10:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar3 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar3 < (float10)10.0)
                {
                    fVar3                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar3;
                }
                fVar3 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar3)
                {
                    fVar3                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar3;
                }
            }
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0x42340000;
            FUN_0042c840(1);
        }
        cVar1 = FUN_005f6a90();
        if ((cVar1 == '\x01') || (0x3c < *(int *)(param_1 + 0x154)))
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
            if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
        if (0x1e < *(int *)(param_1 + 0xec))
        {
            *(undefined4 *)(param_1 + 0xec) = 0x1e;
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154)))
        {
            FUN_0042db10(0, (float)*(int *)(param_1 + 0xec) * 0.033);
            fVar3 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar3)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.5;
            }
            fVar3 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar3 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.5;
            }
        }
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 0.5;
        if (*(float *)(param_1 + 0x54) < 20.0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x41a00000;
        }
        break;
    case 0x14:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar3 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar3 < (float10)10.0)
                {
                    fVar3                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar3;
                }
                fVar3 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar3)
                {
                    fVar3                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar3;
                }
            }
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0x42480000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
            *(undefined4 *)(param_1 + 0x74) = 0x3fc00000;
            *(undefined4 *)(param_1 + 0x78) = 0x3fc00000;
        }
        cVar1 = FUN_005f6a90();
        if ((cVar1 == '\x01') || (0x19 < *(int *)(param_1 + 0x154)))
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
            if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154)))
        {
            FUN_0042db10(0, 0x3e800000);
            fVar3 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar3)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.1;
            }
            fVar3 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar3 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.1;
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
                fVar3 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar3 < (float10)10.0)
                {
                    fVar3                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar3;
                }
                fVar3 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar3)
                {
                    fVar3                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar3;
                }
            }
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0x428c0000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
            *(undefined4 *)(param_1 + 0x74) = 0x3fc00000;
            *(undefined4 *)(param_1 + 0x78) = 0x3fc00000;
        }
        cVar1 = FUN_005f6a90();
        if ((cVar1 == '\x01') || (0x3c < *(int *)(param_1 + 0x154)))
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
            if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
        if (0x1e < *(int *)(param_1 + 0xec))
        {
            *(undefined4 *)(param_1 + 0xec) = 0x1e;
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154)))
        {
            FUN_0042db10(0, (float)*(int *)(param_1 + 0xec) * 0.033);
            fVar3 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar3)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.5;
            }
            fVar3 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar3 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.5;
            }
        }
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 1.0;
        if (*(float *)(param_1 + 0x54) < 35.0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x420c0000;
        }
        break;
    case 0x28:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x41a00000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x30) = 0x42340000;
        }
        if ((*(int *)(param_1 + 0xec) == 0) && (*(int *)(param_1 + 0x154) < 0x14))
        {
            FUN_0042db10(0, 0x40000000);
            fVar3 = (float10)FUN_0042df90(*(undefined4 *)(param_1 + 100));
            if (fVar3 < (float10)1.0)
            {
                *(undefined4 *)(param_1 + 0xec) = 1;
            }
        }
        if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154)))
        {
            FUN_0042db10(0, 0x3e99999a);
            fVar3 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar3)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.3;
            }
            fVar3 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar3 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.3;
            }
        }
        cVar1 = FUN_005f6a90();
        if ((cVar1 == '\x01') || (0x5a < *(int *)(param_1 + 0x154)))
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
            if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 0x32:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x41a00000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x30) = 0xc2340000;
        }
        if ((*(int *)(param_1 + 0xec) == 0) && (*(int *)(param_1 + 0x154) < 0x14))
        {
            FUN_0042db10(0, 0x40000000);
            fVar3 = (float10)FUN_0042df90(*(undefined4 *)(param_1 + 100));
            if (fVar3 < (float10)1.0)
            {
                *(undefined4 *)(param_1 + 0xec) = 1;
            }
        }
        if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154)))
        {
            FUN_0042db10(0, 0x3e99999a);
            fVar3 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar3)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.3;
            }
            fVar3 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar3 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.3;
            }
        }
        cVar1 = FUN_005f6a90();
        if ((cVar1 == '\x01') || (0x5a < *(int *)(param_1 + 0x154)))
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
            if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 0x3c:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x42200000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x30) = 0x42340000;
        }
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 1.0;
        if (*(float *)(param_1 + 0x54) < 30.0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
        }
        if ((*(int *)(param_1 + 0xec) == 0) && (*(int *)(param_1 + 0x154) < 0x14))
        {
            FUN_0042db10(0, 0x40400000);
            fVar3 = (float10)FUN_0042df90(*(undefined4 *)(param_1 + 100));
            if (fVar3 < (float10)1.0)
            {
                *(undefined4 *)(param_1 + 0xec) = 1;
            }
        }
        if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154)))
        {
            FUN_0042db10(0, 0x3ecccccd);
            fVar3 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar3)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.3;
            }
            fVar3 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar3 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.3;
            }
        }
        cVar1 = FUN_005f6a90();
        if ((cVar1 == '\x01') || (0x5a < *(int *)(param_1 + 0x154)))
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
            if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 0x46:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x42200000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x30) = 0xc2340000;
        }
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 1.0;
        if (*(float *)(param_1 + 0x54) < 30.0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
        }
        if ((*(int *)(param_1 + 0xec) == 0) && (*(int *)(param_1 + 0x154) < 0x14))
        {
            FUN_0042db10(0, 0x40400000);
            fVar3 = (float10)FUN_0042df90(*(undefined4 *)(param_1 + 100));
            if (fVar3 < (float10)1.0)
            {
                *(undefined4 *)(param_1 + 0xec) = 1;
            }
        }
        if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154)))
        {
            FUN_0042db10(0, 0x3ecccccd);
            fVar3 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar3)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.3;
            }
            fVar3 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar3 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.3;
            }
        }
        cVar1 = FUN_005f6a90();
        if ((cVar1 == '\x01') || (0x5a < *(int *)(param_1 + 0x154)))
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
            if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 0x50:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            uVar2                           = FUN_0065d150();
            *(float *)(param_1 + 0x30)      = (float)(uVar2 % 0x168);
            *(undefined4 *)(param_1 + 0x54) = 0x42c80000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0x40000000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x78) = 0x40800000;
        }
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0;
        cVar1                      = FUN_005f6a90();
        if ((cVar1 == '\x01') || (5 < *(int *)(param_1 + 0x154)))
        {
            if (10 < *(int *)(param_1 + 0x154))
            {
                FUN_0042c840(0);
            }
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.2;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.4;
            if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 0x5a:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0;
        }
        if (0xf < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
        if (0x1e < *(int *)(param_1 + 0xec))
        {
            *(undefined4 *)(param_1 + 0xec) = 0x1e;
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154)))
        {
            FUN_0042db10(0, (float)*(int *)(param_1 + 0xec) * 0.033);
            fVar3 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar3)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.5;
            }
            fVar3 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar3 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.5;
            }
        }
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 1.0;
        if (*(float *)(param_1 + 0x54) < 20.0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x41a00000;
        }
    }
    *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
    FUN_005f75a0();
    return;
}
