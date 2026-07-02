// Function: FUN_006492f0
// Address:  0x006492f0
// Source:   batch_decompile (mass dump)
// Hash:     b540ccbd029e0f2f


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __fastcall FUN_006492f0(int param_1)

{
  uint uVar1;
  CHAR local_114 [268];
  undefined4 local_8;
  
  local_8 = DAT_006b77f4;
  *(int *)(param_1 + 0x5310) = (int)*(char *)(param_1 + 0x53ad + *(char *)(param_1 + 0x53a4) * 2);
  *(int *)(param_1 + 0x5314) = (int)*(char *)(param_1 + 0x53ae + *(char *)(param_1 + 0x53a4) * 2);
  uVar1 = FUN_0065d150();
  *(char *)(param_1 + 0x532a) = (char)((ulonglong)uVar1 % 3);
  uVar1 = FUN_0065d150();
  *(char *)(param_1 + 0x532b) = (char)((ulonglong)uVar1 % 3);
  *(undefined1 *)(param_1 + 0x532e) = 0;
  *(undefined1 *)(param_1 + 0x532f) = 0;
  *(undefined1 *)(param_1 + 0x5336) = 0;
  *(undefined1 *)(param_1 + 0x5337) = 0;
  if ((*(char *)(param_1 + 0x53a6) == '\a') && (*(char *)(param_1 + 0x53a4) == '\x05')) {
    *(undefined4 *)(param_1 + 0x5320) = 2;
    *(undefined4 *)(param_1 + 0x5324) = 2;
  }
  else {
    if ((*(int *)(param_1 + 0x5310) == 0) || (*(int *)(param_1 + 0x5310) == 4)) {
      uVar1 = FUN_0065d150();
      *(int *)(param_1 + 0x5320) = (int)(char)((ulonglong)uVar1 % 2);
    }
    else {
      uVar1 = FUN_0065d150();
      *(int *)(param_1 + 0x5320) = (int)(char)((ulonglong)uVar1 % 3);
    }
    if ((*(int *)(param_1 + 0x5314) == 0) || (*(int *)(param_1 + 0x5314) == 4)) {
      uVar1 = FUN_0065d150();
      *(int *)(param_1 + 0x5324) = (int)(char)((ulonglong)uVar1 % 2);
    }
    else {
      uVar1 = FUN_0065d150();
      *(int *)(param_1 + 0x5324) = (int)(char)((ulonglong)uVar1 % 3);
    }
  }
  *(int *)(param_1 + 0x52d4) = (int)*(char *)(param_1 + 0x53b9 + (int)*(char *)(param_1 + 0x53a4));
  *(undefined4 *)(param_1 + 0x4b94) = 100;
  *(undefined4 *)(param_1 + 0x4b90) = 100;
  FUN_00634760();
  wsprintfA(local_114,"data/stage%02d",*(undefined4 *)(param_1 + 0x52d4));
  FUN_0064ac60(local_114);
  FUN_00634920();
  FUN_0041dcb0();
  FUN_0041dcb0();
  FUN_0064ab30(2);
  FUN_0064ab30(3);
  FUN_0041dcb0();
  FUN_0041dcb0();
  FUN_006348b0();
  FUN_00634980();
  (**(code **)(*DAT_006d8428 + 0x2c))(DAT_006d8428,0x3c23d70a,0);
  (**(code **)(*DAT_006d8428 + 0x3c))(DAT_006d8428,0x3a03126f,0);
  return;
}

