// ============================================
// Address:  0x0061c410
// Original: FUN_0061c410
// Status:   unreviewed
// ============================================


void __fastcall FUN_0061c410(int param_1)

{
  int iVar1;
  int iVar2;
  char cVar3;
  short sVar4;
  uint uVar5;
  float10 fVar6;
  
  uVar5 = FUN_0042c7b0();
  if ((uVar5 & 0x100) != 0) {
    if (*(int *)(param_1 + 0x150) == 0) {
      FUN_005f72c0(0x43340000,-*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
      FUN_0042c800(0);
      FUN_0042c840(3);
    }
    else if (*(int *)(param_1 + 0x150) == 10) {
      FUN_005f72c0(0x43340000,-*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
      FUN_0042c800(0);
      FUN_0042c840(3);
    }
  }
  switch(*(undefined4 *)(param_1 + 0x150)) {
  case 0:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x420e0000;
      *(undefined4 *)(param_1 + 0x30) = 0x43820000;
      *(undefined4 *)(param_1 + 0x34) = 0x41200000;
      FUN_0042c840(3);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
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
    }
    sVar4 = FUN_0042c7b0();
    if ((sVar4 != 0) &&
       (*(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1, 4 < *(int *)(param_1 + 0xf0))) {
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_0042c800(0);
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    if (0x4b < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x4b;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3e4ccccd);
      fVar6 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar6) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.2;
      }
      fVar6 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar6 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.2;
      }
    }
    if ((0xf0 < *(int *)(param_1 + 0x154)) ||
       ((sVar4 = FUN_0042c7b0(), sVar4 != 0 && (sVar4 = FUN_0042c7b0(), sVar4 != 1)))) {
      FUN_005f5e00();
      return;
    }
    cVar3 = FUN_005f6a90();
    if (cVar3 == '\x01') {
      FUN_005f6db0(8,0,0,0);
      FUN_005f5e00();
      return;
    }
    break;
  case 10:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x420e0000;
      *(undefined4 *)(param_1 + 0x30) = 0x43820000;
      *(undefined4 *)(param_1 + 0x34) = 0x41200000;
      FUN_0042c840(3);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
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
    }
    uVar5 = *(uint *)(param_1 + 0x154) & 0x80000001;
    if ((int)uVar5 < 0) {
      uVar5 = (uVar5 - 1 | 0xfffffffe) + 1;
    }
    if (uVar5 == 0) {
      FUN_005f6fd0(10,0,0,0);
    }
    sVar4 = FUN_0042c7b0();
    if ((sVar4 != 0) &&
       (*(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1, 4 < *(int *)(param_1 + 0xf0))) {
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_0042c800(0);
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    if (0x4b < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x4b;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3e4ccccd);
      fVar6 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar6) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.2;
      }
      fVar6 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar6 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.2;
      }
    }
    if ((0xf0 < *(int *)(param_1 + 0x154)) ||
       ((sVar4 = FUN_0042c7b0(), sVar4 != 0 && (sVar4 = FUN_0042c7b0(), sVar4 != 1)))) {
      FUN_005f5e00();
      return;
    }
    cVar3 = FUN_005f6a90();
    if (cVar3 == '\x01') {
      FUN_005f6db0(9,0,0,0);
      FUN_005f5e00();
      return;
    }
    break;
  case 0x14:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    sVar4 = FUN_0042c7b0();
    if ((sVar4 != 0) &&
       (*(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1, 0x1e < *(int *)(param_1 + 0xf0))) {
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_0042c800(0);
      FUN_0042c840(1);
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 5;
    if (0x96 < *(int *)(param_1 + 0xe8)) {
      *(undefined4 *)(param_1 + 0xe8) = 0x96;
    }
    if ((0xb4 < *(int *)(param_1 + 0x154)) ||
       (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x7a4) < 1)) {
      FUN_0042c840(0);
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
      if ((*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) ||
         (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x7a4) < 1)) {
        FUN_005f5e00();
        return;
      }
    }
    *(float *)(param_1 + 0x18) =
         *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 70.0;
    iVar2 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
    iVar1 = *(int *)(param_1 + 0xe8);
    fVar6 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 9));
    *(float *)(param_1 + 0x14) = (float)(fVar6 * (float10)iVar1 + (float10)*(float *)(iVar2 + 0x14))
    ;
    iVar2 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
    iVar1 = *(int *)(param_1 + 0xe8);
    fVar6 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 9));
    *(float *)(param_1 + 0x1c) = (float)(fVar6 * (float10)iVar1 + (float10)*(float *)(iVar2 + 0x1c))
    ;
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    sVar4 = FUN_0042c7b0();
    if ((sVar4 != 0) &&
       (*(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1, 0x1e < *(int *)(param_1 + 0xf0))) {
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_0042c800(0);
      FUN_0042c840(1);
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 5;
    if (0x96 < *(int *)(param_1 + 0xe8)) {
      *(undefined4 *)(param_1 + 0xe8) = 0x96;
    }
    if ((0xb4 < *(int *)(param_1 + 0x154)) ||
       (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x7a4) < 1)) {
      FUN_0042c840(0);
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
      if ((*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) ||
         (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x7a4) < 1)) {
        FUN_005f5e00();
        return;
      }
    }
    *(float *)(param_1 + 0x18) =
         *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 70.0;
    iVar2 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
    iVar1 = *(int *)(param_1 + 0xe8);
    fVar6 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 9 + 0xb4));
    *(float *)(param_1 + 0x14) = (float)(fVar6 * (float10)iVar1 + (float10)*(float *)(iVar2 + 0x14))
    ;
    iVar2 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
    iVar1 = *(int *)(param_1 + 0xe8);
    fVar6 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 9 + 0xb4));
    *(float *)(param_1 + 0x1c) = (float)(fVar6 * (float10)iVar1 + (float10)*(float *)(iVar2 + 0x1c))
    ;
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    sVar4 = FUN_0042c7b0();
    if ((sVar4 != 0) &&
       (*(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1, 0x1e < *(int *)(param_1 + 0xf0))) {
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_0042c800(0);
      FUN_0042c840(1);
    }
    uVar5 = *(uint *)(param_1 + 0x154) & 0x80000003;
    if ((int)uVar5 < 0) {
      uVar5 = (uVar5 - 1 | 0xfffffffc) + 1;
    }
    if (uVar5 == 1) {
      FUN_005f6fd0(0xb,0,0,0);
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 5;
    if (0x96 < *(int *)(param_1 + 0xe8)) {
      *(undefined4 *)(param_1 + 0xe8) = 0x96;
    }
    if (300 < *(int *)(param_1 + 0x154)) {
      FUN_0042c800(0);
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
      if ((*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) ||
         (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x7a4) < 1)) {
        FUN_005f5e00();
        return;
      }
    }
    *(float *)(param_1 + 0x18) =
         *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 70.0;
    iVar2 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
    iVar1 = *(int *)(param_1 + 0xe8);
    fVar6 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 9));
    *(float *)(param_1 + 0x14) = (float)(fVar6 * (float10)iVar1 + (float10)*(float *)(iVar2 + 0x14))
    ;
    iVar2 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
    iVar1 = *(int *)(param_1 + 0xe8);
    fVar6 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 9));
    *(float *)(param_1 + 0x1c) = (float)(fVar6 * (float10)iVar1 + (float10)*(float *)(iVar2 + 0x1c))
    ;
    break;
  case 0x32:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    sVar4 = FUN_0042c7b0();
    if ((sVar4 != 0) &&
       (*(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1, 0x1e < *(int *)(param_1 + 0xf0))) {
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_0042c800(0);
      FUN_0042c840(1);
    }
    uVar5 = *(uint *)(param_1 + 0x154) & 0x80000003;
    if ((int)uVar5 < 0) {
      uVar5 = (uVar5 - 1 | 0xfffffffc) + 1;
    }
    if (uVar5 == 1) {
      FUN_005f6fd0(0xb,0,0,0);
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 5;
    if (0x96 < *(int *)(param_1 + 0xe8)) {
      *(undefined4 *)(param_1 + 0xe8) = 0x96;
    }
    if (300 < *(int *)(param_1 + 0x154)) {
      FUN_0042c800(0);
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
      if ((*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) ||
         (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x7a4) < 1)) {
        FUN_005f5e00();
        return;
      }
    }
    *(float *)(param_1 + 0x18) =
         *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x18) + 70.0;
    iVar2 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
    iVar1 = *(int *)(param_1 + 0xe8);
    fVar6 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) * 9 + 0xb4));
    *(float *)(param_1 + 0x14) = (float)(fVar6 * (float10)iVar1 + (float10)*(float *)(iVar2 + 0x14))
    ;
    iVar2 = *(int *)(*(int *)(param_1 + 0x11c) + 0x2c);
    iVar1 = *(int *)(param_1 + 0xe8);
    fVar6 = (float10)FUN_0065d010((float)(*(int *)(param_1 + 0x154) * 9 + 0xb4));
    *(float *)(param_1 + 0x1c) = (float)(fVar6 * (float10)iVar1 + (float10)*(float *)(iVar2 + 0x1c))
    ;
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42200000;
      uVar5 = FUN_0065d150();
      *(float *)(param_1 + 0x34) = (float)(uVar5 % 0x14) - 10.0;
    }
    sVar4 = FUN_0042c7b0();
    if ((sVar4 != 0) &&
       (*(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1, 4 < *(int *)(param_1 + 0xf0))) {
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_0042c800(0);
    }
    uVar5 = *(uint *)(param_1 + 0x154) & 0x80000003;
    if ((int)uVar5 < 0) {
      uVar5 = (uVar5 - 1 | 0xfffffffc) + 1;
    }
    if (uVar5 == 1) {
      FUN_005f6fd0(0xb,0,0,0);
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 5.0;
    if (*(float *)(param_1 + 0x54) < 1.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x3f800000;
      FUN_0042c840(1);
    }
    if (0xf0 < *(int *)(param_1 + 0x154)) {
      FUN_0042c800(0);
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
      if ((*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) ||
         (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x7a4) < 1)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x46:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x40a00000;
      FUN_0042c840(10);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
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
    }
    if (*(float *)(param_1 + 0x78) < 2.0) {
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + 0.1;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + 0.1;
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) + 0.1;
    }
    sVar4 = FUN_0042c7b0();
    if ((sVar4 != 0) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1, 5 < *(int *)(param_1 + 0xe8))) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
      FUN_0042c800(0);
    }
    if (0x5a < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x50:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x3dcccccd;
      *(undefined4 *)(param_1 + 0x30) = 0x43820000;
      *(undefined4 *)(param_1 + 0x34) = 0x41200000;
      FUN_0042c840(3);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    sVar4 = FUN_0042c7b0();
    if ((sVar4 != 0) &&
       (*(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1, 4 < *(int *)(param_1 + 0xf0))) {
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_0042c800(0);
    }
    if ((0x5a < *(int *)(param_1 + 0x154)) ||
       ((sVar4 = FUN_0042c7b0(), sVar4 != 0 && (sVar4 = FUN_0042c7b0(), sVar4 != 1)))) {
      FUN_0042c840(0);
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x5a:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x3dcccccd;
      *(undefined4 *)(param_1 + 0x30) = 0x43820000;
      *(undefined4 *)(param_1 + 0x34) = 0x41200000;
      FUN_0042c840(5);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    uVar5 = *(uint *)(param_1 + 0x154) & 0x80000001;
    if ((int)uVar5 < 0) {
      uVar5 = (uVar5 - 1 | 0xfffffffe) + 1;
    }
    if (uVar5 == 0) {
      FUN_005f6fd0(10,0,0,0);
    }
    sVar4 = FUN_0042c7b0();
    if ((sVar4 != 0) &&
       (*(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1, 4 < *(int *)(param_1 + 0xf0))) {
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_0042c800(0);
    }
    if ((0xb4 < *(int *)(param_1 + 0x154)) ||
       ((sVar4 = FUN_0042c7b0(), sVar4 != 0 && (sVar4 = FUN_0042c7b0(), sVar4 != 1)))) {
      FUN_0042c840(0);
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 100:
    if (*(int *)(param_1 + 0x154) == 0) {
      uVar5 = FUN_0065d150();
      *(float *)(param_1 + 0x34) = (float)(uVar5 % 0x14) - 10.0;
      *(undefined4 *)(param_1 + 0x30) = 0x43820000;
    }
    if (0xd < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x6e:
    if (*(int *)(param_1 + 0x154) == 0) {
      uVar5 = FUN_0065d150();
      *(float *)(param_1 + 0x2c) = (float)(uVar5 % 0x168);
      uVar5 = FUN_0065d150();
      *(float *)(param_1 + 0x34) = (float)(uVar5 % 0x14) - 10.0;
      *(undefined4 *)(param_1 + 0x30) = 0;
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

