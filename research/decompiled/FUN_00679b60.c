// Function: FUN_00679b60
// Address:  0x00679b60
// Source:   batch_decompile (mass dump)
// Hash:     4dde0bb3f87942d7


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

