// Function: FUN_00663d20
// Address:  0x00663d20
// Source:   batch_decompile (mass dump)
// Hash:     3c5a8a7c140fd22d


undefined4 * FUN_00663d20(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 extraout_var;
  undefined4 uVar4;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  uVar2 = FUN_00663240(local_8);
  uVar4 = extraout_var;
  cVar1 = const_iterator__operator__(uVar2);
  if (cVar1 != '\0') {
    uVar2 = FUN_00654620(local_c);
    cVar1 = const_iterator__operator__(uVar2);
    if (cVar1 != '\0') {
      FUN_00663420(uVar4);
      FUN_00663240(param_1);
      return param_1;
    }
  }
  while (cVar1 = const_iterator__operator__(&stack0x0000000c), cVar1 != '\0') {
    puVar3 = (undefined4 *)FUN_00663530(local_10,0);
    FUN_00664290(local_14,*puVar3);
  }
  *param_1 = param_2;
  return param_1;
}

