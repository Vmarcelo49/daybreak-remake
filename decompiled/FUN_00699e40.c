// Function: FUN_00699e40
// Address:  0x00699e40
// Source:   batch_decompile (mass dump)
// Hash:     06aae0d727e89a50


int __thiscall
FUN_00699e40(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  int iVar1;
  undefined1 local_34 [4];
  int local_30;
  
  iVar1 = FUN_00699f20(param_2,param_3);
  if (((iVar1 == 0) || (iVar1 = FUN_00698fd0(param_4), iVar1 == 0)) ||
     (iVar1 = FUN_00698fd0(param_5), iVar1 == 0)) {
    local_30 = FUN_00699110(param_1,*(undefined4 *)(param_1 + 0x18),param_2,param_3,param_4,0,
                            param_5,0,0);
    if (-1 < local_30) {
      local_30 = FUN_00699180();
    }
  }
  else {
    local_30 = FUN_00699730(param_2,param_3,param_4,param_5,local_34,0);
  }
  return local_30;
}

