// ============================================
// Address:  0x00695960
// Original: FUN_00695960
// Status:   unreviewed
// ============================================


uint FUN_00695960(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  
  if (param_2 == 0) {
    uVar1 = 0x80004003;
  }
  else {
    iVar2 = FUN_006871b0(param_2,&DAT_006ad154);
    uVar1 = (uint)(iVar2 == 0);
  }
  return uVar1;
}

