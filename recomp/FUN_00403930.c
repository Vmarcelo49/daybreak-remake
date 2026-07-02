// ============================================
// Address:  0x00403930
// Original: FUN_00403930
// Status:   unreviewed
// ============================================


void FUN_00403930(void)

{
  int iVar1;
  undefined4 extraout_var;
  undefined4 uVar2;
  int local_8;
  
  FUN_0065a090(DAT_006cfcf0 * DAT_006cfcf8);
  uVar2 = extraout_var;
  FUN_0065b9f0(DAT_006cfcf0 * DAT_006cfcf4);
  FUN_0065b250(DAT_006cfcf0 * DAT_006cfcfc);
  for (local_8 = 0; local_8 < 0x20; local_8 = local_8 + 1) {
    iVar1 = FUN_0068de10(uVar2);
    if (iVar1 != 0) {
      FUN_0065a1d0(*(undefined4 *)(&DAT_006ca838 + local_8 * 4),10000);
    }
  }
  return;
}

