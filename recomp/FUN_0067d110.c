// ============================================
// Address:  0x0067d110
// Original: FUN_0067d110
// Status:   unreviewed
// ============================================


float10 FUN_0067d110(float param_1,float param_2)

{
  float10 fVar1;
  
  if (param_1 <= 0.0) {
    if ((param_2 < 0.0) || (param_2 < -param_1)) {
      return -SQRT((float10)param_2 * (float10)param_2 + (float10)param_1 * (float10)param_1);
    }
  }
  else if (param_2 <= 0.0) {
    fVar1 = (float10)param_2 * (float10)param_2 + (float10)param_1 * (float10)param_1;
    if (param_1 <= -param_2) {
      return -SQRT(fVar1);
    }
    goto LAB_0067d199;
  }
  fVar1 = (float10)param_2 * (float10)param_2 + (float10)param_1 * (float10)param_1;
LAB_0067d199:
  return SQRT(fVar1);
}

