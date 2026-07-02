// ============================================
// Address:  0x0042d980
// Original: FUN_0042d980
// Status:   unreviewed
// ============================================


float10 __fastcall FUN_0042d980(int param_1)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = (float10)FUN_0040da40(*(float *)(param_1 + 0x14) -
                                *(float *)(*(int *)(param_1 + 0x38) + 0x14),2);
  fVar2 = (float10)FUN_0040da40(*(float *)(param_1 + 0x1c) -
                                *(float *)(*(int *)(param_1 + 0x38) + 0x1c),2);
  return fVar2 + (float10)(float)fVar1;
}

