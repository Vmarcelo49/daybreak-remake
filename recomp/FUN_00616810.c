// ============================================
// Address:  0x00616810
// Original: FUN_00616810
// Status:   unreviewed
// ============================================


void __fastcall FUN_00616810(int param_1)

{
  char cVar1;
  short sVar2;
  
  switch(*(undefined4 *)(param_1 + 0x150)) {
  case 0:
    FUN_005f5e00();
    return;
  case 10:
    FUN_005f5e00();
    return;
  case 0x14:
    if (0xc < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x1e:
    if (0x33 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41700000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
      *(undefined4 *)(param_1 + 0x40) = 0x41700000;
    }
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.5;
    cVar1 = FUN_005f6a90();
    if ((cVar1 == '\x01') || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) {
      FUN_005f6db0(5,0,0,0);
      FUN_0042c8b0(0x69);
      FUN_005f5e00();
      return;
    }
    if (0x708 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x32:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      FUN_0042c840(1);
    }
    if (0x33 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x40e00000;
      *(undefined4 *)(param_1 + 0x74) = 0x41400000;
      *(undefined4 *)(param_1 + 0x78) = 0x40e00000;
    }
    if (*(int *)(param_1 + 0x154) == 0x1e) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      FUN_005f5e00();
      return;
    }
  }
  *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
  FUN_005f75a0();
  return;
}

