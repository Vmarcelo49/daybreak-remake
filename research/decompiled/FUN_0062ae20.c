// Function: FUN_0062ae20
// Address:  0x0062ae20
// Source:   batch_decompile (mass dump)
// Hash:     caf66d7d472177c6


void __fastcall FUN_0062ae20(int param_1)

{
  char cVar1;
  uint uVar2;
  float10 fVar3;
  
  uVar2 = FUN_0042c7b0();
  if (((uVar2 & 0x100) != 0) &&
     ((*(int *)(param_1 + 0x150) == 0x28 || (*(int *)(param_1 + 0x150) == 0x32)))) {
    FUN_005f72c0(0x43340000,-*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
    FUN_0042c800(0);
    FUN_0042c840(1);
  }
  switch(*(undefined4 *)(param_1 + 0x150)) {
  case 0:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    if ((10 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0x28, *(int *)(param_1 + 0xe8) < 0))
    {
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    if (0xf < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 10:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f333333;
      *(undefined4 *)(param_1 + 0x74) = 0x3f333333;
      *(undefined4 *)(param_1 + 0x78) = 0x3f333333;
      uVar2 = FUN_0065d150();
      *(float *)(param_1 + 0x34) = (float)(uVar2 % 0x1e) - 15.0;
      uVar2 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar2 % 0x1e) - 15.0;
      uVar2 = FUN_0065d150();
      *(float *)(param_1 + 0x2c) = (float)(uVar2 % 0x168);
    }
    if (0xe < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x14:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f333333;
      *(undefined4 *)(param_1 + 0x74) = 0x3f333333;
      *(undefined4 *)(param_1 + 0x78) = 0x3f333333;
      uVar2 = FUN_0065d150();
      *(float *)(param_1 + 0x34) = (float)(uVar2 % 0x1e) - 15.0;
      uVar2 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar2 % 0x1e) - 15.0;
      uVar2 = FUN_0065d150();
      *(float *)(param_1 + 0x2c) = (float)(uVar2 % 0x168);
    }
    if (0xe < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x78) = 0x3e800000;
      *(undefined4 *)(param_1 + 0x74) = 0x3e800000;
      *(undefined4 *)(param_1 + 0x70) = 0x3e800000;
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    fVar3 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 5));
    *(float *)(param_1 + 0x70) =
         (float)(fVar3 * (float10)0.05 + (float10)*(float *)(param_1 + 0x70));
    fVar3 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 5));
    *(float *)(param_1 + 0x74) =
         (float)(fVar3 * (float10)0.05 + (float10)*(float *)(param_1 + 0x74));
    fVar3 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 5));
    *(float *)(param_1 + 0x78) =
         (float)(fVar3 * (float10)0.05 + (float10)*(float *)(param_1 + 0x78));
    if ((0 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0xf, *(int *)(param_1 + 0xe8) < 0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (0x12 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),*(undefined1 *)(param_1 + 0xe8),
                 *(undefined1 *)(param_1 + 0xe8),0xff);
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42960000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
    }
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.05;
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.05;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.05;
    uVar2 = *(uint *)(param_1 + 0x154) & 0x80000001;
    if ((int)uVar2 < 0) {
      uVar2 = (uVar2 - 1 | 0xfffffffe) + 1;
    }
    if (uVar2 == 0) {
      FUN_005f6fd0(1,0,0,0);
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3e4ccccd);
      fVar3 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar3) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.1;
      }
      fVar3 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar3 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.1;
      }
    }
    if ((0x28 < *(int *)(param_1 + 0x154)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x32:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42a00000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x40400000;
      *(undefined4 *)(param_1 + 0x74) = 0x40400000;
      *(undefined4 *)(param_1 + 0x78) = 0x40400000;
    }
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.05;
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.05;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.05;
    uVar2 = *(uint *)(param_1 + 0x154) & 0x80000001;
    if ((int)uVar2 < 0) {
      uVar2 = (uVar2 - 1 | 0xfffffffe) + 1;
    }
    if (uVar2 == 0) {
      FUN_005f6fd0(2,0,0,0);
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3e4ccccd);
      fVar3 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar3) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.1;
      }
      fVar3 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar3 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.1;
      }
    }
    if ((0x3c < *(int *)(param_1 + 0x154)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    if ((10 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0x28, *(int *)(param_1 + 0xe8) < 0))
    {
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    if (0xf < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x46:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0x74) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0x78) = 0x3fc00000;
      uVar2 = FUN_0065d150();
      *(float *)(param_1 + 0x34) = (float)(uVar2 % 0x1e) - 15.0;
      uVar2 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar2 % 0x1e) - 15.0;
      uVar2 = FUN_0065d150();
      *(float *)(param_1 + 0x2c) = (float)(uVar2 % 0x168);
    }
    if (0xe < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x50:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0;
      *(undefined4 *)(param_1 + 0x74) = 0;
      *(undefined4 *)(param_1 + 0x78) = 0;
      *(undefined4 *)(param_1 + 0x54) = 0x42480000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
    }
    if (*(int *)(param_1 + 0x154) % 3 == 0) {
      FUN_005f6fd0(9,0,0,0);
    }
    if ((0x28 < *(int *)(param_1 + 0x154)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x5a:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0x74) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0x78) = 0x3fc00000;
      uVar2 = FUN_0065d150();
      *(float *)(param_1 + 0x34) = (float)(uVar2 % 0x1e) - 15.0;
      uVar2 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar2 % 0x1e) - 15.0;
      uVar2 = FUN_0065d150();
      *(float *)(param_1 + 0x2c) = (float)(uVar2 % 0x168);
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

