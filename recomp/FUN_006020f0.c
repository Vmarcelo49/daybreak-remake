// ============================================
// Address:  0x006020f0
// Original: FUN_006020f0
// Status:   unreviewed
// ============================================


void __fastcall FUN_006020f0(int param_1)

{
  int iVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  undefined4 uVar5;
  float10 fVar6;
  
  uVar4 = FUN_0042c7b0();
  if (((uVar4 & 0x100) != 0) &&
     (((iVar1 = *(int *)(param_1 + 0x150), iVar1 == 0 || (iVar1 == 0x1e)) || (iVar1 == 0x3c)))) {
    FUN_005f72c0(0x43340000,-*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
    FUN_0042c800(0);
    FUN_0042c840(1);
  }
  switch(*(undefined4 *)(param_1 + 0x150)) {
  case 0:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x422a0000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(undefined4 *)(param_1 + 0xf4) = 0;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
      FUN_0042db10(0,0x40a00000);
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
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
    if (0x78 < *(int *)(param_1 + 0xf0)) {
      *(undefined4 *)(param_1 + 0xf0) = 0x78;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3e19999a);
      fVar6 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar6) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.1;
      }
      fVar6 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar6 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.1;
      }
    }
    if ((0x77 < *(int *)(param_1 + 0xf0)) ||
       (((sVar3 = FUN_0042c7b0(), sVar3 != 0 && (sVar3 = FUN_0042c7b0(), sVar3 != 1)) ||
        (cVar2 = FUN_005f6a90(), cVar2 == '\x01')))) {
      *(undefined4 *)(param_1 + 0xf4) = 1;
    }
    if (*(int *)(param_1 + 0xf4) == 1) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.15;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.2;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.2;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 10:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42200000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
      *(undefined4 *)(param_1 + 0x40) = 0x41200000;
    }
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.75;
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 0.5;
    if (*(float *)(param_1 + 0x54) < 15.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41700000;
    }
    cVar2 = FUN_005f6a90();
    if ((cVar2 == '\x01') || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) {
      FUN_005f6db0(2,0,0,0);
      FUN_005f6db0(7,0,0,0);
      FUN_0042c8b0(0x73);
      FUN_005f5e00();
      return;
    }
    if (0x708 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x14:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
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
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.4;
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.4;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.4;
    if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_005f7450(0,0x42700000,0xf,1,0);
      *(undefined4 *)(param_1 + 0x54) = 0x427a0000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(undefined4 *)(param_1 + 0xf4) = 0;
      *(undefined4 *)(param_1 + 0x74) = 0x40800000;
      *(undefined4 *)(param_1 + 0x78) = 0x40800000;
      FUN_0042db10(0,0x40a00000);
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
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
    if (0x78 < *(int *)(param_1 + 0xf0)) {
      *(undefined4 *)(param_1 + 0xf0) = 0x78;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3e4ccccd);
      fVar6 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar6) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.1;
      }
      fVar6 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar6 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.1;
      }
    }
    if ((0x77 < *(int *)(param_1 + 0xf0)) ||
       (((sVar3 = FUN_0042c7b0(), sVar3 != 0 && (sVar3 = FUN_0042c7b0(), sVar3 != 1)) ||
        (cVar2 = FUN_005f6a90(), cVar2 == '\x01')))) {
      *(undefined4 *)(param_1 + 0xf4) = 1;
    }
    if (*(int *)(param_1 + 0xf4) == 1) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.15;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.2;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.2;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42200000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
      *(undefined4 *)(param_1 + 0x40) = 0x41200000;
    }
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.5;
    cVar2 = FUN_005f6a90();
    if ((cVar2 == '\x01') || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) {
      FUN_005f6db0(5,0,0,0);
      FUN_005f6db0(7,0,0,0);
      FUN_0042c8b0(0x73);
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
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x41000000;
      *(undefined4 *)(param_1 + 0x74) = 0x41000000;
      *(undefined4 *)(param_1 + 0x78) = 0x41000000;
    }
    if (*(int *)(param_1 + 0x154) == 4) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      FUN_005f5e00();
      return;
    }
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.8;
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.8;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.8;
    if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42340000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
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
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar6) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.2;
      }
      fVar6 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar6 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.2;
      }
    }
    if (((0xf0 < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
       (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      uVar4 = FUN_0042c7b0();
      if ((uVar4 & 1) != 0) {
        FUN_005f6db0(10,0,0,0);
      }
      FUN_005f5e00();
      return;
    }
    break;
  case 0x46:
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
  case 0x50:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x40e00000;
      *(undefined4 *)(param_1 + 0x74) = 0x41400000;
      *(undefined4 *)(param_1 + 0x78) = 0x40e00000;
    }
    if (*(int *)(param_1 + 0x154) == 0x1e) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      FUN_005f5e00();
      return;
    }
    break;
  case 100:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0x74) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0x78) = 0x3fc00000;
      *(undefined4 *)(param_1 + 0x54) = 0;
      uVar5 = FUN_0064e6c0("Bip00");
      FUN_00602ec0(uVar5);
    }
    if (*(int *)(param_1 + 0x154) == 300) {
      FUN_005f5e00();
      return;
    }
  }
  *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
  FUN_005f75a0();
  return;
}

