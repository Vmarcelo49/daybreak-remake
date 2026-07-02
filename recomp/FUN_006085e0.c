// ============================================
// Address:  0x006085e0
// Original: FUN_006085e0
// Status:   unreviewed
// ============================================


void __fastcall FUN_006085e0(int param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  float10 fVar4;
  
  uVar3 = FUN_0042c7b0();
  if ((uVar3 & 0x100) != 0) {
    switch(*(undefined4 *)(param_1 + 0x150)) {
    case 0:
    case 10:
    case 0x28:
    case 0x32:
    case 0x46:
    case 0x5a:
      FUN_005f72c0(0x43340000,-*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
      FUN_0042c800(0);
      FUN_0042c840(1);
    }
  }
  switch(*(undefined4 *)(param_1 + 0x150)) {
  case 0:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f19999a;
      *(undefined4 *)(param_1 + 0x78) = 0x3f19999a;
      *(undefined4 *)(param_1 + 0x54) = 0x42200000;
      FUN_0042c840(1);
    }
    sVar2 = FUN_0042c7b0();
    if ((sVar2 != 0) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_005f6fd0(3,0,0,0);
      FUN_005f5e00();
      return;
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 0.25;
    if (0x3c < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 10:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f19999a;
      *(undefined4 *)(param_1 + 0x78) = 0x3f19999a;
      *(undefined4 *)(param_1 + 0x54) = 0x42200000;
      FUN_0042c840(1);
    }
    uVar3 = FUN_0042c7b0();
    if (((uVar3 & 2) != 0) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_005f6fd0(3,0,0,0);
      FUN_005f5e00();
      return;
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 0.5;
    if (0x3c < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x14:
    *(undefined4 *)(param_1 + 0x54) = 0;
    if (5 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar3 % 0x168);
    }
    if ((4 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0x32, *(int *)(param_1 + 0xe8) < 0))
    {
      *(undefined4 *)(param_1 + 0xe8) = 0;
      FUN_005f5e00();
      return;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
          (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
         (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd)) {
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)10.0) {
          fVar4 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar4;
        }
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)-10.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
          fVar4 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar4;
        }
      }
      FUN_0042db10(0,0x40a00000);
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x54) = 0x428c0000;
      FUN_0042c840(1);
      FUN_005f6fd0(6,0,0,0);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(undefined4 *)(param_1 + 0xf4) = 0;
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
    if (0x3c < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x3c;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154))) {
      FUN_0042db10(0,0x3c23d70a);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.01;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.01;
      }
    }
    if ((0x1e0 < *(int *)(param_1 + 0xf0)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      *(undefined4 *)(param_1 + 0xf4) = 1;
      FUN_0042c840(0);
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
    if (*(int *)(param_1 + 0xf4) == 1) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x32:
    if (*(int *)(param_1 + 0x154) == 0) {
      if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
          (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
         (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd)) {
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)10.0) {
          fVar4 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar4;
        }
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)-10.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
          fVar4 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar4;
        }
      }
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x54) = 0x42960000;
      FUN_0042c840(1);
      FUN_005f6fd0(6,0,0,0);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(undefined4 *)(param_1 + 0xf4) = 0;
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
    if (0x3c < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x3c;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154))) {
      FUN_0042db10(0,0x3e800000);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.25;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.25;
      }
    }
    if ((0x1e0 < *(int *)(param_1 + 0xf0)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      *(undefined4 *)(param_1 + 0xf4) = 1;
      FUN_0042c840(0);
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
    if (*(int *)(param_1 + 0xf4) == 1) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    if (*(int *)(param_1 + 0x154) == 0x3c) {
      *(undefined4 *)(param_1 + 0x154) = 0x28;
      return;
    }
    break;
  case 0x3c:
    if (5 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x46:
    if (*(int *)(param_1 + 0x154) == 0) {
      if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
          (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
         (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd)) {
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)10.0) {
          fVar4 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar4;
        }
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)-10.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
          fVar4 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar4;
        }
      }
      FUN_0042db10(0,0x40a00000);
      *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x54) = 0x42c80000;
      FUN_0042c840(1);
      FUN_005f6fd0(6,0,0,0);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(undefined4 *)(param_1 + 0xf4) = 0;
      *(undefined4 *)(param_1 + 0xf8) = 0;
    }
    if (*(int *)(param_1 + 0xf0) % 5 == 0) {
      FUN_005f6fd0(8,0,0,0);
    }
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    if (0x3c < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x3c;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154))) {
      FUN_0042db10(0,0x3c23d70a);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.01;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.01;
      }
    }
    if ((0x1e0 < *(int *)(param_1 + 0xf0)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      *(undefined4 *)(param_1 + 0xf4) = 1;
      FUN_0042c840(0);
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
    if (*(int *)(param_1 + 0xf4) == 1) {
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.05;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.05;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.05;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    if (*(int *)(param_1 + 0x154) == 0x3c) {
      *(undefined4 *)(param_1 + 0x154) = 0x1e;
      return;
    }
    break;
  case 0x50:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3d4ccccd;
      *(undefined4 *)(param_1 + 0x74) = 0x3d4ccccd;
      *(undefined4 *)(param_1 + 0x78) = 0x3d4ccccd;
    }
    *(undefined4 *)(param_1 + 0x54) = 0;
    fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
    *(float *)(param_1 + 0x70) =
         (float)(fVar4 * (float10)0.025 + (float10)*(float *)(param_1 + 0x70));
    fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
    *(float *)(param_1 + 0x74) =
         (float)(fVar4 * (float10)0.025 + (float10)*(float *)(param_1 + 0x74));
    fVar4 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
    *(float *)(param_1 + 0x78) =
         (float)(fVar4 * (float10)0.025 + (float10)*(float *)(param_1 + 0x78));
    if (0x1c < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x5a:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x54) = 0x425c0000;
      FUN_0042c840(1);
      FUN_005f6fd0(6,0,0,0);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(undefined4 *)(param_1 + 0xf4) = 0;
      FUN_005f6880(0);
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 1.0;
    if (*(float *)(param_1 + 0x54) < 20.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41a00000;
    }
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.5;
    uVar3 = *(uint *)(param_1 + 0x154) & 0x80000001;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
    }
    if (uVar3 == 0) {
      FUN_005f6fd0(10,0,0,0);
    }
    if (400 < *(int *)(param_1 + 0xf0)) {
      FUN_005f5e00();
      return;
    }
    sVar2 = FUN_0042c7b0();
    if ((sVar2 != 0) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_0042c8b0(0x4a);
      FUN_005f6fd0(0xb,0,0,0);
      FUN_005f5e00();
      return;
    }
    break;
  case 100:
    if (*(int *)(param_1 + 0x154) == 0) {
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x70) = (float)(uVar3 % 10) * 0.1 + 1.0;
      *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x70);
      *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x70);
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar3 % 0x168);
    }
    if (0x1d < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x6e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0x70) = 0x3fe00000;
      *(undefined4 *)(param_1 + 0x74) = 0x3fe00000;
      *(undefined4 *)(param_1 + 0x78) = 0x3fe00000;
    }
    if (0x33 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
  }
  *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
  FUN_005f75a0();
  return;
}

