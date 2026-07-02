// Function: FUN_00697240
// Address:  0x00697240
// Source:   batch_decompile (mass dump)
// Hash:     190007af6f7eec6b


undefined4 __thiscall
FUN_00697240(int param_1,int *param_2,undefined4 param_3,undefined8 param_4,undefined4 param_5,
            undefined4 param_6,undefined2 param_7,undefined4 param_8,undefined4 param_9,
            undefined4 param_10,undefined4 param_11,undefined4 param_12)

{
  undefined4 uVar1;
  void *pvVar2;
  int local_30;
  undefined4 local_1c;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fdf3;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 8);
  local_8 = 0;
  local_1c = 0;
  *param_2 = 0;
  pvVar2 = operator_new(0x50);
  local_8 = CONCAT31(local_8._1_3_,1);
  if (pvVar2 == (void *)0x0) {
    local_30 = 0;
  }
  else {
    local_30 = FUN_00696bc0(param_1,0,&local_1c,param_3,param_4,param_5,param_6,param_7,param_8,
                            param_9,param_10,param_11,param_12);
  }
  local_18 = local_30;
  if (local_30 == 0) {
    local_1c = 0x8007000e;
  }
  else {
    *param_2 = local_30;
  }
  uVar1 = local_1c;
  local_8 = 0xffffffff;
  FUN_0068d9a0();
  ExceptionList = local_10;
  return uVar1;
}

