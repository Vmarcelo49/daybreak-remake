// ============================================
// Address:  0x00633ab0
// Original: FUN_00633ab0
// Status:   unreviewed
// ============================================

void __thiscall FUN_00633ab0(int param_1, undefined4 param_2, undefined4 param_3)

{
    undefined4 uVar1;
    float10 fVar2;
    undefined1 local_10[4];
    undefined4 local_c;

    *(undefined4 *)(param_1 + 4)    = param_2;
    *(undefined4 *)(param_1 + 0x38) = param_3;
    FUN_0042dfd0(local_10, *(int *)(param_1 + 0x38) + 0x14);
    local_c = 0;
    fVar2   = (float10)FUN_0042df50(local_10);
    if (fVar2 < (float10)80.0)
    {
        *(undefined4 *)(param_1 + 0x54) = 0;
    }
    fVar2 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 0x60));
    *(float *)(param_1 + 0x3c)      = (float)(fVar2 * (float10) * (float *)(param_1 + 0x54));
    *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(param_1 + 0x40);
    fVar2 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 0x60));
    *(float *)(param_1 + 0x44)      = (float)(fVar2 * (float10) * (float *)(param_1 + 0x54));
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_1 + 0x44);
    uVar1 = FUN_00423750(*(undefined4 *)(param_1 + 0x48), 0, *(undefined4 *)(param_1 + 0x50));
    FUN_0042cb50(uVar1);
    FUN_0042c970(param_1 + 0x4c);
    FUN_0042dd90();
    FUN_00633bc0();
    return;
}
