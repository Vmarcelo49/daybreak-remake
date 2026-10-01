// Function: FUN_0068d030
// Address:  0x0068d030
// Source:   batch_decompile (mass dump)
// Hash:     8276cb75afa17f64


undefined4 FUN_0068d030(undefined4 param_1,undefined4 param_2)

{
  void *pvVar1;
  undefined4 local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f7c7;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  pvVar1 = operator_new(100);
  local_8 = 0;
  if (pvVar1 == (void *)0x0) {
    local_20 = 0;
  }
  else {
    local_20 = FUN_0068d0b0(0,param_1,param_2);
  }
  ExceptionList = local_10;
  return local_20;
}

