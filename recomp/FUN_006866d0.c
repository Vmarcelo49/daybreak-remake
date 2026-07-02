// ============================================
// Address:  0x006866d0
// Original: FUN_006866d0
// Status:   unreviewed
// ============================================


float10 FUN_006866d0(float param_1)

{
  int iVar1;
  
  iVar1 = (int)ROUND(param_1 * 40.743668 - 0.5);
  return ((float10)(param_1 * 40.743668) - (float10)iVar1) *
         ((float10)*(float *)(&DAT_006c6ca0 + iVar1 * 4) -
         (float10)*(float *)(&DAT_006c6c9c + iVar1 * 4)) +
         (float10)*(float *)(&DAT_006c6c9c + iVar1 * 4);
}

