// Function: FUN_00663e30
// Address:  0x00663e30
// Source:   batch_decompile (mass dump)
// Hash:     05b68e1cb60c51c0


undefined4 __thiscall FUN_00663e30(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 local_c;
  undefined4 local_8;
  
  puVar2 = (undefined4 *)FUN_00663b30();
  local_c = *puVar2;
  local_8 = *(undefined4 *)(param_1 + 4);
  while (pcVar3 = (char *)FUN_00663560(local_c), *pcVar3 == '\0') {
    uVar5 = param_2;
    uVar4 = FUN_00663570(local_c,param_2);
    cVar1 = FUN_00663c00(uVar4,uVar5);
    if (cVar1 == '\0') {
      local_8 = local_c;
      puVar2 = (undefined4 *)FUN_00663590(local_c);
      local_c = *puVar2;
    }
    else {
      puVar2 = (undefined4 *)FUN_00654020(local_c);
      local_c = *puVar2;
    }
  }
  return local_8;
}

