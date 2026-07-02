// ============================================
// Address:  0x0060fd10
// Original: FUN_0060fd10
// Status:   unreviewed
// ============================================

void __fastcall FUN_0060fd10(int param_1)

{
    float fVar1;
    char cVar2;
    short sVar3;
    int iVar4;
    float10 fVar5;
    float10 fVar6;

    switch (*(undefined4 *)(param_1 + 0x150))
    {
    case 0:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x54) = 0x42200000;
            *(undefined4 *)(param_1 + 0xe8) = 0xff;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0;
            FUN_0042c840(1);
            FUN_005f6880(0);
            *(undefined1 *)(param_1 + 0x149) = 1;
        }
        *(undefined4 *)(param_1 + 0x154) = 1;
        iVar4                            = *(int *)(param_1 + 0xec) + 1;
        *(int *)(param_1 + 0xec)         = iVar4;
        FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),
                     *(undefined1 *)(param_1 + 0xe8),
                     CONCAT31((int3)((uint)iVar4 >> 8), *(undefined1 *)(param_1 + 0xe8)),
                     0xff);
        *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.05;
        *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.05;
        *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.05;
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 0.75;
        fVar6                      = (float10)FUN_0065d010(*(undefined4 *)(param_1 + 0x6c));
        *(float *)(param_1 + 0x40) = (float)(fVar6 * (float10) * (float *)(param_1 + 0x54));
        if (*(char *)(param_1 + 0x84) != '\0')
        {
            *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) * 0.75;
        }
        if (*(float *)(param_1 + 0x54) < 3.0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x40400000;
        }
        if (((0x28 < *(int *)(param_1 + 0xec)) || (*(char *)(param_1 + 0x85) == '\x01')) ||
            (sVar3 = FUN_0042c7b0(), sVar3 != 0))
        {
            *(undefined4 *)(param_1 + 0xf0) = 1;
        }
        if (0 < *(int *)(param_1 + 0xf0))
        {
            *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -5;
            if (*(int *)(param_1 + 0xe8) < 0x40)
            {
                FUN_0042c840(0);
            }
            if (*(int *)(param_1 + 0xe8) < 0)
            {
                *(undefined4 *)(param_1 + 0xe8) = 0;
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 10:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x54) = 0x42340000;
            *(undefined4 *)(param_1 + 0xe8) = 0xff;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0;
            FUN_0042c840(1);
            FUN_005f6880(0);
            *(undefined1 *)(param_1 + 0x149) = 1;
        }
        *(undefined4 *)(param_1 + 0x154) = 1;
        iVar4                            = *(int *)(param_1 + 0xec) + 1;
        *(int *)(param_1 + 0xec)         = iVar4;
        FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),
                     *(undefined1 *)(param_1 + 0xe8),
                     CONCAT31((int3)((uint)iVar4 >> 8), *(undefined1 *)(param_1 + 0xe8)),
                     0xff);
        *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.1;
        *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.1;
        *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.1;
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 0.65;
        fVar6                      = (float10)FUN_0065d010(*(undefined4 *)(param_1 + 0x6c));
        *(float *)(param_1 + 0x40) = (float)(fVar6 * (float10) * (float *)(param_1 + 0x54));
        if (*(char *)(param_1 + 0x84) != '\0')
        {
            *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) * 0.75;
        }
        if (*(float *)(param_1 + 0x54) < 3.0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x40400000;
        }
        if (((0x28 < *(int *)(param_1 + 0xec)) || (*(char *)(param_1 + 0x85) == '\x01')) ||
            (sVar3 = FUN_0042c7b0(), sVar3 != 0))
        {
            *(undefined4 *)(param_1 + 0xf0) = 1;
        }
        if (0 < *(int *)(param_1 + 0xf0))
        {
            *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -5;
            if (*(int *)(param_1 + 0xe8) < 0x40)
            {
                FUN_0042c840(0);
            }
            if (*(int *)(param_1 + 0xe8) < 0)
            {
                *(undefined4 *)(param_1 + 0xe8) = 0;
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 0x14:
        if ((0x1c1 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
            (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 0x1d0))
        {
            *(undefined4 *)(param_1 + 100) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 100);
            *(undefined4 *)(param_1 + 0x5c) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c);
            iVar4 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
            fVar6 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
            fVar1 = *(float *)(iVar4 + 0x14);
            fVar5 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100) +
                                          90.0);
            *(float *)(param_1 + 0x14) =
                (float)(fVar5 * (float10)50.0 +
                        (float10)(float)(fVar6 * (float10)60.0 + (float10)fVar1));
            *(float *)(param_1 + 0x18) =
                *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 70.0;
            iVar4 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
            fVar6 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
            fVar1 = *(float *)(iVar4 + 0x1c);
            fVar5 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100) +
                                          90.0);
            *(float *)(param_1 + 0x1c) =
                (float)(fVar5 * (float10)50.0 +
                        (float10)(float)(fVar6 * (float10)60.0 + (float10)fVar1));
        }
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3dcccccd;
            *(undefined4 *)(param_1 + 0x78) = 0x3dcccccd;
            *(undefined4 *)(param_1 + 0x54) = 0x3c23d70a;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            FUN_0042c840(0);
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
        if ((0x1c1 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
            (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 0x1d0))
        {
            *(undefined4 *)(param_1 + 100) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 100);
            *(undefined4 *)(param_1 + 0x5c) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c);
            iVar4 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
            fVar6 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
            fVar1 = *(float *)(iVar4 + 0x14);
            fVar5 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100) +
                                          90.0);
            *(float *)(param_1 + 0x14) =
                (float)(fVar5 * (float10)50.0 +
                        (float10)(float)(fVar6 * (float10)60.0 + (float10)fVar1));
            *(float *)(param_1 + 0x18) =
                *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 70.0;
            iVar4 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
            fVar6 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
            fVar1 = *(float *)(iVar4 + 0x1c);
            fVar5 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100) +
                                          90.0);
            *(float *)(param_1 + 0x1c) =
                (float)(fVar5 * (float10)50.0 +
                        (float10)(float)(fVar6 * (float10)60.0 + (float10)fVar1));
        }
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
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
    case 0x28:
        if ((0x1c1 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
            (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 0x1d0))
        {
            *(undefined4 *)(param_1 + 100) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 100);
            *(undefined4 *)(param_1 + 0x5c) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c);
            iVar4 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
            fVar6 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
            fVar1 = *(float *)(iVar4 + 0x14);
            fVar5 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100) +
                                          90.0);
            *(float *)(param_1 + 0x14) =
                (float)(fVar5 * (float10)50.0 +
                        (float10)(float)(fVar6 * (float10)60.0 + (float10)fVar1));
            *(float *)(param_1 + 0x18) =
                *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 70.0;
            iVar4 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
            fVar6 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
            fVar1 = *(float *)(iVar4 + 0x1c);
            fVar5 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100) +
                                          90.0);
            *(float *)(param_1 + 0x1c) =
                (float)(fVar5 * (float10)50.0 +
                        (float10)(float)(fVar6 * (float10)60.0 + (float10)fVar1));
        }
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3fa00000;
            *(undefined4 *)(param_1 + 0x74) = 0x3fa00000;
            *(undefined4 *)(param_1 + 0x78) = 0x3fa00000;
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
    case 0x32:
        if ((0x1c1 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
            (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 0x1d0))
        {
            *(undefined4 *)(param_1 + 100) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 100);
            *(undefined4 *)(param_1 + 0x5c) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c);
            iVar4 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
            fVar6 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
            fVar1 = *(float *)(iVar4 + 0x14);
            fVar5 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100) +
                                          90.0);
            *(float *)(param_1 + 0x14) =
                (float)((float10)(float)(fVar6 * (float10)60.0 + (float10)fVar1) -
                        fVar5 * (float10)50.0);
            *(float *)(param_1 + 0x18) =
                *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 70.0;
            iVar4 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
            fVar6 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
            fVar1 = *(float *)(iVar4 + 0x1c);
            fVar5 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100) +
                                          90.0);
            *(float *)(param_1 + 0x1c) =
                (float)((float10)(float)(fVar6 * (float10)60.0 + (float10)fVar1) -
                        fVar5 * (float10)50.0);
        }
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3dcccccd;
            *(undefined4 *)(param_1 + 0x78) = 0x3dcccccd;
            *(undefined4 *)(param_1 + 0x54) = 0x3c23d70a;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            FUN_0042c840(0);
        }
        *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
        if (*(int *)(param_1 + 0x154) == 0x29)
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x3c:
        if ((0x1c1 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
            (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 0x1d0))
        {
            *(undefined4 *)(param_1 + 100) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 100);
            *(undefined4 *)(param_1 + 0x5c) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c);
            iVar4 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
            fVar6 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
            fVar1 = *(float *)(iVar4 + 0x14);
            fVar5 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100) +
                                          90.0);
            *(float *)(param_1 + 0x14) =
                (float)((float10)(float)(fVar6 * (float10)60.0 + (float10)fVar1) -
                        fVar5 * (float10)50.0);
            *(float *)(param_1 + 0x18) =
                *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 70.0;
            iVar4 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
            fVar6 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
            fVar1 = *(float *)(iVar4 + 0x1c);
            fVar5 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100) +
                                          90.0);
            *(float *)(param_1 + 0x1c) =
                (float)((float10)(float)(fVar6 * (float10)60.0 + (float10)fVar1) -
                        fVar5 * (float10)50.0);
        }
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
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
    case 0x46:
        if ((0x1c1 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
            (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 0x1d0))
        {
            *(undefined4 *)(param_1 + 100) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 100);
            *(undefined4 *)(param_1 + 0x5c) =
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c);
            iVar4 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
            fVar6 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
            fVar1 = *(float *)(iVar4 + 0x14);
            fVar5 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100) +
                                          90.0);
            *(float *)(param_1 + 0x14) =
                (float)((float10)(float)(fVar6 * (float10)60.0 + (float10)fVar1) -
                        fVar5 * (float10)50.0);
            *(float *)(param_1 + 0x18) =
                *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 70.0;
            iVar4 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
            fVar6 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
            fVar1 = *(float *)(iVar4 + 0x1c);
            fVar5 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100) +
                                          90.0);
            *(float *)(param_1 + 0x1c) =
                (float)((float10)(float)(fVar6 * (float10)60.0 + (float10)fVar1) -
                        fVar5 * (float10)50.0);
        }
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3fa00000;
            *(undefined4 *)(param_1 + 0x74) = 0x3fa00000;
            *(undefined4 *)(param_1 + 0x78) = 0x3fa00000;
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
    case 0x50:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3e4ccccd;
            *(undefined4 *)(param_1 + 0x74) = 0x3e4ccccd;
            *(undefined4 *)(param_1 + 0x78) = 0x3e4ccccd;
            *(undefined4 *)(param_1 + 0x54) = 0x42480000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0xff;
            *(undefined4 *)(param_1 + 0xec) = 0;
        }
        *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.01;
        *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.01;
        *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.01;
        if (0.5 < *(float *)(param_1 + 0x70))
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
        }
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
        cVar2                    = FUN_005f6a90();
        if (cVar2 == '\x01')
        {
            FUN_005f5e00();
            return;
        }
        if (0x28 < *(int *)(param_1 + 0xec))
        {
            FUN_0042c840(0);
            *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xd;
            if (*(int *)(param_1 + 0xe8) < 0)
            {
                FUN_005f5e00();
                return;
            }
        }
        FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),
                     0xff,
                     *(undefined1 *)(param_1 + 0xe8),
                     *(undefined1 *)(param_1 + 0xe8));
        if (*(int *)(param_1 + 0x154) == 0x14)
        {
            return;
        }
        break;
    case 0x5a:
        *(undefined4 *)(param_1 + 100) =
            *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 100);
        *(undefined4 *)(param_1 + 0x5c) =
            *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c);
        iVar4 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
        fVar6 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
        *(float *)(param_1 + 0x14) =
            (float)(fVar6 * (float10)70.0 + (float10) * (float *)(iVar4 + 0x14));
        *(float *)(param_1 + 0x18) =
            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 55.0;
        iVar4 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
        fVar6 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
        *(float *)(param_1 + 0x1c) =
            (float)(fVar6 * (float10)70.0 + (float10) * (float *)(iVar4 + 0x1c));
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3dcccccd;
            *(undefined4 *)(param_1 + 0x78) = 0x3dcccccd;
            *(undefined4 *)(param_1 + 0x54) = 0x3c23d70a;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            FUN_0042c840(0);
        }
        *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
        if (*(int *)(param_1 + 0x154) == 0x29)
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 100:
        *(undefined4 *)(param_1 + 100) =
            *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 100);
        *(undefined4 *)(param_1 + 0x5c) =
            *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c);
        iVar4 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
        fVar6 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
        *(float *)(param_1 + 0x14) =
            (float)(fVar6 * (float10)70.0 + (float10) * (float *)(iVar4 + 0x14));
        *(float *)(param_1 + 0x18) =
            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 55.0;
        iVar4 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
        fVar6 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
        *(float *)(param_1 + 0x1c) =
            (float)(fVar6 * (float10)70.0 + (float10) * (float *)(iVar4 + 0x1c));
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
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
    case 0x6e:
        *(undefined4 *)(param_1 + 100) =
            *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 100);
        *(undefined4 *)(param_1 + 0x5c) =
            *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c);
        iVar4 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
        fVar6 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
        *(float *)(param_1 + 0x14) =
            (float)(fVar6 * (float10)60.0 + (float10) * (float *)(iVar4 + 0x14));
        *(float *)(param_1 + 0x18) =
            *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 70.0;
        iVar4 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
        fVar6 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
        *(float *)(param_1 + 0x1c) =
            (float)(fVar6 * (float10)60.0 + (float10) * (float *)(iVar4 + 0x1c));
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3fa00000;
            *(undefined4 *)(param_1 + 0x74) = 0x3fa00000;
            *(undefined4 *)(param_1 + 0x78) = 0x3fa00000;
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
    }
    *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
    FUN_005f75a0();
    return;
}
