// ============================================
// Address:  0x0067d040
// Original: FUN_0067d040
// Status:   unreviewed
// ============================================


float10 FUN_0067d040(float param_1,float param_2)

{
  if (param_1 <= 0.0) {
    if (param_2 < 0.0) {
      return -SQRT((float10)param_2 * (float10)param_2 + (float10)param_1 * (float10)param_1);
    }
    if ((float10)param_2 < -(float10)param_1) {
      return -SQRT((float10)param_1 * (float10)param_1 - (float10)param_2 * (float10)param_2);
    }
    return SQRT((float10)param_2 * (float10)param_2 - (float10)param_1 * (float10)param_1);
  }
  if (0.0 < param_2) {
    return SQRT((float10)param_2 * (float10)param_2 + (float10)param_1 * (float10)param_1);
  }
  if (-param_2 < param_1) {
    return SQRT((float10)param_1 * (float10)param_1 - (float10)param_2 * (float10)param_2);
  }
  return -SQRT((float10)param_2 * (float10)param_2 - (float10)param_1 * (float10)param_1);
}

