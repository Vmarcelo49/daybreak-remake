// Function: FUN_0068a050
// Address:  0x0068a050
// Source:   batch_decompile (mass dump)
// Hash:     7e64bd5332b61686


int __fastcall FUN_0068a050(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x98) != 0) {
    iVar1 = (**(code **)(**(int **)(param_1 + 0x98) + 0x18))(*(undefined4 *)(param_1 + 0x98));
    if (iVar1 < 0) {
      return iVar1;
    }
    (**(code **)(**(int **)(param_1 + 0x98) + 8))(*(undefined4 *)(param_1 + 0x98));
    *(undefined4 *)(param_1 + 0x98) = 0;
  }
  if (*(int *)(param_1 + 0x9c) != 0) {
    (**(code **)(**(int **)(param_1 + 0x9c) + 8))(*(undefined4 *)(param_1 + 0x9c));
    *(undefined4 *)(param_1 + 0x9c) = 0;
  }
  return 0;
}

