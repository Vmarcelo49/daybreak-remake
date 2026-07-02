// ============================================
// Address:  0x00664c40
// Original: FUN_00664c40
// Status:   unreviewed
// ============================================


void __fastcall FUN_00664c40(int *param_1)

{
  char *pcVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  
  pcVar1 = (char *)FUN_00663560(*param_1);
  if (*pcVar1 == '\0') {
    puVar3 = (undefined4 *)FUN_00663590(*param_1);
    pcVar1 = (char *)FUN_00663560(*puVar3);
    if (*pcVar1 == '\0') {
      puVar3 = (undefined4 *)FUN_00663590(*param_1);
      iVar4 = FUN_00664e40(*puVar3);
      *param_1 = iVar4;
    }
    else {
      while( true ) {
        piVar2 = (int *)FUN_00653df0(*param_1);
        iVar4 = *piVar2;
        pcVar1 = (char *)FUN_00663560(iVar4);
        if (*pcVar1 != '\0') break;
        piVar2 = (int *)FUN_00663590(iVar4);
        if (*param_1 != *piVar2) break;
        *param_1 = iVar4;
      }
      pcVar1 = (char *)FUN_00663560(iVar4);
      if (*pcVar1 == '\0') {
        *param_1 = iVar4;
      }
    }
  }
  else {
    piVar2 = (int *)FUN_00654020(*param_1);
    *param_1 = *piVar2;
  }
  return;
}

