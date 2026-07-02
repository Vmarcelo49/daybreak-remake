// Function: FUN_00663ff0
// Address:  0x00663ff0
// Source:   batch_decompile (mass dump)
// Hash:     45f344d62cfeaa2a


void FUN_00663ff0(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  char *pcVar4;
  int *piVar5;
  
  puVar2 = (undefined4 *)FUN_00663590(param_1);
  uVar1 = *puVar2;
  puVar2 = (undefined4 *)FUN_00654020(uVar1);
  puVar3 = (undefined4 *)FUN_00663590(param_1);
  *puVar3 = *puVar2;
  puVar2 = (undefined4 *)FUN_00654020(uVar1);
  pcVar4 = (char *)FUN_00663560(*puVar2);
  if (*pcVar4 == '\0') {
    puVar2 = (undefined4 *)FUN_00654020(uVar1);
    piVar5 = (int *)FUN_00653df0(*puVar2);
    *piVar5 = param_1;
  }
  puVar2 = (undefined4 *)FUN_00653df0(param_1);
  puVar3 = (undefined4 *)FUN_00653df0(uVar1);
  *puVar3 = *puVar2;
  piVar5 = (int *)FUN_00663b30();
  if (param_1 == *piVar5) {
    puVar2 = (undefined4 *)FUN_00663b30();
    *puVar2 = uVar1;
  }
  else {
    puVar2 = (undefined4 *)FUN_00653df0(param_1);
    piVar5 = (int *)FUN_00654020(*puVar2);
    if (param_1 == *piVar5) {
      puVar2 = (undefined4 *)FUN_00653df0(param_1);
      puVar2 = (undefined4 *)FUN_00654020(*puVar2);
      *puVar2 = uVar1;
    }
    else {
      puVar2 = (undefined4 *)FUN_00653df0(param_1);
      puVar2 = (undefined4 *)FUN_00663590(*puVar2);
      *puVar2 = uVar1;
    }
  }
  piVar5 = (int *)FUN_00654020(uVar1);
  *piVar5 = param_1;
  puVar2 = (undefined4 *)FUN_00653df0(param_1);
  *puVar2 = uVar1;
  return;
}

