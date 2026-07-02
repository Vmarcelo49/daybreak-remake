// ============================================
// Address:  0x0042fff0
// Original: FUN_0042fff0
// Status:   unreviewed
// ============================================


void __fastcall FUN_0042fff0(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int local_8;
  
  *(float *)(param_1 + 4) = *(float *)(param_1 + 4) + 0.016;
  iVar1 = FUN_00430670(param_1 + 0x98);
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_1 + 0x98);
    *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_1 + 0x9c);
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_1 + 0xa0);
    *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_1 + 0xa4);
    for (local_8 = 0xc; 1 < local_8; local_8 = local_8 + -1) {
      puVar2 = (undefined4 *)(param_1 + 0x88 + (local_8 + -1) * 0x10);
      puVar3 = (undefined4 *)(param_1 + 0x88 + local_8 * 0x10);
      *puVar3 = *puVar2;
      puVar3[1] = puVar2[1];
      puVar3[2] = puVar2[2];
      puVar3[3] = puVar2[3];
    }
    if (*(char *)(param_1 + 0x38) != '\0') {
      if (*(int *)(param_1 + 0x3c) < 0x28) {
        *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + 5;
      }
      if (0x28 < *(int *)(param_1 + 0x3c)) {
        *(undefined4 *)(param_1 + 0x3c) = 0x28;
      }
    }
  }
  if ((*(char *)(param_1 + 0x38) == '\0') && (0 < *(int *)(param_1 + 0x3c))) {
    *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + -2;
  }
  puVar2 = *(undefined4 **)(param_1 + 0x96c);
  puVar3 = (undefined4 *)(param_1 + 0x48);
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  return;
}

