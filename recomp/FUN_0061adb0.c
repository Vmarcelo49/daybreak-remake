// ============================================
// Address:  0x0061adb0
// Original: FUN_0061adb0
// Status:   unreviewed
// ============================================

void __fastcall FUN_0061adb0(int param_1)

{
    int iVar1;
    char cVar2;
    uint uVar3;
    float10 fVar4;

    uVar3 = FUN_0042c7b0();
    if ((uVar3 & 0x100) == 0)
        goto LAB_0061ae4f;
    iVar1 = *(int *)(param_1 + 0x150);
    if (iVar1 != 0)
    {
        if (iVar1 == 10)
        {
            FUN_005f72c0(0x43340000, -*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
            FUN_0042c800(0);
            FUN_0042c840(3);
            goto LAB_0061ae4f;
        }
        if (iVar1 != 0x14)
            goto LAB_0061ae4f;
    }
    FUN_005f72c0(0x43340000, -*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
    FUN_0042c800(0);
    FUN_0042c840(1);
LAB_0061ae4f:
    switch (*(undefined4 *)(param_1 + 0x150))
    {
    case 0:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0x42700000;
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x40400000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
            FUN_0042c840(1);
        }
        cVar2 = FUN_005f6a90();
        if ((cVar2 == '\x01') || (10 < *(int *)(param_1 + 0x154)))
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.2;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 1.0;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.2;
            if (*(float *)(param_1 + 0x74) < 0.0 != (*(float *)(param_1 + 0x74) == 0.0))
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
        break;
    case 10:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0x42a00000;
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x40400000;
            *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
            FUN_0042c840(3);
        }
        uVar3 = FUN_0042c7b0();
        if ((uVar3 & 1) != 0)
        {
            if (*(int *)(param_1 + 0xec) < 10)
            {
                *(undefined4 *)(param_1 + 0x54) = 0;
                *(int *)(param_1 + 0xec)        = *(int *)(param_1 + 0xec) + 1;
                return;
            }
            *(undefined4 *)(param_1 + 0xec) = 0;
            FUN_0042c800(0);
        }
        cVar2 = FUN_005f6a90();
        if ((cVar2 == '\x01') || (10 < *(int *)(param_1 + 0x154)))
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.2;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 1.0;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.2;
            if (*(float *)(param_1 + 0x74) < 0.0 != (*(float *)(param_1 + 0x74) == 0.0))
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
        break;
    case 0x14:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0x42480000;
            FUN_0042c840(1);
        }
        cVar2 = FUN_005f6a90();
        if ((cVar2 == '\x01') || (0x1e < *(int *)(param_1 + 0x154)))
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
        break;
    case 0x1e:
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
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.5;
            }
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.5;
            }
        }
        *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 1.0;
        if (*(float *)(param_1 + 0x54) < 20.0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x41a00000;
        }
        break;
    case 0x28:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0x54) = 0x42480000;
            *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
            *(undefined4 *)(param_1 + 0x78) = 0x40400000;
            FUN_0042c840(1);
        }
        cVar2 = FUN_005f6a90();
        if ((cVar2 == '\x01') || (5 < *(int *)(param_1 + 0x154)))
        {
            FUN_0042c840(0);
            *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.2;
            *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.2;
            *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.6;
            if (*(float *)(param_1 + 0x74) < 0.0 != (*(float *)(param_1 + 0x74) == 0.0))
            {
                FUN_005f5e00();
                return;
            }
        }
        break;
    case 0x32:
        FUN_005f5e00();
        return;
    case 0x3c:
        if (*(int *)(param_1 + 0x154) == 0)
        {
            *(undefined4 *)(param_1 + 0x54) = 0x41a00000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
        }
        if ((*(int *)(param_1 + 0xe8) == 0) && (*(int *)(param_1 + 0x154) < 0x14))
        {
            FUN_0042db10(0, 0x40000000);
        }
        if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154)))
        {
            FUN_0042db10(0, 0x3e99999a);
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.3;
            }
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.3;
            }
        }
        cVar2 = FUN_005f6a90();
        if ((cVar2 == '\x01') || (0x78 < *(int *)(param_1 + 0x154)))
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
            *(undefined4 *)(param_1 + 0x54) = 0x41a00000;
            FUN_0042c840(1);
            *(undefined4 *)(param_1 + 0xe8) = 0;
        }
        if ((*(int *)(param_1 + 0xe8) == 0) && (*(int *)(param_1 + 0x154) < 0x14))
        {
            FUN_0042db10(0, 0x40000000);
        }
        if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154)))
        {
            FUN_0042db10(0, 0x3e99999a);
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10)3.0 < (float10) * (float *)(param_1 + 0x6c) - fVar4)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.3;
            }
            fVar4 = (float10)FUN_0042dac0(2);
            if ((float10) * (float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0)
            {
                *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.3;
            }
        }
        cVar2 = FUN_005f6a90();
        if ((cVar2 == '\x01') || (0x78 < *(int *)(param_1 + 0x154)))
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
        if (0x1d < *(int *)(param_1 + 0x154))
        {
            FUN_005f5e00();
            return;
        }
    }
    *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
    FUN_005f75a0();
    return;
}
