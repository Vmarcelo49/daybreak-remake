// Function: FUN_0068ff60
// Address:  0x0068ff60
// Source:   batch_decompile (mass dump)
// Hash:     86c183facf269016


undefined4 __fastcall FUN_0068ff60(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int local_28;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fa0e;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 0x25);
  local_8 = 0;
  iVar1 = FUN_0068da80();
  if (iVar1 == 0) {
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    uVar2 = 0;
  }
  else {
    if (param_1[0x1e] == 0) {
      local_28 = 0;
    }
    else {
      local_28 = param_1[0x1e] + 0xc;
    }
    (**(code **)(*(int *)(param_1[0x1e] + 0xc) + 4))(param_1[0x1e] + 0xc);
    FUN_006883f0(0x16,local_28,0);
    FUN_00691bd0(1);
    (**(code **)(*param_1 + 0x70))();
    (**(code **)(*(int *)(param_1[0x1e] + 0xc) + 8))(param_1[0x1e] + 0xc);
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    uVar2 = 1;
  }
  ExceptionList = local_10;
  return uVar2;
}

