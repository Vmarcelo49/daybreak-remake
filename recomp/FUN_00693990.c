// ============================================
// Address:  0x00693990
// Original: FUN_00693990
// Status:   unreviewed
// ============================================


int __thiscall FUN_00693990(int *param_1,undefined4 param_2)

{
  allocator<char> *this;
  int local_24;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fbb5;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_14 = FUN_006941d0();
  if (local_14 == 0) {
    this = operator_new(0xc);
    local_8 = 0;
    if (this == (allocator<char> *)0x0) {
      local_24 = 0;
    }
    else {
      local_24 = std::allocator<char>::allocator<char>(this);
    }
    local_8 = 0xffffffff;
    local_14 = local_24;
  }
  if (local_14 == 0) {
    local_14 = 0;
  }
  else {
    FUN_006940d0(param_2);
    FUN_00687260(0);
    FUN_006940b0(*param_1);
    if (*param_1 == 0) {
      param_1[1] = local_14;
    }
    else {
      FUN_00687260(local_14);
    }
    *param_1 = local_14;
    param_1[2] = param_1[2] + 1;
  }
  ExceptionList = local_10;
  return local_14;
}

