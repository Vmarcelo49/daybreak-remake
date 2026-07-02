// Function: FUN_00693cb0
// Address:  0x00693cb0
// Source:   batch_decompile (mass dump)
// Hash:     4cfd2b68e55580db


int __thiscall FUN_00693cb0(int *param_1,int param_2,undefined4 param_3)

{
  allocator<char> *this;
  undefined4 uVar1;
  int local_2c;
  int local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fbdf;
  local_10 = ExceptionList;
  if (param_2 == 0) {
    ExceptionList = &local_10;
    local_1c = FUN_006938a0(param_3);
  }
  else if (param_2 == *param_1) {
    ExceptionList = &local_10;
    local_1c = FUN_00693990(param_3);
  }
  else {
    ExceptionList = &local_10;
    local_1c = FUN_006941d0();
    if (local_1c == 0) {
      this = operator_new(0xc);
      local_8 = 0;
      if (this == (allocator<char> *)0x0) {
        local_2c = 0;
      }
      else {
        local_2c = std::allocator<char>::allocator<char>(this);
      }
      local_8 = 0xffffffff;
      local_1c = local_2c;
    }
    if (local_1c == 0) {
      local_1c = 0;
    }
    else {
      FUN_006940d0(param_3);
      uVar1 = FUN_0068de10();
      FUN_00687260(uVar1);
      FUN_006940b0(param_2);
      FUN_00687260(local_1c);
      FUN_006940b0(local_1c);
      param_1[2] = param_1[2] + 1;
    }
  }
  ExceptionList = local_10;
  return local_1c;
}

