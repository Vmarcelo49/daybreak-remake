// ============================================
// Address:  0x0063b4d0
// Original: FUN_0063b4d0
// Status:   unreviewed
// ============================================

undefined4 FUN_0063b4d0(undefined4 param_1, float param_2, undefined4 param_3)

{
    undefined2 extraout_var;
    undefined2 extraout_var_00;
    float10 fVar1;
    float10 fVar2;
    float10 fVar3;
    float in_stack_0000001c;
    undefined1 *puVar4;
    undefined4 uVar5;
    bool local_58;
    undefined1 local_40[12];
    undefined1 local_34[12];
    undefined1 local_28[12];
    undefined1 local_1c[12];
    undefined1 local_10[12];

    FUN_0042dfd0(local_1c, param_1);
    FUN_0042dfd0(local_10, param_3);
    fVar1 = (float10)FUN_0063bec0(local_1c);
    fVar2 = (float10)FUN_0042e0e0(local_1c, local_10, 2);
    fVar2 = (float10)FUN_0040da40((float)fVar2);
    fVar3 = (float10)FUN_0063bec0(local_10);
    fVar1 = (float10)(float)fVar1 - (float10)(float)fVar2 / fVar3;
    fVar2 = ((float10)param_2 + (float10)in_stack_0000001c) *
            ((float10)param_2 + (float10)in_stack_0000001c);
    uVar5 = CONCAT22(extraout_var,
                     (ushort)(fVar2 < fVar1) << 8 | (ushort)(NAN(fVar2) || NAN(fVar1)) << 10 |
                         (ushort)(fVar2 == fVar1) << 0xe);
    if (fVar2 >= fVar1 && (fVar2 == fVar1) == 0)
    {
        uVar5  = 0x40000000;
        puVar4 = local_34;
        FUN_00424180(local_28, &stack0x00000010);
        uVar5    = FUN_0063bef0(puVar4, uVar5);
        uVar5    = FUN_0042dfd0(local_40, uVar5);
        fVar1    = (float10)FUN_0063bec0(uVar5);
        param_2  = param_2 + in_stack_0000001c;
        fVar2    = (float10)FUN_0042df50(local_10, 2);
        fVar2    = (float10)FUN_0040da40((float)(fVar2 / (float10)2.0 + (float10)param_2));
        fVar1    = (float10)(float)fVar1;
        local_58 = fVar2 < fVar1 == 0 && (fVar2 == fVar1) == 0;
        uVar5    = CONCAT31((int3)(CONCAT22(extraout_var_00,
                                            (ushort)(fVar2 < fVar1) << 8 |
                                                (ushort)(NAN(fVar2) || NAN(fVar1)) << 10 |
                                                (ushort)(fVar2 == fVar1) << 0xe) >>
                                   8),
                            local_58);
    }
    return uVar5;
}
