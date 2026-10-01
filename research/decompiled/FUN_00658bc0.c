// Function: FUN_00658bc0
// Address:  0x00658bc0
// Source:   batch_decompile (mass dump)
// Hash:     5e6f3eec2fc8ef4f


undefined4 FUN_00658bc0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 extraout_var;
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined4 local_8;
  
  iVar1 = FUN_0064f010();
  uVar3 = extraout_var;
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    uVar2 = FUN_00654620(local_c);
    local_8 = FUN_0064fa40(uVar2);
  }
  FUN_00658e60(param_2,1,param_3,local_8,uVar3);
  uVar3 = param_1;
  uVar2 = local_8;
  FUN_00654620(local_10);
  iterator__operator_(uVar3,uVar2);
  return param_1;
}

