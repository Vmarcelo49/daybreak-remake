// Function: FUN_00648cf0
// Address:  0x00648cf0
// Source:   batch_decompile (mass dump)
// Hash:     56f4b6740ed1ef6d


void __fastcall FUN_00648cf0(int param_1)

{
  int local_8;
  
  FUN_00650210();
  FUN_0065b520();
  FUN_0065b9b0();
  FUN_0065ba70(10000);
  FUN_0042fa80();
  if (*(int *)(param_1 + 0x52c0) != 0) {
    if (*(undefined4 **)(param_1 + 0x52c0) != (undefined4 *)0x0) {
      (**(code **)**(undefined4 **)(param_1 + 0x52c0))(1);
    }
    *(undefined4 *)(param_1 + 0x52c0) = 0;
  }
  if (*(int *)(param_1 + 0x52c4) != 0) {
    if (*(undefined4 **)(param_1 + 0x52c4) != (undefined4 *)0x0) {
      (**(code **)**(undefined4 **)(param_1 + 0x52c4))(1);
    }
    *(undefined4 *)(param_1 + 0x52c4) = 0;
  }
  if (*(int *)(param_1 + 0x52c8) != 0) {
    if (*(undefined4 **)(param_1 + 0x52c8) != (undefined4 *)0x0) {
      (**(code **)**(undefined4 **)(param_1 + 0x52c8))(1);
    }
    *(undefined4 *)(param_1 + 0x52c8) = 0;
  }
  if (*(int *)(param_1 + 0x52cc) != 0) {
    if (*(undefined4 **)(param_1 + 0x52cc) != (undefined4 *)0x0) {
      (**(code **)**(undefined4 **)(param_1 + 0x52cc))(1);
    }
    *(undefined4 *)(param_1 + 0x52cc) = 0;
  }
  if (*(int *)(param_1 + 0x52d0) != 0) {
    if (*(int *)(param_1 + 0x52d0) != 0) {
      FUN_0064c7f0(1);
    }
    *(undefined4 *)(param_1 + 0x52d0) = 0;
  }
  for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1) {
    if ((*(int *)(*(int *)(param_1 + 0x5204) + local_8 * 4) != 0) &&
       (*(int *)(*(int *)(param_1 + 0x5204) + local_8 * 4) != 0)) {
      if (*(int *)(*(int *)(param_1 + 0x5204) + local_8 * 4) != 0) {
        FUN_0040dce0(1);
      }
      *(undefined4 *)(*(int *)(param_1 + 0x5204) + local_8 * 4) = 0;
    }
  }
  return;
}

