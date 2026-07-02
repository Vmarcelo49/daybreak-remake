// ============================================
// Address:  0x00686d80
// Original: FUN_00686d80
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_00686d80(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_006871b0(param_1,&DAT_006ad998);
  if ((iVar1 == 0) && (iVar1 = FUN_006871b0(param_1 + 0x2c,&DAT_006ad998), iVar1 == 0)) {
    return 0;
  }
  return 1;
}

