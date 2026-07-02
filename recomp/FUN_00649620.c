// ============================================
// Address:  0x00649620
// Original: FUN_00649620
// Status:   unreviewed
// ============================================


void __fastcall FUN_00649620(int param_1)

{
  FUN_00650210();
  FUN_0065b520();
  FUN_0065b9b0();
  FUN_0065ba70(10000);
  FUN_0042fa80();
  FUN_0064c820();
  FUN_0064c820();
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
  return;
}

