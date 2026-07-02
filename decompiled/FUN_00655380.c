// Function: FUN_00655380
// Address:  0x00655380
// Source:   batch_decompile (mass dump)
// Hash:     af69caa4b65eb001


void __fastcall FUN_00655380(int param_1)

{
  if (*(int *)(param_1 + 0x20) != 0) {
    (**(code **)(**(int **)(param_1 + 0x20) + 8))(*(undefined4 *)(param_1 + 0x20));
    *(undefined4 *)(param_1 + 0x20) = 0;
  }
  if (*(int *)(param_1 + 0x1c) != 0) {
    (**(code **)(**(int **)(param_1 + 0x1c) + 8))(*(undefined4 *)(param_1 + 0x1c));
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  return;
}

