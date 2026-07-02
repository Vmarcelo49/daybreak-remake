// ============================================
// Address:  0x00425920
// Original: FUN_00425920
// Status:   unreviewed
// ============================================


undefined4 FUN_00425920(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 extraout_var;
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined4 local_8;
  
  iVar1 = FUN_004258e0();
  uVar3 = extraout_var;
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    uVar2 = FUN_00654620(local_c);
    local_8 = FUN_00426cf0(uVar2);
  }
  FUN_00426870(param_2,1,param_3,local_8,uVar3);
  uVar3 = param_1;
  uVar2 = local_8;
  FUN_00654620(local_10);
  FUN_00425e20(uVar3,uVar2);
  return param_1;
}

