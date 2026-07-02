// Function: FUN_00667b00
// Address:  0x00667b00
// Source:   batch_decompile (mass dump)
// Hash:     0ed75b9bad78b529


undefined4 __thiscall
FUN_00667b00(undefined4 *param_1,void *param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  void *local_1c;
  size_t local_18;
  size_t local_14;
  void *local_10;
  undefined4 local_c;
  int local_8;
  
  if (param_1[1] != 0) {
    local_c = (**(code **)(*(int *)param_1[1] + 8))(param_1[1]);
    param_1[1] = 0;
  }
  cVar1 = (**(code **)*param_1)(param_4,param_3);
  if (cVar1 == '\0') {
    uVar2 = 0;
  }
  else {
    if (param_2 != (void *)0x0) {
      local_8 = (**(code **)(*(int *)param_1[1] + 0x2c))
                          (param_1[1],0,param_3,&local_1c,&local_18,&local_10,&local_14,2);
      if (local_8 < 0) {
        FUN_00661cf0(&DAT_006ab1fc);
        return 0;
      }
      _memcpy(local_1c,param_2,local_18);
      _memcpy(local_10,(void *)((int)param_2 + local_18),local_14);
      (**(code **)(*(int *)param_1[1] + 0x4c))(param_1[1],local_1c,local_18,local_10,local_14);
      param_1[2] = param_3;
    }
    uVar2 = 1;
  }
  return uVar2;
}

