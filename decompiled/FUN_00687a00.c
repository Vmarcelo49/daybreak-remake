// Function: FUN_00687a00
// Address:  0x00687a00
// Source:   batch_decompile (mass dump)
// Hash:     b47fd04c8ed3489b


int __thiscall
FUN_00687a00(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 *param_5)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f444;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068dee0(param_2,param_3);
  local_8 = 0;
  FUN_0068d8b0();
  FUN_0068d8d0();
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  FUN_0068d890();
  *(undefined4 *)(param_1 + 0x28) = *param_5;
  *(undefined4 *)(param_1 + 0x2c) = param_5[1];
  *(undefined4 *)(param_1 + 0x30) = param_5[2];
  *(undefined4 *)(param_1 + 0x34) = param_5[3];
  *(undefined4 *)(param_1 + 0x38) = param_4;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x48) = 1;
  ExceptionList = local_10;
  return param_1;
}

