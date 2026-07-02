// Function: FUN_00620e20
// Address:  0x00620e20
// Source:   batch_decompile (mass dump)
// Hash:     542e0466ef523ea4


void __fastcall FUN_00620e20(int param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  float10 fVar4;
  int local_c;
  int local_8;
  
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
      *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x2c) = (float)(uVar3 % 0x168);
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar3 % 0x168);
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x34) = (float)(uVar3 % 0x168);
      *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 0x32;
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.2;
    cVar1 = FUN_005f6a90();
    if ((cVar1 == '\x01') || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) {
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
      *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x2c) = (float)(uVar3 % 0x168);
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar3 % 0x168);
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x34) = (float)(uVar3 % 0x168);
      *(undefined4 *)(param_1 + 0x54) = 0x42340000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 0x32;
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.4;
    cVar1 = FUN_005f6a90();
    if ((cVar1 == '\x01') || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) {
      FUN_005f5e00();
      return;
    }
    if (0xb4 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x14:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x2c) = (float)(uVar3 % 0x168);
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar3 % 0x168);
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x34) = (float)(uVar3 % 0x168);
      FUN_0042db10(0,0x41200000);
      *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_005f6880(0);
    }
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.25;
    if (((800 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
       (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_0042c8b0(0xb0);
      for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1) {
        uVar3 = FUN_0065d150();
        *(uint *)(param_1 + 0xf0) = uVar3 % 0x168;
        uVar3 = FUN_0065d150();
        *(uint *)(param_1 + 0xec) = uVar3 % 0x28;
        FUN_005f6ef0(4,0,0,0,(float)*(int *)(param_1 + 0xf0),(float)*(int *)(param_1 + 0xec) + 30.0)
        ;
      }
      FUN_005f5e00();
      return;
    }
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f400000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f400000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f400000;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x2c) = (float)(uVar3 % 0x168);
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar3 % 0x168);
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x34) = (float)(uVar3 % 0x168);
      FUN_0042db10(0,0x41200000);
      *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_005f6880(0);
    }
    FUN_0042db10(0,0x3dcccccd);
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.25;
    if (((800 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
       (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_0042c8b0(0xb0);
      for (local_c = 0; local_c < 0xc; local_c = local_c + 1) {
        uVar3 = FUN_0065d150();
        *(uint *)(param_1 + 0xf0) = uVar3 % 0x168;
        uVar3 = FUN_0065d150();
        *(uint *)(param_1 + 0xec) = uVar3 % 0x28;
        FUN_005f6ef0(4,0,0,0,(float)*(int *)(param_1 + 0xf0),(float)*(int *)(param_1 + 0xec) + 30.0)
        ;
      }
      FUN_005f5e00();
      return;
    }
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x2c) = (float)(uVar3 % 0x168);
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar3 % 0x168);
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x34) = (float)(uVar3 % 0x168);
      *(undefined4 *)(param_1 + 0x54) = 0x41700000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 0x32;
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.5;
    cVar1 = FUN_005f6a90();
    if ((cVar1 == '\x01') || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) {
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
      *(undefined4 *)(param_1 + 0x54) = 0x42520000;
      FUN_0042c840(3);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      FUN_005f7450(0,0x43480000,0x3c,1,0);
      FUN_005f6fd0(9,0,0,0);
    }
    if (*(int *)(param_1 + 0x154) % 5 == 0) {
      FUN_005f6fd0(7,0,0,0);
    }
    FUN_0042c800(0);
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3ba3d70a);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.005;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.005;
      }
    }
    if ((0x1e0 < *(int *)(param_1 + 0x154)) ||
       (((sVar2 = FUN_0042c7b0(), sVar2 != 0 && (sVar2 = FUN_0042c7b0(), sVar2 != 1)) ||
        (cVar1 = FUN_005f6a90(), cVar1 == '\x01')))) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.05;
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.05;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.05;
    if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
      *(undefined4 *)(param_1 + 0x70) = 0;
      *(undefined4 *)(param_1 + 0x74) = 0;
      *(undefined4 *)(param_1 + 0x78) = 0;
    }
    if (*(int *)(param_1 + 0x154) % 0xf == 0) {
      FUN_005f7110(9,0,0,0,0,0);
    }
    if (((0x5a < *(int *)(param_1 + 0x154)) && (*(int *)(param_1 + 0x154) < 600)) &&
       (*(int *)(param_1 + 0x154) == 0x5b)) {
      FUN_005f6ef0(7,0,0,0,0,0);
    }
    if (((800 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
       (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_005f5e00();
      return;
    }
    if (600 < *(int *)(param_1 + 0x154)) {
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.05;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.05;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.05;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x46:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x3dcccccd;
      *(undefined4 *)(param_1 + 0x74) = 0x3e19999a;
      *(undefined4 *)(param_1 + 0x78) = 0x3dcccccd;
    }
    if (2.0 <= *(float *)(param_1 + 0x70)) {
      FUN_0042c840(99);
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40400000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
    }
    else {
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.1;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.15;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.1;
    }
    if (*(int *)(param_1 + 0x154) % 0x1e == 0) {
      FUN_0042c8b0(0xb2);
    }
    sVar2 = FUN_0042c7b0();
    if ((sVar2 != 0) &&
       (*(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1, 0x28 < *(int *)(param_1 + 0xec))) {
      *(undefined4 *)(param_1 + 0xec) = 0;
      FUN_0042c800(0);
    }
    if (0x1fe < *(int *)(param_1 + 0x154)) {
      FUN_0042c840(0);
      *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -5;
      if (*(int *)(param_1 + 0xe8) < 0) {
        FUN_005f5e00();
        return;
      }
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    break;
  case 0x50:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
    }
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.5;
    if (0x3c < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x5a:
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_0042c840(1);
      FUN_0042c800(0);
      *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar3 % 0x168);
    }
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 4.0);
    *(float *)(param_1 + 0x78) = (float)(fVar4 * (float10)0.1 + (float10)*(float *)(param_1 + 0x78))
    ;
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 4.0);
    *(float *)(param_1 + 0x74) = (float)(fVar4 * (float10)0.1 + (float10)*(float *)(param_1 + 0x74))
    ;
    fVar4 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0x154) * 4.0);
    *(float *)(param_1 + 0x70) = (float)(fVar4 * (float10)0.1 + (float10)*(float *)(param_1 + 0x70))
    ;
    if (*(int *)(param_1 + 0x154) == 6) {
      FUN_0042c840(0);
    }
    if ((10 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xd, *(int *)(param_1 + 0xe8) < 0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),*(undefined1 *)(param_1 + 0xe8),
                 *(undefined1 *)(param_1 + 0xe8),0xff);
    if (*(int *)(param_1 + 0xe8) < 1) {
      FUN_005f5e00();
      return;
    }
  }
  *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
  FUN_005f75a0();
  return;
}

