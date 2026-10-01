// Function: FUN_00687350
// Address:  0x00687350
// Source:   batch_decompile (mass dump)
// Hash:     880aa37463671e72


int __thiscall
FUN_00687350(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 *param_5)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f3d8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068dee0(param_2,param_3);
  local_8 = 0;
  FUN_0068db70();
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  FUN_0068d890();
  *(undefined4 *)(param_1 + 0x20) = *param_5;
  *(undefined4 *)(param_1 + 0x24) = param_5[1];
  *(undefined4 *)(param_1 + 0x28) = param_5[2];
  *(undefined4 *)(param_1 + 0x2c) = param_5[3];
  *(undefined4 *)(param_1 + 0x30) = param_4;
  ExceptionList = local_10;
  return param_1;
}

