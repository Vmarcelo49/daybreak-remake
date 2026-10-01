// Function: FUN_00686780
// Address:  0x00686780
// Source:   batch_decompile (mass dump)
// Hash:     c3c72244a6ddab69


float10 FUN_00686780(float param_1)

{
  uint uVar1;
  
  uVar1 = (uint)ROUND(param_1 * -8.0 - 0.5);
  if ((int)uVar1 < 0) {
    return (float10)1.0;
  }
  if (0x45f < (int)uVar1) {
    return (float10)0.0;
  }
  return (float10)*(float *)(&DAT_006c70b4 + (uVar1 & 0x1f) * 4) *
         (float10)*(float *)(&DAT_006c7028 + ((int)uVar1 >> 5) * 4);
}

