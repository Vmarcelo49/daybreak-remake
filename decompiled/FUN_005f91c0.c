// Function: FUN_005f91c0
// Address:  0x005f91c0
// Source:   batch_decompile (mass dump)
// Hash:     2ccc61f56e33ed4c


void __fastcall FUN_005f91c0(int param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  float10 fVar4;
  
  uVar3 = FUN_0042c7b0();
  if ((uVar3 & 0x100) != 0) {
    switch(*(undefined4 *)(param_1 + 0x150)) {
    case 0:
    case 10:
    case 0x28:
    case 0x3c:
    case 0x46:
    case 0x5a:
    case 0x82:
    case 0x8c:
      FUN_005f72c0(0x43340000,-*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
      FUN_0042c800(0);
      FUN_0042c840(1);
      break;
    case 0x6e:
    case 0x78:
      FUN_005f72c0(0x43340000,-*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
      FUN_0042c800(0);
      FUN_0042c840(5);
    }
  }
  switch(*(undefined4 *)(param_1 + 0x150)) {
  case 0:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42160000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
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
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.2;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.2;
      }
    }
    if (((0xf0 < *(int *)(param_1 + 0x154)) ||
        ((sVar2 = FUN_0042c7b0(), sVar2 != 0 && (sVar2 = FUN_0042c7b0(), sVar2 != 1)))) ||
       (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      cVar1 = FUN_005f6a90();
      if (cVar1 == '\x01') {
        FUN_005f6db0(5,0,0,0);
      }
      FUN_005f5e00();
      return;
    }
    break;
  case 10:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42160000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
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
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.2;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.2;
      }
    }
    if (((0xf0 < *(int *)(param_1 + 0x154)) ||
        ((sVar2 = FUN_0042c7b0(), sVar2 != 0 && (sVar2 = FUN_0042c7b0(), sVar2 != 1)))) ||
       (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      cVar1 = FUN_005f6a90();
      if (cVar1 == '\x01') {
        FUN_005f6db0(5,0,0,0);
      }
      FUN_005f5e00();
      return;
    }
    break;
  case 0x14:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41c80000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
      *(undefined4 *)(param_1 + 0x40) = 0x41200000;
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 0x32;
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.3;
    cVar1 = FUN_005f6a90();
    if (cVar1 == '\x01') {
      FUN_005f6db0(3,0,0,0);
      FUN_0042c8b0(0x47);
      FUN_005f5e00();
      return;
    }
    if (0x708 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_0042c840(1);
    }
    if (0x33 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0x30) = 0x42340000;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    if (30.0 < *(float *)(param_1 + 0x54)) {
      *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
    }
    if (100 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 100;
    }
    if (*(int *)(param_1 + 0xf0) < 2) {
      if (*(int *)(param_1 + 0xf0) == 0) {
        fVar4 = (float10)FUN_0042df90(*(undefined4 *)(param_1 + 100));
        if (fVar4 < (float10)3.0) {
          *(undefined4 *)(param_1 + 0xf0) = 1;
        }
        fVar4 = (float10)FUN_0042df90(*(undefined4 *)(param_1 + 100));
        if ((float10)90.0 < fVar4) {
          *(undefined4 *)(param_1 + 0xf0) = 2;
        }
        FUN_0042db10(0,0x40400000);
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 2.0;
        }
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 2.0;
        }
      }
      if (*(int *)(param_1 + 0xf0) == 1) {
        fVar4 = (float10)FUN_0042df90(*(undefined4 *)(param_1 + 100));
        if ((float10)90.0 < fVar4) {
          *(undefined4 *)(param_1 + 0xf0) = 2;
        }
        FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.0035);
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
          *(float *)(param_1 + 0x6c) =
               *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.005;
        }
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0) {
          *(float *)(param_1 + 0x6c) =
               (float)*(int *)(param_1 + 0xec) * 0.005 + *(float *)(param_1 + 0x6c);
        }
      }
    }
    if (((0x1e0 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
       (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      cVar1 = FUN_005f6a90();
      if (cVar1 == '\x01') {
        FUN_005f6db0(5,0,0,0);
      }
      FUN_005f5e00();
      return;
    }
    break;
  case 0x32:
    *(undefined4 *)(param_1 + 0x54) = 0;
    *(undefined4 *)(param_1 + 0x40) = 0;
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    if ((0 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -10, *(int *)(param_1 + 0xe8) < 0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
      FUN_005f5e00();
      return;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x34) = 0x41a00000;
      *(undefined4 *)(param_1 + 0x54) = 0x42340000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
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
    }
    uVar3 = *(uint *)(param_1 + 0x154) & 0x80000001;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
    }
    if (uVar3 == 0) {
      FUN_005f6fd0(0xf,0,0,0);
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    if (0x78 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x78;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.01 + 0.25);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.25;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.25;
      }
    }
    if ((0xf0 < *(int *)(param_1 + 0x154)) ||
       (((sVar2 = FUN_0042c7b0(), sVar2 != 0 && (sVar2 = FUN_0042c7b0(), sVar2 != 1)) ||
        (cVar1 = FUN_005f6a90(), cVar1 == '\x01')))) {
      cVar1 = FUN_005f6a90();
      if (cVar1 == '\x01') {
        FUN_005f6db0(5,0,0,0);
      }
      FUN_005f5e00();
      return;
    }
    break;
  case 0x46:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42340000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
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
    }
    uVar3 = *(uint *)(param_1 + 0x154) & 0x80000001;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
    }
    if (uVar3 == 0) {
      FUN_005f6fd0(0x10,0,0,0);
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    if (0x78 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x78;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.01 + 0.25);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.25;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.25;
      }
    }
    if ((0xf0 < *(int *)(param_1 + 0x154)) ||
       (((sVar2 = FUN_0042c7b0(), sVar2 != 0 && (sVar2 = FUN_0042c7b0(), sVar2 != 1)) ||
        (cVar1 = FUN_005f6a90(), cVar1 == '\x01')))) {
      cVar1 = FUN_005f6a90();
      if (cVar1 == '\x01') {
        FUN_005f6db0(5,0,0,0);
      }
      FUN_005f5e00();
      return;
    }
    break;
  case 0x50:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41c80000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
      *(undefined4 *)(param_1 + 0x40) = 0x41200000;
    }
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.3;
    FUN_0042db10(0,0x40000000);
    cVar1 = FUN_005f6a90();
    if (cVar1 == '\x01') {
      FUN_005f6db0(10,0,0,0);
      FUN_0042c8b0(0x47);
      FUN_005f5e00();
      return;
    }
    if (0x708 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x5a:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0x30) = 0xc2340000;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    if (30.0 < *(float *)(param_1 + 0x54)) {
      *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
    }
    if (100 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 100;
    }
    if (*(int *)(param_1 + 0xf0) < 2) {
      if (*(int *)(param_1 + 0xf0) == 0) {
        fVar4 = (float10)FUN_0042df90(*(undefined4 *)(param_1 + 100));
        if (fVar4 < (float10)3.0) {
          *(undefined4 *)(param_1 + 0xf0) = 1;
        }
        fVar4 = (float10)FUN_0042df90(*(undefined4 *)(param_1 + 100));
        if ((float10)90.0 < fVar4) {
          *(undefined4 *)(param_1 + 0xf0) = 2;
        }
        FUN_0042db10(0,0x40400000);
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 2.0;
        }
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 2.0;
        }
      }
      if (*(int *)(param_1 + 0xf0) == 1) {
        fVar4 = (float10)FUN_0042df90(*(undefined4 *)(param_1 + 100));
        if ((float10)90.0 < fVar4) {
          *(undefined4 *)(param_1 + 0xf0) = 2;
        }
        FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.0035);
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
          *(float *)(param_1 + 0x6c) =
               *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.005;
        }
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0) {
          *(float *)(param_1 + 0x6c) =
               (float)*(int *)(param_1 + 0xec) * 0.005 + *(float *)(param_1 + 0x6c);
        }
      }
    }
    if (((0x1e0 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
       (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      cVar1 = FUN_005f6a90();
      if (cVar1 == '\x01') {
        FUN_005f6db0(5,0,0,0);
      }
      FUN_005f5e00();
      return;
    }
    break;
  case 100:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x40400000;
      *(undefined4 *)(param_1 + 0x74) = 0x40400000;
      *(undefined4 *)(param_1 + 0x78) = 0x40400000;
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      FUN_0042c840(1);
    }
    if (0x33 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x6e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x30) = 0x42340000;
      *(undefined4 *)(param_1 + 0x54) = 0x42340000;
      FUN_0042c840(5);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0x32;
      *(undefined4 *)(param_1 + 0xf0) = 5;
      FUN_0042c800(0);
    }
    uVar3 = *(uint *)(param_1 + 0x154) & 0x80000001;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
    }
    if (uVar3 == 0) {
      FUN_005f6fd0(0x11,0,0,0);
    }
    sVar2 = FUN_0042c7b0();
    if (sVar2 != 0) {
      if (0 < *(int *)(param_1 + 0xf0)) {
        *(undefined4 *)(param_1 + 0x54) = 0;
        *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + -1;
        return;
      }
      *(undefined4 *)(param_1 + 0x54) = 0x42700000;
      FUN_0042c800(0);
      *(undefined4 *)(param_1 + 0xf0) = 10;
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + -1;
    if (*(int *)(param_1 + 0xec) < 0) {
      *(undefined4 *)(param_1 + 0xec) = 0;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.005 + 0.05);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) =
             *(float *)(param_1 + 0x6c) - ((float)*(int *)(param_1 + 0xec) * 0.005 + 0.05);
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) =
             (float)*(int *)(param_1 + 0xec) * 0.005 + 0.05 + *(float *)(param_1 + 0x6c);
      }
    }
    if ((0xf0 < *(int *)(param_1 + 0x154)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      cVar1 = FUN_005f6a90();
      if (cVar1 == '\x01') {
        FUN_005f6db0(5,0,0,0);
      }
      FUN_005f5e00();
      return;
    }
    break;
  case 0x78:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x30) = 0xc2340000;
      *(undefined4 *)(param_1 + 0x54) = 0x42340000;
      FUN_0042c840(5);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0x32;
      *(undefined4 *)(param_1 + 0xf0) = 5;
      FUN_0042c800(0);
    }
    uVar3 = *(uint *)(param_1 + 0x154) & 0x80000001;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
    }
    if (uVar3 == 0) {
      FUN_005f6fd0(0x11,0,0,0);
    }
    sVar2 = FUN_0042c7b0();
    if (sVar2 != 0) {
      if (0 < *(int *)(param_1 + 0xf0)) {
        *(undefined4 *)(param_1 + 0x54) = 0;
        *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + -1;
        return;
      }
      *(undefined4 *)(param_1 + 0x54) = 0x42700000;
      FUN_0042c800(0);
      *(undefined4 *)(param_1 + 0xf0) = 10;
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + -1;
    if (*(int *)(param_1 + 0xec) < 0) {
      *(undefined4 *)(param_1 + 0xec) = 0;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.005 + 0.05);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) =
             *(float *)(param_1 + 0x6c) - ((float)*(int *)(param_1 + 0xec) * 0.005 + 0.05);
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) =
             (float)*(int *)(param_1 + 0xec) * 0.005 + 0.05 + *(float *)(param_1 + 0x6c);
      }
    }
    if ((0xf0 < *(int *)(param_1 + 0x154)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      cVar1 = FUN_005f6a90();
      if (cVar1 == '\x01') {
        FUN_005f6db0(5,0,0,0);
      }
      FUN_005f5e00();
      return;
    }
    break;
  case 0x82:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41c80000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0x30) = 0x42700000;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    if (30.0 < *(float *)(param_1 + 0x54)) {
      *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
    }
    if (100 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 100;
    }
    if (*(int *)(param_1 + 0xf0) < 2) {
      if (*(int *)(param_1 + 0xf0) == 0) {
        fVar4 = (float10)FUN_0042df90(*(undefined4 *)(param_1 + 100));
        if (fVar4 < (float10)3.0) {
          *(undefined4 *)(param_1 + 0xf0) = 1;
        }
        fVar4 = (float10)FUN_0042df90(*(undefined4 *)(param_1 + 100));
        if ((float10)90.0 < fVar4) {
          *(undefined4 *)(param_1 + 0xf0) = 2;
        }
        FUN_0042db10(0,0x40400000);
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 2.0;
        }
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 2.0;
        }
      }
      if (*(int *)(param_1 + 0xf0) == 1) {
        fVar4 = (float10)FUN_0042df90(*(undefined4 *)(param_1 + 100));
        if ((float10)90.0 < fVar4) {
          *(undefined4 *)(param_1 + 0xf0) = 2;
        }
        FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.004);
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
          *(float *)(param_1 + 0x6c) =
               *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.005;
        }
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0) {
          *(float *)(param_1 + 0x6c) =
               (float)*(int *)(param_1 + 0xec) * 0.005 + *(float *)(param_1 + 0x6c);
        }
      }
    }
    if (((0x1e0 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
       (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      cVar1 = FUN_005f6a90();
      if (cVar1 == '\x01') {
        FUN_005f6db0(5,0,0,0);
      }
      FUN_005f5e00();
      return;
    }
    break;
  case 0x8c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41c80000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0x30) = 0xc2700000;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 1;
    if (30.0 < *(float *)(param_1 + 0x54)) {
      *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
    }
    if (100 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 100;
    }
    if (*(int *)(param_1 + 0xf0) < 2) {
      if (*(int *)(param_1 + 0xf0) == 0) {
        fVar4 = (float10)FUN_0042df90(*(undefined4 *)(param_1 + 100));
        if (fVar4 < (float10)3.0) {
          *(undefined4 *)(param_1 + 0xf0) = 1;
        }
        fVar4 = (float10)FUN_0042df90(*(undefined4 *)(param_1 + 100));
        if ((float10)90.0 < fVar4) {
          *(undefined4 *)(param_1 + 0xf0) = 2;
        }
        FUN_0042db10(0,0x40200000);
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 2.0;
        }
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 2.0;
        }
      }
      if (*(int *)(param_1 + 0xf0) == 1) {
        fVar4 = (float10)FUN_0042df90(*(undefined4 *)(param_1 + 100));
        if ((float10)90.0 < fVar4) {
          *(undefined4 *)(param_1 + 0xf0) = 2;
        }
        FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.004);
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
          *(float *)(param_1 + 0x6c) =
               *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.005;
        }
        fVar4 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0) {
          *(float *)(param_1 + 0x6c) =
               (float)*(int *)(param_1 + 0xec) * 0.005 + *(float *)(param_1 + 0x6c);
        }
      }
    }
    if (((0x1e0 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
       (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      cVar1 = FUN_005f6a90();
      if (cVar1 == '\x01') {
        FUN_005f6db0(5,0,0,0);
      }
      FUN_005f5e00();
      return;
    }
    break;
  case 0x96:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x34) = 0x420c0000;
    }
    if (0xd < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0xa0:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x30) = 0x42b40000;
    }
    if (0xd < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0xaa:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x2c) = (float)(uVar3 % 0x168);
      *(undefined4 *)(param_1 + 0x34) = 0x420c0000;
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

