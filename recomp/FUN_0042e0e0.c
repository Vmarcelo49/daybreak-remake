// ============================================
// Address:  0x0042e0e0
// Original: FUN_0042e0e0
// Status:   unreviewed
// ============================================

float10 FUN_0042e0e0(float *param_1, float *param_2)

{
    return (float10)param_1[2] * (float10)param_2[2] + (float10)param_1[1] * (float10)param_2[1] +
           (float10)*param_1 * (float10)*param_2;
}
