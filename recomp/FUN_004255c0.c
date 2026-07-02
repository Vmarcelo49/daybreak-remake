// ============================================
// Address:  0x004255c0
// Original: FUN_004255c0
// Status:   unreviewed
// ============================================


void FUN_004255c0(undefined4 param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_30 [4];
  undefined4 local_2c [10];
  
  puVar3 = local_2c;
  for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *param_2;
    param_2 = param_2 + 1;
    puVar3 = puVar3 + 1;
  }
  FUN_004261d0();
  puVar3 = local_2c;
  puVar1 = (undefined4 *)FUN_00653d10(local_30);
  FUN_00426330(*puVar1,param_1,puVar3);
  return;
}

