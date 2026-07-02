// ============================================
// Address:  0x00667c00
// Original: FUN_00667c00
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_00667c00(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_3c [20];
  void *local_28;
  undefined4 local_24;
  void *local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f3a8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (param_1[1] != 0) {
    ExceptionList = &local_10;
    (**(code **)(*(int *)param_1[1] + 8))(param_1[1]);
    param_1[1] = 0;
  }
  FUN_0065a3c0();
  local_8 = 0;
  cVar1 = FUN_00661db0(param_2,local_3c);
  if (cVar1 == '\0') {
    local_8 = 0xffffffff;
    FUN_0065a420();
    uVar2 = 0;
  }
  else {
    param_1[2] = local_24;
    cVar1 = (**(code **)*param_1)(local_3c,param_1[2]);
    if (cVar1 == '\0') {
      local_8 = 0xffffffff;
      FUN_0065a420();
      uVar2 = 0;
    }
    else {
      iVar3 = (**(code **)(*(int *)param_1[1] + 0x2c))
                        (param_1[1],0,param_1[2],&local_20,&local_1c,&local_14,&local_18,2);
      if (iVar3 < 0) {
        FUN_00661cf0(&DAT_006ab214);
        local_8 = 0xffffffff;
        FUN_0065a420();
        uVar2 = 0;
      }
      else {
        _memcpy(local_20,local_28,param_1[2]);
        (**(code **)(*(int *)param_1[1] + 0x4c))(param_1[1],local_20,local_1c,local_14,local_18);
        local_8 = 0xffffffff;
        FUN_0065a420();
        uVar2 = 1;
      }
    }
  }
  ExceptionList = local_10;
  return uVar2;
}

