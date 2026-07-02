// Function: FUN_0067a9d0
// Address:  0x0067a9d0
// Source:   batch_decompile (mass dump)
// Hash:     badbcb93ff2c51cc


undefined4 FUN_0067a9d0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  byte bVar3;
  int iVar4;
  
  iVar1 = *(int *)(param_1 + 0x68);
  if (iVar1 == 0) {
    return 0xffffffff;
  }
  if (*(int *)(param_1 + 4) == 0) {
    return 0xffffffff;
  }
  iVar4 = *(int *)(*(int *)(param_1 + 4) + 0x1c);
  if (iVar4 == 0) {
    return 0xffffffff;
  }
  uVar2 = *(undefined4 *)(iVar4 + 0xe78);
  iVar4 = *(int *)(iVar4 + 4);
  *(undefined4 *)(param_1 + 0x20) = 0;
  bVar3 = (byte)uVar2;
  iVar4 = iVar4 >> (bVar3 + 1 & 0x1f);
  *(int *)(param_1 + 0x30) = iVar4;
  *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x40) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x18) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x3c) = 0xffffffff;
  *(int *)(param_1 + 0x14) = iVar4 >> (bVar3 & 0x1f);
  *(undefined4 *)(param_1 + 0x44) = 0xffffffff;
  *(undefined4 *)(iVar1 + 0xb8) = 0xffffffff;
  *(undefined4 *)(iVar1 + 0xbc) = 0xffffffff;
  return 0;
}

