// Function: FUN_0062e5d0
// Address:  0x0062e5d0
// Source:   batch_decompile (mass dump)
// Hash:     fc220e2216780e8d


void __fastcall FUN_0062e5d0(int param_1)

{
  float fVar1;
  float fVar2;
  char cVar3;
  short sVar4;
  uint uVar5;
  float10 fVar6;
  
  uVar5 = FUN_0042c7b0();
  if (((uVar5 & 0x100) != 0) &&
     ((*(int *)(param_1 + 0x150) == 0x32 || (*(int *)(param_1 + 0x150) == 0x3c)))) {
    FUN_005f72c0(0x43340000,-*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
    FUN_0042c800(0);
    FUN_0042c840(1);
  }
  switch(*(undefined4 *)(param_1 + 0x150)) {
  case 0:
    FUN_0042cc90();
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x3f800000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
    }
    if (*(int *)(param_1 + 0x154) == 4) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      FUN_005f5e00();
      return;
    }
    sVar4 = FUN_0042c7b0();
    if ((sVar4 != 0) && (0 < *(int *)(param_1 + 0x154))) {
      fVar6 = (float10)FUN_0042d980();
      *(float *)(param_1 + 0x100) = (float)fVar6;
      fVar1 = *(float *)(param_1 + 0x80);
      fVar2 = *(float *)(param_1 + 0x80);
      fVar6 = (float10)FUN_0040da40(*(float *)(*(int *)(param_1 + 0x38) + 0x18) -
                                    *(float *)(param_1 + 0x18),2);
      if ((fVar6 + (float10)*(float *)(param_1 + 0x100) < (float10)(fVar1 * fVar2)) &&
         (*(int *)(param_1 + 0xe8) == 0)) {
        FUN_005f6ef0(1,(*(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14)) +
                       0.0,(*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18)
                           ) + 100.0,
                     (*(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c)) +
                     0.0,0,0);
        *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
      }
    }
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.4;
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.4;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.4;
    if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 10:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x3f800000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
    }
    if (*(int *)(param_1 + 0x154) == 4) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      FUN_005f5e00();
      return;
    }
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.4;
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.4;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.4;
    if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x14:
    FUN_005f6a90();
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x3f800000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x40800000;
      *(undefined4 *)(param_1 + 0x74) = 0x40800000;
      *(undefined4 *)(param_1 + 0x78) = 0x40800000;
    }
    if (*(int *)(param_1 + 0x154) == 4) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      FUN_005f5e00();
      return;
    }
    sVar4 = FUN_0042c7b0();
    if (((sVar4 != 0) &&
        (fVar1 = *(float *)(param_1 + 0x80), fVar2 = *(float *)(param_1 + 0x80),
        fVar6 = (float10)FUN_0042d980(), fVar6 < (float10)(fVar1 * fVar2))) &&
       (*(int *)(param_1 + 0xe8) == 0)) {
      FUN_005f6ef0(3,(*(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14)) +
                     0.0,(*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18))
                         + 100.0,
                   (*(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c)) + 0.0,
                   0,0);
      FUN_005f7110(4,(*(float *)(*(int *)(param_1 + 0x38) + 0x14) - *(float *)(param_1 + 0x14)) +
                     0.0,(*(float *)(*(int *)(param_1 + 0x38) + 0x18) - *(float *)(param_1 + 0x18))
                         + 100.0,
                   (*(float *)(*(int *)(param_1 + 0x38) + 0x1c) - *(float *)(param_1 + 0x1c)) + 0.0,
                   0,0);
      *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
    }
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.8;
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.8;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.8;
    if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x3f800000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
    }
    if (*(int *)(param_1 + 0x154) == 4) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      FUN_005f5e00();
      return;
    }
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.4;
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.4;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.4;
    if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    fVar6 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) << 2));
    *(float *)(param_1 + 0x70) = (float)(fVar6 * (float10)0.2 + (float10)*(float *)(param_1 + 0x70))
    ;
    fVar6 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) << 2));
    *(float *)(param_1 + 0x74) = (float)(fVar6 * (float10)0.2 + (float10)*(float *)(param_1 + 0x74))
    ;
    fVar6 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) << 2));
    *(float *)(param_1 + 0x78) = (float)(fVar6 * (float10)0.2 + (float10)*(float *)(param_1 + 0x78))
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
  case 0x32:
    if (*(int *)(param_1 + 0x154) == 0) {
      if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
          (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
         (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd)) {
        fVar6 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar6 < (float10)10.0) {
          fVar6 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar6;
        }
        fVar6 = (float10)FUN_0042dac0(2);
        if ((float10)-10.0 < (float10)*(float *)(param_1 + 0x6c) - fVar6) {
          fVar6 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar6;
        }
      }
      *(undefined4 *)(param_1 + 0x70) = 0x40c00000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x54) = 0x42820000;
      FUN_0042c840(1);
    }
    sVar4 = FUN_0042c7b0();
    if ((sVar4 != 0) || (cVar3 = FUN_005f6a90(), cVar3 == '\x01')) {
      FUN_005f6fd0(8,0,0,0);
      FUN_005f5e00();
      return;
    }
    if (0xb4 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
          (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
         (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd)) {
        fVar6 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar6 < (float10)10.0) {
          fVar6 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar6;
        }
        fVar6 = (float10)FUN_0042dac0(2);
        if ((float10)-10.0 < (float10)*(float *)(param_1 + 0x6c) - fVar6) {
          fVar6 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar6;
        }
      }
      *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x54) = 0x42aa0000;
      FUN_0042c840(1);
    }
    sVar4 = FUN_0042c7b0();
    if ((sVar4 != 0) || (cVar3 = FUN_005f6a90(), cVar3 == '\x01')) {
      FUN_005f6fd0(8,0,0,0);
      FUN_005f5e00();
      return;
    }
    if (0xb4 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x46:
    *(undefined4 *)(param_1 + 0x54) = 0;
    if (5 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x50:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
      uVar5 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar5 % 0x168);
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
  case 0x5a:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x78) = 0x40a00000;
      *(undefined4 *)(param_1 + 0x74) = 0x40a00000;
      *(undefined4 *)(param_1 + 0x70) = 0x40a00000;
      uVar5 = FUN_0065d150();
      *(float *)(param_1 + 0x54) = (float)(uVar5 % 0x14) * 0.1 + 2.0;
      uVar5 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar5 % 0x168);
      *(undefined4 *)(param_1 + 0x6c) = 0x42b40000;
    }
    if (0x1d < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
  }
  *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
  FUN_005f75a0();
  return;
}

