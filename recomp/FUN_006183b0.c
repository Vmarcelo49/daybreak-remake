// ============================================
// Address:  0x006183b0
// Original: FUN_006183b0
// Status:   unreviewed
// ============================================

void __fastcall FUN_006183b0(int param_1)

{
    char cVar1;
    short sVar2;
    uint uVar3;
    float10 fVar4;
    float10 fVar5;
    float10 fVar6;
    int local_8;

    uVar3 = FUN_0042c7b0();
    if (((uVar3 & 0x100) != 0) &&
        ((*(int *)(param_1 + 0x150) == 0x3c || (*(int *)(param_1 + 0x150) == 0x6e))))
    {
        FUN_005f72c0(0x43340000, -*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
        FUN_0042c800(0);
        FUN_0042c840(1);
    }
    switch (*(undefined4 *)(param_1 + 0x150))
    {
    case 0:
        *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + 25.0;
        if (*(int *)(param_1 + 0x154) == 0)
        {
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar6 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar6 < (float10)10.0)
                {
                    fVar6                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar6;
                }
                fVar6 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar6)
                {
                    fVar6                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar6;
                }
            }
            *(undefined4 *)(param_1 + 0x54) = 0x42480000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
        }
        if ((*(int *)(param_1 + 0xec) == 0) &&
            ((*(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 1.0,
              *(float *)(param_1 + 0x54) < 0.0 != (*(float *)(param_1 + 0x54) == 0.0) ||
                  (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))))
        {
            *(undefined4 *)(param_1 + 0xec) = 1;
            *(undefined4 *)(param_1 + 0x54) = 0;
            FUN_005f7430();
            FUN_0042c840(1);
            FUN_0042c800(0);
        }
        else
        {
            if (0 < *(int *)(param_1 + 0xec))
            {
                *(int *)(param_1 + 0xec)   = *(int *)(param_1 + 0xec) + 1;
                *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + 1.5;
                if (60.0 < *(float *)(param_1 + 0x54))
                {
                    *(undefined4 *)(param_1 + 0x54) = 0x42700000;
                }
                FUN_0042db10(0, 0x43340000);
                fVar6                      = (float10)FUN_0042dac0(2);
                *(float *)(param_1 + 0x6c) = (float)fVar6;
                fVar6                      = (float10)FUN_0042d980();
                fVar4                      = (float10)FUN_0042da30();
                fVar5                      = (float10)FUN_0042da30();
                if (fVar5 * (float10)(float)fVar4 + (float10)(float)fVar6 < (float10)10000.0)
                {
                    FUN_005f5e00();
                    return;
                }
            }
            if (0xb4 < *(int *)(param_1 + 0x154))
            {
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 10:
        *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) - 25.0;
        if (*(int *)(param_1 + 0x154) == 0)
        {
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar6 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar6 < (float10)10.0)
                {
                    fVar6                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar6;
                }
                fVar6 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar6)
                {
                    fVar6                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar6;
                }
            }
            *(undefined4 *)(param_1 + 0x54) = 0x42480000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
        }
        if ((*(int *)(param_1 + 0xec) == 0) &&
            ((*(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 1.0,
              *(float *)(param_1 + 0x54) < 0.0 != (*(float *)(param_1 + 0x54) == 0.0) ||
                  (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))))
        {
            *(undefined4 *)(param_1 + 0xec) = 1;
            *(undefined4 *)(param_1 + 0x54) = 0;
            FUN_005f7430();
            FUN_0042c840(1);
            FUN_0042c800(0);
        }
        else
        {
            if (0 < *(int *)(param_1 + 0xec))
            {
                *(int *)(param_1 + 0xec)   = *(int *)(param_1 + 0xec) + 1;
                *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + 1.5;
                if (60.0 < *(float *)(param_1 + 0x54))
                {
                    *(undefined4 *)(param_1 + 0x54) = 0x42700000;
                }
                FUN_0042db10(0, 0x43340000);
                fVar6                      = (float10)FUN_0042dac0(2);
                *(float *)(param_1 + 0x6c) = (float)fVar6;
                fVar6                      = (float10)FUN_0042d980();
                fVar4                      = (float10)FUN_0042da30();
                fVar5                      = (float10)FUN_0042da30();
                if (fVar5 * (float10)(float)fVar4 + (float10)(float)fVar6 < (float10)10000.0)
                {
                    FUN_005f5e00();
                    return;
                }
            }
            if (0xb4 < *(int *)(param_1 + 0x154))
            {
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 0x14:
        *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + 25.0;
        if (*(int *)(param_1 + 0x154) == 0)
        {
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar6 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar6 < (float10)10.0)
                {
                    fVar6                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar6;
                }
                fVar6 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar6)
                {
                    fVar6                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar6;
                }
            }
            *(undefined4 *)(param_1 + 0x54) = 0x42700000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0x40000000;
            *(undefined4 *)(param_1 + 0x74) = 0x40000000;
            *(undefined4 *)(param_1 + 0x78) = 0x40000000;
        }
        if ((*(int *)(param_1 + 0xec) == 0) &&
            ((*(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 1.0,
              *(float *)(param_1 + 0x54) < 0.0 != (*(float *)(param_1 + 0x54) == 0.0) ||
                  (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))))
        {
            *(undefined4 *)(param_1 + 0xec) = 1;
            *(undefined4 *)(param_1 + 0x54) = 0;
            FUN_005f7430();
            FUN_0042c840(1);
            FUN_0042c800(0);
        }
        else
        {
            if (0 < *(int *)(param_1 + 0xec))
            {
                *(int *)(param_1 + 0xec)   = *(int *)(param_1 + 0xec) + 1;
                *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + 1.5;
                if (60.0 < *(float *)(param_1 + 0x54))
                {
                    *(undefined4 *)(param_1 + 0x54) = 0x42700000;
                }
                FUN_0042db10(0, 0x43340000);
                fVar6                      = (float10)FUN_0042dac0(2);
                *(float *)(param_1 + 0x6c) = (float)fVar6;
                fVar6                      = (float10)FUN_0042d980();
                fVar4                      = (float10)FUN_0042da30();
                fVar5                      = (float10)FUN_0042da30();
                if (fVar5 * (float10)(float)fVar4 + (float10)(float)fVar6 < (float10)10000.0)
                {
                    FUN_005f5e00();
                    return;
                }
            }
            if (0xb4 < *(int *)(param_1 + 0x154))
            {
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 0x1e:
        *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) - 25.0;
        if (*(int *)(param_1 + 0x154) == 0)
        {
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar6 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar6 < (float10)10.0)
                {
                    fVar6                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar6;
                }
                fVar6 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar6)
                {
                    fVar6                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar6;
                }
            }
            *(undefined4 *)(param_1 + 0x54) = 0x42700000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0x40000000;
            *(undefined4 *)(param_1 + 0x74) = 0x40000000;
            *(undefined4 *)(param_1 + 0x78) = 0x40000000;
        }
        if ((*(int *)(param_1 + 0xec) == 0) &&
            ((*(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 1.0,
              *(float *)(param_1 + 0x54) < 0.0 != (*(float *)(param_1 + 0x54) == 0.0) ||
                  (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))))
        {
            *(undefined4 *)(param_1 + 0xec) = 1;
            *(undefined4 *)(param_1 + 0x54) = 0;
            FUN_005f7430();
            FUN_0042c840(1);
            FUN_0042c800(0);
        }
        else
        {
            if (0 < *(int *)(param_1 + 0xec))
            {
                *(int *)(param_1 + 0xec)   = *(int *)(param_1 + 0xec) + 1;
                *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + 1.5;
                if (60.0 < *(float *)(param_1 + 0x54))
                {
                    *(undefined4 *)(param_1 + 0x54) = 0x42700000;
                }
                FUN_0042db10(0, 0x43340000);
                fVar6                      = (float10)FUN_0042dac0(2);
                *(float *)(param_1 + 0x6c) = (float)fVar6;
                fVar6                      = (float10)FUN_0042d980();
                fVar4                      = (float10)FUN_0042da30();
                fVar5                      = (float10)FUN_0042da30();
                if (fVar5 * (float10)(float)fVar4 + (float10)(float)fVar6 < (float10)10000.0)
                {
                    FUN_005f5e00();
                    return;
                }
            }
            if (0xb4 < *(int *)(param_1 + 0x154))
            {
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 0x28:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar6 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar6 < (float10)10.0)
                {
                    fVar6                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar6;
                }
                fVar6 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar6)
                {
                    fVar6                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar6;
                }
            }
            FUN_0042db10(0, 0x41200000);
            *(undefined4 *)(param_1 + 0x54) = 0x42480000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0x70) = 0x40400000;
            *(undefined4 *)(param_1 + 0x74) = 0x40400000;
            *(undefined4 *)(param_1 + 0x78) = 0x40400000;
        }
        FUN_0042db10(0, 0x3e4ccccd);
        fVar6 = (float10)FUN_0042dac0(2);
        if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar6)
        {
            *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.2;
        }
        fVar6 = (float10)FUN_0042dac0(2);
        if ((float10) * (float *)(param_1 + 0x6c) - fVar6 < (float10)-3.0)
        {
            *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.2;
        }
        sVar2 = FUN_0042c7b0();
        if ((sVar2 != 0) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            FUN_005f6fd0(7, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        if (*(int *)(param_1 + 0x154) == 0xf)
        {
            FUN_005f6ef0(0xb, 0, 0, 0, 0x41100000, 0);
            FUN_005f6fd0(7, 0, 0, 0);
        }
        if (*(int *)(param_1 + 0x154) == 0x10)
        {
            FUN_005f6ef0(0xb, 0, 0, 0, 0x40400000, 0);
        }
        if (*(int *)(param_1 + 0x154) == 0x11)
        {
            FUN_005f6ef0(0xb, 0, 0, 0, 0xc0400000, 0);
        }
        if (*(int *)(param_1 + 0x154) == 0x12)
        {
            FUN_005f6ef0(0xb, 0, 0, 0, 0xc1100000, 0);
            FUN_005f5e00();
            return;
        }
        break;
    case 0x32:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar6 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar6 < (float10)10.0)
                {
                    fVar6                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar6;
                }
                fVar6 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar6)
                {
                    fVar6                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar6;
                }
            }
            FUN_0042db10(0, 0x41200000);
            *(undefined4 *)(param_1 + 0x54) = 0x42480000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0x70) = 0x40400000;
            *(undefined4 *)(param_1 + 0x74) = 0x40400000;
            *(undefined4 *)(param_1 + 0x78) = 0x40400000;
            FUN_005f7450(0, 0x42700000, 0x19, 1, 0);
        }
        FUN_0042db10(0, 0x3e4ccccd);
        fVar6 = (float10)FUN_0042dac0(2);
        if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar6)
        {
            *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.2;
        }
        fVar6 = (float10)FUN_0042dac0(2);
        if ((float10) * (float *)(param_1 + 0x6c) - fVar6 < (float10)-3.0)
        {
            *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.2;
        }
        sVar2 = FUN_0042c7b0();
        if ((sVar2 != 0) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            FUN_005f6fd0(7, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        if (*(int *)(param_1 + 0x154) == 0xf)
        {
            FUN_005f6ef0(0xb, 0, 0, 0, 0x41400000, 0);
            FUN_005f6fd0(7, 0, 0, 0);
        }
        if (*(int *)(param_1 + 0x154) == 0x10)
        {
            FUN_005f6ef0(0xb, 0, 0, 0, 0x41000000, 0);
        }
        if (*(int *)(param_1 + 0x154) == 0x11)
        {
            FUN_005f6ef0(0xb, 0, 0, 0, 0x40400000, 0);
        }
        if (*(int *)(param_1 + 0x154) == 0x12)
        {
            FUN_005f6ef0(0xb, 0, 0, 0, 0xc0400000, 0);
        }
        if (*(int *)(param_1 + 0x154) == 0x13)
        {
            FUN_005f6ef0(0xb, 0, 0, 0, 0xc1000000, 0);
        }
        if (*(int *)(param_1 + 0x154) == 0x14)
        {
            FUN_005f6ef0(0xb, 0, 0, 0, 0xc1400000, 0);
            FUN_005f5e00();
            return;
        }
        break;
    case 0x3c:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x420c0000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0;
            FUN_005f7450(0, 0x41200000, 0x14, 1, 0);
        }
        *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 2;
        if (100 < *(int *)(param_1 + 0xf0))
        {
            *(undefined4 *)(param_1 + 0xf0) = 100;
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            FUN_0042db10(0, (float)*(int *)(param_1 + 0xf0) * 0.005);
            fVar6 = (float10)FUN_0042dac0(2);
            if ((float10)1.0 < (float10) * (float *)(param_1 + 0x6c) - fVar6)
            {
                *(float *)(param_1 + 0x6c) =
                    *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xf0) * 0.005;
            }
            fVar6 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar6 < (float10)-1.0)
            {
                *(float *)(param_1 + 0x6c) =
                    (float)*(int *)(param_1 + 0xf0) * 0.005 + *(float *)(param_1 + 0x6c);
            }
        }
        if ((0xf0 < *(int *)(param_1 + 0x154)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x46:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
        }
        if (0x33 < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x50:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x42340000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0x40000000;
            *(undefined4 *)(param_1 + 0x74) = 0x40000000;
            *(undefined4 *)(param_1 + 0x78) = 0x40000000;
        }
        if (*(int *)(param_1 + 0x154) == 1)
        {
            FUN_005f6880(0);
        }
        *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.5;
        if (((800 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
            (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            FUN_0042c8b0(0xa5);
            if (*(int *)(param_1 + 0x154) < 0x321)
            {
                FUN_005f6db0(9, 0, 0, 0);
            }
            FUN_005f5e00();
            return;
        }
        break;
    case 0x5a:
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
    case 100:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x42340000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0x40000000;
            *(undefined4 *)(param_1 + 0x74) = 0x40000000;
            *(undefined4 *)(param_1 + 0x78) = 0x40000000;
        }
        if (*(int *)(param_1 + 0x154) == 1)
        {
            FUN_005f6880(0);
        }
        *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.5;
        if (((800 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
            (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            FUN_0042c8b0(0xa7);
            if (*(int *)(param_1 + 0x154) < 0x321)
            {
                FUN_005f6db0(9, 0, 0, 0);
            }
            FUN_005f5e00();
            return;
        }
        break;
    case 0x6e:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
                 (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
                (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd))
            {
                fVar6 = (float10)FUN_0042dac0(2);
                if ((float10) * (float *)(param_1 + 0x6c) - fVar6 < (float10)10.0)
                {
                    fVar6                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar6;
                }
                fVar6 = (float10)FUN_0042dac0(2);
                if ((float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar6)
                {
                    fVar6                      = (float10)FUN_0042dac0(2);
                    *(float *)(param_1 + 0x6c) = (float)fVar6;
                }
            }
            *(undefined4 *)(param_1 + 0x54) = 0x42200000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0x70) = 0x40000000;
            *(undefined4 *)(param_1 + 0x74) = 0x40000000;
            *(undefined4 *)(param_1 + 0x78) = 0x40000000;
        }
        FUN_0042db10(0, 0x3dcccccd);
        fVar6 = (float10)FUN_0042dac0(2);
        if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar6)
        {
            *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.1;
        }
        fVar6 = (float10)FUN_0042dac0(2);
        if ((float10) * (float *)(param_1 + 0x6c) - fVar6 < (float10)-3.0)
        {
            *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.1;
        }
        if (0x14 < *(int *)(param_1 + 0x154))
        {
            for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1)
            {
                uVar3                     = FUN_0065d150();
                *(uint *)(param_1 + 0xf0) = uVar3 % 0x14;
                uVar3                     = FUN_0065d150();
                *(uint *)(param_1 + 0xec) = uVar3 % 0x14;
                FUN_005f6ef0(6,
                             0,
                             0,
                             0,
                             (float)*(int *)(param_1 + 0xf0) - 10.0,
                             (float)*(int *)(param_1 + 0xec) - 10.0);
            }
            FUN_005f6fd0(7, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        sVar2 = FUN_0042c7b0();
        if ((sVar2 != 0) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            FUN_005f6fd0(7, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        break;
    case 0x78:
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
        if (1.5 <= *(float *)(param_1 + 0x78))
        {
            *(undefined4 *)(param_1 + 0x78) = 0x3fc00000;
            *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
        }
        else
        {
            fVar6 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 3));
            *(float *)(param_1 + 0x78) =
                (float)(fVar6 * (float10)0.1 + (float10) * (float *)(param_1 + 0x78));
            fVar6 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 3));
            *(float *)(param_1 + 0x70) =
                (float)(fVar6 * (float10)0.1 + (float10) * (float *)(param_1 + 0x70));
        }
        if (*(int *)(param_1 + 0x154) % 0x1e == 0)
        {
            FUN_0042c840(1);
            FUN_0042c800(0);
        }
        if ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0x172) &&
            (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xae04) == 0))
        {
            *(undefined4 *)(param_1 + 0xf8) = 1;
        }
        if ((*(int *)(param_1 + 0x154) < 0x12d) && (*(int *)(param_1 + 0xf8) < 1))
        {
            fVar6 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 6));
            *(float *)(param_1 + 0x74) = (float)(fVar6 * (float10)0.25 + (float10)0.75);
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
    *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
    FUN_005f75a0();
    return;
}
