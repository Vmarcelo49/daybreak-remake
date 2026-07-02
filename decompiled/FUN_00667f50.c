// Function: FUN_00667f50
// Address:  0x00667f50
// Source:   batch_decompile (mass dump)
// Hash:     10808e30d92d5c31


undefined4 __fastcall FUN_00667f50(int param_1)

{
  uint local_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  if (*(int *)(param_1 + 4) != 0) {
    (**(code **)(**(int **)(param_1 + 4) + 0x24))(*(undefined4 *)(param_1 + 4),&local_c);
    if ((local_c & 1) != 0) {
      (**(code **)(**(int **)(param_1 + 4) + 0x10))(*(undefined4 *)(param_1 + 4),&local_8,0);
    }
  }
  return local_8;
}

