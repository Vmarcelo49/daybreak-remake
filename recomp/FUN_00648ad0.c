// ============================================
// Address:  0x00648ad0
// Original: FUN_00648ad0
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __fastcall FUN_00648ad0(int param_1)

{
  int local_118;
  CHAR local_114 [268];
  undefined4 local_8;
  
  local_8 = DAT_006b77f4;
  FUN_00634760();
  wsprintfA(local_114,"data/stage%02d",*(undefined4 *)(param_1 + 0x52d4));
  FUN_0064ac60(local_114);
  FUN_00634920();
  *(undefined1 *)(param_1 + 0x5330) = 0;
  *(undefined1 *)(param_1 + 0x5331) = 0;
  FUN_0064ab30(0);
  FUN_0064ab30(1);
  if ((*(int *)(param_1 + 0x5308) == *(int *)(param_1 + 0x5310)) ||
     (*(int *)(param_1 + 0x530c) == *(int *)(param_1 + 0x5310))) {
    *(undefined1 *)(param_1 + 0x5332) = 1;
  }
  else {
    *(undefined1 *)(param_1 + 0x5332) = 0;
  }
  if ((*(int *)(param_1 + 0x5308) == *(int *)(param_1 + 0x5314)) ||
     (*(int *)(param_1 + 0x530c) == *(int *)(param_1 + 0x5314))) {
    *(undefined1 *)(param_1 + 0x5333) = 1;
  }
  else {
    *(undefined1 *)(param_1 + 0x5333) = 0;
  }
  FUN_0064ab30(2);
  FUN_0064ab30(3);
  for (local_118 = 0; local_118 < 4; local_118 = local_118 + 1) {
    FUN_0041dcb0();
  }
  FUN_006348b0();
  FUN_00634980();
  if (*(char *)(param_1 + 0x5590) == '\x01') {
    FUN_00642060();
  }
  (**(code **)(*DAT_006d8428 + 0x2c))(DAT_006d8428,0x3c23d70a,0);
  (**(code **)(*DAT_006d8428 + 0x3c))(DAT_006d8428,0x3a03126f,0);
  return;
}

