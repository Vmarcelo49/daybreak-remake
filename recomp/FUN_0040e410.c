// ============================================
// Address:  0x0040e410
// Original: FUN_0040e410
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_0040e410(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  if (*(int *)(param_1 + 0x1f0) < 2) {
    FUN_00650f40();
    cVar1 = FUN_00650f70();
    if (cVar1 == '\0') {
      uVar2 = 0;
    }
    else {
      FUN_00655d60(0,0);
      FUN_00650fd0();
      uVar2 = 1;
    }
  }
  else {
    cVar1 = FUN_00650f70();
    if (cVar1 != '\0') {
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,7,0);
      FUN_00655d60(0,0);
      if ((*(int *)(param_1 + 0x1f0) < 2) || (4 < *(int *)(param_1 + 0x1f0))) {
        if ((4 < *(int *)(param_1 + 0x1f0)) && (*(int *)(param_1 + 0x1f0) < 7)) {
          if (*(int *)(param_1 + 0x200) == 4) {
            FUN_00655830(0x43c80000,0x436c0000,0,3);
          }
          else if (*(int *)(param_1 + 0x200) == 3) {
            FUN_00655830(0x43c80000,0x436c0000,0,4);
          }
          else {
            FUN_00655830(0x43c80000,0x436c0000,0,*(undefined4 *)(param_1 + 0x200));
          }
          FUN_00655830(0x43c80000,0x43960000,0,8);
          FUN_00655830(0x43c80000,0x43a60000,0,9);
        }
      }
      else {
        FUN_00655830(0x43c80000,0x43960000,0,(DAT_006cfd04 & 0xf) - 3);
      }
      if (*(int *)(param_1 + 500) < 0xff) {
        FUN_00651860(0,0,0x44480000,0x44160000,(0xff - *(int *)(param_1 + 500)) * 0x1000000);
      }
      FUN_00650fd0();
    }
    uVar2 = 1;
  }
  return uVar2;
}

