// ============================================
// Address:  0x0060ea90
// Original: FUN_0060ea90
// Status:   unreviewed
// ============================================


void __fastcall FUN_0060ea90(int param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  float10 fVar4;
  
  uVar3 = FUN_0042c7b0();
  if (((uVar3 & 0x100) != 0) &&
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
      *(undefined4 *)(param_1 + 0x54) = 0x42200000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
    }
    *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + 25.0;
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    if (0x4b < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x4b;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3e4ccccd);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.2;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.2;
      }
    }
    if ((0xf0 < *(int *)(param_1 + 0x154)) ||
       (((sVar2 = FUN_0042c7b0(), sVar2 != 0 && (sVar2 = FUN_0042c7b0(), sVar2 != 1)) ||
        (cVar1 = FUN_005f6a90(), cVar1 == '\x01')))) {
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
      *(undefined4 *)(param_1 + 0x54) = 0x42520000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
    }
    *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + 25.0;
    if (*(int *)(param_1 + 0x154) % 3 == 0) {
      FUN_005f6fd0(0xb,0,0,0);
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    if (0x4b < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x4b;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3e99999a);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.3;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.3;
      }
    }
    if ((0xf0 < *(int *)(param_1 + 0x154)) ||
       (((sVar2 = FUN_0042c7b0(), sVar2 != 0 && (sVar2 = FUN_0042c7b0(), sVar2 != 1)) ||
        (cVar1 = FUN_005f6a90(), cVar1 == '\x01')))) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x14:
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_0042db10(0,0x41200000);
      *(undefined4 *)(param_1 + 0x54) = 0x42320000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
    }
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.5;
    if (((800 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
       (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_0042c8b0(0x4a);
      FUN_005f6db0(4,0,0,0);
      FUN_005f5e00();
      return;
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 3;
    if (0x46 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x46;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      if (1.0 < *(float *)(param_1 + 100)) {
        *(float *)(param_1 + 100) =
             *(float *)(param_1 + 100) - (float)*(int *)(param_1 + 0xec) * 0.01;
      }
      if (*(float *)(param_1 + 100) < -1.0) {
        *(float *)(param_1 + 100) =
             (float)*(int *)(param_1 + 0xec) * 0.01 + *(float *)(param_1 + 100);
      }
    }
    fVar4 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
    *(float *)(param_1 + 0x3c) = (float)(fVar4 * (float10)*(float *)(param_1 + 0x54));
    fVar4 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
    *(float *)(param_1 + 0x44) = (float)(fVar4 * (float10)*(float *)(param_1 + 0x54));
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_0042db10(0,0x41200000);
      *(undefined4 *)(param_1 + 0x54) = 0x42320000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      FUN_005f7450(3,0x42700000,0x19,1,0);
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
    }
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.5;
    if (((800 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
       (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_0042c8b0(0x4a);
      FUN_005f6db0(5,0,0,0);
      FUN_005f5e00();
      return;
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 3;
    if (0x46 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x46;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      if (1.0 < *(float *)(param_1 + 100)) {
        *(float *)(param_1 + 100) =
             *(float *)(param_1 + 100) - (float)*(int *)(param_1 + 0xec) * 0.01;
      }
      if (*(float *)(param_1 + 100) < -1.0) {
        *(float *)(param_1 + 100) =
             (float)*(int *)(param_1 + 0xec) * 0.01 + *(float *)(param_1 + 100);
      }
    }
    fVar4 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
    *(float *)(param_1 + 0x3c) = (float)(fVar4 * (float10)*(float *)(param_1 + 0x54));
    fVar4 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
    *(float *)(param_1 + 0x44) = (float)(fVar4 * (float10)*(float *)(param_1 + 0x54));
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x6c) = 0;
      FUN_0042c840(1);
      FUN_0042c800(0);
      *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x78) =
         (float)(fVar4 * (float10)0.15 + (float10)*(float *)(param_1 + 0x78));
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x74) =
         (float)(fVar4 * (float10)0.15 + (float10)*(float *)(param_1 + 0x74));
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x70) =
         (float)(fVar4 * (float10)0.15 + (float10)*(float *)(param_1 + 0x70));
    if (*(int *)(param_1 + 0x154) == 6) {
      FUN_0042c840(0);
    }
    if ((10 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xd, *(int *)(param_1 + 0xe8) < 0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    if (0x1e < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x32:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x6c) = 0;
      FUN_0042c840(1);
      FUN_0042c800(0);
      *(undefined4 *)(param_1 + 0x78) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0x74) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x78) = (float)(fVar4 * (float10)0.2 + (float10)*(float *)(param_1 + 0x78))
    ;
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x74) = (float)(fVar4 * (float10)0.2 + (float10)*(float *)(param_1 + 0x74))
    ;
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x70) = (float)(fVar4 * (float10)0.2 + (float10)*(float *)(param_1 + 0x70))
    ;
    if (*(int *)(param_1 + 0x154) == 6) {
      FUN_0042c840(0);
    }
    if ((10 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xd, *(int *)(param_1 + 0xe8) < 0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    if (0x1e < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42320000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
    }
    if ((*(float *)(param_1 + 0x40) < 0.0) && (*(int *)(param_1 + 0xf0) == 0)) {
      FUN_005f6880(1);
      *(undefined4 *)(param_1 + 0xf0) = 1;
      FUN_0042c8b0(0x5d);
      *(undefined4 *)(param_1 + 0x3c) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      *(undefined4 *)(param_1 + 0x44) = 0;
    }
    if (*(int *)(param_1 + 0xf0) == 1) {
      FUN_0042db10(0,0x43340000);
      fVar4 = (float10)FUN_0042dac0(2);
      *(float *)(param_1 + 0x6c) = (float)fVar4;
      *(undefined4 *)(param_1 + 0x54) = 0x42700000;
      *(undefined4 *)(param_1 + 0xf0) = 2;
      FUN_0042c8b0(0x5d);
      FUN_005f6fd0(10,0,0,0);
    }
    sVar2 = FUN_0042c7b0();
    if ((sVar2 != 0) ||
       ((cVar1 = FUN_005f6a90(), cVar1 == '\x01' && (1 < *(int *)(param_1 + 0xf0))))) {
      FUN_0042c8b0(0x5c);
      FUN_005f6db0(7,0,0,0);
      FUN_005f5e00();
      return;
    }
    if (800 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    if ((*(int *)(param_1 + 0xf0) == 2) && (*(int *)(param_1 + 0x154) % 5 == 0)) {
      FUN_005f6fd0(8,0,0,0);
      FUN_005f6fd0(9,0,0,0);
    }
    if (*(int *)(param_1 + 0xf0) == 0) {
      *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.5;
      fVar4 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
      *(float *)(param_1 + 0x3c) = (float)(fVar4 * (float10)*(float *)(param_1 + 0x54));
      fVar4 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
      *(float *)(param_1 + 0x44) = (float)(fVar4 * (float10)*(float *)(param_1 + 0x54));
    }
    break;
  case 0x46:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x6c) = 0;
      FUN_0042c840(1);
      FUN_0042c800(0);
      *(undefined4 *)(param_1 + 0x78) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0x74) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x78) = (float)(fVar4 * (float10)0.3 + (float10)*(float *)(param_1 + 0x78))
    ;
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x74) = (float)(fVar4 * (float10)0.3 + (float10)*(float *)(param_1 + 0x74))
    ;
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x70) = (float)(fVar4 * (float10)0.3 + (float10)*(float *)(param_1 + 0x70))
    ;
    if (*(int *)(param_1 + 0x154) == 6) {
      FUN_0042c840(0);
    }
    if ((10 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xd, *(int *)(param_1 + 0xe8) < 0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    if (0x1e < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x50:
    *(undefined4 *)(param_1 + 0x54) = 0x42340000;
    if (0xc < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x5a:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x78) = 0x3e4ccccd;
      *(undefined4 *)(param_1 + 0x74) = 0x3e4ccccd;
      *(undefined4 *)(param_1 + 0x70) = 0x3e4ccccd;
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
  case 100:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x78) = 0x3e99999a;
      *(undefined4 *)(param_1 + 0x74) = 0x3e99999a;
      *(undefined4 *)(param_1 + 0x70) = 0x3e99999a;
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 4.0);
    *(float *)(param_1 + 0x70) = (float)(fVar4 * (float10)0.2 + (float10)*(float *)(param_1 + 0x70))
    ;
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 4.0);
    *(float *)(param_1 + 0x74) = (float)(fVar4 * (float10)0.2 + (float10)*(float *)(param_1 + 0x74))
    ;
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 4.0);
    *(float *)(param_1 + 0x78) = (float)(fVar4 * (float10)0.2 + (float10)*(float *)(param_1 + 0x78))
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
  case 0x6e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x34) = 0x41200000;
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

