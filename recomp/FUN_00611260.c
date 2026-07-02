// ============================================
// Address:  0x00611260
// Original: FUN_00611260
// Status:   unreviewed
// ============================================

void __fastcall FUN_00611260(int param_1)

{
    char cVar1;
    short sVar2;
    uint uVar3;

    uVar3 = FUN_0042c7b0();
    if (((uVar3 & 0x100) != 0) &&
        ((*(int *)(param_1 + 0x150) == 0x14 || (*(int *)(param_1 + 0x150) == 0x1e))))
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
            *(undefined4 *)(param_1 + 0x70) = 0x40000000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x54) = 0x3c23d70a;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0;
        }
        if (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadf4) == 3)
        {
            *(undefined4 *)(param_1 + 0xec) = 1;
        }
        if ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 400) &&
            (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x192))
        {
            FUN_005f6db0(10, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        sVar2 = FUN_0042c7b0();
        if ((sVar2 != 0) && (*(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1,
                             10 < *(int *)(param_1 + 0xf0)))
        {
            *(undefined4 *)(param_1 + 0xf0) = 0;
            FUN_0042c840(1);
            FUN_0042c800(0);
        }
        if (*(int *)(param_1 + 0xec) == 1)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x3c23d70a;
            FUN_0042c840(0);
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.0;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
            if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 10:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x40200000;
            *(undefined4 *)(param_1 + 0x74) = 0x40000000;
            *(undefined4 *)(param_1 + 0x78) = 0x40000000;
            *(undefined4 *)(param_1 + 0x54) = 0x3c23d70a;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0;
        }
        if (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadf4) == 3)
        {
            *(undefined4 *)(param_1 + 0xec) = 1;
        }
        if ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 400) &&
            (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x192))
        {
            FUN_005f6db0(0xb, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        sVar2 = FUN_0042c7b0();
        if ((sVar2 != 0) && (*(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1,
                             10 < *(int *)(param_1 + 0xf0)))
        {
            *(undefined4 *)(param_1 + 0xf0) = 0;
            FUN_0042c840(1);
            FUN_0042c800(0);
        }
        if (*(int *)(param_1 + 0xec) == 1)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x3c23d70a;
            FUN_0042c840(0);
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.0;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
            if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 0x14:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x42480000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (((10 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
            (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            FUN_005f6db0(4, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        break;
    case 0x1e:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x42480000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (((10 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
            (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            FUN_005f6db0(5, 0, 0, 0);
            FUN_005f5e00();
            return;
        }
        break;
    case 0x28:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0x40000000;
            *(undefined4 *)(param_1 + 0x74) = 0x40000000;
            *(undefined4 *)(param_1 + 0x78) = 0x40000000;
        }
        uVar3 = *(uint *)(param_1 + 0x154) & 0x80000000;
        if ((int)uVar3 < 0)
        {
            uVar3 = 0;
        }
        if (uVar3 == 0)
        {
            FUN_005f6fd0(8, 0, 0, 0);
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (0x3c < *(int *)(param_1 + 0x154))
        {
            *(undefined4 *)(param_1 + 0xec) = 1;
        }
        if (*(int *)(param_1 + 0xec) == 1)
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
        break;
    case 0x32:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0x40400000;
            *(undefined4 *)(param_1 + 0x74) = 0x40400000;
            *(undefined4 *)(param_1 + 0x78) = 0x40400000;
        }
        uVar3 = *(uint *)(param_1 + 0x154) & 0x80000000;
        if ((int)uVar3 < 0)
        {
            uVar3 = 0;
        }
        if (uVar3 == 0)
        {
            FUN_005f6fd0(8, 0, 0, 0);
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (0x78 < *(int *)(param_1 + 0x154))
        {
            *(undefined4 *)(param_1 + 0xec) = 1;
        }
        if (*(int *)(param_1 + 0xec) == 1)
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
        break;
    case 0x3c:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x3c23d70a;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x70) = 0x40800000;
            *(undefined4 *)(param_1 + 0x74) = 0x40800000;
            *(undefined4 *)(param_1 + 0x78) = 0x40800000;
        }
        uVar3 = *(uint *)(param_1 + 0x154) & 0x80000000;
        if ((int)uVar3 < 0)
        {
            uVar3 = 0;
        }
        if (uVar3 == 0)
        {
            FUN_005f6fd0(8, 0, 0, 0);
        }
        if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0))
        {
            *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
        }
        if (0 < *(int *)(param_1 + 0x154))
        {
            *(undefined4 *)(param_1 + 0xec) = 1;
        }
        if (*(int *)(param_1 + 0xec) == 1)
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.2;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.2;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.2;
            if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
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
            FUN_0042c840(1);
        }
        if (0x14 < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x50:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x41a00000;
            uVar3                           = FUN_0065d150();
            *(float *)(param_1 + 100)       = (float)(int)(short)((ulonglong)uVar3 % 0x168);
            uVar3                           = FUN_0065d150();
            *(float *)(param_1 + 0x6c)      = (float)(int)(short)((ulonglong)uVar3 % 0x168);
            *(undefined4 *)(param_1 + 0xe8) = 0;
            FUN_0042c840(0);
        }
        sVar2 = FUN_0042c7b0();
        if ((sVar2 != 0) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01'))
        {
            FUN_005f5e00();
            return;
        }
        if (0xf < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
        break;
    case 0x5a:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
            *(undefined4 *)(param_1 + 0x54) = 0x3c23d70a;
        }
        if (0 < *(int *)(param_1 + 0x154))
        {
            *(undefined4 *)(param_1 + 0xec) = 1;
        }
        if (*(int *)(param_1 + 0xec) == 1)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x3c23d70a;
            FUN_0042c840(0);
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.0;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
            if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 100:
    case 0x6e:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x3c23d70a;
            FUN_0042c840(1);
            FUN_005fafc0(0, 0xff, 0xff, 0xff);
        }
        if (0 < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
    }
    *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
    FUN_005f75a0();
    return;
}
