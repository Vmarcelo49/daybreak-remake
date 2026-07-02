// ============================================
// Address:  0x00663dc0
// Original: FUN_00663dc0
// Status:   unreviewed
// ============================================


void __fastcall FUN_00663dc0(int param_1)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  undefined4 *puVar3;
  
  uVar1 = FUN_00664a40();
  *(undefined4 *)(param_1 + 4) = uVar1;
  puVar2 = (undefined1 *)FUN_00663560(*(undefined4 *)(param_1 + 4));
  *puVar2 = 1;
  puVar3 = (undefined4 *)FUN_00663b30();
  *puVar3 = *(undefined4 *)(param_1 + 4);
  puVar3 = (undefined4 *)FUN_00663af0();
  *puVar3 = *(undefined4 *)(param_1 + 4);
  puVar3 = (undefined4 *)FUN_00663b10();
  *puVar3 = *(undefined4 *)(param_1 + 4);
  *(undefined4 *)(param_1 + 8) = 0;
  return;
}

