// Function: FUN_00421670
// Address:  0x00421670
// Source:   batch_decompile (mass dump)
// Hash:     e561cef53512583b


void __fastcall FUN_00421670(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  FUN_00424740(&stack0x00000004);
  puVar1 = (undefined4 *)FUN_00658a10(0);
  *(undefined4 *)(param_1 + 0x38) = *puVar1;
  puVar1 = (undefined4 *)FUN_00658a10(0);
  *(undefined4 *)(param_1 + 0x308) = *puVar1;
  uVar2 = FUN_00423940();
  FUN_00424840(uVar2);
  FUN_0042dd90();
  *(undefined4 *)(param_1 + 0x300) = 0;
  puVar1 = (undefined4 *)FUN_00658a10(0);
  *(undefined4 *)(param_1 + 0x38) = *puVar1;
  puVar1 = (undefined4 *)FUN_00658a10(0);
  *(undefined4 *)(param_1 + 0x308) = *puVar1;
  *(undefined4 *)(param_1 + 100) = 0;
  return;
}

