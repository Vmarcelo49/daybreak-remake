// ============================================
// Address:  0x0068fe80
// Original: FUN_0068fe80
// Status:   unreviewed
// ============================================


void __fastcall FUN_0068fe80(int param_1)

{
  int iVar1;
  int local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f9fc;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 0x94);
  local_8 = 0;
  if (*(int *)(param_1 + 0x60) == 0) {
    iVar1 = FUN_0068da80();
    if (iVar1 == 1) {
      iVar1 = FUN_00691ab0();
      if (iVar1 == 0) {
        iVar1 = FUN_00691b70();
        if ((iVar1 == 0) && (*(int *)(param_1 + 0xb0) == 1)) {
          if (*(int *)(param_1 + 0x78) == 0) {
            local_20 = 0;
          }
          else {
            local_20 = *(int *)(param_1 + 0x78) + 0xc;
          }
          FUN_006883f0(5,local_20,0);
          FUN_0068fde0(0);
        }
      }
    }
  }
  local_8 = 0xffffffff;
  FUN_0068d9a0();
  ExceptionList = local_10;
  return;
}

