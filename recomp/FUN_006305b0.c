// ============================================
// Address:  0x006305b0
// Original: FUN_006305b0
// Status:   unreviewed
// ============================================


void __fastcall FUN_006305b0(int param_1)

{
  int iVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  float10 fVar5;
  undefined4 uVar6;
  float fVar7;
  
  uVar4 = FUN_0042c7b0();
  if ((uVar4 & 0x100) != 0) {
    switch(*(undefined4 *)(param_1 + 0x150)) {
    case 0:
    case 10:
    case 0x14:
    case 0x1e:
    case 0x46:
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
      *(undefined4 *)(param_1 + 0x54) = 0x42340000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (((0xb4 < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
       (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
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
      *(undefined4 *)(param_1 + 0x54) = 0x42700000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      FUN_005f7450(0,0x41200000,0x14,1,0);
    }
    if (((0xb4 < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
       (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
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
      *(undefined4 *)(param_1 + 0x54) = 0x42340000;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0x28;
      FUN_0042c840(1);
    }
    uVar4 = *(uint *)(param_1 + 0x154) & 0x80000001;
    if ((int)uVar4 < 0) {
      uVar4 = (uVar4 - 1 | 0xfffffffe) + 1;
    }
    if (uVar4 == 0) {
      FUN_005f6fd0(8,0,0,0);
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    if (100 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 100;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.0025);
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
        *(float *)(param_1 + 0x6c) =
             *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.0025;
      }
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) =
             (float)*(int *)(param_1 + 0xec) * 0.0025 + *(float *)(param_1 + 0x6c);
      }
    }
    sVar3 = FUN_0042c7b0();
    if ((sVar3 != 0) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_0042c8b0(0xcc);
      FUN_005f6db0(4,0,0,0);
      FUN_005f6fd0(9,0,0,0);
      FUN_005f5e00();
      return;
    }
    if (0xf0 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x1e:
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
      *(undefined4 *)(param_1 + 0x54) = 0x42340000;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0x28;
      FUN_0042c840(1);
    }
    uVar4 = *(uint *)(param_1 + 0x154) & 0x80000001;
    if ((int)uVar4 < 0) {
      uVar4 = (uVar4 - 1 | 0xfffffffe) + 1;
    }
    if (uVar4 == 0) {
      FUN_005f6fd0(8,0,0,0);
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    if (100 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 100;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.0025);
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
        *(float *)(param_1 + 0x6c) =
             *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.0025;
      }
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) =
             (float)*(int *)(param_1 + 0xec) * 0.0025 + *(float *)(param_1 + 0x6c);
      }
    }
    sVar3 = FUN_0042c7b0();
    if ((sVar3 != 0) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_0042c8b0(0xcc);
      FUN_005f6db0(5,0,0,0);
      FUN_005f6fd0(9,0,0,0);
      FUN_005f5e00();
      return;
    }
    if (0xf0 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x28:
    *(undefined4 *)(param_1 + 0x6c) = 0;
    *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + 1.0;
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x78) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0;
    }
    if (3.0 <= *(float *)(param_1 + 0x78)) {
      *(undefined4 *)(param_1 + 0x78) = 0x40400000;
      *(undefined4 *)(param_1 + 0x70) = 0x40400000;
    }
    else {
      fVar5 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 3));
      *(float *)(param_1 + 0x78) =
           (float)(fVar5 * (float10)0.2 + (float10)*(float *)(param_1 + 0x78));
      fVar5 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 3));
      *(float *)(param_1 + 0x70) =
           (float)(fVar5 * (float10)0.2 + (float10)*(float *)(param_1 + 0x70));
    }
    if (*(int *)(param_1 + 0x154) % 0x1e == 0) {
      FUN_0042c840(1);
      FUN_0042c800(0);
    }
    if (*(int *)(param_1 + 0x154) % 3 == 0) {
      uVar4 = FUN_0065d150();
      *(uint *)(param_1 + 0xe8) = uVar4 % 0x168;
      uVar4 = FUN_0065d150();
      *(uint *)(param_1 + 0xec) = uVar4 % 300;
      iVar1 = *(int *)(param_1 + 0xec);
      fVar5 = (float10)FUN_0065d010((float)*(int *)(param_1 + 0xe8));
      fVar7 = (float)(fVar5 * (float10)iVar1);
      uVar6 = 0;
      iVar1 = *(int *)(param_1 + 0xec);
      fVar5 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0xe8),0,fVar7);
      FUN_005f6fd0(6,(float)(fVar5 * (float10)iVar1),uVar6,fVar7);
    }
    if (*(int *)(param_1 + 0x154) < 0x169) {
      fVar5 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 6));
      *(float *)(param_1 + 0x74) = (float)(fVar5 * (float10)0.25 + (float10)0.75);
    }
    else {
      FUN_0042c840(0);
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      if (*(float *)(param_1 + 0x74) < 0.0 != (*(float *)(param_1 + 0x74) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x32:
    *(undefined4 *)(param_1 + 0x6c) = 0;
    *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + 1.0;
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x78) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0;
    }
    if (5.0 <= *(float *)(param_1 + 0x78)) {
      *(undefined4 *)(param_1 + 0x78) = 0x40a00000;
      *(undefined4 *)(param_1 + 0x70) = 0x40a00000;
    }
    else {
      fVar5 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 3));
      *(float *)(param_1 + 0x78) =
           (float)(fVar5 * (float10)0.5 + (float10)*(float *)(param_1 + 0x78));
      fVar5 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 3));
      *(float *)(param_1 + 0x70) =
           (float)(fVar5 * (float10)0.5 + (float10)*(float *)(param_1 + 0x70));
    }
    if (*(int *)(param_1 + 0x154) % 0x1e == 0) {
      FUN_0042c840(1);
      FUN_0042c800(0);
    }
    if (*(int *)(param_1 + 0x154) % 3 == 0) {
      uVar4 = FUN_0065d150();
      *(uint *)(param_1 + 0xe8) = uVar4 % 0x168;
      uVar4 = FUN_0065d150();
      *(uint *)(param_1 + 0xec) = uVar4 % 500;
      iVar1 = *(int *)(param_1 + 0xec);
      fVar5 = (float10)FUN_0065d010((float)*(int *)(param_1 + 0xe8));
      fVar7 = (float)(fVar5 * (float10)iVar1);
      uVar6 = 0;
      iVar1 = *(int *)(param_1 + 0xec);
      fVar5 = (float10)FUN_0065d050((float)*(int *)(param_1 + 0xe8),0,fVar7);
      FUN_005f6fd0(6,(float)(fVar5 * (float10)iVar1),uVar6,fVar7);
    }
    if (*(int *)(param_1 + 0x154) < 0x169) {
      fVar5 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 6));
      *(float *)(param_1 + 0x74) = (float)(fVar5 * (float10)0.25 + (float10)0.75);
    }
    else {
      FUN_0042c840(0);
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      if (*(float *)(param_1 + 0x74) < 0.0 != (*(float *)(param_1 + 0x74) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x78) = 0x40a00000;
      *(undefined4 *)(param_1 + 0x74) = 0x40a00000;
      *(undefined4 *)(param_1 + 0x70) = 0x40a00000;
      uVar4 = FUN_0065d150();
      *(float *)(param_1 + 0x54) = (float)(uVar4 % 0x14) * 0.1 + 2.0;
      uVar4 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar4 % 0x168);
      *(undefined4 *)(param_1 + 0x6c) = 0x42b40000;
    }
    if (0x1d < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x46:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42960000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (((0xb4 < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
       (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
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
      FUN_0042c840(1);
    }
    if (0x33 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
  }
  *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
  FUN_005f75a0();
  return;
}

