// ============================================
// Address:  0x0041a5a0
// Original: FUN_0041a5a0
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_0041a5a0(int param_1)

{
  char cVar1;
  int local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  int local_14;
  undefined4 local_10;
  int local_8;
  
  FUN_00650f40();
  (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,7,0);
  cVar1 = FUN_00650f70();
  if (cVar1 != '\0') {
    FUN_00655d60(0,0);
    for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1) {
      if (((&DAT_006cfdd1)[local_8] != '\0') || (local_8 == 0)) {
        if ((char)(&DAT_006cfde1)[local_8] < '\0') {
          FUN_00646bd0(local_8,0x42400000,(float)local_8 * 48.0 + 112.0,0);
        }
        else {
          FUN_00646bd0(local_8,0x42400000,(float)local_8 * 48.0 + 112.0,1);
          FUN_00655830(0xc0000000,(float)local_8 * 48.0 + 112.0,(char)(&DAT_006cfde1)[local_8] + 2,
                       0xe);
        }
      }
    }
    FUN_00646b00(0x43980000,0x42dc0000);
    cVar1 = FUN_004164b0();
    if (cVar1 != '\0') {
      FUN_00655830(0x442f8000,0x42e00000,2,0xe);
    }
    cVar1 = FUN_004164d0();
    if (cVar1 != '\0') {
      FUN_00655830(0x442f8000,0x43a80000,3,0xe);
    }
    if ((*(char *)(param_1 + 0x171) == '\0') || (*(char *)(param_1 + 0x170) == '\0')) {
      local_10 = 1;
    }
    else {
      local_10 = 0;
    }
    FUN_00655830(0x43980000,0x43ce0000,0,local_10);
    if ((*(char *)(param_1 + 0x171) == '\x01') || (*(char *)(param_1 + 0x170) == '\0')) {
      local_14 = 1;
    }
    else {
      local_14 = 0;
    }
    FUN_00655830(0x43980000,0x43de0000,0,local_14 + 2);
    if ((*(char *)(param_1 + 0x171) == '\x02') || (*(char *)(param_1 + 0x170) == '\0')) {
      local_18 = 1;
    }
    else {
      local_18 = 0;
    }
    FUN_00655830(0x44000000,0x43ce0000,0,local_18 + 4);
    if ((*(char *)(param_1 + 0x171) == '\x03') || (*(char *)(param_1 + 0x170) == '\0')) {
      local_1c = 1;
    }
    else {
      local_1c = 0;
    }
    FUN_00655830(0x44000000,0x43de0000,0,local_1c + 6);
    if ((*(char *)(param_1 + 0x171) == '\0') || (*(char *)(param_1 + 0x170) == '\0')) {
      local_20 = 1;
    }
    else {
      local_20 = 0;
    }
    FUN_00655830(0x43e00000,0x43ce0000,*(char *)(param_1 + 0x16c) + 0x20,local_20);
    if ((*(char *)(param_1 + 0x171) == '\x01') || (*(char *)(param_1 + 0x170) == '\0')) {
      local_24 = 1;
    }
    else {
      local_24 = 0;
    }
    FUN_00655830(0x43d80000,0x43de0000,*(char *)(param_1 + 0x16d) + 1,local_24 + 2);
    if ((*(char *)(param_1 + 0x171) == '\x02') || (*(char *)(param_1 + 0x170) == '\0')) {
      local_28 = 1;
    }
    else {
      local_28 = 0;
    }
    FUN_00655830(0x44240000,0x43ce0000,*(char *)(param_1 + 0x16e) + 1,local_28 + 4);
    if ((*(char *)(param_1 + 0x171) == '\x03') || (*(char *)(param_1 + 0x170) == '\0')) {
      local_2c = 1;
    }
    else {
      local_2c = 0;
    }
    FUN_00655830(0x44240000,0x43de0000,1 - *(char *)(param_1 + 0x16f),local_2c + 6);
    FUN_00646500(0x43500000,0x44000000);
    FUN_0064c1e0();
    FUN_00650fd0();
  }
  return 1;
}

