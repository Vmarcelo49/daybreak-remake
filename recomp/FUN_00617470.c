// ============================================
// Address:  0x00617470
// Original: FUN_00617470
// Status:   unreviewed
// ============================================


void __fastcall FUN_00617470(int param_1)

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
      FUN_005f72c0(0x43340000,-*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
      FUN_0042c800(0);
      FUN_0042c840(5);
      break;
    case 0x14:
    case 0x1e:
      FUN_005f72c0(0x43340000,-*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
      FUN_0042c800(0);
      FUN_0042c840(1);
      break;
    case 0x46:
      FUN_005f72c0(0x43340000,-*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
      FUN_0042c800(0);
      FUN_0042c840(4);
    }
  }
  switch(*(undefined4 *)(param_1 + 0x150)) {
  case 0:
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
      *(undefined4 *)(param_1 + 0xf4) = 0x37;
      FUN_0042c840(4);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    if (*(int *)(param_1 + 0x154) % 3 == 0) {
      FUN_005f6fd0(8,0,0,0);
    }
    sVar2 = FUN_0042c7b0();
    if (sVar2 != 0) {
      if (*(int *)(param_1 + 0xf0) < 5) {
        *(undefined4 *)(param_1 + 0x54) = 0x3f800000;
        *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
        return;
      }
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(float *)(param_1 + 0x54) = (float)*(int *)(param_1 + 0xf4);
      FUN_0042c800(0);
    }
    *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + -2;
    if (*(int *)(param_1 + 0xf4) < 0x1e) {
      *(undefined4 *)(param_1 + 0xf4) = 0x1e;
    }
    *(float *)(param_1 + 0x54) = (float)*(int *)(param_1 + 0xf4);
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    if (0x3c < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x3c;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.007);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) =
             *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.007;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) =
             (float)*(int *)(param_1 + 0xec) * 0.007 + *(float *)(param_1 + 0x6c);
      }
    }
    if ((300 < *(int *)(param_1 + 0x154)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_005f5e00();
      return;
    }
    break;
  case 10:
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
      FUN_005f7450(2,0x42200000,0xf,1,0);
      *(undefined4 *)(param_1 + 0xf4) = 0x37;
      FUN_0042c840(5);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0x28;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    if (*(int *)(param_1 + 0x154) % 3 == 0) {
      FUN_005f6fd0(8,0,0,0);
    }
    sVar2 = FUN_0042c7b0();
    if (sVar2 != 0) {
      if (*(int *)(param_1 + 0xf0) < 5) {
        *(undefined4 *)(param_1 + 0x54) = 0x3f800000;
        *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
        return;
      }
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(float *)(param_1 + 0x54) = (float)*(int *)(param_1 + 0xf4);
      FUN_0042c800(0);
    }
    *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + -1;
    if (*(int *)(param_1 + 0xf4) < 0x1e) {
      *(undefined4 *)(param_1 + 0xf4) = 0x1e;
    }
    *(float *)(param_1 + 0x54) = (float)*(int *)(param_1 + 0xf4);
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
    if (0x5a < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x5a;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.01);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) =
             *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.01;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) =
             (float)*(int *)(param_1 + 0xec) * 0.01 + *(float *)(param_1 + 0x6c);
      }
    }
    if ((0xf0 < *(int *)(param_1 + 0x154)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x14:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x78) = 0x3f400000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f400000;
      *(undefined4 *)(param_1 + 0x70) = 0x3f400000;
      *(undefined4 *)(param_1 + 0x54) = 0x42480000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      FUN_005f7450(0,0x41200000,0x28,1,0);
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 1.5;
    if (*(float *)(param_1 + 0x54) < 25.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41c80000;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3dcccccd);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.05;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.05;
      }
    }
    if ((300 < *(int *)(param_1 + 0x154)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x54) = 0x428c0000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      FUN_005f7450(2,0x41200000,0x32,1,0);
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 1.5;
    if (*(float *)(param_1 + 0x54) < 25.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41c80000;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3e99999a);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.1;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.1;
      }
    }
    if ((300 < *(int *)(param_1 + 0x154)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_0042c840(1);
    }
    if (0x33 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x32:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 4.0);
    *(float *)(param_1 + 0x70) = (float)(fVar4 * (float10)0.1 + (float10)*(float *)(param_1 + 0x70))
    ;
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 4.0);
    *(float *)(param_1 + 0x74) = (float)(fVar4 * (float10)0.1 + (float10)*(float *)(param_1 + 0x74))
    ;
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 4.0);
    *(float *)(param_1 + 0x78) = (float)(fVar4 * (float10)0.1 + (float10)*(float *)(param_1 + 0x78))
    ;
    if ((0 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xd, *(int *)(param_1 + 0xe8) < 0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (0x14 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42b40000;
      FUN_0042c840(1);
    }
    if ((0x78 < *(int *)(param_1 + 0x154)) ||
       (((sVar2 = FUN_0042c7b0(), sVar2 != 0 && (sVar2 = FUN_0042c7b0(), sVar2 != 1)) ||
        (cVar1 = FUN_005f6a90(), cVar1 == '\x01')))) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x46:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42480000;
      FUN_005f7450(2,0x42200000,0xf,1,0);
      FUN_0042c840(4);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 1.0;
    if (*(float *)(param_1 + 0x54) < 30.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
    }
    sVar2 = FUN_0042c7b0();
    if (sVar2 != 0) {
      if (*(int *)(param_1 + 0xf0) < 5) {
        *(undefined4 *)(param_1 + 0x54) = 0x3f800000;
        *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
        return;
      }
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(undefined4 *)(param_1 + 0x54) = 0x420c0000;
      FUN_0042c800(0);
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    if (0x1e < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x1e;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.009);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) =
             *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.009;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) =
             (float)*(int *)(param_1 + 0xec) * 0.009 + *(float *)(param_1 + 0x6c);
      }
    }
    if ((0xf0 < *(int *)(param_1 + 0x154)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x50:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3ecccccd;
      *(undefined4 *)(param_1 + 0x74) = 0x3ecccccd;
      *(undefined4 *)(param_1 + 0x78) = 0x3ecccccd;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x34) = (float)(uVar3 % 0x14) - 10.0;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar3 % 0x14) - 10.0;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x2c) = (float)(uVar3 % 0x168);
    }
    if (0xe < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
  }
  *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
  FUN_005f75a0();
  return;
}

