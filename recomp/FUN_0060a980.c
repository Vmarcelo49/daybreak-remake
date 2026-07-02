// ============================================
// Address:  0x0060a980
// Original: FUN_0060a980
// Status:   unreviewed
// ============================================

void __fastcall FUN_0060a980(int param_1)

{
    int iVar1;
    char cVar2;
    short sVar3;
    uint uVar4;
    undefined4 uVar5;
    float10 fVar6;

    uVar4 = FUN_0042c7b0();
    if ((uVar4 & 0x100) != 0)
    {
        switch (*(undefined4 *)(param_1 + 0x150))
        {
        case 0:
        case 10:
        case 0x14:
        case 0x1e:
        case 0x28:
        case 0x32:
            FUN_0042c800(0);
            FUN_0042c840(1);
            break;
        case 0x5a:
        case 100:
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
            FUN_005f71f0();
            *(undefined4 *)(param_1 + 0x54) = 0;
            FUN_0042c840(0);
            FUN_0042c800(0);
            *(undefined4 *)(param_1 + 0xe8) = 0;
        }
        if (*(int *)(param_1 + 0x154) == 0x3c)
        {
            FUN_0042c840(1);
        }
        sVar3 = FUN_0042c7b0();
        if (sVar3 != 0)
        {
            *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
            if (*(int *)(param_1 + 0xe8) == 1)
            {
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64) = 0x168;
                *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) =
                    *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) + 1;
                if (3 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60))
                {
                    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) = 3;
                }
                *(undefined4 *)(param_1 + 0xec) =
                    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60);
                if (*(short *)(param_1 + 0x88 + *(int *)(*(int *)(param_1 + 0x38) + 8) * 2) == 0)
                {
                    FUN_005f71f0();
                }
            }
            if (*(int *)(param_1 + 0xec) == 1)
            {
                if (*(int *)(param_1 + 0xe8) < 0x46)
                {
                    FUN_0042db10(0, 0x43340000);
                }
                if (((*(int *)(param_1 + 0xe8) % 10 == 0) && (10 < *(int *)(param_1 + 0xe8))) &&
                    (*(int *)(param_1 + 0xe8) < 0x47))
                {
                    FUN_0042c8b0(0x48);
                    fVar6 = (float10)FUN_0042da80();
                    FUN_005f6ef0(9, 0, 0x428c0000, 0, 0, (float)fVar6);
                }
                if (0x46 < *(int *)(param_1 + 0xe8))
                {
                    if (*(float *)(param_1 + 0x70) <= 0.0)
                    {
                        FUN_005f5e00();
                        return;
                    }
                    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.05;
                    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.05;
                    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.05;
                }
            }
            if (*(int *)(param_1 + 0xec) == 2)
            {
                if (*(int *)(param_1 + 0xe8) < 0x5a)
                {
                    FUN_0042db10(0, 0x43340000);
                }
                if (((*(int *)(param_1 + 0xe8) % 0x1e == 0) && (10 < *(int *)(param_1 + 0xe8))) &&
                    (*(int *)(param_1 + 0xe8) < 0x5b))
                {
                    FUN_0042c8b0(0x50);
                    fVar6 = (float10)FUN_0042da80();
                    FUN_005f6ef0(10, 0, 0x428c0000, 0, 0, (float)fVar6);
                }
                if (0x5a < *(int *)(param_1 + 0xe8))
                {
                    if (*(float *)(param_1 + 0x70) <= 0.0)
                    {
                        FUN_005f5e00();
                        return;
                    }
                    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.05;
                    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.05;
                    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.05;
                }
            }
            if (*(int *)(param_1 + 0xec) == 3)
            {
                if (*(int *)(param_1 + 0xe8) == 1)
                {
                    FUN_0042da80();
                    uVar5                           = FUN_0066b668();
                    *(undefined4 *)(param_1 + 0xf0) = uVar5;
                    FUN_0042db10(0, 0x43340000);
                }
                if ((*(int *)(param_1 + 0xe8) % 0xf == 0) && (*(int *)(param_1 + 0xe8) < 0x5b))
                {
                    if (*(int *)(param_1 + 0xe8) == 0xf)
                    {
                        FUN_0042c8b0(0x52);
                    }
                    FUN_005f6ef0(0xb, 0, 0x428c0000, 0, 0, (float)*(int *)(param_1 + 0xf0));
                }
                if (0x5a < *(int *)(param_1 + 0xe8))
                {
                    if (*(float *)(param_1 + 0x70) <= 0.0)
                    {
                        FUN_005f5e00();
                        return;
                    }
                    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.05;
                    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.05;
                    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.05;
                }
            }
        }
        if (0x1c20 < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 10:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            FUN_005f71f0();
            *(undefined4 *)(param_1 + 0x54) = 0;
            FUN_0042c840(0);
            FUN_0042c800(0);
            *(undefined4 *)(param_1 + 0xe8) = 0;
        }
        if (*(int *)(param_1 + 0x154) == 0x3c)
        {
            FUN_0042c840(1);
        }
        sVar3 = FUN_0042c7b0();
        if (sVar3 != 0)
        {
            *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
            if (*(int *)(param_1 + 0xe8) == 1)
            {
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64) = 0x168;
                *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) =
                    *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) + 1;
                if (3 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60))
                {
                    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) = 3;
                }
                *(undefined4 *)(param_1 + 0xec) =
                    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60);
                if (*(short *)(param_1 + 0x88 + *(int *)(*(int *)(param_1 + 0x38) + 8) * 2) == 0)
                {
                    FUN_005f71f0();
                }
            }
            if (*(int *)(param_1 + 0xec) == 1)
            {
                if (*(int *)(param_1 + 0xe8) < 0x46)
                {
                    FUN_0042db10(0, 0x43340000);
                }
                if (((*(int *)(param_1 + 0xe8) % 10 == 0) && (10 < *(int *)(param_1 + 0xe8))) &&
                    (*(int *)(param_1 + 0xe8) < 0x47))
                {
                    FUN_0042c8b0(0x48);
                    fVar6 = (float10)FUN_0042da80();
                    FUN_005f6ef0(9, 0, 0x428c0000, 0, 0, (float)fVar6);
                }
                if (0x46 < *(int *)(param_1 + 0xe8))
                {
                    if (*(float *)(param_1 + 0x70) <= 0.0)
                    {
                        FUN_005f5e00();
                        return;
                    }
                    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.05;
                    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.05;
                    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.05;
                }
            }
            if (*(int *)(param_1 + 0xec) == 2)
            {
                if (*(int *)(param_1 + 0xe8) < 0x5a)
                {
                    FUN_0042db10(0, 0x43340000);
                }
                if (((*(int *)(param_1 + 0xe8) % 0x1e == 0) && (10 < *(int *)(param_1 + 0xe8))) &&
                    (*(int *)(param_1 + 0xe8) < 0x5b))
                {
                    FUN_0042c8b0(0x50);
                    fVar6 = (float10)FUN_0042da80();
                    FUN_005f6ef0(10, 0, 0x428c0000, 0, 0, (float)fVar6);
                }
                if (0x5a < *(int *)(param_1 + 0xe8))
                {
                    if (*(float *)(param_1 + 0x70) <= 0.0)
                    {
                        FUN_005f5e00();
                        return;
                    }
                    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.05;
                    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.05;
                    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.05;
                }
            }
            if (*(int *)(param_1 + 0xec) == 3)
            {
                if (*(int *)(param_1 + 0xe8) == 1)
                {
                    FUN_0042da80();
                    uVar5                           = FUN_0066b668();
                    *(undefined4 *)(param_1 + 0xf0) = uVar5;
                    FUN_0042db10(0, 0x43340000);
                }
                if ((*(int *)(param_1 + 0xe8) % 0xf == 0) && (*(int *)(param_1 + 0xe8) < 0x5b))
                {
                    if (*(int *)(param_1 + 0xe8) == 0xf)
                    {
                        FUN_0042c8b0(0x52);
                    }
                    FUN_005f6ef0(0xb, 0, 0x428c0000, 0, 0, (float)*(int *)(param_1 + 0xf0));
                }
                if (0x5a < *(int *)(param_1 + 0xe8))
                {
                    if (*(float *)(param_1 + 0x70) <= 0.0)
                    {
                        FUN_005f5e00();
                        return;
                    }
                    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.05;
                    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.05;
                    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.05;
                }
            }
        }
        if (0x1c20 < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x14:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            FUN_005f71f0();
            *(undefined4 *)(param_1 + 0x54) = 0;
            FUN_0042c840(0);
            FUN_0042c800(0);
            *(undefined4 *)(param_1 + 0xe8) = 0;
        }
        if (*(int *)(param_1 + 0x154) == 0x3c)
        {
            FUN_0042c840(1);
        }
        sVar3 = FUN_0042c7b0();
        if (sVar3 != 0)
        {
            *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
            if (*(int *)(param_1 + 0xe8) == 1)
            {
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64) = 0x168;
                *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) =
                    *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) + 1;
                if (3 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60))
                {
                    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) = 3;
                }
                *(undefined4 *)(param_1 + 0xec) =
                    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60);
                if (*(short *)(param_1 + 0x88 + *(int *)(*(int *)(param_1 + 0x38) + 8) * 2) == 0)
                {
                    FUN_005f71f0();
                }
            }
            if (*(int *)(param_1 + 0xec) == 1)
            {
                if (*(int *)(param_1 + 0xe8) == 1)
                {
                    *(float *)(param_1 + 0x100) =
                        *(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14);
                    *(float *)(param_1 + 0x104) =
                        *(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18);
                    *(float *)(param_1 + 0x108) =
                        *(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c);
                    FUN_005f6ef0(0xc,
                                 *(undefined4 *)(param_1 + 0x100),
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(undefined4 *)(param_1 + 0x108),
                                 0,
                                 0);
                }
                if (*(int *)(param_1 + 0xe8) == 6)
                {
                    FUN_005f6ef0(0xc,
                                 *(float *)(param_1 + 0x100) + 80.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) + 80.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xc,
                                 *(float *)(param_1 + 0x100) + 80.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) - 80.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xc,
                                 *(float *)(param_1 + 0x100) - 80.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) + 80.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xc,
                                 *(float *)(param_1 + 0x100) - 80.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) - 80.0,
                                 0,
                                 0);
                }
                if (*(int *)(param_1 + 0xe8) == 0xb)
                {
                    FUN_005f6ef0(0xc,
                                 *(float *)(param_1 + 0x100) + 160.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) + 0.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xc,
                                 *(float *)(param_1 + 0x100) - 160.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) - 0.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xc,
                                 *(float *)(param_1 + 0x100) - 0.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) + 160.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xc,
                                 *(float *)(param_1 + 0x100) - 0.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) - 160.0,
                                 0,
                                 0);
                }
                if (10 < *(int *)(param_1 + 0xe8))
                {
                    FUN_005f5e00();
                    return;
                }
            }
            if (*(int *)(param_1 + 0xec) == 2)
            {
                if (*(int *)(param_1 + 0xe8) == 1)
                {
                    *(float *)(param_1 + 0x100) =
                        *(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14);
                    *(float *)(param_1 + 0x104) =
                        *(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18);
                    *(float *)(param_1 + 0x108) =
                        *(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c);
                    FUN_005f6ef0(0xd,
                                 *(undefined4 *)(param_1 + 0x100),
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(undefined4 *)(param_1 + 0x108),
                                 0,
                                 0);
                }
                if (*(int *)(param_1 + 0xe8) == 6)
                {
                    FUN_005f6ef0(0xd,
                                 *(float *)(param_1 + 0x100) + 80.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) + 80.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xd,
                                 *(float *)(param_1 + 0x100) + 80.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) - 80.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xd,
                                 *(float *)(param_1 + 0x100) - 80.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) + 80.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xd,
                                 *(float *)(param_1 + 0x100) - 80.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) - 80.0,
                                 0,
                                 0);
                }
                if (*(int *)(param_1 + 0xe8) == 0xb)
                {
                    FUN_005f6ef0(0xd,
                                 *(float *)(param_1 + 0x100) + 160.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) + 0.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xd,
                                 *(float *)(param_1 + 0x100) - 160.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) - 0.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xd,
                                 *(float *)(param_1 + 0x100) - 0.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) + 160.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xd,
                                 *(float *)(param_1 + 0x100) - 0.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) - 160.0,
                                 0,
                                 0);
                }
                if (10 < *(int *)(param_1 + 0xe8))
                {
                    FUN_005f5e00();
                    return;
                }
            }
            if (*(int *)(param_1 + 0xec) == 3)
            {
                if (*(int *)(param_1 + 0xe8) == 1)
                {
                    FUN_0042c8b0(0x6c);
                    FUN_005f6ef0(
                        0xe,
                        *(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14),
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18)) +
                            0.0,
                        *(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c),
                        0,
                        0);
                }
                if (*(int *)(param_1 + 0xe8) == 6)
                {
                    FUN_0042c8b0(0x6c);
                    FUN_005f6ef0(
                        0xe,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14)) +
                            80.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18)) +
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c)) +
                            80.0,
                        0,
                        0);
                    FUN_005f6ef0(
                        0xe,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14)) +
                            80.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18)) +
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c)) -
                            80.0,
                        0,
                        0);
                    FUN_005f6ef0(
                        0xe,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14)) -
                            80.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18)) +
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c)) +
                            80.0,
                        0,
                        0);
                    FUN_005f6ef0(
                        0xe,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14)) -
                            80.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18)) +
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c)) -
                            80.0,
                        0,
                        0);
                }
                if (*(int *)(param_1 + 0xe8) == 0xb)
                {
                    FUN_0042c8b0(0x6c);
                    FUN_005f6ef0(
                        0xe,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14)) +
                            160.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18)) +
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c)) +
                            0.0,
                        0,
                        0);
                    FUN_005f6ef0(
                        0xe,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14)) -
                            160.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18)) +
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c)) -
                            0.0,
                        0,
                        0);
                    FUN_005f6ef0(
                        0xe,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14)) -
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18)) +
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c)) +
                            160.0,
                        0,
                        0);
                    FUN_005f6ef0(
                        0xe,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14)) -
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18)) +
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c)) -
                            160.0,
                        0,
                        0);
                }
                if (10 < *(int *)(param_1 + 0xe8))
                {
                    FUN_005f5e00();
                    return;
                }
            }
        }
        if (0x1c20 < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x1e:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            FUN_005f71f0();
            *(undefined4 *)(param_1 + 0x54) = 0;
            FUN_0042c840(0);
            FUN_0042c800(0);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0;
            *(undefined4 *)(param_1 + 0x74) = 0;
            *(undefined4 *)(param_1 + 0x78) = 0;
        }
        if (*(int *)(param_1 + 0x154) == 0x3c)
        {
            FUN_0042c840(1);
        }
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
        sVar3 = FUN_0042c7b0();
        if (sVar3 != 0)
        {
            *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
            if (*(int *)(param_1 + 0xe8) == 1)
            {
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64) = 0x168;
                *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) =
                    *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) + 1;
                if (3 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60))
                {
                    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) = 3;
                }
                *(undefined4 *)(param_1 + 0xec) =
                    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60);
                if (*(short *)(param_1 + 0x88 + *(int *)(*(int *)(param_1 + 0x38) + 8) * 2) == 0)
                {
                    FUN_005f71f0();
                }
            }
            if (*(int *)(param_1 + 0xec) == 1)
            {
                if (*(int *)(param_1 + 0xe8) == 1)
                {
                    *(float *)(param_1 + 0x100) =
                        *(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14);
                    *(float *)(param_1 + 0x104) =
                        *(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18);
                    *(float *)(param_1 + 0x108) =
                        *(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c);
                    FUN_005f6ef0(0xc,
                                 *(undefined4 *)(param_1 + 0x100),
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(undefined4 *)(param_1 + 0x108),
                                 0,
                                 0);
                }
                if (*(int *)(param_1 + 0xe8) == 6)
                {
                    FUN_005f6ef0(0xc,
                                 *(float *)(param_1 + 0x100) + 80.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) + 80.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xc,
                                 *(float *)(param_1 + 0x100) + 80.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) - 80.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xc,
                                 *(float *)(param_1 + 0x100) - 80.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) + 80.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xc,
                                 *(float *)(param_1 + 0x100) - 80.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) - 80.0,
                                 0,
                                 0);
                }
                if (*(int *)(param_1 + 0xe8) == 0xb)
                {
                    FUN_005f6ef0(0xc,
                                 *(float *)(param_1 + 0x100) + 160.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) + 0.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xc,
                                 *(float *)(param_1 + 0x100) - 160.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) - 0.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xc,
                                 *(float *)(param_1 + 0x100) - 0.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) + 160.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xc,
                                 *(float *)(param_1 + 0x100) - 0.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) - 160.0,
                                 0,
                                 0);
                }
                if (10 < *(int *)(param_1 + 0xe8))
                {
                    FUN_005f5e00();
                    return;
                }
            }
            if (*(int *)(param_1 + 0xec) == 2)
            {
                if (*(int *)(param_1 + 0xe8) == 1)
                {
                    *(float *)(param_1 + 0x100) =
                        *(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14);
                    *(float *)(param_1 + 0x104) =
                        *(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18);
                    *(float *)(param_1 + 0x108) =
                        *(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c);
                    FUN_005f6ef0(0xd,
                                 *(undefined4 *)(param_1 + 0x100),
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(undefined4 *)(param_1 + 0x108),
                                 0,
                                 0);
                }
                if (*(int *)(param_1 + 0xe8) == 6)
                {
                    FUN_005f6ef0(0xd,
                                 *(float *)(param_1 + 0x100) + 80.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) + 80.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xd,
                                 *(float *)(param_1 + 0x100) + 80.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) - 80.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xd,
                                 *(float *)(param_1 + 0x100) - 80.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) + 80.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xd,
                                 *(float *)(param_1 + 0x100) - 80.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) - 80.0,
                                 0,
                                 0);
                }
                if (*(int *)(param_1 + 0xe8) == 0xb)
                {
                    FUN_005f6ef0(0xd,
                                 *(float *)(param_1 + 0x100) + 160.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) + 0.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xd,
                                 *(float *)(param_1 + 0x100) - 160.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) - 0.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xd,
                                 *(float *)(param_1 + 0x100) - 0.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) + 160.0,
                                 0,
                                 0);
                    FUN_005f6ef0(0xd,
                                 *(float *)(param_1 + 0x100) - 0.0,
                                 *(float *)(param_1 + 0x104) + 450.0,
                                 *(float *)(param_1 + 0x108) - 160.0,
                                 0,
                                 0);
                }
                if (10 < *(int *)(param_1 + 0xe8))
                {
                    FUN_005f5e00();
                    return;
                }
            }
            if (*(int *)(param_1 + 0xec) == 3)
            {
                if (*(int *)(param_1 + 0xe8) == 1)
                {
                    FUN_0042c8b0(0x6c);
                    FUN_005f6ef0(
                        0xe,
                        *(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14),
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18)) +
                            0.0,
                        *(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c),
                        0,
                        0);
                }
                if (*(int *)(param_1 + 0xe8) == 6)
                {
                    FUN_0042c8b0(0x6c);
                    FUN_005f6ef0(
                        0xe,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14)) +
                            80.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18)) +
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c)) +
                            80.0,
                        0,
                        0);
                    FUN_005f6ef0(
                        0xe,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14)) +
                            80.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18)) +
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c)) -
                            80.0,
                        0,
                        0);
                    FUN_005f6ef0(
                        0xe,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14)) -
                            80.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18)) +
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c)) +
                            80.0,
                        0,
                        0);
                    FUN_005f6ef0(
                        0xe,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14)) -
                            80.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18)) +
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c)) -
                            80.0,
                        0,
                        0);
                }
                if (*(int *)(param_1 + 0xe8) == 0xb)
                {
                    FUN_0042c8b0(0x6c);
                    FUN_005f6ef0(
                        0xe,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14)) +
                            160.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18)) +
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c)) +
                            0.0,
                        0,
                        0);
                    FUN_005f6ef0(
                        0xe,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14)) -
                            160.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18)) +
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c)) -
                            0.0,
                        0,
                        0);
                    FUN_005f6ef0(
                        0xe,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14)) -
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18)) +
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c)) +
                            160.0,
                        0,
                        0);
                    FUN_005f6ef0(
                        0xe,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14)) -
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18)) +
                            0.0,
                        (*(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c)) -
                            160.0,
                        0,
                        0);
                }
                if (10 < *(int *)(param_1 + 0xe8))
                {
                    FUN_005f5e00();
                    return;
                }
            }
        }
        if (0x1c20 < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x28:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            FUN_005f71f0();
            *(undefined4 *)(param_1 + 0x54) = 0;
            FUN_0042c840(0);
            FUN_0042c800(0);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0;
            *(undefined4 *)(param_1 + 0x74) = 0;
            *(undefined4 *)(param_1 + 0x78) = 0;
        }
        if (*(int *)(param_1 + 0x154) == 0x3c)
        {
            FUN_0042c840(1);
        }
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
        sVar3 = FUN_0042c7b0();
        if (sVar3 != 0)
        {
            *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
            if (*(int *)(param_1 + 0xe8) == 1)
            {
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64) = 0x168;
                *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) =
                    *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) + 1;
                if (3 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60))
                {
                    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) = 3;
                }
                *(undefined4 *)(param_1 + 0xec) =
                    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60);
                if (*(short *)(param_1 + 0x88 + *(int *)(*(int *)(param_1 + 0x38) + 8) * 2) == 0)
                {
                    FUN_005f71f0();
                }
            }
            if (*(int *)(param_1 + 0xec) == 1)
            {
                if (*(int *)(param_1 + 0xe8) == 0x14)
                {
                    FUN_0042c8b0(0x6e);
                    fVar6 = (float10)FUN_0042da80();
                    FUN_005f6ef0(0xf, 0, 0x428c0000, 0, -*(float *)(param_1 + 100), (float)fVar6);
                }
                if (0x46 < *(int *)(param_1 + 0xe8))
                {
                    FUN_005f5e00();
                    return;
                }
            }
            if (*(int *)(param_1 + 0xec) == 2)
            {
                if (*(int *)(param_1 + 0xe8) == 0x14)
                {
                    FUN_0042c8b0(0x71);
                    fVar6 = (float10)FUN_0042da80();
                    FUN_005f6ef0(0x10, 0, 0x428c0000, 0, -*(float *)(param_1 + 100), (float)fVar6);
                }
                if (0x46 < *(int *)(param_1 + 0xe8))
                {
                    FUN_005f5e00();
                    return;
                }
            }
            if (*(int *)(param_1 + 0xec) == 3)
            {
                if (*(int *)(param_1 + 0xe8) == 10)
                {
                    FUN_0042c8b0(0x9d);
                    FUN_005f6db0(0x11, 0, 0, 0);
                }
                if (10 < *(int *)(param_1 + 0xe8))
                {
                    FUN_005f5e00();
                    return;
                }
            }
        }
        if (0x1c20 < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x32:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            FUN_005f71f0();
            *(undefined4 *)(param_1 + 0x54) = 0;
            FUN_0042c840(0);
            FUN_0042c800(0);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0;
            *(undefined4 *)(param_1 + 0x74) = 0;
            *(undefined4 *)(param_1 + 0x78) = 0;
        }
        if (*(int *)(param_1 + 0x154) == 0x3c)
        {
            FUN_0042c840(1);
        }
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
        sVar3 = FUN_0042c7b0();
        if (sVar3 != 0)
        {
            *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
            if (*(int *)(param_1 + 0xe8) == 1)
            {
                *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64) = 0x168;
                *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) =
                    *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) + 1;
                if (3 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60))
                {
                    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) = 3;
                }
                *(undefined4 *)(param_1 + 0xec) =
                    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60);
                if (*(short *)(param_1 + 0x88 + *(int *)(*(int *)(param_1 + 0x38) + 8) * 2) == 0)
                {
                    FUN_005f71f0();
                }
            }
            if (*(int *)(param_1 + 0xec) == 1)
            {
                if (*(int *)(param_1 + 0xe8) == 0x14)
                {
                    FUN_0042c8b0(0x6e);
                    fVar6 = (float10)FUN_0042da80();
                    FUN_005f6ef0(0xf, 0, 0x428c0000, 0, -*(float *)(param_1 + 100), (float)fVar6);
                }
                if (0x46 < *(int *)(param_1 + 0xe8))
                {
                    FUN_005f5e00();
                    return;
                }
            }
            if (*(int *)(param_1 + 0xec) == 2)
            {
                if (*(int *)(param_1 + 0xe8) == 0x14)
                {
                    FUN_0042c8b0(0x71);
                    fVar6 = (float10)FUN_0042da80();
                    FUN_005f6ef0(0x10, 0, 0x428c0000, 0, -*(float *)(param_1 + 100), (float)fVar6);
                }
                if (0x46 < *(int *)(param_1 + 0xe8))
                {
                    FUN_005f5e00();
                    return;
                }
            }
            if (*(int *)(param_1 + 0xec) == 3)
            {
                if (*(int *)(param_1 + 0xe8) == 10)
                {
                    FUN_0042c8b0(0x9d);
                    FUN_005f6db0(0x11, 0, 0, 0);
                }
                if (10 < *(int *)(param_1 + 0xe8))
                {
                    FUN_005f5e00();
                    return;
                }
            }
        }
        if (0x1c20 < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x3c:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3e800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3e800000;
            *(undefined4 *)(param_1 + 0x78) = 0x3e800000;
            *(undefined4 *)(param_1 + 0x54) = 0;
            FUN_0042c840(0);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_005f6880(0);
            *(undefined4 *)(param_1 + 0x40) = 0;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.5;
            cVar2                      = FUN_005f6a90();
            if (cVar2 == '\x01')
            {
                FUN_0042c840(1);
                *(undefined4 *)(param_1 + 0x40) = 0;
                *(undefined4 *)(param_1 + 0x3c) = 0;
                *(undefined4 *)(param_1 + 0x44) = 0;
                *(undefined4 *)(param_1 + 0x54) = 0;
                *(undefined4 *)(param_1 + 0xe8) = 1;
            }
        }
        if ((300 < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0))
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
            FUN_0042c840(0);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_005f6880(0);
            *(undefined4 *)(param_1 + 0x40) = 0;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.5;
            cVar2                      = FUN_005f6a90();
            if (cVar2 == '\x01')
            {
                FUN_0042c840(1);
                *(undefined4 *)(param_1 + 0x40) = 0;
                *(undefined4 *)(param_1 + 0x3c) = 0;
                *(undefined4 *)(param_1 + 0x44) = 0;
                *(undefined4 *)(param_1 + 0x54) = 0;
                *(undefined4 *)(param_1 + 0xe8) = 1;
            }
        }
        if ((600 < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0))
        {
            FUN_0042c8b0(0x73);
            FUN_005f6db0(8, 0, 0, 0);
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
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            FUN_0042db10(0, 0x3c23d70a);
            fVar6 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar6)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.01;
            }
            fVar6 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar6 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.01;
            }
        }
        sVar3 = FUN_0042c7b0();
        if ((sVar3 != 0) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01'))
        {
            FUN_005f5e00();
            return;
        }
        if (0x5a < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 100:
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
            *(undefined4 *)(param_1 + 0xf0) = 0;
        }
        sVar3 = FUN_0042c7b0();
        if (((sVar3 != 0) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) &&
            ((uVar4 = FUN_0042c7b0(),
              (uVar4 & 2) != 0 || (cVar2 = FUN_005f6a90(), cVar2 == '\x01'))))
        {
            FUN_005f5e00();
            return;
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
        }
        if (*(int *)(param_1 + 0x154) == 0x1e)
        {
            *(undefined4 *)(param_1 + 0x154) = 0x14;
            return;
        }
        if (0xb4 < *(int *)(param_1 + 0xf0))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x6e:
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
    case 0x78:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            FUN_005f6880(0);
            *(undefined4 *)(param_1 + 0x6c) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0x40) = 0xc1a00000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_0042c800(0);
        }
        *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.5;
        sVar3                      = FUN_0042c7b0();
        if (((sVar3 != 0) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) &&
            (*(int *)(param_1 + 0xe8) == 0))
        {
            FUN_0042c840(0);
            *(undefined4 *)(param_1 + 0x40) = 0x40a00000;
            *(undefined4 *)(param_1 + 0xe8) = 1;
        }
        if ((0 < *(int *)(param_1 + 0xe8)) &&
            (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1,
             0x78 < *(int *)(param_1 + 0xe8)))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x82:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
            *(undefined4 *)(param_1 + 0x74) = 0x3fc00000;
            *(undefined4 *)(param_1 + 0x78) = 0x3fc00000;
            *(undefined4 *)(param_1 + 0x34) = 0x43340000;
            FUN_005f6880(0);
            *(undefined4 *)(param_1 + 0x6c) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0x40) = 0xc1a00000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_0042c800(0);
        }
        *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.5;
        cVar2                      = FUN_005f6a90();
        if ((cVar2 == '\x01') && (*(int *)(param_1 + 0xe8) == 0))
        {
            FUN_005f5e00();
            return;
        }
        sVar3 = FUN_0042c7b0();
        if ((sVar3 != 0) && (*(int *)(param_1 + 0xe8) == 0))
        {
            FUN_005f5e00();
            return;
        }
        if ((0 < *(int *)(param_1 + 0xe8)) &&
            (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1,
             300 < *(int *)(param_1 + 0xe8)))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x8c:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3e800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3e800000;
            *(undefined4 *)(param_1 + 0x78) = 0x3e800000;
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0x6c) = 0;
            *(undefined4 *)(param_1 + 0x40) = 0;
            *(undefined4 *)(param_1 + 0xe8) = 0xff;
            FUN_0042c840(1);
            FUN_005f6880(0);
        }
        *(float *)(param_1 + 0x70)      = *(float *)(param_1 + 0x70) + 0.02;
        *(float *)(param_1 + 0x74)      = *(float *)(param_1 + 0x74) + 0.02;
        *(float *)(param_1 + 0x78)      = *(float *)(param_1 + 0x78) + 0.02;
        *(undefined4 *)(param_1 + 0x40) = 0x41a00000;
        if (0xf < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        if ((5 < *(int *)(param_1 + 0x154)) &&
            (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0x19,
             *(int *)(param_1 + 0xe8) < 0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0;
        }
        FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8), 0xff, 0xff, 0xff);
        break;
    case 0x96:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x41200000;
            *(undefined4 *)(param_1 + 0x74) = 0x41200000;
            *(undefined4 *)(param_1 + 0x78) = 0x41200000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0;
        }
        fVar6                      = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x54) = (float)(fVar6 * (float10)50.0);
        if (*(int *)(param_1 + 0x154) == 0x1e)
        {
            FUN_0042c840(0);
        }
        if (*(int *)(param_1 + 0x154) == 0x3c)
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0xa0:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x40800000;
            *(undefined4 *)(param_1 + 0x74) = 0x40800000;
            *(undefined4 *)(param_1 + 0x78) = 0x40800000;
            *(undefined4 *)(param_1 + 0x54) = 0x42700000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0;
        }
        fVar6                      = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
        *(float *)(param_1 + 0x54) = (float)(fVar6 * (float10)60.0);
        if (*(int *)(param_1 + 0x154) == 0x1e)
        {
            FUN_0042c840(0);
        }
        if (*(int *)(param_1 + 0x154) == 0x3c)
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0xaa:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
            *(undefined4 *)(param_1 + 0x74) = 0x3fc00000;
            *(undefined4 *)(param_1 + 0x78) = 0x3fc00000;
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
    case 0xb4:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x40a00000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
            *(undefined4 *)(param_1 + 0x74) = 0x3fc00000;
            *(undefined4 *)(param_1 + 0x78) = 0x3fc00000;
        }
        if (*(int *)(param_1 + 0x154) == 1)
        {
            FUN_005f6880(0);
            *(undefined4 *)(param_1 + 0x40) = 0;
        }
        if (*(int *)(param_1 + 0xe8) == 0)
        {
            *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.5;
        }
        cVar2 = FUN_005f6a90();
        if ((cVar2 == '\x01') && (*(int *)(param_1 + 0xe8) == 0))
        {
            *(undefined4 *)(param_1 + 0x40) = 0;
            *(undefined4 *)(param_1 + 0x3c) = 0;
            *(undefined4 *)(param_1 + 0x44) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0xe8) = 1;
        }
        if (*(int *)(param_1 + 0x154) == 600)
        {
            FUN_005f6db0(0x13, 0, 0, 0);
            FUN_005f6db0(0x14, 0, 0, 0);
            FUN_005f6db0(0x15, 0, 0, 0);
            FUN_0042c8b0(0x9d);
            FUN_005f5e00();
            return;
        }
        break;
    case 0xbe:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x2c) = 0;
            *(undefined4 *)(param_1 + 0x30) = 0;
            *(float *)(param_1 + 0x34)      = -*(float *)(param_1 + 0x6c);
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0x40) = 0;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0xff;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0x70) = 0x40900000;
            *(undefined4 *)(param_1 + 0x74) = 0x40900000;
            *(undefined4 *)(param_1 + 0x78) = 0x40900000;
        }
        if (6.0 <= *(float *)(param_1 + 0x70))
        {
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.005;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.005;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.005;
        }
        else
        {
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.5;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.5;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.5;
        }
        *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
        if (0x14 < *(int *)(param_1 + 0xe8))
        {
            FUN_0042c840(0);
            *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + -5;
            if (*(int *)(param_1 + 0xec) < 0)
            {
                *(undefined4 *)(param_1 + 0xe8) = 0;
                FUN_005f5e00();
                return;
            }
        }
        FUN_005fafc0(*(undefined1 *)(param_1 + 0xec), 0xff, 0xff, 0xff);
        break;
    case 200:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x2c) = 0;
            *(undefined4 *)(param_1 + 0x30) = 0;
            *(float *)(param_1 + 0x34)      = -*(float *)(param_1 + 0x6c);
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0x40) = 0;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0xff;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0x70) = 0x40d00000;
            *(undefined4 *)(param_1 + 0x74) = 0x40d00000;
            *(undefined4 *)(param_1 + 0x78) = 0x40d00000;
        }
        if (10.0 <= *(float *)(param_1 + 0x70))
        {
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.0035;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.0035;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.0035;
        }
        else
        {
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.25;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.25;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.25;
        }
        *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
        if (((0x14 < *(int *)(param_1 + 0xe8)) &&
             (FUN_0042c840(0), 0x1e < *(int *)(param_1 + 0xe8))) &&
            (*(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + -5,
             *(int *)(param_1 + 0xec) < 0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_005f5e00();
            return;
        }
        FUN_005fafc0(*(undefined1 *)(param_1 + 0xec), 0xff, 0xff, 0xff);
        if (*(int *)(param_1 + 0x154) == 0x11)
        {
            *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + -0x10;
            return;
        }
        break;
    case 0xd2:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x2c) = 0;
            *(undefined4 *)(param_1 + 0x30) = 0;
            *(float *)(param_1 + 0x34)      = -*(float *)(param_1 + 0x6c);
            *(undefined4 *)(param_1 + 0x54) = 0;
            *(undefined4 *)(param_1 + 0x40) = 0;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0xff;
            *(undefined4 *)(param_1 + 0x70) = 0x40c00000;
            *(undefined4 *)(param_1 + 0x74) = 0x40c00000;
            *(undefined4 *)(param_1 + 0x78) = 0x40c00000;
        }
        *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 1.0;
        *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 1.0;
        *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 1.0;
        if (0x3c < *(int *)(param_1 + 0x154))
        {
            FUN_0042c840(0);
            *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + -0xf;
            if (*(int *)(param_1 + 0xec) < 0)
            {
                *(undefined4 *)(param_1 + 0xe8) = 0;
                FUN_005f5e00();
                return;
            }
        }
        FUN_005fafc0(*(undefined1 *)(param_1 + 0xec), 0xff, 0xff, 0xff);
        break;
    case 0xdc:
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
                fVar6 = (float10)FUN_0065d010(
                    90.0 - (*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)));
                *(float *)(param_1 + 0x14) =
                    (float)(fVar6 * (float10)135.0 + (float10) * (float *)(iVar1 + 0x14));
                *(float *)(param_1 + 0x18) =
                    *(float *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) +
                               0x18) +
                    90.0;
                iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0);
                fVar6 = (float10)FUN_0065d050(
                    90.0 - (*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)));
                *(float *)(param_1 + 0x1c) =
                    (float)(fVar6 * (float10)135.0 + (float10) * (float *)(iVar1 + 0x1c));
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
    case 0xe6:
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
            fVar6 = (float10)FUN_0065d010(90.0 -
                                          (*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)));
            *(float *)(param_1 + 0x14) =
                (float)(fVar6 * (float10)125.0 + (float10) * (float *)(iVar1 + 0x14));
            *(float *)(param_1 + 0x18) =
                *(float *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) + 0x18) +
                50.0;
            iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0);
            fVar6 = (float10)FUN_0065d050(90.0 -
                                          (*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)));
            *(float *)(param_1 + 0x1c) =
                (float)(fVar6 * (float10)125.0 + (float10) * (float *)(iVar1 + 0x1c));
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
    case 0xf0:
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
            fVar6 = (float10)FUN_0065d010(90.0 -
                                          (*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)));
            *(float *)(param_1 + 0x14) =
                (float)(fVar6 * (float10)125.0 + (float10) * (float *)(iVar1 + 0x14));
            *(float *)(param_1 + 0x18) =
                *(float *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) + 0x18) +
                50.0;
            iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0);
            fVar6 = (float10)FUN_0065d050(90.0 -
                                          (*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)));
            *(float *)(param_1 + 0x1c) =
                (float)(fVar6 * (float10)125.0 + (float10) * (float *)(iVar1 + 0x1c));
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
