// ============================================
// Address:  0x006815f0
// Original: FUN_006815f0
// Status:   unreviewed
// ============================================


void FUN_006815f0(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  fVar1 = param_1[6];
  fVar2 = param_1[6];
  fVar3 = param_1[4];
  fVar4 = *param_1;
  param_1[6] = *param_1 + param_1[4] + param_1[2] + fVar1;
  param_1[4] = (param_1[2] + fVar1) - (*param_1 + param_1[4]);
  fVar1 = param_1[3];
  *param_1 = (fVar2 - param_1[2]) + (param_1[5] - param_1[1]);
  param_1[2] = (fVar2 - param_1[2]) - (param_1[5] - param_1[1]);
  fVar2 = param_1[1];
  fVar5 = param_1[3];
  fVar6 = param_1[7];
  param_1[3] = (fVar3 - fVar4) + (param_1[7] - fVar1);
  param_1[1] = (param_1[7] - fVar1) - (fVar3 - fVar4);
  param_1[7] = fVar5 + fVar6 + fVar2 + param_1[5];
  param_1[5] = (fVar5 + fVar6) - (fVar2 + param_1[5]);
  return;
}

