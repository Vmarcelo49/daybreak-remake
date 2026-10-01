// Function: FUN_0064e420
// Address:  0x0064e420
// Source:   batch_decompile (mass dump)
// Hash:     068d64ee31a0f137


void __thiscall FUN_0064e420(int param_1,int param_2)

{
  int local_24;
  uint local_1c;
  undefined4 local_18;
  uint local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  for (local_8 = *(int *)(param_2 + 0x44); local_8 != 0; local_8 = *(int *)(local_8 + 0x20)) {
    if (local_8 == 0) {
      local_24 = 0;
    }
    else {
      local_24 = local_8 + -4;
    }
    local_c = local_24;
    if (*(int *)(local_24 + 0x20) != 0) {
      local_14 = (**(code **)(**(int **)(local_24 + 0x20) + 0x24))(*(undefined4 *)(local_24 + 0x20))
      ;
      for (local_1c = 0; local_1c < local_14; local_1c = local_1c + 1) {
        D3DXMatrixMultiply(local_1c * 0x40 + *(int *)(param_1 + 4),
                           local_1c * 0x40 + *(int *)(local_c + 0x44),
                           *(undefined4 *)(*(int *)(local_c + 0x40) + local_1c * 4));
      }
      (**(code **)(**(int **)(local_c + 0x30) + 0x3c))
                (*(undefined4 *)(local_c + 0x30),0x10,&local_10);
      (**(code **)(**(int **)(local_c + 0xc) + 0x3c))(*(undefined4 *)(local_c + 0xc),0,&local_18);
      (**(code **)(**(int **)(local_c + 0x20) + 0x60))
                (*(undefined4 *)(local_c + 0x20),*(undefined4 *)(param_1 + 4),0,local_10,local_18);
      (**(code **)(**(int **)(local_c + 0x30) + 0x40))(*(undefined4 *)(local_c + 0x30));
      (**(code **)(**(int **)(local_c + 0xc) + 0x40))(*(undefined4 *)(local_c + 0xc));
    }
  }
  if (*(int *)(param_2 + 0x48) != 0) {
    FUN_0064e420(*(undefined4 *)(param_2 + 0x48));
  }
  if (*(int *)(param_2 + 0x4c) != 0) {
    FUN_0064e420(*(undefined4 *)(param_2 + 0x4c));
  }
  return;
}

