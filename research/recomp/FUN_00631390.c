// ============================================
// Address:  0x00631390
// Original: FUN_00631390
// Status:   unreviewed
// ============================================

void __fastcall FUN_00631390(int param_1)

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
        case 0x1e:
        case 0x28:
        case 0x3c:
        case 0x6e:
        case 0x78:
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
            fVar4 = (float10)FUN_0042dac0(3);
            if (((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)10.0) &&
                (fVar4 = (float10)FUN_0042dac0(3),
                 (float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4))
            {
                fVar4                      = (float10)FUN_0042dac0(3);
                *(float *)(param_1 + 0x6c) = (float)fVar4;
            }
            fVar4 = (float10)FUN_0042dac0(3);
            if ((float10)10.0 <= (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 10.0;
            }
            fVar4 = (float10)FUN_0042dac0(3);
            fVar4 = (float10) * (float *)(param_1 + 0x6c) - fVar4;
            if (fVar4 < (float10)-10.0 != (fVar4 == (float10)-10.0))
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 10.0;
            }
            FUN_0042db10(0, 0x40a00000);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_005f6fd0(2, 0, 0, 0);
            *(undefined4 *)(param_1 + 0x54) = 0x42a00000;
            FUN_0042c840(1);
        }
        if ((*(int *)(param_1 + 0xe8) == 0) &&
            (((sVar2 = FUN_0042c7b0(), sVar2 != 0 || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) ||
              (0xb4 < *(int *)(param_1 + 0x154)))))
        {
            *(undefined4 *)(param_1 + 0xe8) = 1;
            *(undefined4 *)(param_1 + 0x54) = 0;
        }
        if (*(int *)(param_1 + 0xe8) == 1)
        {
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
    case 10:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            fVar4 = (float10)FUN_0042dac0(3);
            if (((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)10.0) &&
                (fVar4 = (float10)FUN_0042dac0(3),
                 (float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4))
            {
                fVar4                      = (float10)FUN_0042dac0(3);
                *(float *)(param_1 + 0x6c) = (float)fVar4;
            }
            fVar4 = (float10)FUN_0042dac0(3);
            if ((float10)10.0 <= (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 10.0;
            }
            fVar4 = (float10)FUN_0042dac0(3);
            fVar4 = (float10) * (float *)(param_1 + 0x6c) - fVar4;
            if (fVar4 < (float10)-10.0 != (fVar4 == (float10)-10.0))
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 10.0;
            }
            FUN_0042db10(0, 0x40a00000);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_005f6fd0(2, 0, 0, 0);
            *(undefined4 *)(param_1 + 0x54) = 0x43160000;
            FUN_0042c840(1);
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            if (*(int *)(param_1 + 0x154) % 5 == 0)
            {
                FUN_005f6fd0(10, 0, 0, 0);
            }
            sVar2 = FUN_0042c7b0();
            if (((sVar2 != 0) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) ||
                (0xb4 < *(int *)(param_1 + 0x154)))
            {
                *(undefined4 *)(param_1 + 0xe8) = 1;
                *(undefined4 *)(param_1 + 0x54) = 0;
            }
        }
        if (*(int *)(param_1 + 0xe8) == 1)
        {
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
    case 0x14:
        *(undefined4 *)(param_1 + 0x54) = 0;
        if (5 < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x1e:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            fVar4 = (float10)FUN_0042dac0(3);
            if (((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)10.0) &&
                (fVar4 = (float10)FUN_0042dac0(3),
                 (float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4))
            {
                fVar4                      = (float10)FUN_0042dac0(3);
                *(float *)(param_1 + 0x6c) = (float)fVar4;
            }
            fVar4 = (float10)FUN_0042dac0(3);
            if ((float10)10.0 <= (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 10.0;
            }
            fVar4 = (float10)FUN_0042dac0(3);
            fVar4 = (float10) * (float *)(param_1 + 0x6c) - fVar4;
            if (fVar4 < (float10)-10.0 != (fVar4 == (float10)-10.0))
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 10.0;
            }
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_005f6fd0(2, 0, 0, 0);
            *(undefined4 *)(param_1 + 0x54) = 0x43160000;
            FUN_0042c840(1);
        }
        sVar2 = FUN_0042c7b0();
        if (((sVar2 != 0) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) ||
            (0xb4 < *(int *)(param_1 + 0x154)))
        {
            FUN_005f6fd0(9, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        break;
    case 0x28:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            fVar4 = (float10)FUN_0042dac0(3);
            if (((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)10.0) &&
                (fVar4 = (float10)FUN_0042dac0(3),
                 (float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4))
            {
                fVar4                      = (float10)FUN_0042dac0(3);
                *(float *)(param_1 + 0x6c) = (float)fVar4;
            }
            fVar4 = (float10)FUN_0042dac0(3);
            if ((float10)10.0 <= (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 10.0;
            }
            fVar4 = (float10)FUN_0042dac0(3);
            fVar4 = (float10) * (float *)(param_1 + 0x6c) - fVar4;
            if (fVar4 < (float10)-10.0 != (fVar4 == (float10)-10.0))
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 10.0;
            }
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_005f6fd0(2, 0, 0, 0);
            *(undefined4 *)(param_1 + 0x54) = 0x43610000;
            FUN_0042c840(1);
        }
        sVar2 = FUN_0042c7b0();
        if (((sVar2 != 0) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) ||
            (0xb4 < *(int *)(param_1 + 0x154)))
        {
            FUN_005f6fd0(9, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        break;
    case 0x32:
        *(undefined4 *)(param_1 + 0x54) = 0;
        if (5 < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x3c:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_005f6fd0(7, 0, 0, 0);
            *(undefined4 *)(param_1 + 0x54) = 0x43fa0000;
            FUN_0042c840(1);
        }
        if (*(int *)(param_1 + 0x154) == 1)
        {
            FUN_0042c840(1);
        }
        sVar2 = FUN_0042c7b0();
        if (((sVar2 != 0) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) ||
            (0xb4 < *(int *)(param_1 + 0x154)))
        {
            FUN_005f6fd0(8, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        break;
    case 0x46:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x74) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x78) = 0x3d4ccccd;
        }
        *(undefined4 *)(param_1 + 0x54) = 0;
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x70) =
            (float)(fVar4 * (float10)0.2 + (float10) * (float *)(param_1 + 0x70));
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x74) =
            (float)(fVar4 * (float10)0.2 + (float10) * (float *)(param_1 + 0x74));
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x78) =
            (float)(fVar4 * (float10)0.2 + (float10) * (float *)(param_1 + 0x78));
        if (10 < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x50:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x74) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x78) = 0x3d4ccccd;
        }
        *(undefined4 *)(param_1 + 0x54) = 0;
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x70) =
            (float)(fVar4 * (float10)0.5 + (float10) * (float *)(param_1 + 0x70));
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x74) =
            (float)(fVar4 * (float10)0.5 + (float10) * (float *)(param_1 + 0x74));
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x78) =
            (float)(fVar4 * (float10)0.5 + (float10) * (float *)(param_1 + 0x78));
        if (0x1c < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x5a:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x74) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x78) = 0x3d4ccccd;
        }
        *(undefined4 *)(param_1 + 0x54) = 0;
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x70) =
            (float)(fVar4 * (float10)0.5 + (float10) * (float *)(param_1 + 0x70));
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x74) =
            (float)(fVar4 * (float10)0.5 + (float10) * (float *)(param_1 + 0x74));
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x78) =
            (float)(fVar4 * (float10)0.5 + (float10) * (float *)(param_1 + 0x78));
        if (5 < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 100:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x74) = 0x3d4ccccd;
            *(undefined4 *)(param_1 + 0x78) = 0x3d4ccccd;
        }
        *(undefined4 *)(param_1 + 0x54) = 0;
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x70) =
            (float)(fVar4 * (float10)0.025 + (float10) * (float *)(param_1 + 0x70));
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x74) =
            (float)(fVar4 * (float10)0.025 + (float10) * (float *)(param_1 + 0x74));
        fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x78) =
            (float)(fVar4 * (float10)0.025 + (float10) * (float *)(param_1 + 0x78));
        if (0x1c < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x6e:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            fVar4 = (float10)FUN_0042dac0(3);
            if (((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)10.0) &&
                (fVar4 = (float10)FUN_0042dac0(3),
                 (float10)-10.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4))
            {
                fVar4                      = (float10)FUN_0042dac0(3);
                *(float *)(param_1 + 0x6c) = (float)fVar4;
            }
            fVar4 = (float10)FUN_0042dac0(3);
            if ((float10)10.0 <= (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 10.0;
            }
            fVar4 = (float10)FUN_0042dac0(3);
            fVar4 = (float10) * (float *)(param_1 + 0x6c) - fVar4;
            if (fVar4 < (float10)-10.0 != (fVar4 == (float10)-10.0))
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 10.0;
            }
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_005f6fd0(7, 0, 0, 0);
            *(undefined4 *)(param_1 + 0x54) = 0x43480000;
            FUN_0042c840(1);
        }
        if (*(int *)(param_1 + 0x154) == 1)
        {
            FUN_0042c840(1);
        }
        sVar2 = FUN_0042c7b0();
        if (((sVar2 != 0) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) ||
            (0xb4 < *(int *)(param_1 + 0x154)))
        {
            FUN_005f6fd0(8, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        break;
    case 0x78:
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
            FUN_0042db10(0, 0x40a00000);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_005f6fd0(2, 0, 0, 0);
            *(undefined4 *)(param_1 + 0x54) = 0x42a00000;
            FUN_0042c840(1);
        }
        if ((*(int *)(param_1 + 0xe8) == 0) &&
            (((sVar2 = FUN_0042c7b0(), sVar2 != 0 || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) ||
              (0xb4 < *(int *)(param_1 + 0x154)))))
        {
            *(undefined4 *)(param_1 + 0xe8) = 1;
            *(undefined4 *)(param_1 + 0x54) = 0;
        }
        if (*(int *)(param_1 + 0xe8) == 1)
        {
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
            if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0))
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
