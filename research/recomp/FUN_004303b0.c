// ============================================
// Address:  0x004303b0
// Original: FUN_004303b0
// Status:   unreviewed
// ============================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004303b0(int param_1)

{
    ulonglong uVar1;
    ulonglong uVar2;
    uint uVar3;
    uint uVar4;
    int local_1c;
    int local_18;

    if (0 < *(int *)(param_1 + 0x3c))
    {
        uVar3 = (DAT_006d1628 >> 1) + _DAT_006d1620;
        uVar4 = (DAT_006d162c >> 1) + _DAT_006d1624;
        uVar2 = (ulonglong)DAT_006d1628;
        uVar1 = (ulonglong)DAT_006d162c;
        (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x16, 1);
        FUN_00656300(*(undefined4 *)(param_1 + 0x44));
        (**(code **)(*DAT_006d16f8 + 0x170))(DAT_006d16f8, 0);
        (**(code **)(*DAT_006d16f8 + 0x164))(DAT_006d16f8, 0x144);
        (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0xe, 0);
        (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x14, 2);
        for (local_18 = 0; local_18 <= *(int *)(param_1 + 0x3c) + 1; local_18 = local_18 + 1)
        {
            D3DXVec4Transform(param_1 + 0x448 + local_18 * 0x1c,
                              param_1 + 0x158 + local_18 * 0x10,
                              &DAT_006d1510);
            FUN_004307e0(*(undefined4 *)(param_1 + 0x454 + local_18 * 0x1c));
            *(float *)(param_1 + 0x448 + local_18 * 0x1c) =
                ((float)uVar2 / 2.0) * *(float *)(param_1 + 0x448 + local_18 * 0x1c) + (float)uVar3;
            *(float *)(param_1 + 0x44c + local_18 * 0x1c) =
                -*(float *)(param_1 + 0x44c + local_18 * 0x1c) * ((float)uVar1 / 2.0) +
                (float)uVar4;
        }
        for (local_1c = 0; local_1c <= *(int *)(param_1 + 0x3c); local_1c = local_1c + 1)
        {
            *(float *)(param_1 + 0x460 + (local_1c + 1) * 0x1c) =
                (float)local_1c / (float)*(int *)(param_1 + 0x3c);
        }
        (**(code **)(*DAT_006d16f8 + 0x14c))(
            DAT_006d16f8, 6, *(undefined4 *)(param_1 + 0x3c), param_1 + 0x448, 0x1c);
        (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0xe, 1);
        (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 0x14, 6);
    }
    return;
}
