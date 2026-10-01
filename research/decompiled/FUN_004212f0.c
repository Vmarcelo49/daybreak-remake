// Function: FUN_004212f0
// Address:  0x004212f0
// Source:   batch_decompile (mass dump)
// Hash:     845d56c74b201f87


void __fastcall FUN_004212f0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  FUN_004244e0(*(undefined4 *)(param_1 + 0xadf4));
  iVar1 = FUN_0063bf40();
  if (*(int *)(param_1 + 0xadfc) + 1 < iVar1) {
    do {
      iVar3 = *(int *)(param_1 + 0xadfc) + 1;
      FUN_004244e0(*(undefined4 *)(param_1 + 0xadf4));
      iVar3 = FUN_00424370(iVar3);
      if (*(int *)(param_1 + 0xae04) < *(int *)(iVar3 + 4)) goto LAB_004213c7;
      *(int *)(param_1 + 0xadfc) = *(int *)(param_1 + 0xadfc) + 1;
    } while (*(int *)(param_1 + 0xadfc) + 1 < iVar1);
    *(int *)(param_1 + 0xadfc) = iVar1 + -1;
LAB_004213c7:
    uVar2 = *(undefined4 *)(param_1 + 0xadfc);
    FUN_004244e0(*(undefined4 *)(param_1 + 0xadf4));
    uVar2 = FUN_00424370(uVar2);
    *(undefined4 *)(param_1 + 0x10) = uVar2;
  }
  return;
}

