// Function: FUN_00650210
// Address:  0x00650210
// Source:   batch_decompile (mass dump)
// Hash:     e049bc95a72eb320


void __fastcall FUN_00650210(int param_1)

{
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < 10; local_8 = local_8 + 1) {
    if (*(int *)(param_1 + local_8 * 4) != 0) {
      (**(code **)(**(int **)(param_1 + local_8 * 4) + 8))(*(undefined4 *)(param_1 + local_8 * 4));
      *(undefined4 *)(param_1 + local_8 * 4) = 0;
    }
  }
  FUN_0064ff80();
  return;
}

