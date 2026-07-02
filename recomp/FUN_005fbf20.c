// ============================================
// Address:  0x005fbf20
// Original: FUN_005fbf20
// Status:   unreviewed
// ============================================


void __fastcall FUN_005fbf20(int param_1)

{
  int iVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  float10 fVar5;
  float fVar6;
  
  switch(*(undefined4 *)(param_1 + 0x150)) {
  case 0:
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
  case 10:
    if (*(int *)(param_1 + 0x154) == 0) {
      uVar4 = FUN_0065d150();
      *(float *)(param_1 + 0x54) = (float)(uVar4 % 0x50) * 0.1 + 4.0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
      uVar4 = FUN_0065d150();
      *(float *)(param_1 + 0x40) = (float)(uVar4 % 0x28) * 0.1 + 8.0;
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 0x32;
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.3;
    cVar2 = FUN_005f6a90();
    if (cVar2 == '\x01') {
      FUN_005f6db0(2,0,0,0);
      FUN_0042c8b0(0x4e);
      FUN_005f5e00();
      return;
    }
    if (0x708 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x14:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (((0x1a < *(int *)(param_1 + 0x154)) && (*(int *)(param_1 + 0xe8) < 7)) && (param_1 != -0x90)
       ) {
      *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
      *(undefined4 *)(param_1 + 0x154) = 0x12;
      return;
    }
    if (*(int *)(param_1 + 0x154) == 0x34) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
      uVar4 = FUN_0065d150();
      *(float *)(param_1 + 0x54) = (float)(uVar4 % 0x50) * 0.1 + 4.0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
      uVar4 = FUN_0065d150();
      *(float *)(param_1 + 0x40) = (float)(uVar4 % 0x28) * 0.1 + 8.0;
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 0x32;
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.3;
    cVar2 = FUN_005f6a90();
    if (cVar2 == '\x01') {
      FUN_005f6db0(4,0,0,0);
      FUN_0042c8b0(0x4e);
      FUN_005f5e00();
      return;
    }
    if (0x708 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0x74) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0x78) = 0x3fc00000;
    }
    if (((0x1a < *(int *)(param_1 + 0x154)) && (*(int *)(param_1 + 0xe8) < 0xf)) &&
       (param_1 != -0x90)) {
      *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
      *(undefined4 *)(param_1 + 0x154) = 0x12;
      return;
    }
    if (*(int *)(param_1 + 0x154) == 0x34) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x32:
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_005f6880(0);
      fVar5 = (float10)FUN_0065d050(*(undefined4 *)(param_1 + 0x6c));
      *(float *)(param_1 + 0x54) = (float)(fVar5 * (float10)10.0);
      fVar5 = (float10)FUN_0065d010(*(undefined4 *)(param_1 + 0x6c));
      *(float *)(param_1 + 0x40) = (float)(fVar5 * (float10)17.5);
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    cVar2 = FUN_005f6a90();
    if (cVar2 == '\x01') {
      FUN_005f5e00();
      return;
    }
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.75;
    if (0x708 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0x70) = 0x40400000;
      *(undefined4 *)(param_1 + 0x74) = 0x40400000;
      *(undefined4 *)(param_1 + 0x78) = 0x40400000;
    }
    if (0x1e < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x46:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      *(undefined4 *)(param_1 + 0x6c) = 0;
      FUN_0042c840(1);
    }
    if (*(int *)(param_1 + 0x154) < 0x14) {
      uVar4 = FUN_0065d150();
      fVar6 = (float)(uVar4 % 0x14) + 60.0;
      iVar1 = *(int *)(param_1 + 0x154);
      uVar4 = FUN_0065d150(fVar6);
      FUN_005f6ef0(3,0,0,0,(float)(uVar4 % 5) + (float)(iVar1 * 0xd),fVar6);
    }
    if (0x33 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x50:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41c80000;
      FUN_005f6880(0);
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.35;
      *(float *)(param_1 + 0x34) = *(float *)(param_1 + 0x34) + 20.0;
    }
    cVar2 = FUN_005f6a90();
    if ((cVar2 == '\x01') || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) {
      FUN_005f6db0(7,0,0,0);
      FUN_0042c8b0(0x47);
      FUN_005f5e00();
      return;
    }
    if (0x708 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x5a:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0x70) = 0x40c00000;
      *(undefined4 *)(param_1 + 0x74) = 0x40c00000;
      *(undefined4 *)(param_1 + 0x78) = 0x40c00000;
    }
    if (0x1e < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
  }
  *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
  FUN_005f75a0();
  return;
}

