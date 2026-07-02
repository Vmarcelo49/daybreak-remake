// ============================================
// Address:  0x00664d20
// Original: FUN_00664d20
// Status:   unreviewed
// ============================================


void __fastcall FUN_00664d20(int *param_1)

{
  char *pcVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  
  pcVar1 = (char *)FUN_00663560(*param_1);
  if (*pcVar1 == '\0') {
    puVar2 = (undefined4 *)FUN_00654020(*param_1);
    pcVar1 = (char *)FUN_00663560(*puVar2);
    if (*pcVar1 == '\0') {
      puVar2 = (undefined4 *)FUN_00654020(*param_1);
      iVar3 = FUN_00664e80(*puVar2);
      *param_1 = iVar3;
    }
    else {
      while( true ) {
        piVar4 = (int *)FUN_00653df0(*param_1);
        iVar3 = *piVar4;
        pcVar1 = (char *)FUN_00663560(iVar3);
        if ((*pcVar1 != '\0') || (piVar4 = (int *)FUN_00654020(iVar3), *param_1 != *piVar4)) break;
        *param_1 = iVar3;
      }
      *param_1 = iVar3;
    }
  }
  return;
}

