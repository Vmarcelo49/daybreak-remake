// Function: FUN_00686720
// Address:  0x00686720
// Source:   batch_decompile (mass dump)
// Hash:     d3a9137697a94047


float10 FUN_00686720(float param_1)

{
  int iVar1;
  float fVar2;
  
  fVar2 = param_1 * 64.0 - 32.0;
  iVar1 = (int)ROUND(fVar2 - 0.5);
  return ((float10)fVar2 - (float10)iVar1) *
         ((float10)*(float *)(&DAT_006c6ea4 + iVar1 * 4) -
         (float10)*(float *)(&DAT_006c6ea0 + iVar1 * 4)) +
         (float10)*(float *)(&DAT_006c6ea0 + iVar1 * 4);
}

