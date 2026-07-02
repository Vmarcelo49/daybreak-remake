// ============================================
// Address:  0x00679b60
// Original: FUN_00679b60
// Status:   unreviewed
// ============================================


void FUN_00679b60(undefined4 *param_1)

{
  void *pvVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = param_1;
  for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  pvVar1 = _calloc(1,0xe80);
  param_1[7] = pvVar1;
  return;
}

