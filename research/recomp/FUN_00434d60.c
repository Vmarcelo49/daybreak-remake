// ============================================
// Address:  0x00434d60
// Original: FUN_00434d60
// Status:   unreviewed
// ============================================

void __thiscall FUN_00434d60(int param_1, float *param_2)

{
    float10 fVar1;
    float10 fVar2;
    float10 fVar3;

    fVar1      = (float10)FUN_0065d010(*(undefined4 *)(param_1 + 0x100));
    fVar2      = (float10)FUN_0065d050(*(undefined4 *)(param_1 + 0x100));
    fVar3      = (float10)FUN_0065d050(*(float *)(*(int *)(param_1 + 0x20) + 0x5c) +
                                       *(float *)(*(int *)(param_1 + 0x20) + 100));
    *param_2   = (float)(fVar3 * (float10)(float)fVar2);
    param_2[1] = (float)fVar1;
    fVar1      = (float10)FUN_0065d010(*(float *)(*(int *)(param_1 + 0x20) + 0x5c) +
                                       *(float *)(*(int *)(param_1 + 0x20) + 100));
    param_2[2] = (float)(fVar1 * (float10)(float)fVar2);
    return;
}
