// ============================================
// Address:  0x0042dec0
// Original: FUN_0042dec0
// Status:   unreviewed
// ============================================

float *__thiscall FUN_0042dec0(float *param_1, float *param_2)

{
    *param_1   = *param_1 + *param_2;
    param_1[1] = param_1[1] + param_2[1];
    param_1[2] = param_1[2] + param_2[2];
    return param_1;
}
