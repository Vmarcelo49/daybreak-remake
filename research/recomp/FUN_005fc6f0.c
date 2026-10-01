// ============================================
// Address:  0x005fc6f0
// Original: FUN_005fc6f0
// Status:   unreviewed
// ============================================

void __fastcall FUN_005fc6f0(int param_1)

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
            FUN_005f6fd0(3, 0, 0, 0);
            *(undefined4 *)(param_1 + 0x54) = 0x422a0000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0;
            *(undefined4 *)(param_1 + 0xf4) = 0;
        }
        sVar2 = FUN_0042c7b0();
        if (((sVar2 != 0) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) &&
            ((uVar3 = FUN_0042c7b0(),
              (uVar3 & 2) != 0 || (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))))
        {
            *(undefined4 *)(param_1 + 0xf4) = 1;
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
        *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
        if (0x3c < *(int *)(param_1 + 0xec))
        {
            *(undefined4 *)(param_1 + 0xec) = 0x3c;
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
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.05;
            }
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.05;
            }
        }
        if ((0xb4 < *(int *)(param_1 + 0xf0)) || (*(int *)(param_1 + 0xf4) == 1))
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.15;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.2;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.2;
            if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        if (*(int *)(param_1 + 0x154) == 0x1e)
        {
            *(undefined4 *)(param_1 + 0x154) = 0x14;
            return;
        }
        break;
    case 10:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            FUN_005f6fd0(3, 0, 0, 0);
            *(undefined4 *)(param_1 + 0x54) = 0x42200000;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0;
            FUN_0042c840(1);
        }
        *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
        sVar2                    = FUN_0042c7b0();
        if (((sVar2 != 0) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) &&
            ((uVar3 = FUN_0042c7b0(),
              (uVar3 & 2) != 0 || (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))))
        {
            *(undefined4 *)(param_1 + 0xf0) = 1;
        }
        if ((0x5a < *(int *)(param_1 + 0xe8)) || (*(int *)(param_1 + 0xf0) == 1))
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
        if (*(int *)(param_1 + 0x154) == 0x1e)
        {
            *(undefined4 *)(param_1 + 0x154) = 0x14;
            return;
        }
        break;
    case 0x14:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
            *(undefined4 *)(param_1 + 0x74) = 0x3fc00000;
            *(undefined4 *)(param_1 + 0x78) = 0x3fc00000;
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
    case 0x1e:
        if (5 < *(int *)(param_1 + 0x154))
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
            *(undefined4 *)(param_1 + 0x70) = 0x40000000;
            *(undefined4 *)(param_1 + 0x74) = 0x40000000;
            *(undefined4 *)(param_1 + 0x78) = 0x40000000;
            FUN_005f6fd0(3, 0, 0, 0);
            *(undefined4 *)(param_1 + 0x54) = 0x423e0000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0;
        }
        sVar2 = FUN_0042c7b0();
        if (((sVar2 != 0) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) &&
            ((uVar3 = FUN_0042c7b0(),
              (uVar3 & 2) != 0 || (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))))
        {
            *(undefined4 *)(param_1 + 0xf0) = 1;
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
            FUN_0042db10(0, 0x3e99999a);
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
        if ((0xb4 < *(int *)(param_1 + 0x154)) || (*(int *)(param_1 + 0xf0) == 1))
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.2;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.2;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.2;
            if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        if (*(int *)(param_1 + 0x154) == 0x1e)
        {
            *(undefined4 *)(param_1 + 0x154) = 0x14;
            return;
        }
        break;
    case 0x32:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
            *(undefined4 *)(param_1 + 0x74) = 0x40000000;
            *(undefined4 *)(param_1 + 0x78) = 0x40000000;
            FUN_005f6fd0(3, 0, 0, 0);
            *(undefined4 *)(param_1 + 0x54) = 0x42340000;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0;
            FUN_0042c840(1);
        }
        *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
        sVar2                    = FUN_0042c7b0();
        if ((((sVar2 != 0) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) &&
             (*(int *)(param_1 + 0xf0) == 0)) &&
            ((uVar3 = FUN_0042c7b0(),
              (uVar3 & 2) != 0 || (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))))
        {
            *(undefined4 *)(param_1 + 0xf0) = 1;
        }
        if ((0x5a < *(int *)(param_1 + 0xe8)) || (*(int *)(param_1 + 0xf0) == 1))
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.15;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.2;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.2;
            if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        if (*(int *)(param_1 + 0x154) == 0x1e)
        {
            *(undefined4 *)(param_1 + 0x154) = 0x14;
            return;
        }
    }
    *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
    FUN_005f75a0();
    return;
}
