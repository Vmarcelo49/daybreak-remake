// ============================================
// Address:  0x0068a740
// Original: FUN_0068a740
// Status:   unreviewed
// ============================================


int __fastcall FUN_0068a740(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x9c) != 0) {
    iVar1 = (**(code **)(**(int **)(param_1 + 0x9c) + 0x18))(*(undefined4 *)(param_1 + 0x9c));
    if (iVar1 < 0) {
      return iVar1;
    }
    (**(code **)(**(int **)(param_1 + 0x9c) + 8))(*(undefined4 *)(param_1 + 0x9c));
    *(undefined4 *)(param_1 + 0x9c) = 0;
  }
  return 0;
}

