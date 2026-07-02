// ============================================
// Address:  0x0068a320
// Original: FUN_0068a320
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_0068a320(int param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x98) == 0) {
    uVar1 = 0x8004020a;
  }
  else {
    uVar1 = (**(code **)(**(int **)(param_1 + 0x98) + 0x14))(*(undefined4 *)(param_1 + 0x98));
  }
  return uVar1;
}

