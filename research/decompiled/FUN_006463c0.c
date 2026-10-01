// Function: FUN_006463c0
// Address:  0x006463c0
// Source:   batch_decompile (mass dump)
// Hash:     79a4367eb605810b


void __fastcall FUN_006463c0(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_8 [4];
  
  FUN_006471d0();
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

