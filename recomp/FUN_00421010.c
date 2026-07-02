// ============================================
// Address:  0x00421010
// Original: FUN_00421010
// Status:   unreviewed
// ============================================


void __fastcall FUN_00421010(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int local_8;
  
  FUN_0064e600();
  FUN_004348e0();
  for (local_8 = 0; local_8 < 0xb; local_8 = local_8 + 1) {
    puVar2 = *(undefined4 **)(param_1 + 0x64c + local_8 * 4);
    puVar3 = (undefined4 *)(param_1 + 0x38c + local_8 * 0x40);
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  return;
}

