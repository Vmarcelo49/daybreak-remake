// ============================================
// Address:  0x006006b0
// Original: FUN_006006b0
// Status:   unreviewed
// ============================================

void __fastcall FUN_006006b0(int param_1)

{
    int iVar1;
    char cVar2;
    short sVar3;
    uint uVar4;
    float10 fVar5;
    undefined4 uVar6;

    uVar4 = FUN_0042c7b0();
    if (((uVar4 & 0x100) != 0) &&
        ((*(int *)(param_1 + 0x150) == 0x6e || (*(int *)(param_1 + 0x150) == 0x78))))
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
            *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
            FUN_005f6880(0);
            *(undefined1 *)(param_1 + 0x149) = 1;
            *(undefined1 *)(param_1 + 0x85)  = 0;
        }
        FUN_0042db10(0, 0x3dcccccd);
        *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.3;
        cVar2                      = FUN_005f6a90();
        if (((cVar2 == '\x01') && (*(float *)(param_1 + 0x40) < 0.0)) &&
            (*(float *)(param_1 + 0x40) = -*(float *)(param_1 + 0x40),
             6.0 < *(float *)(param_1 + 0x40)))
        {
            *(undefined4 *)(param_1 + 0x40) = 0x40c00000;
        }
        if (((0x5a < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
            (*(char *)(param_1 + 0x85) != '\0'))
        {
            FUN_0042c8b0(0x69);
            FUN_005f6db0(8, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        break;
    case 10:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
            FUN_005f6880(0);
            *(undefined1 *)(param_1 + 0x149) = 1;
            *(undefined1 *)(param_1 + 0x85)  = 0;
        }
        FUN_0042db10(0, 0x3dcccccd);
        *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.3;
        cVar2                      = FUN_005f6a90();
        if (((cVar2 == '\x01') && (*(float *)(param_1 + 0x40) < 0.0)) &&
            (*(float *)(param_1 + 0x40) = -*(float *)(param_1 + 0x40),
             6.0 < *(float *)(param_1 + 0x40)))
        {
            *(undefined4 *)(param_1 + 0x40) = 0x40c00000;
        }
        if (((0x5a < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
            (*(char *)(param_1 + 0x85) != '\0'))
        {
            FUN_0042c8b0(0x69);
            FUN_005f6db0(8, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        break;
    case 0x14:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x42200000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_005f7450(2, 0x41200000, 10, 1, 0);
            *(undefined4 *)(param_1 + 0x70) = 0x40000000;
            *(undefined4 *)(param_1 + 0x74) = 0x40000000;
            *(undefined4 *)(param_1 + 0x78) = 0x40000000;
        }
        if (0x19 < *(int *)(param_1 + 0x154))
        {
            FUN_0042c8b0(0x69);
            uVar6 = 0;
            uVar4 = FUN_0065d150(0);
            FUN_005f6ef0(4, 0, 0, 0, (float)(uVar4 % 0x168), uVar6);
            FUN_005f6fd0(7, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        sVar3 = FUN_0042c7b0();
        if ((sVar3 != 0) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01'))
        {
            FUN_0042c8b0(0x73);
            FUN_005f6db0(7, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        break;
    case 0x1e:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x42200000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_005f7450(2, 0x41200000, 10, 1, 0);
            *(undefined4 *)(param_1 + 0x70) = 0x40000000;
            *(undefined4 *)(param_1 + 0x74) = 0x40000000;
            *(undefined4 *)(param_1 + 0x78) = 0x40000000;
        }
        if (*(int *)(param_1 + 0x154) == 0x19)
        {
            FUN_0042c8b0(0x69);
            uVar4                     = FUN_0065d150();
            *(uint *)(param_1 + 0xe8) = uVar4 % 0x168;
            FUN_005f6ef0(5, 0, 0, 0, (float)*(int *)(param_1 + 0xe8), 0);
            FUN_005f6ef0(5, 0, 0, 0, (float)*(int *)(param_1 + 0xe8) + 180.0, 0);
            FUN_005f6fd0(7, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        sVar3 = FUN_0042c7b0();
        if ((sVar3 != 0) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01'))
        {
            FUN_0042c8b0(0x73);
            FUN_005f6db0(7, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        break;
    case 0x28:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x40000000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_005f6880(0);
            *(undefined4 *)(param_1 + 0x6c) = 0;
        }
        *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.05;
        if (*(float *)(param_1 + 0x40) < -4.0)
        {
            *(undefined4 *)(param_1 + 0x40) = 0xc0800000;
        }
        cVar2 = FUN_005f6a90();
        if (((cVar2 == '\x01') || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
            (600 < *(int *)(param_1 + 0x154)))
        {
            FUN_005f6db0(8, 0, 0, 0);
            FUN_0042c8b0(0x69);
            FUN_005f5e00();
            return;
        }
        if (1.0 < *(float *)(param_1 + 100))
        {
            *(float *)(param_1 + 100) = *(float *)(param_1 + 100) - 1.0;
        }
        if (*(float *)(param_1 + 100) < -1.0)
        {
            *(float *)(param_1 + 100) = *(float *)(param_1 + 100) + 1.0;
        }
        fVar5 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
        *(float *)(param_1 + 0x3c) = (float)(fVar5 * (float10) * (float *)(param_1 + 0x54));
        fVar5 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
        *(float *)(param_1 + 0x44) = (float)(fVar5 * (float10) * (float *)(param_1 + 0x54));
        break;
    case 0x32:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x41a00000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_005f6880(0);
        }
        if (*(int *)(param_1 + 0x154) == 1)
        {
            *(undefined4 *)(param_1 + 0x6c) = 0;
            *(undefined4 *)(param_1 + 0x40) = 0;
        }
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 0.5;
        if (*(float *)(param_1 + 0x54) < 2.0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x40000000;
        }
        *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.05;
        if (*(float *)(param_1 + 0x40) < -4.0)
        {
            *(undefined4 *)(param_1 + 0x40) = 0xc0800000;
        }
        cVar2 = FUN_005f6a90();
        if (((cVar2 == '\x01') || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
            (600 < *(int *)(param_1 + 0x154)))
        {
            FUN_005f6db0(8, 0, 0, 0);
            FUN_0042c8b0(0x69);
            FUN_005f5e00();
            return;
        }
        if (1.0 < *(float *)(param_1 + 100))
        {
            *(float *)(param_1 + 100) = *(float *)(param_1 + 100) - 1.0;
        }
        if (*(float *)(param_1 + 100) < -1.0)
        {
            *(float *)(param_1 + 100) = *(float *)(param_1 + 100) + 1.0;
        }
        fVar5 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
        *(float *)(param_1 + 0x3c) = (float)(fVar5 * (float10) * (float *)(param_1 + 0x54));
        fVar5 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
        *(float *)(param_1 + 0x44) = (float)(fVar5 * (float10) * (float *)(param_1 + 0x54));
        break;
    case 0x3c:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0x40) = 0;
            FUN_0042c840(1);
        }
        if (0x33 < *(int *)(param_1 + 0x154))
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
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0x40) = 0;
            FUN_0042c840(0);
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
            *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0x40) = 0;
            FUN_0042c840(1);
        }
        if (0x33 < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x5a:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x420c0000;
            FUN_005f6880(0);
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.75;
            *(float *)(param_1 + 0x34) = *(float *)(param_1 + 0x34) + 20.0;
        }
        if ((*(int *)(param_1 + 0xe8) == 0) && (cVar2 = FUN_005f6a90(), cVar2 == '\x01'))
        {
            *(undefined4 *)(param_1 + 0x34) = 0;
            *(undefined4 *)(param_1 + 0x6c) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0x3c) = 0;
            *(undefined4 *)(param_1 + 0x40) = 0;
            *(undefined4 *)(param_1 + 0x44) = 0;
            *(undefined4 *)(param_1 + 0xe8) = 1;
        }
        if (0 < *(int *)(param_1 + 0xe8))
        {
            *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
            if (*(int *)(param_1 + 0xe8) == 0x5a)
            {
                FUN_0042c8b0(0x6c);
                FUN_005f6db0(10, 0, 0x42200000, 0);
            }
            if (*(int *)(param_1 + 0xe8) == 300)
            {
                FUN_005f5e00();
                return;
            }
        }
        if (0x708 < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 100:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0;
            *(undefined4 *)(param_1 + 0x74) = 0;
            *(undefined4 *)(param_1 + 0x78) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0x6c) = 0;
            *(undefined4 *)(param_1 + 0x40) = 0;
            *(undefined4 *)(param_1 + 0xe8) = 0xff;
            *(undefined4 *)(param_1 + 0xec) = 0;
            FUN_0042c840(0);
            FUN_005f6880(0);
        }
        if (*(int *)(param_1 + 0xec) == 0)
        {
            if (1.0 <= *(float *)(param_1 + 0x70))
            {
                *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
                *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
                *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
                *(undefined4 *)(param_1 + 0xec) = 1;
                FUN_0042c840(5);
            }
            else
            {
                *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.05;
                *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.05;
                *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.05;
            }
        }
        if (0 < *(int *)(param_1 + 0xec))
        {
            if (*(int *)(param_1 + 0xec) % 10 == 0)
            {
                FUN_0042c800(0);
            }
            *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
        }
        if (0x96 < *(int *)(param_1 + 0xec))
        {
            FUN_0042c840(0);
            *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xf;
            if (*(int *)(param_1 + 0xe8) < 0)
            {
                FUN_005f5e00();
                return;
            }
        }
        FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8), 0xff, 0xff, 0xff);
        break;
    case 0x6e:
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
            *(undefined4 *)(param_1 + 0x70) = 0x40000000;
            *(undefined4 *)(param_1 + 0x74) = 0x40000000;
            *(undefined4 *)(param_1 + 0x78) = 0x40000000;
            *(undefined4 *)(param_1 + 0x54) = 0x41200000;
            FUN_005f7450(2, 0x41200000, 0x14, 1, 0);
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
        }
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + 1.5;
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            FUN_0042db10(0, 0x3d4ccccd);
            fVar5 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar5)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.05;
            }
            fVar5 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar5 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.05;
            }
        }
        if (((0x5a < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
            (cVar2 = FUN_005f6a90(), cVar2 == '\x01'))
        {
            FUN_005f6db0(7, 0, 0, 0);
            FUN_0042c8b0(0x69);
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
            *(undefined4 *)(param_1 + 0x70) = 0x40000000;
            *(undefined4 *)(param_1 + 0x74) = 0x40000000;
            *(undefined4 *)(param_1 + 0x78) = 0x40000000;
            *(undefined4 *)(param_1 + 0x54) = 0x41200000;
            FUN_005f7450(2, 0x41200000, 0x14, 1, 0);
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
        }
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + 2.25;
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            FUN_0042db10(0, 0x3d4ccccd);
            fVar5 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar5)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.05;
            }
            fVar5 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar5 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.05;
            }
        }
        if (((0x5a < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
            (cVar2 = FUN_005f6a90(), cVar2 == '\x01'))
        {
            FUN_005f6db0(7, 0, 0, 0);
            FUN_0042c8b0(0x69);
            FUN_005f5e00();
            return;
        }
        break;
    case 0x82:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0x40) = 0;
            FUN_0042c840(1);
        }
        if (0x33 < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x8c:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0xf4) = 0;
            *(undefined4 *)(param_1 + 0xf8) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0;
            *(undefined4 *)(param_1 + 0x74) = 0;
            *(undefined4 *)(param_1 + 0x78) = 0;
        }
        if ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x87) &&
            (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0xba))
        {
            FUN_005f5e00();
            return;
        }
        *(undefined4 *)(param_1 + 0x6c) = 0;
        if (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0xba)
        {
            if (1.0 <= *(float *)(param_1 + 0x70))
            {
                *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
                *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
                *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
            }
            else
            {
                *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.05;
                *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.05;
                *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.05;
            }
            if (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) != 0)
            {
                *(undefined4 *)(param_1 + 0x5c) =
                    *(undefined4 *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) +
                                    0x5c);
                *(undefined4 *)(param_1 + 100) =
                    *(undefined4 *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) +
                                    100);
                iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0);
                fVar5 = (float10)FUN_0065d010(
                    90.0 - (*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)));
                *(float *)(param_1 + 0x14) =
                    (float)(fVar5 * (float10)135.0 + (float10) * (float *)(iVar1 + 0x14));
                *(float *)(param_1 + 0x18) =
                    *(float *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) +
                               0x18) +
                    90.0;
                iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0);
                fVar5 = (float10)FUN_0065d050(
                    90.0 - (*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)));
                *(float *)(param_1 + 0x1c) =
                    (float)(fVar5 * (float10)135.0 + (float10) * (float *)(iVar1 + 0x1c));
            }
        }
        if (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0x87)
        {
            if (1.0 <= *(float *)(param_1 + 0x70))
            {
                *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
                *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
                *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
            }
            else
            {
                *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.05;
                *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.05;
                *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.05;
            }
            *(undefined4 *)(param_1 + 0x5c) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c);
            *(undefined4 *)(param_1 + 0x6c) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x100);
            *(undefined4 *)(param_1 + 100) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 100);
            *(undefined4 *)(param_1 + 0x14) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x14);
            *(float *)(param_1 + 0x18) =
                *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 85.0;
            *(undefined4 *)(param_1 + 0x1c) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x1c);
        }
        break;
    case 0x96:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0xf4) = 0;
            *(undefined4 *)(param_1 + 0xf8) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0;
            *(undefined4 *)(param_1 + 0x74) = 0;
            *(undefined4 *)(param_1 + 0x78) = 0;
        }
        if ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x87) &&
            (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0xba))
        {
            FUN_005f5e00();
            return;
        }
        *(undefined4 *)(param_1 + 0x6c) = 0;
        if (1.0 <= *(float *)(param_1 + 0x70))
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
        }
        else
        {
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.05;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.05;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.05;
        }
        if ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0xba) &&
            (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) != 0))
        {
            *(undefined4 *)(param_1 + 0x5c) = *(
                undefined4 *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) + 0x5c);
            *(undefined4 *)(param_1 + 100) = *(
                undefined4 *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) + 100);
            iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0);
            fVar5 = (float10)FUN_0065d010(90.0 -
                                          (*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)));
            *(float *)(param_1 + 0x14) =
                (float)(fVar5 * (float10)125.0 + (float10) * (float *)(iVar1 + 0x14));
            *(float *)(param_1 + 0x18) =
                *(float *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) + 0x18) +
                50.0;
            iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0);
            fVar5 = (float10)FUN_0065d050(90.0 -
                                          (*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)));
            *(float *)(param_1 + 0x1c) =
                (float)(fVar5 * (float10)125.0 + (float10) * (float *)(iVar1 + 0x1c));
        }
        if (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0x87)
        {
            *(undefined4 *)(param_1 + 0x5c) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c);
            *(undefined4 *)(param_1 + 100) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 100);
            *(undefined4 *)(param_1 + 0x6c) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x100);
            *(undefined4 *)(param_1 + 0x14) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x14);
            *(float *)(param_1 + 0x18) =
                *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 85.0;
            *(undefined4 *)(param_1 + 0x1c) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x1c);
        }
        break;
    case 0xa0:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0xf4) = 0;
            *(undefined4 *)(param_1 + 0xf8) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0;
            *(undefined4 *)(param_1 + 0x74) = 0;
            *(undefined4 *)(param_1 + 0x78) = 0;
        }
        if ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x87) &&
            (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0xba))
        {
            FUN_005f5e00();
            return;
        }
        *(undefined4 *)(param_1 + 0x6c) = 0;
        if (1.0 <= *(float *)(param_1 + 0x70))
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
        }
        else
        {
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.05;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.05;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.05;
        }
        if ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0xba) &&
            (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) != 0))
        {
            *(undefined4 *)(param_1 + 0x5c) = *(
                undefined4 *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) + 0x5c);
            *(undefined4 *)(param_1 + 100) = *(
                undefined4 *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) + 100);
            iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0);
            fVar5 = (float10)FUN_0065d010(90.0 -
                                          (*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)));
            *(float *)(param_1 + 0x14) =
                (float)(fVar5 * (float10)125.0 + (float10) * (float *)(iVar1 + 0x14));
            *(float *)(param_1 + 0x18) =
                *(float *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) + 0x18) +
                50.0;
            iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0);
            fVar5 = (float10)FUN_0065d050(90.0 -
                                          (*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)));
            *(float *)(param_1 + 0x1c) =
                (float)(fVar5 * (float10)125.0 + (float10) * (float *)(iVar1 + 0x1c));
        }
        if (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0x87)
        {
            *(undefined4 *)(param_1 + 0x5c) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c);
            *(undefined4 *)(param_1 + 100) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 100);
            *(undefined4 *)(param_1 + 0x6c) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x100);
            *(undefined4 *)(param_1 + 0x14) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x14);
            *(float *)(param_1 + 0x18) =
                *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 85.0;
            *(undefined4 *)(param_1 + 0x1c) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x1c);
        }
    }
    *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
    FUN_005f75a0();
    return;
}
