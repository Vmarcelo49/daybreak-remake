// Function: FUN_00620290
// Address:  0x00620290
// Source:   batch_decompile (mass dump)
// Hash:     5d7f9a5ac5a6570c


void __fastcall FUN_00620290(int param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  float10 fVar4;
  
  uVar3 = FUN_0042c7b0();
  if (((uVar3 & 0x100) != 0) &&
     ((*(int *)(param_1 + 0x150) == 0x28 || (*(int *)(param_1 + 0x150) == 0x32)))) {
    FUN_005f72c0(0x43340000,-*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
    FUN_0042c800(0);
    FUN_0042c840(1);
  }
  switch(*(undefined4 *)(param_1 + 0x150)) {
  case 0:
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
  case 10:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41a00000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
    }
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 1.0;
    cVar1 = FUN_005f6a90();
    if (cVar1 == '\x01') {
      FUN_005f5e00();
      return;
    }
    if (0x3c < *(int *)(param_1 + 0x154)) {
      FUN_0042c840(0);
      *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xd;
      if (*(int *)(param_1 + 0xe8) < 0) {
        *(undefined4 *)(param_1 + 0xe8) = 0;
        FUN_005f5e00();
        return;
      }
      FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    }
    break;
  case 0x14:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0x70) = 0x40800000;
      *(undefined4 *)(param_1 + 0x74) = 0x40800000;
      *(undefined4 *)(param_1 + 0x78) = 0x40800000;
    }
    if (0x1e < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x54) = 0x420c0000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
    }
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 1.0;
    cVar1 = FUN_005f6a90();
    if (cVar1 == '\x01') {
      FUN_005f5e00();
      return;
    }
    if (0x3c < *(int *)(param_1 + 0x154)) {
      FUN_0042c840(0);
      *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xd;
      if (*(int *)(param_1 + 0xe8) < 0) {
        *(undefined4 *)(param_1 + 0xe8) = 0;
        FUN_005f5e00();
        return;
      }
      FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    }
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41a00000;
      FUN_0042c840(5);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0;
      *(undefined4 *)(param_1 + 0x74) = 0;
      *(undefined4 *)(param_1 + 0x78) = 0;
    }
    sVar2 = FUN_0042c7b0();
    if ((sVar2 != 0) &&
       (*(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1, 2 < *(int *)(param_1 + 0xf0))) {
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_0042c800(0);
    }
    if (*(int *)(param_1 + 0x154) % 3 == 0) {
      FUN_005f6fd0(6,0,0,0);
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3e4ccccd);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.1;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.1;
      }
    }
    if ((0x5a < *(int *)(param_1 + 0x154)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x32:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41c80000;
      FUN_0042c840(5);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0;
      *(undefined4 *)(param_1 + 0x74) = 0;
      *(undefined4 *)(param_1 + 0x78) = 0;
    }
    sVar2 = FUN_0042c7b0();
    if ((sVar2 != 0) &&
       (*(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1, 2 < *(int *)(param_1 + 0xf0))) {
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_0042c800(0);
    }
    if (*(int *)(param_1 + 0x154) % 3 == 0) {
      FUN_005f6fd0(6,0,0,0);
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3e4ccccd);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.1;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.1;
      }
    }
    if ((0xb4 < *(int *)(param_1 + 0x154)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0x74) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0x78) = 0x3fc00000;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x34) = (float)(uVar3 % 0x1e) - 15.0;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar3 % 0x1e) - 15.0;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x2c) = (float)(uVar3 % 0x168);
    }
    if (0xe < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x46:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42340000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
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
    }
    uVar3 = *(uint *)(param_1 + 0x154) & 0x80000001;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
    }
    if (uVar3 == 0) {
      FUN_005f6fd0(0x10,0,0,0);
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    if (0x78 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x78;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.01 + 0.25);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.25;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.25;
      }
    }
    if (((0xf0 < *(int *)(param_1 + 0x154)) ||
        ((sVar2 = FUN_0042c7b0(), sVar2 != 0 && (sVar2 = FUN_0042c7b0(), sVar2 != 1)))) ||
       (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      cVar1 = FUN_005f6a90();
      if (cVar1 == '\x01') {
        FUN_005f6db0(5,0,0,0);
      }
      FUN_005f5e00();
      return;
    }
    break;
  case 0x50:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x40400000;
      *(undefined4 *)(param_1 + 0x74) = 0x40400000;
      *(undefined4 *)(param_1 + 0x78) = 0x40400000;
      *(undefined4 *)(param_1 + 0x54) = 0x42340000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    FUN_0042db10(0,0x3c23d70a);
    if (*(int *)(param_1 + 0x154) % 6 == 0) {
      FUN_005f6fd0(0xb,0,0,0);
    }
    cVar1 = FUN_005f6a90();
    if (cVar1 == '\x01') {
      FUN_005f6db0(9,0,0,0);
      FUN_0042c8b0(0xad);
      FUN_005f5e00();
      return;
    }
    if (600 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x5a:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x40800000;
      *(undefined4 *)(param_1 + 0x74) = 0x40800000;
      *(undefined4 *)(param_1 + 0x78) = 0x40800000;
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
    }
    if (0x33 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x6e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x40400000;
      *(undefined4 *)(param_1 + 0x74) = 0x40400000;
      *(undefined4 *)(param_1 + 0x78) = 0x40400000;
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x34) = 0x41c80000;
    }
    if (0xd < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
  }
  *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
  FUN_005f75a0();
  return;
}

