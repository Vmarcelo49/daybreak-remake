// Function: FUN_00619ad0
// Address:  0x00619ad0
// Source:   batch_decompile (mass dump)
// Hash:     169d5df622f29687


void __fastcall FUN_00619ad0(int param_1)

{
  int iVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  float10 fVar5;
  
  uVar4 = FUN_0042c7b0();
  if (((uVar4 & 0x100) != 0) &&
     (((iVar1 = *(int *)(param_1 + 0x150), iVar1 == 0 || (iVar1 == 10)) || (iVar1 == 0x8c)))) {
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
      FUN_0042db10(0,0x40a00000);
      *(undefined4 *)(param_1 + 0x70) = 0x40c00000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x54) = 0x42340000;
      FUN_0042c840(1);
    }
    sVar3 = FUN_0042c7b0();
    if ((sVar3 != 0) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_005f6fd0(3,0,0,0);
      FUN_005f5e00();
      return;
    }
    if (0xb4 < *(int *)(param_1 + 0x154)) {
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
      FUN_0042db10(0,0x40a00000);
      *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x54) = 0x42820000;
      FUN_0042c840(1);
    }
    sVar3 = FUN_0042c7b0();
    if ((sVar3 != 0) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_005f6fd0(3,0,0,0);
      FUN_005f5e00();
      return;
    }
    if (0xb4 < *(int *)(param_1 + 0x154)) {
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
      uVar4 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar4 % 0x168);
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
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
      FUN_0042c840(1);
      FUN_005f6fd0(7,0,0,0);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      uVar4 = FUN_0065d150();
      *(uint *)(param_1 + 0xf0) = uVar4 % 10;
      FUN_005f7450(5,0x42200000,0x28,1,0);
      *(undefined4 *)(param_1 + 0x54) = 0x425c0000;
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 2.0;
    if (*(float *)(param_1 + 0x54) < (float)*(int *)(param_1 + 0xf0) + 25.0) {
      *(float *)(param_1 + 0x54) = (float)*(int *)(param_1 + 0xf0) + 25.0;
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
    if (0x96 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x96;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154))) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.003);
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
        *(float *)(param_1 + 0x6c) =
             *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.002;
      }
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) =
             (float)*(int *)(param_1 + 0xec) * 0.002 + *(float *)(param_1 + 0x6c);
      }
    }
    if (((0x1e0 < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
       (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_005f6db0(6,0,0,0);
      FUN_0042c8b0(0x4a);
      FUN_005f5e00();
      return;
    }
    break;
  case 0x32:
  case 0x82:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
      FUN_0042c840(1);
      FUN_005f6fd0(7,0,0,0);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      uVar4 = FUN_0065d150();
      *(uint *)(param_1 + 0xf0) = uVar4 % 10;
      FUN_005f7450(2,0x42200000,0x14,1,0);
      *(undefined4 *)(param_1 + 0x54) = 0x425c0000;
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 2.0;
    if (*(float *)(param_1 + 0x54) < (float)*(int *)(param_1 + 0xf0) + 25.0) {
      *(float *)(param_1 + 0x54) = (float)*(int *)(param_1 + 0xf0) + 20.0;
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
    if (0x96 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x96;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154))) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.004);
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
        *(float *)(param_1 + 0x6c) =
             *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.0025;
      }
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) =
             (float)*(int *)(param_1 + 0xec) * 0.0025 + *(float *)(param_1 + 0x6c);
      }
    }
    if (((0x1e0 < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
       (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_005f6db0(6,0,0,0);
      FUN_0042c8b0(0x4a);
      FUN_005f5e00();
      return;
    }
    break;
  case 0x3c:
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
  case 0x46:
    if (5 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x50:
    if (0x1d < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x5a:
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
      *(undefined4 *)(param_1 + 0x54) = 0x40a00000;
      FUN_0042c840(1);
      FUN_005f6fd0(7,0,0,0);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
    }
    fVar5 = (float10)FUN_0065d010((float)*(int *)(param_1 + 0x154) * 30.0);
    *(float *)(param_1 + 0x70) = (float)(fVar5 * (float10)0.05 + (float10)0.5);
    fVar5 = (float10)FUN_0065d010((float)*(int *)(param_1 + 0x154) * 30.0);
    *(float *)(param_1 + 0x74) = (float)(fVar5 * (float10)0.05 + (float10)0.5);
    fVar5 = (float10)FUN_0065d010((float)*(int *)(param_1 + 0x154) * 30.0);
    *(float *)(param_1 + 0x78) = (float)(fVar5 * (float10)0.05 + (float10)0.5);
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + 0.25;
    if (40.0 < *(float *)(param_1 + 0x54)) {
      *(undefined4 *)(param_1 + 0x54) = 0x42200000;
    }
    if (100 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 100;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154))) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.002);
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
        *(float *)(param_1 + 0x6c) =
             *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.002;
      }
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) =
             (float)*(int *)(param_1 + 0xec) * 0.002 + *(float *)(param_1 + 0x6c);
      }
    }
    if (((0x1e0 < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
       (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_005f6db0(10,0,0,0);
      FUN_005f6db0(0xb,0,0,0);
      FUN_005f6db0(0xc,0,0,0);
      FUN_0042c8b0(0x9d);
      FUN_005f5e00();
      return;
    }
    break;
  case 100:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x2c) = 0;
      *(undefined4 *)(param_1 + 0x30) = 0;
      *(float *)(param_1 + 0x34) = -*(float *)(param_1 + 0x6c);
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0xff;
      FUN_0042c840(0);
      *(undefined4 *)(param_1 + 0x70) = 0x41000000;
      *(undefined4 *)(param_1 + 0x74) = 0x41000000;
      *(undefined4 *)(param_1 + 0x78) = 0x41000000;
    }
    if (14.0 <= *(float *)(param_1 + 0x70)) {
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.005;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.005;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.005;
    }
    else {
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.5;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.5;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.5;
    }
    if (*(int *)(param_1 + 0x154) == 0x11) {
      *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + -0x10;
      return;
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
    if (((10 < *(int *)(param_1 + 0xe8)) && (*(int *)(param_1 + 0xe8) % 5 == 0)) &&
       (*(int *)(param_1 + 0xe8) < 0x78)) {
      FUN_0042c840(1);
      FUN_0042c800(0);
    }
    if (0x78 < *(int *)(param_1 + 0xe8)) {
      *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + -5;
      FUN_0042c840(0);
      if (*(int *)(param_1 + 0xec) < 0) {
        *(undefined4 *)(param_1 + 0xe8) = 0;
        FUN_005f5e00();
        return;
      }
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xec),0xff,0xff,0xff);
    break;
  case 0x6e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x2c) = 0;
      *(undefined4 *)(param_1 + 0x30) = 0;
      *(float *)(param_1 + 0x34) = -*(float *)(param_1 + 0x6c);
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0xff;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0x70) = 0x40900000;
      *(undefined4 *)(param_1 + 0x74) = 0x40900000;
      *(undefined4 *)(param_1 + 0x78) = 0x40900000;
    }
    if (10.0 <= *(float *)(param_1 + 0x70)) {
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.0035;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.0035;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.0035;
    }
    else {
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.25;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.25;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.25;
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
    if (((0x14 < *(int *)(param_1 + 0xe8)) && (FUN_0042c840(0), 0x5a < *(int *)(param_1 + 0xe8))) &&
       (*(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + -5, *(int *)(param_1 + 0xec) < 0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
      FUN_005f5e00();
      return;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xec),0xff,0xff,0xff);
    break;
  case 0x78:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x2c) = 0;
      *(undefined4 *)(param_1 + 0x30) = 0;
      *(float *)(param_1 + 0x34) = -*(float *)(param_1 + 0x6c);
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0xff;
      *(undefined4 *)(param_1 + 0x70) = 0x40c00000;
      *(undefined4 *)(param_1 + 0x74) = 0x40c00000;
      *(undefined4 *)(param_1 + 0x78) = 0x40c00000;
    }
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 1.0;
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 1.0;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 1.0;
    if (0x3c < *(int *)(param_1 + 0x154)) {
      FUN_0042c840(0);
      *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + -0xf;
      if (*(int *)(param_1 + 0xec) < 0) {
        *(undefined4 *)(param_1 + 0xe8) = 0;
        FUN_005f5e00();
        return;
      }
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xec),0xff,0xff,0xff);
    break;
  case 0x8c:
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
      FUN_0042db10(0,0x40a00000);
      *(undefined4 *)(param_1 + 0x70) = 0x40c00000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x54) = 0x42340000;
      FUN_0042c840(1);
    }
    sVar3 = FUN_0042c7b0();
    if ((sVar3 != 0) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_005f6fd0(3,0,0,0);
      FUN_005f5e00();
      return;
    }
    if (0xb4 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
  }
  *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
  FUN_005f75a0();
  return;
}

