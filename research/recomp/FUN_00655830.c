// ============================================
// Address:  0x00655830
// Original: FUN_00655830
// Status:   unreviewed
// ============================================

void __thiscall
FUN_00655830(undefined4 *param_1, float param_2, float param_3, int param_4, int param_5)

{
    float fVar1;
    float10 fVar2;
    float10 fVar3;
    int local_18;

    param_1[1]    = (param_2 - (float)param_1[0x1f] * (float)param_1[0x21]) - 0.5;
    param_1[2]    = (param_3 - (float)param_1[0x20] * (float)param_1[0x22]) - 0.5;
    param_1[8]    = (float)param_1[0x1d] * (float)param_1[0x21] + (float)param_1[1];
    param_1[9]    = param_1[2];
    param_1[0xf]  = param_1[1];
    param_1[0x10] = (float)param_1[0x1e] * (float)param_1[0x22] + (float)param_1[2];
    param_1[0x16] = param_1[8];
    param_1[0x17] = param_1[0x10];
    param_1[6]    = (float)param_4 * (float)param_1[0x26] + (float)param_1[0x24];
    param_1[7]    = (float)param_5 * (float)param_1[0x27] + (float)param_1[0x25];
    param_1[0xd]  = (float)(param_4 + 1) * (float)param_1[0x26] + (float)param_1[0x24];
    param_1[0xe]  = (float)param_5 * (float)param_1[0x27] + (float)param_1[0x25];
    param_1[0x14] = (float)param_4 * (float)param_1[0x26] + (float)param_1[0x24];
    param_1[0x15] = (float)(param_5 + 1) * (float)param_1[0x27] + (float)param_1[0x25];
    param_1[0x1b] = (float)(param_4 + 1) * (float)param_1[0x26] + (float)param_1[0x24];
    param_1[0x1c] = (float)(param_5 + 1) * (float)param_1[0x27] + (float)param_1[0x25];
    if ((float)param_1[0x23] != 0.0)
    {
        fVar2 = (float10)FUN_0065d050(param_1[0x23]);
        fVar3 = (float10)FUN_0065d010(param_1[0x23]);
        for (local_18 = 0; local_18 < 4; local_18 = local_18 + 1)
        {
            fVar1                     = (float)param_1[local_18 * 7 + 1];
            param_1[local_18 * 7 + 1] = ((fVar1 - param_2) * (float)fVar2 + param_2) -
                                        ((float)param_1[local_18 * 7 + 2] - param_3) * (float)fVar3;
            param_1[local_18 * 7 + 2] =
                ((float)param_1[local_18 * 7 + 2] - param_3) * (float)fVar2 +
                (fVar1 - param_2) * (float)fVar3 + param_3;
        }
    }
    FUN_00656300(*param_1);
    (**(code **)(*DAT_006d16f8 + 0x164))(DAT_006d16f8, 0x144);
    FUN_006517e0(5, 2, param_1 + 1, 0x1c);
    return;
}
