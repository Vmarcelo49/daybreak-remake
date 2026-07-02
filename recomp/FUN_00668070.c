// ============================================
// Address:  0x00668070
// Original: FUN_00668070
// Status:   unreviewed
// ============================================


void __fastcall FUN_00668070(undefined4 *param_1)

{
  char cVar1;
  
  FUN_006777e0(param_1 + 4);
  cVar1 = FUN_0064d6e0();
  if (cVar1 == '\0') {
    FUN_006536c0(*param_1);
    FUN_00654170(0);
  }
  if (param_1[0x4c3] != 0) {
    _free((void *)param_1[0x4c3]);
    param_1[0x4c3] = 0;
  }
  return;
}

