// ============================================
// Address:  0x00633860
// Original: FUN_00633860
// Status:   unreviewed
// ============================================


void __fastcall FUN_00633860(int param_1)

{
  undefined4 uVar1;
  
  if (*(char *)(param_1 + 0x95) == '\0') {
    FUN_00661740(0x3f490fdb,0x3faaaaab,0x42480000,0x48127c00);
  }
  else {
    FUN_00661740(0x3de5c8fa,0x3faaaaab,0x42c80000,0x48127c00);
  }
  FUN_006618a0(*(undefined4 *)(param_1 + 0x30),*(undefined4 *)(param_1 + 0x34),
               *(undefined4 *)(param_1 + 0x38));
  FUN_00661910(*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 100),
               *(undefined4 *)(param_1 + 0x68));
  FUN_0066b860(param_1 + 0x96,&DAT_006a491e);
  uVar1 = FUN_0064ecb0();
  FUN_00633930(uVar1);
  return;
}

