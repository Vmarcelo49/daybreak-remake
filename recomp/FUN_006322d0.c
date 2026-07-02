// ============================================
// Address:  0x006322d0
// Original: FUN_006322d0
// Status:   unreviewed
// ============================================

void __fastcall FUN_006322d0(int param_1)

{
    char cVar1;
    uint uVar2;
    float10 fVar3;

    uVar2 = FUN_0042c7b0();
    if ((uVar2 & 0x100) != 0)
    {
        switch (*(undefined4 *)(param_1 + 0x150))
        {
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
            *(undefined4 *)(param_1 + 0x70) = 0x40000000;
            *(undefined4 *)(param_1 + 0x74) = 0x40000000;
            *(undefined4 *)(param_1 + 0x78) = 0x40000000;
            *(undefined4 *)(param_1 + 0x54) = 0x42700000;
            FUN_0042c840(1);
        }
        cVar1 = FUN_005f6a90();
        if ((cVar1 == '\x01') || (10 < *(int *)(param_1 + 0x154)))
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
        break;
    case 0x14:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x42200000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x30) = 0x42700000;
            *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
            *(undefined4 *)(param_1 + 0x74) = 0x3fc00000;
            *(undefined4 *)(param_1 + 0x78) = 0x3fc00000;
        }
        cVar1 = FUN_005f6a90();
        if ((cVar1 == '\x01') || (0x1e < *(int *)(param_1 + 0x154)))
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
    case 0x1e:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x42700000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x30) = 0x42700000;
            *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
            *(undefined4 *)(param_1 + 0x74) = 0x3fc00000;
            *(undefined4 *)(param_1 + 0x78) = 0x3fc00000;
        }
        cVar1 = FUN_005f6a90();
        if ((cVar1 == '\x01') || (0x1e < *(int *)(param_1 + 0x154)))
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
    case 0x28:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined1 *)(param_1 + 0x149) = 1;
            *(undefined1 *)(param_1 + 0x85)  = 0;
            *(undefined4 *)(param_1 + 0x54)  = 0x42700000;
            FUN_0042c840(99);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x30) = 0x42340000;
        }
        *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
        if (10 < *(int *)(param_1 + 0xe8))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_0042c800(0);
        }
        if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154)))
        {
            FUN_0042db10(0, 0x3f800000);
        }
        uVar2 = *(uint *)(param_1 + 0x154) & 0x80000001;
        if ((int)uVar2 < 0)
        {
            uVar2 = (uVar2 - 1 | 0xfffffffe) + 1;
        }
        if (uVar2 == 0)
        {
            FUN_005f6fd0(5, 0, 0, 0);
            FUN_005f6fd0(6, 0, 0, 0);
        }
        if (*(char *)(param_1 + 0x84) == '\0')
        {
            *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.5;
            *(int *)(param_1 + 0xec)   = *(int *)(param_1 + 0xec) + 1;
            if (0x14 < *(int *)(param_1 + 0xec))
            {
                FUN_005f5e00();
                return;
            }
        }
        if (*(char *)(param_1 + 0x84) != '\0')
        {
            *(undefined4 *)(param_1 + 0x40) = 0;
        }
        if (0x78 < *(int *)(param_1 + 0x154))
        {
            FUN_0042c840(0);
            FUN_005f5e00();
            return;
        }
        break;
    case 0x32:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            uVar2                      = FUN_0065d150();
            *(float *)(param_1 + 0x30) = (float)(uVar2 % 0x32) + -25.0;
            uVar2                      = FUN_0065d150();
            *(float *)(param_1 + 0x34) = (float)(uVar2 % 0x32) + -25.0;
        }
        *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) * 0.8;
        *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.1;
        *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) * 0.8;
        if (*(float *)(param_1 + 0x78) < 0.05)
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x3c:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            FUN_0042c840(1);
            FUN_0042c800(0);
            *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
            *(undefined4 *)(param_1 + 0xe8) = 0xff;
            uVar2                           = FUN_0065d150();
            *(float *)(param_1 + 0x30)      = (float)(uVar2 % 0x168);
        }
        fVar3 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 4.0);
        *(float *)(param_1 + 0x78) =
            (float)(fVar3 * (float10)0.1 + (float10) * (float *)(param_1 + 0x78));
        fVar3 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 4.0);
        *(float *)(param_1 + 0x74) =
            (float)(fVar3 * (float10)0.1 + (float10) * (float *)(param_1 + 0x74));
        fVar3 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 4.0);
        *(float *)(param_1 + 0x70) =
            (float)(fVar3 * (float10)0.1 + (float10) * (float *)(param_1 + 0x70));
        if (*(int *)(param_1 + 0x154) == 6)
        {
            FUN_0042c840(0);
        }
        if ((10 < *(int *)(param_1 + 0x154)) &&
            (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xd,
             *(int *)(param_1 + 0xe8) < 0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0;
        }
        FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),
                     *(undefined1 *)(param_1 + 0xe8),
                     *(undefined1 *)(param_1 + 0xe8),
                     0xff);
        if (*(int *)(param_1 + 0xe8) < 1)
        {
            FUN_005f5e00();
            return;
        }
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
    }
    *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
    FUN_005f75a0();
    return;
}
