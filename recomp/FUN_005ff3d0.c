// ============================================
// Address:  0x005ff3d0
// Original: FUN_005ff3d0
// Status:   unreviewed
// ============================================


void __fastcall FUN_005ff3d0(int param_1)

{
  int iVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  float10 fVar5;
  
  uVar4 = FUN_0042c7b0();
  if (((uVar4 & 0x100) != 0) &&
     (((iVar1 = *(int *)(param_1 + 0x150), iVar1 == 0 || (iVar1 == 10)) || (iVar1 == 0x46)))) {
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
      *(undefined4 *)(param_1 + 0x54) = 0x422a0000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_005f7450(0,0x41200000,0x14,1,0);
    }
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
    if (100 < *(int *)(param_1 + 0xf0)) {
      *(undefined4 *)(param_1 + 0xf0) = 100;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xf0) * 0.001);
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
    if ((0xf0 < *(int *)(param_1 + 0x154)) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
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
      *(undefined4 *)(param_1 + 0x54) = 0x422a0000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_005f7450(0,0x41200000,0x3c,1,0);
    }
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
    if (100 < *(int *)(param_1 + 0xf0)) {
      *(undefined4 *)(param_1 + 0xf0) = 100;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xf0) * 0.001);
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
    if ((0xf0 < *(int *)(param_1 + 0x154)) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x14:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x428c0000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0x3c;
      *(undefined4 *)(param_1 + 0xf0) = 0x3c;
      *(undefined4 *)(param_1 + 0xf4) = 0;
      *(undefined4 *)(param_1 + 0xf8) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
    }
    if ((*(int *)(param_1 + 0xf8) == 0) &&
       (*(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0,
       *(float *)(param_1 + 0x54) < 20.0)) {
      *(undefined4 *)(param_1 + 0x54) = 0x41a00000;
      *(undefined4 *)(param_1 + 0xf8) = 1;
      FUN_005f7450(0,0x41a00000,0x1e,1,0);
    }
    if ((*(int *)(param_1 + 0xf8) == 1) &&
       (*(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + 0.75,
       50.0 < *(float *)(param_1 + 0x54))) {
      *(undefined4 *)(param_1 + 0x54) = 0x42480000;
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + -2;
    if (*(int *)(param_1 + 0xf0) < 0) {
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    if (0x78 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x78;
    }
    if (((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) &&
       (0xf < *(int *)(param_1 + 0x154))) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      if (*(int *)(param_1 + 0xf4) == 0) {
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
          *(float *)(param_1 + 0x6c) =
               *(float *)(param_1 + 0x6c) -
               ((float)*(int *)(param_1 + 0xf0) * 0.05 + (float)*(int *)(param_1 + 0xec) * 0.005);
        }
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-1.0) {
          *(float *)(param_1 + 0x6c) =
               (float)*(int *)(param_1 + 0xf0) * 0.05 + (float)*(int *)(param_1 + 0xec) * 0.005 +
               *(float *)(param_1 + 0x6c);
        }
        fVar5 = (float10)FUN_0042dac0(2);
        fVar5 = (float10)FUN_0042df90((float)((float10)*(float *)(param_1 + 0x6c) - fVar5));
        if (fVar5 < (float10)1.0) {
          *(undefined4 *)(param_1 + 0xf4) = 1;
        }
      }
      if (*(int *)(param_1 + 0xf4) == 1) {
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.3;
        }
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-1.0) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.3;
        }
      }
      FUN_0042db10(0,0x3e4ccccd);
    }
    if (((300 < *(int *)(param_1 + 0x154)) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) ||
       (sVar3 = FUN_0042c7b0(), sVar3 != 0)) {
      FUN_005f6db0(4,0,0,0);
      FUN_0042c8b0(0x4a);
      FUN_005f5e00();
      return;
    }
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x428c0000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0x3c;
      *(undefined4 *)(param_1 + 0xf0) = 0x3c;
      *(undefined4 *)(param_1 + 0xf4) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
      FUN_005f7450(2,0x42480000,0x5a,1,0);
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 2.5;
    if (*(float *)(param_1 + 0x54) < 30.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + -2;
    if (*(int *)(param_1 + 0xf0) < 0) {
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    if (0x78 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x78;
    }
    if (((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) &&
       (0xf < *(int *)(param_1 + 0x154))) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      if (*(int *)(param_1 + 0xf4) == 0) {
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
          *(float *)(param_1 + 0x6c) =
               *(float *)(param_1 + 0x6c) -
               ((float)*(int *)(param_1 + 0xf0) * 0.05 + (float)*(int *)(param_1 + 0xec) * 0.005);
        }
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-1.0) {
          *(float *)(param_1 + 0x6c) =
               (float)*(int *)(param_1 + 0xf0) * 0.05 + (float)*(int *)(param_1 + 0xec) * 0.005 +
               *(float *)(param_1 + 0x6c);
        }
        fVar5 = (float10)FUN_0042dac0(2);
        fVar5 = (float10)FUN_0042df90((float)((float10)*(float *)(param_1 + 0x6c) - fVar5));
        if (fVar5 < (float10)1.0) {
          *(undefined4 *)(param_1 + 0xf4) = 1;
        }
      }
      if (*(int *)(param_1 + 0xf4) == 1) {
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.4;
        }
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-1.0) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.4;
        }
      }
      FUN_0042db10(0,0x3eb33333);
    }
    if (((300 < *(int *)(param_1 + 0x154)) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) ||
       (sVar3 = FUN_0042c7b0(), sVar3 != 0)) {
      FUN_005f6db0(4,0,0,0);
      FUN_0042c8b0(0x4a);
      FUN_005f5e00();
      return;
    }
    break;
  case 0x28:
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
  case 0x32:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42700000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0xb4;
    }
    if (*(int *)(param_1 + 0x154) == 0x78) {
      *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(*(int *)(param_1 + 0x38) + 0x14);
      *(float *)(param_1 + 0x18) = *(float *)(*(int *)(param_1 + 0x38) + 0x18) + 1000.0;
      *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(*(int *)(param_1 + 0x38) + 0x1c);
    }
    if (*(int *)(param_1 + 0x154) == 0x79) {
      fVar5 = (float10)FUN_0042dac0(2);
      *(float *)(param_1 + 0x6c) = (float)fVar5;
      *(undefined4 *)(param_1 + 100) = 0;
      FUN_005f7450(0,0x41200000,0x14,1,0);
    }
    if ((0x78 < *(int *)(param_1 + 0x154)) && (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_005f6fd0(8,0,0,0);
      FUN_005f5e00();
      return;
    }
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0xb4;
    }
    if ((*(int *)(param_1 + 0x154) < 0x1e) &&
       (*(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0,
       *(float *)(param_1 + 0x54) < 0.0)) {
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
    if (((0x1d < *(int *)(param_1 + 0x154)) && (*(int *)(param_1 + 0x154) < 300)) &&
       (*(int *)(param_1 + 0xec) < 1)) {
      if (*(int *)(param_1 + 0x154) == 0x1e) {
        FUN_005f7450(0,0x41200000,0x1e,1,0);
      }
      *(undefined4 *)(param_1 + 0x54) = 0x42700000;
      if (*(int *)(param_1 + 0x154) % 0x28 == 0) {
        FUN_0042c8b0(99);
      }
      if (*(int *)(param_1 + 0x154) % 0x14 == 0) {
        *(undefined4 *)(param_1 + 0xf0) = 0xb4;
        FUN_0042db10(0,(float)*(int *)(param_1 + 0xf0) * 0.5);
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
          *(float *)(param_1 + 0x6c) =
               *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xf0) * 0.5;
        }
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-3.0) {
          *(float *)(param_1 + 0x6c) =
               (float)*(int *)(param_1 + 0xf0) * 0.5 + *(float *)(param_1 + 0x6c);
        }
        *(undefined4 *)(param_1 + 0xec) = 5;
      }
      fVar5 = (float10)FUN_0042d980();
      if ((((float10)*(float *)(param_1 + 0x18) -
           (float10)*(float *)(*(int *)(param_1 + 0x38) + 0x18)) *
           ((float10)*(float *)(param_1 + 0x18) -
           (float10)*(float *)(*(int *)(param_1 + 0x38) + 0x18)) + fVar5 < (float10)360000.0) &&
         (*(int *)(param_1 + 0xe8) == 0)) {
        *(undefined4 *)(param_1 + 0xe8) = 1;
      }
      if (((0x67 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
          (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 200)) ||
         ((0xcb < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) &&
          (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 300)))) {
        *(undefined4 *)(param_1 + 0x154) = 300;
        break;
      }
    }
    if (0 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      fVar5 = (float10)FUN_0042d980();
      if ((((float10)*(float *)(param_1 + 0x18) -
           (float10)*(float *)(*(int *)(param_1 + 0x38) + 0x18)) *
           ((float10)*(float *)(param_1 + 0x18) -
           (float10)*(float *)(*(int *)(param_1 + 0x38) + 0x18)) + fVar5 < (float10)360000.0) &&
         (*(int *)(param_1 + 0xe8) == 0)) {
        *(undefined4 *)(param_1 + 0xe8) = 1;
      }
      if (0 < *(int *)(param_1 + 0xe8)) {
        *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
        if (*(int *)(param_1 + 0xe8) < 0x1e) {
          FUN_0042db10(0,0x43340000);
          fVar5 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar5;
        }
        if (*(int *)(param_1 + 0xe8) == 0x28) {
          FUN_0042c8b0(0x50);
          FUN_005f6db0(7,0,0,0);
        }
        if (*(int *)(param_1 + 0xe8) == 0x3c) {
          *(undefined4 *)(param_1 + 0x154) = 300;
        }
      }
      if (*(int *)(param_1 + 0xe8) == 0) {
        *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + -1;
      }
    }
    if (300 < *(int *)(param_1 + 0x154)) {
      uVar4 = FUN_0065d150();
      *(float *)(param_1 + 0x6c) = 90.0 - (float)(uVar4 % 0x14);
      *(undefined4 *)(param_1 + 0x54) = 0x42a00000;
      if (0x280 < *(int *)(param_1 + 0x154)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x46:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42200000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
    }
    sVar3 = FUN_0042c7b0();
    if (((sVar3 != 0) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) &&
       ((uVar4 = FUN_0042c7b0(), (uVar4 & 2) != 0 || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')))) {
      FUN_005f5e00();
      return;
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
    if (100 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 100;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154))) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.0025);
    }
    if (*(int *)(param_1 + 0x154) == 0x1e) {
      *(undefined4 *)(param_1 + 0x154) = 0x14;
      return;
    }
    if (0xf0 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x50:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
    if (*(int *)(param_1 + 0xe8) < 0xf1) {
      return;
    }
    FUN_005f5e00();
    return;
  }
  *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
  FUN_005f75a0();
  return;
}

