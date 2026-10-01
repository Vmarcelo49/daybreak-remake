// Function: FUN_00626f30
// Address:  0x00626f30
// Source:   batch_decompile (mass dump)
// Hash:     2b7f895a1cfe8b3e


void __fastcall FUN_00626f30(int param_1)

{
  int iVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  float10 fVar5;
  float fVar6;
  
  uVar4 = FUN_0042c7b0();
  if (((uVar4 & 0x100) != 0) &&
     ((*(int *)(param_1 + 0x150) == 0 || (*(int *)(param_1 + 0x150) == 10)))) {
    FUN_005f72c0(0x43340000,-*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
    FUN_0042c800(0);
    FUN_0042c840(1);
  }
  switch(*(undefined4 *)(param_1 + 0x150)) {
  case 0:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x100) = 0;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0x54) = 0x420c0000;
      FUN_0042c840(1);
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 0.25;
    if (*(float *)(param_1 + 0x54) < 25.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41c80000;
    }
    if (*(int *)(param_1 + 0x154) % 3 == 0) {
      FUN_005f6fd0(3,0,0,0);
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      *(float *)(param_1 + 0x100) = *(float *)(param_1 + 0x100) + 0.01;
      if (0.6 < *(float *)(param_1 + 0x100)) {
        *(undefined4 *)(param_1 + 0x100) = 0x3f19999a;
      }
      FUN_0042db10(0,*(float *)(param_1 + 0x100) + 0.75);
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
        *(float *)(param_1 + 0x6c) =
             *(float *)(param_1 + 0x6c) - (*(float *)(param_1 + 0x100) * 0.5 + 0.2);
      }
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) =
             *(float *)(param_1 + 0x100) * 0.5 + 0.2 + *(float *)(param_1 + 0x6c);
      }
    }
    cVar2 = FUN_005f6a90();
    if (((cVar2 == '\x01') || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
       (0xb4 < *(int *)(param_1 + 0x154))) {
      FUN_0042c8b0(0x69);
      FUN_005f6db0(2,0,0,0);
      FUN_005f5e00();
      return;
    }
    break;
  case 10:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x100) = 0;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0x54) = 0x42200000;
      FUN_0042c840(1);
      FUN_005f7450(2,0x43480000,0x19,1,0);
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 0.25;
    if (*(float *)(param_1 + 0x54) < 25.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41c80000;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      *(float *)(param_1 + 0x100) = *(float *)(param_1 + 0x100) + 0.01;
      if (0.6 < *(float *)(param_1 + 0x100)) {
        *(undefined4 *)(param_1 + 0x100) = 0x3f19999a;
      }
      FUN_0042db10(0,*(float *)(param_1 + 0x100) + 1.25);
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
        *(float *)(param_1 + 0x6c) =
             *(float *)(param_1 + 0x6c) - (*(float *)(param_1 + 0x100) * 0.5 + 0.3);
      }
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) =
             *(float *)(param_1 + 0x100) * 0.5 + 0.3 + *(float *)(param_1 + 0x6c);
      }
    }
    cVar2 = FUN_005f6a90();
    if (((cVar2 == '\x01') || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
       (0xb4 < *(int *)(param_1 + 0x154))) {
      FUN_0042c8b0(0x69);
      FUN_005f6db0(2,0,0,0);
      FUN_005f5e00();
      return;
    }
    break;
  case 0x14:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      FUN_0042c840(1);
    }
    if (0x33 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
      uVar4 = FUN_0065d150();
      *(float *)(param_1 + 0x70) = (float)(uVar4 % 10) * 0.1 + 1.0;
      *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x70);
      *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x70);
      uVar4 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar4 % 0x168);
    }
    if (0x1d < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x100) = 0;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0x54) = 0x40a00000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0x70) = 0x40800000;
      *(undefined4 *)(param_1 + 0x74) = 0x40800000;
      *(undefined4 *)(param_1 + 0x78) = 0x40800000;
    }
    if (*(int *)(param_1 + 0x154) % 3 == 0) {
      FUN_005f6fd0(3,0,0,0);
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + 0.5;
    if (100.0 < *(float *)(param_1 + 0x54)) {
      *(undefined4 *)(param_1 + 0x54) = 0x42c80000;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3f400000);
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.1;
      }
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.1;
      }
    }
    cVar2 = FUN_005f6a90();
    if (((cVar2 == '\x01') || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
       (0xf0 < *(int *)(param_1 + 0x154))) {
      FUN_0042c8b0(0x4a);
      FUN_005f6db0(6,0,0,0);
      FUN_005f5e00();
      return;
    }
    break;
  case 0x32:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x100) = 0;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0x54) = 0x40a00000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0x70) = 0x40d00000;
      *(undefined4 *)(param_1 + 0x74) = 0x40d00000;
      *(undefined4 *)(param_1 + 0x78) = 0x40d00000;
      FUN_005f7450(2,0x43480000,0x19,1,0);
    }
    if (*(int *)(param_1 + 0x154) % 3 == 0) {
      FUN_005f6fd0(3,0,0,0);
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + 0.75;
    if (120.0 < *(float *)(param_1 + 0x54)) {
      *(undefined4 *)(param_1 + 0x54) = 0x42f00000;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3f800000);
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.2;
      }
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.2;
      }
    }
    cVar2 = FUN_005f6a90();
    if (((cVar2 == '\x01') || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
       (0xf0 < *(int *)(param_1 + 0x154))) {
      FUN_0042c8b0(0x4a);
      FUN_005f6db0(6,0,0,0);
      FUN_005f5e00();
      return;
    }
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
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
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x100) = 0;
      *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0x70) = 0x40c00000;
      *(undefined4 *)(param_1 + 0x74) = 0x40c00000;
      *(undefined4 *)(param_1 + 0x78) = 0x40c00000;
      FUN_0042c800(0);
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 0.5;
    if (*(float *)(param_1 + 0x54) < 4.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x40800000;
    }
    uVar4 = *(uint *)(param_1 + 0x154) & 0x80000003;
    if ((int)uVar4 < 0) {
      uVar4 = (uVar4 - 1 | 0xfffffffc) + 1;
    }
    if (uVar4 == 0) {
      uVar4 = FUN_0065d150();
      fVar6 = ((float)(uVar4 % 0x14) - 10.0) -
              (*(float *)(param_1 + 0x6c) + *(float *)(param_1 + 0x6c));
      uVar4 = FUN_0065d150(fVar6);
      FUN_005f7110(0xb,*(float *)(param_1 + 0x3c) * -150.0,*(float *)(param_1 + 0x40) * -150.0,
                   *(float *)(param_1 + 0x44) * -150.0,(float)(uVar4 % 0x14) + 170.0,fVar6);
    }
    FUN_0042db10(0,0x3f400000);
    fVar5 = (float10)FUN_0042dac0(2);
    if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
      *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.3;
    }
    fVar5 = (float10)FUN_0042dac0(2);
    if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-1.0) {
      *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.3;
    }
    if (((10 < *(int *)(param_1 + 0x154)) && (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) ||
       (sVar3 = FUN_0042c7b0(), sVar3 != 0)) {
      FUN_0042c8b0(0x9d);
      FUN_005f6db0(8,0,0,0);
      FUN_005f6db0(9,0,0,0);
      FUN_005f6db0(10,0,0,0);
      FUN_005f5e00();
      return;
    }
    if (0x4b0 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x50:
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
  case 0x5a:
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
  case 100:
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
  case 0x6e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
      *(undefined4 *)(param_1 + 0x100) = 0x41200000;
      uVar4 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar4 % 0x168);
      *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
      uVar4 = FUN_0065d150();
      *(uint *)(param_1 + 0xec) = uVar4 % 100;
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 0.5;
    if (*(float *)(param_1 + 0x54) < 1.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x3f800000;
    }
    *(float *)(param_1 + 0x100) = *(float *)(param_1 + 0x100) - 0.5;
    if (*(float *)(param_1 + 0x100) < 1.0) {
      *(undefined4 *)(param_1 + 0x100) = 0x3f800000;
    }
    if (*(int *)(param_1 + 0xec) < 0x32) {
      *(float *)(param_1 + 0x30) = *(float *)(param_1 + 0x30) + *(float *)(param_1 + 0x100);
    }
    else {
      *(float *)(param_1 + 0x30) = *(float *)(param_1 + 0x30) - *(float *)(param_1 + 0x100);
    }
    if ((4 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -10, *(int *)(param_1 + 0xe8) < 0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
      FUN_005f5e00();
      return;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    break;
  case 0x78:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0xf4) = 0;
      *(undefined4 *)(param_1 + 0xf8) = 0;
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0;
      *(undefined4 *)(param_1 + 0x74) = 0;
      *(undefined4 *)(param_1 + 0x78) = 0;
    }
    if ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x87) &&
       (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0xba)) {
      FUN_005f5e00();
      return;
    }
    *(undefined4 *)(param_1 + 0x6c) = 0;
    if (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0xba) {
      if (1.0 <= *(float *)(param_1 + 0x70)) {
        *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
        *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
        *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
      }
      else {
        *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.05;
        *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.05;
        *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.05;
      }
      if (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) != 0) {
        *(undefined4 *)(param_1 + 0x5c) =
             *(undefined4 *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) + 0x5c);
        *(undefined4 *)(param_1 + 100) =
             *(undefined4 *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) + 100);
        iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0);
        fVar5 = (float10)FUN_0065d010(90.0 - (*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)
                                             ));
        *(float *)(param_1 + 0x14) =
             (float)(fVar5 * (float10)135.0 + (float10)*(float *)(iVar1 + 0x14));
        *(float *)(param_1 + 0x18) =
             *(float *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) + 0x18) + 90.0
        ;
        iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0);
        fVar5 = (float10)FUN_0065d050(90.0 - (*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)
                                             ));
        *(float *)(param_1 + 0x1c) =
             (float)(fVar5 * (float10)135.0 + (float10)*(float *)(iVar1 + 0x1c));
      }
    }
    if (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0x87) {
      if (1.0 <= *(float *)(param_1 + 0x70)) {
        *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
        *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
        *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
      }
      else {
        *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.05;
        *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.05;
        *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.05;
      }
      *(undefined4 *)(param_1 + 0x5c) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c);
      *(undefined4 *)(param_1 + 0x6c) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x100);
      *(undefined4 *)(param_1 + 100) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 100);
      *(undefined4 *)(param_1 + 0x14) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x14);
      *(float *)(param_1 + 0x18) =
           *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 85.0;
      *(undefined4 *)(param_1 + 0x1c) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x1c);
    }
    break;
  case 0x82:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0xf4) = 0;
      *(undefined4 *)(param_1 + 0xf8) = 0;
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0;
      *(undefined4 *)(param_1 + 0x74) = 0;
      *(undefined4 *)(param_1 + 0x78) = 0;
    }
    if ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x87) &&
       (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0xba)) {
      FUN_005f5e00();
      return;
    }
    *(undefined4 *)(param_1 + 0x6c) = 0;
    if (1.0 <= *(float *)(param_1 + 0x70)) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
    }
    else {
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.05;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.05;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.05;
    }
    if ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0xba) &&
       (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) != 0)) {
      *(undefined4 *)(param_1 + 0x5c) =
           *(undefined4 *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) + 0x5c);
      *(undefined4 *)(param_1 + 100) =
           *(undefined4 *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) + 100);
      iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0);
      fVar5 = (float10)FUN_0065d010(90.0 - (*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)))
      ;
      *(float *)(param_1 + 0x14) =
           (float)(fVar5 * (float10)125.0 + (float10)*(float *)(iVar1 + 0x14));
      *(float *)(param_1 + 0x18) =
           *(float *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) + 0x18) + 50.0;
      iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0);
      fVar5 = (float10)FUN_0065d050(90.0 - (*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)))
      ;
      *(float *)(param_1 + 0x1c) =
           (float)(fVar5 * (float10)125.0 + (float10)*(float *)(iVar1 + 0x1c));
    }
    if (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0x87) {
      *(undefined4 *)(param_1 + 0x5c) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c);
      *(undefined4 *)(param_1 + 100) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 100);
      *(undefined4 *)(param_1 + 0x6c) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x100);
      *(undefined4 *)(param_1 + 0x14) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x14);
      *(float *)(param_1 + 0x18) =
           *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 85.0;
      *(undefined4 *)(param_1 + 0x1c) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x1c);
    }
    break;
  case 0x8c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0xf4) = 0;
      *(undefined4 *)(param_1 + 0xf8) = 0;
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0;
      *(undefined4 *)(param_1 + 0x74) = 0;
      *(undefined4 *)(param_1 + 0x78) = 0;
    }
    if ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x87) &&
       (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0xba)) {
      FUN_005f5e00();
      return;
    }
    *(undefined4 *)(param_1 + 0x6c) = 0;
    if (1.0 <= *(float *)(param_1 + 0x70)) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
    }
    else {
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.05;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.05;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.05;
    }
    if ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0xba) &&
       (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) != 0)) {
      *(undefined4 *)(param_1 + 0x5c) =
           *(undefined4 *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) + 0x5c);
      *(undefined4 *)(param_1 + 100) =
           *(undefined4 *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) + 100);
      iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0);
      fVar5 = (float10)FUN_0065d010(90.0 - (*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)))
      ;
      *(float *)(param_1 + 0x14) =
           (float)(fVar5 * (float10)125.0 + (float10)*(float *)(iVar1 + 0x14));
      *(float *)(param_1 + 0x18) =
           *(float *)(*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0) + 0x18) + 50.0;
      iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaed0);
      fVar5 = (float10)FUN_0065d050(90.0 - (*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)))
      ;
      *(float *)(param_1 + 0x1c) =
           (float)(fVar5 * (float10)125.0 + (float10)*(float *)(iVar1 + 0x1c));
    }
    if (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0x87) {
      *(undefined4 *)(param_1 + 0x5c) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x5c);
      *(undefined4 *)(param_1 + 100) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 100);
      *(undefined4 *)(param_1 + 0x6c) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x100);
      *(undefined4 *)(param_1 + 0x14) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x14);
      *(float *)(param_1 + 0x18) =
           *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 85.0;
      *(undefined4 *)(param_1 + 0x1c) =
           *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x1c);
    }
  }
  *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
  FUN_005f75a0();
  return;
}

