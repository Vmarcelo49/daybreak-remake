// ============================================
// Address:  0x00659750
// Original: FUN_00659750
// Status:   unreviewed
// ============================================


void FUN_00659750(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  for (; param_1 != param_2; param_1 = param_1 + 0x14) {
    puVar2 = param_3;
    puVar3 = param_1;
    for (iVar1 = 0x14; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  return;
}

