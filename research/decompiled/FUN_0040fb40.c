// Function: FUN_0040fb40
// Address:  0x0040fb40
// Source:   batch_decompile (mass dump)
// Hash:     2ba2302fc82d3c30


undefined4 FUN_0040fb40(undefined4 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 extraout_var;
  undefined1 local_14 [8];
  undefined1 local_c [8];
  
  uVar2 = FUN_00425150(local_c);
  uVar3 = extraout_var;
  cVar1 = FUN_00647670(uVar2);
  if (cVar1 == '\0') {
    puVar4 = (undefined4 *)FUN_0040fbf0(uVar3);
    *param_1 = *puVar4;
    FUN_00437270(local_14,0);
    uVar3 = *(undefined4 *)*param_1;
  }
  else {
    uVar3 = 8;
  }
  return uVar3;
}

