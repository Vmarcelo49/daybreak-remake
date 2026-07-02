// ============================================
// Address:  0x0067e0e0
// Original: FUN_0067e0e0
// Status:   unreviewed
// ============================================


void FUN_0067e0e0(undefined4 *param_1)

{
  int iVar1;
  
  if ((void *)param_1[4] != (void *)0x0) {
    _free((void *)param_1[4]);
  }
  if ((void *)param_1[5] != (void *)0x0) {
    _free((void *)param_1[5]);
  }
  if ((void *)param_1[6] != (void *)0x0) {
    _free((void *)param_1[6]);
  }
  if ((void *)param_1[7] != (void *)0x0) {
    _free((void *)param_1[7]);
  }
  if ((void *)param_1[8] != (void *)0x0) {
    _free((void *)param_1[8]);
  }
  for (iVar1 = 0xb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = 0;
    param_1 = param_1 + 1;
  }
  return;
}

