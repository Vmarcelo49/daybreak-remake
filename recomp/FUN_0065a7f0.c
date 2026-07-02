// ============================================
// Address:  0x0065a7f0
// Original: FUN_0065a7f0
// Status:   unreviewed
// ============================================


void FUN_0065a7f0(void)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 local_8;
  
  local_8 = FUN_006543b0();
  piVar1 = (int *)FUN_00658a10(local_8);
  iVar2 = FUN_00654390();
  if (*piVar1 == iVar2) {
    puVar3 = (undefined4 *)FUN_00658a10(local_8);
    *puVar3 = 0;
    FUN_00654510(&local_8);
  }
  return;
}

