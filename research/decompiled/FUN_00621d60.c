// Function: FUN_00621d60
// Address:  0x00621d60
// Source:   batch_decompile (mass dump)
// Hash:     81add5c7d28b257b


void __fastcall FUN_00621d60(int param_1)

{
  char cVar1;
  uint uVar2;
  float10 fVar3;
  
  uVar2 = FUN_0042c7b0();
  if (((uVar2 & 0x100) != 0) &&
     ((*(int *)(param_1 + 0x150) == 0 || (*(int *)(param_1 + 0x150) == 10)))) {
    FUN_005f72c0(0x43340000,-*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
    FUN_0042c800(0);
    FUN_0042c840(1);
  }
  switch(*(undefined4 *)(param_1 + 0x150)) {
  case 0:
    if (*(int *)(param_1 + 0x154) == 0) {
      if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
          (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
         (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd)) {
        fVar3 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar3 < (float10)10.0) {
          fVar3 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar3;
        }
        fVar3 = (float10)FUN_0042dac0(2);
        if ((float10)-10.0 < (float10)*(float *)(param_1 + 0x6c) - fVar3) {
          fVar3 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar3;
        }
      }
      FUN_005f6fd0(5,0,0,0);
      *(undefined4 *)(param_1 + 0x54) = 0x42700000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(undefined4 *)(param_1 + 0xf4) = 0;
    }
    cVar1 = FUN_005f6a90();
    if (cVar1 == '\x01') {
      *(undefined4 *)(param_1 + 0xf4) = 1;
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3dcccccd);
      fVar3 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar3) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.05;
      }
      fVar3 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar3 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.05;
      }
    }
    if ((0x1e0 < *(int *)(param_1 + 0xf0)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      *(undefined4 *)(param_1 + 0xf4) = 1;
      FUN_0042c840(0);
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
    if (*(int *)(param_1 + 0xf4) == 1) {
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
  case 10:
    if (*(int *)(param_1 + 0x154) == 0) {
      if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
          (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
         (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd)) {
        fVar3 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar3 < (float10)10.0) {
          fVar3 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar3;
        }
        fVar3 = (float10)FUN_0042dac0(2);
        if ((float10)-10.0 < (float10)*(float *)(param_1 + 0x6c) - fVar3) {
          fVar3 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar3;
        }
      }
      FUN_005f6fd0(5,0,0,0);
      *(undefined4 *)(param_1 + 0x54) = 0x42960000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0x74) = 0x40200000;
      *(undefined4 *)(param_1 + 0x78) = 0x40200000;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(undefined4 *)(param_1 + 0xf4) = 0;
    }
    cVar1 = FUN_005f6a90();
    if (cVar1 == '\x01') {
      *(undefined4 *)(param_1 + 0xf4) = 1;
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3dcccccd);
      fVar3 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar3) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.05;
      }
      fVar3 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar3 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.05;
      }
    }
    if ((0x1e0 < *(int *)(param_1 + 0xf0)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      *(undefined4 *)(param_1 + 0xf4) = 1;
      FUN_0042c840(0);
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
    if (*(int *)(param_1 + 0xf4) == 1) {
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
  case 0x14:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0x74) = 0x3e800000;
      *(undefined4 *)(param_1 + 0x78) = 0x3e800000;
      *(undefined4 *)(param_1 + 0x54) = 0x3c23d70a;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      FUN_0042c840(1);
      FUN_005f6fd0(6,0,0,0);
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
    if (*(int *)(param_1 + 0x154) == 0x29) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x54) = 0x3c23d70a;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      FUN_0042c840(1);
      FUN_005f6fd0(6,0,0,0);
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
    if (*(int *)(param_1 + 0x154) == 0x29) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x74) = 0x40800000;
      *(undefined4 *)(param_1 + 0x78) = 0x40800000;
      *(undefined4 *)(param_1 + 0x54) = 0x3c23d70a;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      FUN_0042c840(1);
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
    if (*(int *)(param_1 + 0x154) == 0x29) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x32:
    *(undefined4 *)(param_1 + 0x70) = 0x40400000;
    *(undefined4 *)(param_1 + 0x74) = 0x40400000;
    *(undefined4 *)(param_1 + 0x78) = 0x40400000;
    if (5 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
      uVar2 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar2 % 0x168);
      *(undefined4 *)(param_1 + 0x70) = 0x3d4ccccd;
      *(undefined4 *)(param_1 + 0x74) = 0x3d4ccccd;
      *(undefined4 *)(param_1 + 0x78) = 0x3d4ccccd;
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_005f6fd0(7,0,0,0);
    }
    fVar3 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
    *(float *)(param_1 + 0x70) =
         (float)(fVar3 * (float10)0.025 + (float10)*(float *)(param_1 + 0x70));
    fVar3 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
    *(float *)(param_1 + 0x74) =
         (float)(fVar3 * (float10)0.025 + (float10)*(float *)(param_1 + 0x74));
    fVar3 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
    *(float *)(param_1 + 0x78) =
         (float)(fVar3 * (float10)0.025 + (float10)*(float *)(param_1 + 0x78));
    if ((6 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -10, *(int *)(param_1 + 0xe8) < 0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
      FUN_005f5e00();
      return;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    break;
  case 0x46:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
      uVar2 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar2 % 0x168);
      *(undefined4 *)(param_1 + 0x70) = 0x3d4ccccd;
      *(undefined4 *)(param_1 + 0x74) = 0x3d4ccccd;
      *(undefined4 *)(param_1 + 0x78) = 0x3d4ccccd;
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
    fVar3 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
    *(float *)(param_1 + 0x70) =
         (float)(fVar3 * (float10)0.025 + (float10)*(float *)(param_1 + 0x70));
    fVar3 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
    *(float *)(param_1 + 0x74) =
         (float)(fVar3 * (float10)0.025 + (float10)*(float *)(param_1 + 0x74));
    fVar3 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 3));
    *(float *)(param_1 + 0x78) =
         (float)(fVar3 * (float10)0.025 + (float10)*(float *)(param_1 + 0x78));
    if ((6 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -10, *(int *)(param_1 + 0xe8) < 0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
      FUN_005f5e00();
      return;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    break;
  case 0x50:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x74) = 0x3dcccccd;
      *(undefined4 *)(param_1 + 0x78) = 0x3dcccccd;
      *(undefined4 *)(param_1 + 0x54) = 0x3c23d70a;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      FUN_0042c840(0);
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
    if (*(int *)(param_1 + 0x154) == 0x29) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x5a:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x74) = 0x40800000;
      *(undefined4 *)(param_1 + 0x78) = 0x40800000;
      *(undefined4 *)(param_1 + 0x54) = 0x3e99999a;
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
      *(undefined4 *)(param_1 + 0xec) = 0;
      FUN_0042c840(1);
    }
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.15;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.15;
    if ((0x14 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0x14, *(int *)(param_1 + 0xe8) < 0))
    {
      *(undefined4 *)(param_1 + 0xe8) = 0;
      FUN_005f5e00();
      return;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),*(undefined1 *)(param_1 + 0xe8),
                 *(undefined1 *)(param_1 + 0xe8),0xff);
    if (0x1e < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
  }
  *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
  FUN_005f75a0();
  return;
}

