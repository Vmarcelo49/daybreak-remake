// ============================================
// Address:  0x00695f60
// Original: FUN_00695f60
// Status:   unreviewed
// ============================================


int __thiscall
FUN_00695f60(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  undefined4 *puVar1;
  undefined4 local_20;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fcdf;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00694800(param_2,param_3);
  local_8 = 0;
  FUN_00697f20();
  puVar1 = (undefined4 *)FUN_0068d8f0(0,0);
  FUN_0068d8f0(*puVar1,puVar1[1]);
  FUN_00697f20();
  *(undefined4 *)(param_1 + 0x38) = param_5;
  local_20 = 0xffffffff;
  local_1c = 0x7fffffff;
  FUN_00697ec0(&local_20);
  *(undefined8 *)(param_1 + 0x30) = 0x3ff0000000000000;
  ExceptionList = local_10;
  return param_1;
}

