// Function: FUN_0067a270
// Address:  0x0067a270
// Source:   batch_decompile (mass dump)
// Hash:     02cafa42e278121b


undefined4 FUN_0067a270(int *param_1,undefined4 *param_2)

{
  void *pvVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = param_2;
  for (iVar2 = 0x1c; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  param_2[0x10] = param_1;
  param_2[0x13] = 0;
  param_2[0x11] = 0;
  if (*param_1 != 0) {
    pvVar1 = _calloc(1,0x48);
    param_2[0x1a] = pvVar1;
    FUN_0069d480(param_2 + 1);
    *(undefined4 *)((int)pvVar1 + 4) = 0xc61c3c00;
  }
  return 0;
}

