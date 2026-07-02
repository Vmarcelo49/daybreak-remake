// ============================================
// Address:  0x0042d9d0
// Original: FUN_0042d9d0
// Status:   unreviewed
// ============================================

float10 __thiscall FUN_0042d9d0(int param_1, undefined4 param_2)

{
    float *pfVar1;
    float10 fVar2;
    float10 fVar3;

    pfVar1 = (float *)(**(code **)(**(int **)(param_1 + 0x38) + 4))(param_2);
    fVar2  = (float10)FUN_0040da40(*(float *)(param_1 + 0x14) - *pfVar1, 2);
    fVar3  = (float10)FUN_0040da40(*(float *)(param_1 + 0x1c) - pfVar1[2], 2);
    return fVar3 + (float10)(float)fVar2;
}
