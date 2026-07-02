// Function: FUN_00648450
// Address:  0x00648450
// Source:   batch_decompile (mass dump)
// Hash:     b3c1f2e18674d7c6


void __fastcall FUN_00648450(int param_1)

{
  int local_c;
  int local_8;
  
  FUN_00645b90();
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
  FUN_00656200(*(undefined4 *)(param_1 + 0x498));
  FUN_00660050();
  FUN_0065f8b0();
  if (*(char *)(param_1 + 0x54cd) != '\0') {
    FUN_00650ef0();
  }
  FUN_0065b6f0();
  for (local_8 = 0; local_8 < 0x100; local_8 = local_8 + 1) {
    FUN_00659fb0(*(undefined4 *)(param_1 + 0x98 + local_8 * 4));
  }
  for (local_c = 0; local_c < 0x20; local_c = local_c + 1) {
    FUN_00659fb0(*(undefined4 *)(param_1 + 0x18 + local_c * 4));
  }
  FUN_00634520();
  FUN_0042ea40();
  FUN_0065b0a0();
  FUN_00659d30();
  return;
}

