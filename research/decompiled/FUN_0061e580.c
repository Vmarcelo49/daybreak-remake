// Function: FUN_0061e580
// Address:  0x0061e580
// Source:   batch_decompile (mass dump)
// Hash:     4fd7af47ea8774cc


void __fastcall FUN_0061e580(int param_1)

{
  int iVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  float10 fVar5;
  
  uVar4 = FUN_0042c7b0();
  if ((uVar4 & 0x100) != 0) {
    switch(*(undefined4 *)(param_1 + 0x150)) {
    case 0:
    case 10:
    case 0x14:
    case 0x1e:
    case 0x28:
    case 0x32:
      FUN_005f72c0(0x43340000,-*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
      FUN_0042c800(0);
      FUN_0042c840(1);
    }
  }
  switch(*(undefined4 *)(param_1 + 0x150)) {
  case 0:
    if (*(int *)(param_1 + 0x154) == 0) {
      if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
          (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
         (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd)) {
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)10.0) {
          fVar5 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar5;
        }
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)-10.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
          fVar5 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar5;
        }
      }
      *(undefined4 *)(param_1 + 0x54) = 0x420c0000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_005f7450(0,0x42700000,10,1,0);
    }
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
    if (100 < *(int *)(param_1 + 0xf0)) {
      *(undefined4 *)(param_1 + 0xf0) = 100;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xf0) * 0.002);
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
        *(float *)(param_1 + 0x6c) =
             *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xf0) * 0.0005;
      }
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) =
             (float)*(int *)(param_1 + 0xf0) * 0.0005 + *(float *)(param_1 + 0x6c);
      }
    }
    if (((0xf0 < *(int *)(param_1 + 0x154)) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) ||
       (sVar3 = FUN_0042c7b0(), sVar3 != 0)) {
      FUN_005f6fd0(0xe,0,0,0);
      FUN_005f6fd0(0xf,0,0,0);
      FUN_005f5e00();
      return;
    }
    break;
  case 10:
    if (*(int *)(param_1 + 0x154) == 0) {
      if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
          (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
         (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd)) {
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)10.0) {
          fVar5 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar5;
        }
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)-10.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
          fVar5 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar5;
        }
      }
      *(undefined4 *)(param_1 + 0x54) = 0x423e0000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_005f7450(0,0x42700000,10,1,0);
    }
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
    if (100 < *(int *)(param_1 + 0xf0)) {
      *(undefined4 *)(param_1 + 0xf0) = 100;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3dcccccd);
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.1;
      }
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.1;
      }
    }
    if ((0xf0 < *(int *)(param_1 + 0x154)) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_005f6fd0(0xe,0,0,0);
      FUN_005f6fd0(0xf,0,0,0);
      FUN_005f5e00();
      return;
    }
    break;
  case 0x14:
    if (*(int *)(param_1 + 0x154) == 0) {
      if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
          (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
         (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd)) {
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)10.0) {
          fVar5 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar5;
        }
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)-10.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
          fVar5 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar5;
        }
      }
      *(undefined4 *)(param_1 + 0x54) = 0x42820000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_005f7450(0,0x42700000,10,1,0);
    }
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
    if (100 < *(int *)(param_1 + 0xf0)) {
      *(undefined4 *)(param_1 + 0xf0) = 100;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3f000000);
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.1;
      }
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.1;
      }
    }
    if ((0xf0 < *(int *)(param_1 + 0x154)) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_005f6fd0(0xe,0,0,0);
      FUN_005f6fd0(0xf,0,0,0);
      FUN_005f5e00();
      return;
    }
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42480000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(undefined4 *)(param_1 + 0xf4) = 0;
      *(undefined4 *)(param_1 + 0xf8) = 0;
      *(undefined4 *)(param_1 + 0x78) = 0x3f400000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f400000;
      *(undefined4 *)(param_1 + 0x70) = 0x3f400000;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3f800000);
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.5;
      }
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.5;
      }
    }
    uVar4 = FUN_0042c7b0();
    if (((uVar4 & 2) != 0) || (uVar4 = FUN_0042c7b0(), (uVar4 & 1) != 0)) {
      FUN_0042c840(0);
      *(undefined4 *)(param_1 + 0x54) = 0;
      if (*(int *)(param_1 + 0xf8) == 0) {
        FUN_005f6fd0(0xe,0,0,0);
        FUN_005f6fd0(0xf,0,0,0);
        FUN_005f6ef0(6,0,0x44fa0000,0,0,-*(float *)(param_1 + 0x6c) - 90.0);
        FUN_0042c8b0(0xdb);
        FUN_005f5e00();
        return;
      }
    }
    if ((300 < *(int *)(param_1 + 0x154)) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x428c0000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(undefined4 *)(param_1 + 0xf4) = 0;
      *(undefined4 *)(param_1 + 0xf8) = 0;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3fc00000);
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.5;
      }
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.5;
      }
    }
    uVar4 = FUN_0042c7b0();
    if (((uVar4 & 2) != 0) || (uVar4 = FUN_0042c7b0(), (uVar4 & 1) != 0)) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      FUN_005f6fd0(0xe,0,0,0);
      FUN_005f6fd0(0xf,0,0,0);
      FUN_005f6db0(0x10,0,0,0);
      FUN_0042c8b0(0xdb);
      FUN_005f5e00();
      return;
    }
    if ((300 < *(int *)(param_1 + 0x154)) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x32:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x428c0000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(undefined4 *)(param_1 + 0xf4) = 0;
      *(undefined4 *)(param_1 + 0xf8) = 0;
      *(undefined4 *)(param_1 + 0x78) = 0x3fa00000;
      *(undefined4 *)(param_1 + 0x74) = 0x3fa00000;
      *(undefined4 *)(param_1 + 0x70) = 0x3fa00000;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3fc00000);
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.5;
      }
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.5;
      }
    }
    uVar4 = FUN_0042c7b0();
    if (((uVar4 & 2) != 0) || (uVar4 = FUN_0042c7b0(), (uVar4 & 1) != 0)) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      FUN_005f6fd0(0xe,0,0,0);
      FUN_005f6fd0(0xf,0,0,0);
      FUN_005f6db0(0x11,0,0,0);
      FUN_0042c8b0(0xdb);
      FUN_005f5e00();
      return;
    }
    if ((300 < *(int *)(param_1 + 0x154)) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42b40000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0x78) = 0x3e4ccccd;
      *(undefined4 *)(param_1 + 0x70) = 0x3e4ccccd;
    }
    if (((300 < *(int *)(param_1 + 0x154)) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) ||
       (sVar3 = FUN_0042c7b0(), sVar3 != 0)) {
      FUN_005f6db0(9,0,0,0);
      FUN_005f6db0(10,0,0,0);
      FUN_0042c8b0(0xdc);
      FUN_005f5e00();
      return;
    }
    break;
  case 0x46:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42960000;
      FUN_0042c840(1);
    }
    if (((300 < *(int *)(param_1 + 0x154)) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) ||
       (sVar3 = FUN_0042c7b0(), sVar3 != 0)) {
      FUN_005f6db0(9,0,0,0);
      FUN_0042c8b0(0xdc);
      FUN_005f5e00();
      return;
    }
    break;
  case 0x50:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42a00000;
      FUN_0042c840(1);
    }
    if (((300 < *(int *)(param_1 + 0x154)) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) ||
       (sVar3 = FUN_0042c7b0(), sVar3 != 0)) {
      FUN_005f6db0(9,0,0,0);
      FUN_0042c8b0(0xdc);
      FUN_005f5e00();
      return;
    }
    break;
  case 0x5a:
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_0042c840(1);
      FUN_0042c800(0);
      *(undefined4 *)(param_1 + 0x78) = 0x3e19999a;
      *(undefined4 *)(param_1 + 0x74) = 0x3e19999a;
      *(undefined4 *)(param_1 + 0x70) = 0x3e19999a;
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    fVar5 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x78) = (float)(fVar5 * (float10)0.1 + (float10)*(float *)(param_1 + 0x78))
    ;
    fVar5 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x74) = (float)(fVar5 * (float10)0.1 + (float10)*(float *)(param_1 + 0x74))
    ;
    fVar5 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 3.0);
    *(float *)(param_1 + 0x70) = (float)(fVar5 * (float10)0.1 + (float10)*(float *)(param_1 + 0x70))
    ;
    if (*(int *)(param_1 + 0x154) == 6) {
      FUN_0042c840(0);
    }
    if ((5 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xd, *(int *)(param_1 + 0xe8) < 1)) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
      FUN_005f5e00();
      return;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),*(undefined1 *)(param_1 + 0xe8),
                 *(undefined1 *)(param_1 + 0xe8),0xff);
    break;
  case 100:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
    }
    if (0x1e < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x6e:
    if ((0x15d < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
       (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 0x16a)) {
      *(undefined4 *)(param_1 + 100) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 100);
      *(undefined4 *)(param_1 + 0x5c) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c);
      iVar1 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
      fVar5 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
      *(float *)(param_1 + 0x14) =
           (float)(fVar5 * (float10)60.0 + (float10)*(float *)(iVar1 + 0x14));
      *(float *)(param_1 + 0x18) =
           *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 70.0;
      iVar1 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
      fVar5 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
      *(float *)(param_1 + 0x1c) =
           (float)(fVar5 * (float10)60.0 + (float10)*(float *)(iVar1 + 0x1c));
    }
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x54) = 0x3c23d70a;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_0042c840(5);
    }
    sVar3 = FUN_0042c7b0();
    if ((sVar3 != 0) &&
       (*(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1, 9 < *(int *)(param_1 + 0xf0))) {
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_0042c800(0);
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
    if (*(int *)(param_1 + 0x154) == 0x29) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x78:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x74) = 0x40400000;
      *(undefined4 *)(param_1 + 0x78) = 0x40400000;
      *(undefined4 *)(param_1 + 0x54) = 0x3e99999a;
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
      FUN_0042c840(1);
    }
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.05;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.05;
    if ((0x1a < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0x14, *(int *)(param_1 + 0xe8) < 0))
    {
      *(undefined4 *)(param_1 + 0xe8) = 0;
      FUN_005f5e00();
      return;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),*(undefined1 *)(param_1 + 0xe8),
                 *(undefined1 *)(param_1 + 0xe8),0xff);
    if (0x29 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
    break;
  case 0x82:
    if ((0x15d < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
       (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 0x16a)) {
      *(float *)(param_1 + 100) =
           (*(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 100) + 60.0) -
           (float)(*(int *)(param_1 + 0x154) * 6);
      *(undefined4 *)(param_1 + 0x5c) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c);
      iVar1 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
      fVar5 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
      *(float *)(param_1 + 0x14) =
           (float)(fVar5 * (float10)60.0 + (float10)*(float *)(iVar1 + 0x14));
      *(float *)(param_1 + 0x18) =
           *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 70.0;
      iVar1 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
      fVar5 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100));
      *(float *)(param_1 + 0x1c) =
           (float)(fVar5 * (float10)60.0 + (float10)*(float *)(iVar1 + 0x1c));
    }
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x74) = 0x3e800000;
      *(undefined4 *)(param_1 + 0x78) = 0x3e800000;
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
    if (0x14 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x8c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
      uVar4 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar4 % 0x168);
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
    }
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.05;
    if (*(float *)(param_1 + 0x70) < 0.0) {
      *(undefined4 *)(param_1 + 0x70) = 0;
    }
    if ((10 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0x14, *(int *)(param_1 + 0xe8) < 0))
    {
      *(undefined4 *)(param_1 + 0xe8) = 0;
      FUN_005f5e00();
      return;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),*(undefined1 *)(param_1 + 0xe8),
                 *(undefined1 *)(param_1 + 0xe8),0xff);
    break;
  case 0x96:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
      uVar4 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar4 % 0x168);
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
    fVar5 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) << 2));
    *(float *)(param_1 + 0x70) = (float)(fVar5 * (float10)1.0 + (float10)1.0);
    *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x70);
    *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x70);
    if ((3 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0x14, *(int *)(param_1 + 0xe8) < 0))
    {
      *(undefined4 *)(param_1 + 0xe8) = 0;
      FUN_005f5e00();
      return;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),*(undefined1 *)(param_1 + 0xe8),
                 *(undefined1 *)(param_1 + 0xe8),0xff);
    break;
  case 0xa0:
    *(undefined4 *)(param_1 + 0x6c) = 0;
    *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + 2.0;
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x78) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0;
    }
    if (2.0 <= *(float *)(param_1 + 0x78)) {
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.01;
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.01;
    }
    else {
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.2;
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.2;
    }
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_005f6ef0(6,0,0x44fa0000,0,0,-*(float *)(param_1 + 0x6c) - 90.0);
      FUN_0042c8b0(0xdb);
    }
    if (*(int *)(param_1 + 0x154) == 10) {
      FUN_005f6ef0(6,0x43160000,0x44fa0000,0,0,-*(float *)(param_1 + 0x6c) - 90.0);
      FUN_005f6ef0(6,0xc3160000,0x44fa0000,0,0,-*(float *)(param_1 + 0x6c) - 90.0);
      FUN_005f6ef0(6,0,0x44fa0000,0x43160000,0,-*(float *)(param_1 + 0x6c) - 90.0);
      FUN_005f6ef0(6,0,0x44fa0000,0xc3160000,0,-*(float *)(param_1 + 0x6c) - 90.0);
      FUN_0042c8b0(0xdb);
    }
    if (*(int *)(param_1 + 0x154) < 0x3d) {
      fVar5 = (float10)FUN_0065d010((float)*(int *)(param_1 + 0x154) * 6.0);
      *(float *)(param_1 + 0x74) = (float)(fVar5 * (float10)0.1 + (float10)1.0);
    }
    else {
      FUN_0042c840(0);
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) * 0.85;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.01;
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.01;
      if (*(float *)(param_1 + 0x74) < 0.01 != (*(float *)(param_1 + 0x74) == 0.01)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0xaa:
    *(undefined4 *)(param_1 + 0x6c) = 0;
    *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + 2.0;
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x78) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0;
    }
    if (3.0 <= *(float *)(param_1 + 0x78)) {
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.01;
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.01;
    }
    else {
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.3;
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.3;
    }
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_005f6ef0(6,0,0x44fa0000,0,0,-*(float *)(param_1 + 0x6c) - 90.0);
      FUN_0042c8b0(0xdb);
    }
    if (*(int *)(param_1 + 0x154) == 10) {
      FUN_005f6ef0(6,0x43160000,0x44fa0000,0,0,-*(float *)(param_1 + 0x6c) - 90.0);
      FUN_005f6ef0(6,0xc3160000,0x44fa0000,0,0,-*(float *)(param_1 + 0x6c) - 90.0);
      FUN_005f6ef0(6,0,0x44fa0000,0x43160000,0,-*(float *)(param_1 + 0x6c) - 90.0);
      FUN_005f6ef0(6,0,0x44fa0000,0xc3160000,0,-*(float *)(param_1 + 0x6c) - 90.0);
      FUN_0042c8b0(0xdb);
    }
    if (*(int *)(param_1 + 0x154) == 0x14) {
      FUN_005f6ef0(6,0x43480000,0x44fa0000,0x43480000,0,-*(float *)(param_1 + 0x6c) - 90.0);
      FUN_005f6ef0(6,0xc3480000,0x44fa0000,0x43480000,0,-*(float *)(param_1 + 0x6c) - 90.0);
      FUN_005f6ef0(6,0x43480000,0x44fa0000,0xc3480000,0,-*(float *)(param_1 + 0x6c) - 90.0);
      FUN_005f6ef0(6,0xc3480000,0x44fa0000,0xc3480000,0,-*(float *)(param_1 + 0x6c) - 90.0);
      FUN_0042c8b0(0xdb);
    }
    if (*(int *)(param_1 + 0x154) < 0x3d) {
      fVar5 = (float10)FUN_0065d010((float)*(int *)(param_1 + 0x154) * 6.0);
      *(float *)(param_1 + 0x74) = (float)(fVar5 * (float10)0.1 + (float10)1.0);
    }
    else {
      FUN_0042c840(0);
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) * 0.85;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.01;
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.01;
      if (*(float *)(param_1 + 0x74) < 0.01 != (*(float *)(param_1 + 0x74) == 0.01)) {
        FUN_005f5e00();
        return;
      }
    }
  }
  *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
  FUN_005f75a0();
  return;
}

