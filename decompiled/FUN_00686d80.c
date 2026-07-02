// Function: FUN_00686d80
// Address:  0x00686d80
// Source:   batch_decompile (mass dump)
// Hash:     0aeec4c5bf313834


undefined4 __fastcall FUN_00686d80(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_006871b0(param_1,&DAT_006ad998);
  if ((iVar1 == 0) && (iVar1 = FUN_006871b0(param_1 + 0x2c,&DAT_006ad998), iVar1 == 0)) {
    return 0;
  }
  return 1;
}

