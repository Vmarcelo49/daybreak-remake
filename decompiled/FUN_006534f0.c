// Function: FUN_006534f0
// Address:  0x006534f0
// Source:   batch_decompile (mass dump)
// Hash:     dd451e919e98e7d8


void __fastcall FUN_006534f0(int param_1)

{
  undefined4 *puVar1;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  FUN_004261d0();
  puVar1 = (undefined4 *)FUN_00653d10(local_8);
  *(undefined4 *)(param_1 + 0x74) = *puVar1;
  puVar1 = (undefined4 *)FUN_00654620(local_c);
  *(undefined4 *)(param_1 + 0x78) = *puVar1;
  *(undefined4 *)(param_1 + 0x7c) = 0;
  return;
}

