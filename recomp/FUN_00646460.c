// ============================================
// Address:  0x00646460
// Original: FUN_00646460
// Status:   unreviewed
// ============================================


void __fastcall FUN_00646460(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_8 [4];
  
  FUN_00647220();
  FUN_0065d670();
  FUN_00656200(*(undefined4 *)(param_1 + 0x13c));
  uVar3 = *(undefined4 *)(param_1 + 0x144);
  uVar1 = FUN_00647130(uVar3);
  puVar2 = (undefined4 *)FUN_00656190(local_8,uVar1,uVar3);
  *(undefined4 *)(param_1 + 0x13c) = *puVar2;
  FUN_00655af0(*(undefined4 *)(param_1 + 0x13c),0,0,300,0x200);
  FUN_0065d6a0();
  return;
}

