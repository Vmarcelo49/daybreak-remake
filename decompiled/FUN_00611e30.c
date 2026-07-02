// Function: FUN_00611e30
// Address:  0x00611e30
// Source:   batch_decompile (mass dump)
// Hash:     02f032ed9fbdb6bb


void __fastcall FUN_00611e30(int param_1)

{
  int iVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  float10 fVar5;
  
  uVar4 = FUN_0042c7b0();
  if ((uVar4 & 0x100) != 0) {
    switch(*(undefined4 *)(param_1 + 0x150)) {
    case 0:
    case 10:
    case 0x14:
    case 0x1e:
    case 0x3c:
      FUN_005f72c0(0x43340000,-*(float *)(param_1 + 0x6c) + -*(float *)(param_1 + 0x6c));
      FUN_0042c800(0);
      FUN_0042c840(1);
    }
  }
  iVar1 = *(int *)(param_1 + 0x150);
  if (0xbe < iVar1) {
    switch(iVar1) {
    case 200:
      if (*(int *)(param_1 + 0x154) == 0) {
        *(undefined4 *)(param_1 + 0x54) = 0x42200000;
        FUN_0042c840(1);
        FUN_005f6fd0(4,0,0,0);
        *(undefined4 *)(param_1 + 0xe8) = 0;
        *(undefined4 *)(param_1 + 0xec) = 0;
      }
      *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 3;
      if (100 < *(int *)(param_1 + 0xec)) {
        *(undefined4 *)(param_1 + 0xec) = 100;
      }
      uVar4 = *(uint *)(param_1 + 0x154) & 0x80000001;
      if ((int)uVar4 < 0) {
        uVar4 = (uVar4 - 1 | 0xfffffffe) + 1;
      }
      if (uVar4 == 0) {
        FUN_005f6fd0(7,0,0,0);
      }
      if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
        *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
      }
      if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154))) {
        FUN_0042db10(0,0x3fa00000);
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 1.0;
        }
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-3.0) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 1.0;
        }
      }
      if (((0x1e0 < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
         (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
        FUN_005f6db0(3,0,0,0);
        FUN_0042c8b0(0x4a);
        FUN_005f5e00();
        return;
      }
      break;
    case 0xd2:
      if (*(int *)(param_1 + 0x154) == 0) {
        FUN_005f6fd0(1,0,0,0);
        *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
        FUN_0042c840(1);
        *(undefined4 *)(param_1 + 0xe8) = 0;
      }
      sVar3 = FUN_0042c7b0();
      if ((sVar3 != 0) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
        FUN_005f6db0(8,0,0,0);
        FUN_005f5e00();
        return;
      }
      if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
        *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
      }
      if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154))) {
        FUN_0042db10(0,0x3f800000);
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.5;
        }
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-3.0) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.5;
        }
      }
      if (0x5a < *(int *)(param_1 + 0x154)) {
        FUN_005f5e00();
        return;
      }
      break;
    case 0xdc:
      if (*(int *)(param_1 + 0x154) == 0) {
        FUN_005f6fd0(1,0,0,0);
        *(undefined4 *)(param_1 + 0x54) = 0x42480000;
        FUN_0042c840(1);
        *(undefined4 *)(param_1 + 0xe8) = 0;
      }
      if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
        *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
      }
      if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154))) {
        FUN_0042db10(0,0x3f800000);
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.5;
        }
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-3.0) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.5;
        }
      }
      if (((0xf0 < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
         (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
        FUN_005f6db0(8,0,0,0);
        FUN_005f5e00();
        return;
      }
      break;
    case 0xe6:
      if (*(int *)(param_1 + 0x154) == 0) {
        *(undefined4 *)(param_1 + 0x54) = 0x420c0000;
        FUN_0042c840(1);
        *(undefined4 *)(param_1 + 0xe8) = 0;
      }
      if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
        *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
      }
      if (*(int *)(param_1 + 0x154) < 0x3c) {
        FUN_0042db10(0,0x3e800000);
      }
      if (((0x1e0 < *(int *)(param_1 + 0x154)) ||
          ((sVar3 = FUN_0042c7b0(), sVar3 != 0 && (sVar3 = FUN_0042c7b0(), sVar3 != 1)))) ||
         (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
        FUN_005f5e00();
        return;
      }
      break;
    case 0xf0:
      if (*(int *)(param_1 + 0x154) == 0) {
        FUN_005f6fd0(1,0,0,0);
        *(undefined4 *)(param_1 + 0x54) = 0x42480000;
        FUN_0042c840(1);
        *(undefined4 *)(param_1 + 0xe8) = 0;
      }
      if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
        *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
      }
      if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154))) {
        FUN_0042db10(0,0x3f800000);
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.5;
        }
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-3.0) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.5;
        }
      }
      if (((0xf0 < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
         (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
        FUN_005f5e00();
        return;
      }
      break;
    case 0xfa:
      if (*(int *)(param_1 + 0x154) == 0) {
        *(undefined4 *)(param_1 + 0x54) = 0x420c0000;
        FUN_0042c840(1);
        *(undefined4 *)(param_1 + 0xe8) = 0;
        *(undefined4 *)(param_1 + 0xec) = 0;
        *(undefined4 *)(param_1 + 0xf0) = 0x19;
      }
      *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 3;
      *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + -1;
      uVar4 = *(uint *)(param_1 + 0x154) & 0x80000000;
      if ((int)uVar4 < 0) {
        uVar4 = 0;
      }
      if (uVar4 == 0) {
        FUN_005f6fd0(2,0,0,0);
      }
      if (*(int *)(param_1 + 0xf0) < 0) {
        *(undefined4 *)(param_1 + 0xf0) = 0;
      }
      if (100 < *(int *)(param_1 + 0xec)) {
        *(undefined4 *)(param_1 + 0xec) = 100;
      }
      if (((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) &&
         (*(int *)(param_1 + 0xf0) == 0)) {
        *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
      }
      if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154))) {
        FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.02 + (float)*(int *)(param_1 + 0xf0));
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
          *(float *)(param_1 + 0x6c) =
               *(float *)(param_1 + 0x6c) -
               ((float)*(int *)(param_1 + 0xec) * 0.02 + (float)*(int *)(param_1 + 0xf0));
        }
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-3.0) {
          *(float *)(param_1 + 0x6c) =
               (float)*(int *)(param_1 + 0xec) * 0.02 + (float)*(int *)(param_1 + 0xf0) +
               *(float *)(param_1 + 0x6c);
        }
      }
      if (((0x1e0 < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
         (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
        FUN_0042c8b0(0x4a);
        FUN_005f5e00();
        return;
      }
      break;
    case 0x104:
      if (0x3c < *(int *)(param_1 + 0x154)) {
        FUN_005f5e00();
        return;
      }
      break;
    case 0x10e:
      if (*(int *)(param_1 + 0x154) == 0) {
        *(undefined4 *)(param_1 + 0x54) = 0x42200000;
        FUN_0042c840(1);
        *(undefined4 *)(param_1 + 0xe8) = 0;
        *(undefined4 *)(param_1 + 0xec) = 0;
        *(undefined4 *)(param_1 + 0xf0) = 0x19;
      }
      *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 3;
      *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + -1;
      uVar4 = *(uint *)(param_1 + 0x154) & 0x80000001;
      if ((int)uVar4 < 0) {
        uVar4 = (uVar4 - 1 | 0xfffffffe) + 1;
      }
      if (uVar4 == 0) {
        FUN_005f6fd0(4,0,0,0);
      }
      if (*(int *)(param_1 + 0xf0) < 0) {
        *(undefined4 *)(param_1 + 0xf0) = 0;
      }
      if (100 < *(int *)(param_1 + 0xec)) {
        *(undefined4 *)(param_1 + 0xec) = 100;
      }
      if (((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) &&
         (*(int *)(param_1 + 0xf0) == 0)) {
        *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
      }
      if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154))) {
        FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.02 + (float)*(int *)(param_1 + 0xf0));
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
          *(float *)(param_1 + 0x6c) =
               *(float *)(param_1 + 0x6c) -
               ((float)*(int *)(param_1 + 0xec) * 0.02 + (float)*(int *)(param_1 + 0xf0));
        }
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-3.0) {
          *(float *)(param_1 + 0x6c) =
               (float)*(int *)(param_1 + 0xec) * 0.02 + (float)*(int *)(param_1 + 0xf0) +
               *(float *)(param_1 + 0x6c);
        }
      }
      if (((0x1e0 < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
         (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
        FUN_0042c8b0(0x4a);
        FUN_005f5e00();
        return;
      }
      break;
    case 0x118:
      if (0x1e < *(int *)(param_1 + 0x154)) {
        FUN_005f5e00();
        return;
      }
      break;
    case 0x122:
      if (*(int *)(param_1 + 0x154) == 0) {
        *(undefined4 *)(param_1 + 0x54) = 0;
        FUN_0042c840(1);
        *(undefined4 *)(param_1 + 0xe8) = 0;
      }
      sVar3 = FUN_0042c7b0();
      if ((sVar3 != 0) && (*(int *)(param_1 + 0x154) < 6)) {
        *(undefined4 *)(param_1 + 0xe8) = 0;
        FUN_0042c840(0);
        *(undefined4 *)(param_1 + 0x154) = 6;
        return;
      }
      if (*(int *)(param_1 + 0x154) == 5) {
        *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
        *(undefined4 *)(param_1 + 0x154) = 1;
        if (*(int *)(param_1 + 0xe8) < 0x97) {
          return;
        }
        FUN_005f5e00();
        return;
      }
      if (*(int *)(param_1 + 0x154) == 0xf) {
        *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
        *(undefined4 *)(param_1 + 0x154) = 0xb;
        if (*(int *)(param_1 + 0xe8) < 0x3d) {
          return;
        }
        FUN_005f5e00();
        return;
      }
      break;
    case 300:
      if (*(int *)(param_1 + 0x154) == 0) {
        *(undefined4 *)(param_1 + 0x54) = 0;
        FUN_0042c840(1);
        *(undefined4 *)(param_1 + 0xe8) = 0;
        FUN_005f6880(0);
        *(undefined4 *)(param_1 + 0x40) = 0x41700000;
      }
      *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.3;
      cVar2 = FUN_005f6a90();
      if (((cVar2 == '\x01') || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) &&
         (*(int *)(param_1 + 0xe8) == 0)) {
        *(undefined4 *)(param_1 + 0xe8) = 1;
        FUN_0042c840(0);
        *(undefined4 *)(param_1 + 0x40) = 0x40a00000;
        FUN_0042c8b0(0x47);
        return;
      }
      if ((0xb4 < *(int *)(param_1 + 0x154)) && (*(int *)(param_1 + 0xe8) == 1)) {
        FUN_005f5e00();
        return;
      }
      break;
    case 0x136:
      if (*(int *)(param_1 + 0x154) == 0) {
        *(undefined4 *)(param_1 + 0x54) = 0;
        FUN_0042c840(1);
        *(undefined4 *)(param_1 + 0xe8) = 0;
        FUN_005f6880(0);
        *(undefined4 *)(param_1 + 0x40) = 0x40a00000;
      }
      *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.8;
      cVar2 = FUN_005f6a90();
      if (((cVar2 == '\x01') || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) &&
         (*(int *)(param_1 + 0xe8) == 0)) {
        *(undefined4 *)(param_1 + 0xe8) = 1;
        FUN_0042c840(0);
        *(undefined4 *)(param_1 + 0x40) = 0x40a00000;
        FUN_0042c8b0(0x47);
        return;
      }
      if ((0xb4 < *(int *)(param_1 + 0x154)) && (*(int *)(param_1 + 0xe8) == 1)) {
        FUN_005f5e00();
        return;
      }
      break;
    case 0x140:
      if (*(int *)(param_1 + 0x154) == 0) {
        *(undefined4 *)(param_1 + 0x54) = 0x42200000;
        FUN_0042c840(1);
        *(undefined4 *)(param_1 + 0xe8) = 0;
      }
      if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
        *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
      }
      if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
        *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
      }
      if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154))) {
        FUN_0042db10(0,0x3f000000);
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.5;
        }
        fVar5 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-3.0) {
          *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.5;
        }
      }
      if ((0x1e0 < *(int *)(param_1 + 0x154)) ||
         (((sVar3 = FUN_0042c7b0(), sVar3 != 0 && (sVar3 = FUN_0042c7b0(), sVar3 != 1)) ||
          (cVar2 = FUN_005f6a90(), cVar2 == '\x01')))) {
        FUN_005f5e00();
        return;
      }
      break;
    case 0x14a:
      if (*(int *)(param_1 + 0x154) == 0) {
        *(undefined4 *)(param_1 + 0x54) = 0x42200000;
        FUN_0042c840(1);
      }
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 0.5;
      if (*(float *)(param_1 + 0x54) < 5.0) {
        *(undefined4 *)(param_1 + 0x54) = 0x40a00000;
      }
      sVar3 = FUN_0042c7b0();
      if ((sVar3 != 0) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
        FUN_005f5e00();
        return;
      }
      if (0x1e < *(int *)(param_1 + 0x154)) {
        FUN_005f5e00();
        return;
      }
      break;
    case 0x154:
      if (*(int *)(param_1 + 0x154) == 0) {
        *(undefined4 *)(param_1 + 0x54) = 0;
        *(undefined4 *)(param_1 + 0x40) = 0;
      }
      if (0x1d < *(int *)(param_1 + 0x154)) {
        FUN_005f5e00();
        return;
      }
      break;
    case 0x15e:
      if (*(int *)(param_1 + 0x154) == 0) {
        *(undefined4 *)(param_1 + 0x54) = 0x420c0000;
        FUN_0042c840(1);
        *(undefined4 *)(param_1 + 0xe8) = 0;
      }
      if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
        *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
      }
      if (*(int *)(param_1 + 0xe8) == 0) {
        FUN_0042db10(0,0x3e800000);
      }
      if (((0x1e0 < *(int *)(param_1 + 0x154)) ||
          ((sVar3 = FUN_0042c7b0(), sVar3 != 0 && (sVar3 = FUN_0042c7b0(), sVar3 != 1)))) ||
         (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
        FUN_005f5e00();
        return;
      }
      break;
    case 0x168:
      if (*(int *)(param_1 + 0x154) == 0) {
        *(undefined4 *)(param_1 + 0x54) = 0;
        FUN_005f6880(0);
        *(undefined4 *)(param_1 + 0x40) = 0x41700000;
      }
      *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 1.75;
      if (0x12 < *(int *)(param_1 + 0x154)) {
        FUN_005f5e00();
        return;
      }
      break;
    case 0x172:
      if (*(int *)(param_1 + 0x154) == 0) {
        *(undefined4 *)(param_1 + 0x54) = 0x42700000;
        FUN_0042c840(1);
        *(undefined4 *)(param_1 + 0xe8) = 0;
      }
      if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
        *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
      }
      if (*(int *)(param_1 + 0x154) < 0x3c) {
        FUN_0042db10(0,0x3eb33333);
      }
      if ((0x1e0 < *(int *)(param_1 + 0x154)) ||
         (((sVar3 = FUN_0042c7b0(), sVar3 != 0 && (sVar3 = FUN_0042c7b0(), sVar3 != 1)) ||
          (cVar2 = FUN_005f6a90(), cVar2 == '\x01')))) {
        FUN_005f5e00();
        return;
      }
    }
    goto switchD_00611ed6_caseD_1;
  }
  if (iVar1 == 0xbe) {
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
    }
    if (0x3c < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    goto switchD_00611ed6_caseD_1;
  }
  switch(iVar1) {
  case 0:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x420c0000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0xff;
      *(undefined4 *)(param_1 + 0xf0) = 1;
    }
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 5;
    if (0x5a < *(int *)(param_1 + 0xf0)) {
      *(undefined4 *)(param_1 + 0xf0) = 0x5a;
    }
    if (*(int *)(param_1 + 0xf0) < 0) {
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    fVar5 = (float10)FUN_0065d010((float)*(int *)(param_1 + 0xf0));
    *(float *)(param_1 + 0x70) = (float)(fVar5 * (float10)0.5);
    fVar5 = (float10)FUN_0065d010((float)*(int *)(param_1 + 0xf0));
    *(float *)(param_1 + 0x74) = (float)(fVar5 * (float10)0.5);
    fVar5 = (float10)FUN_0065d010((float)*(int *)(param_1 + 0xf0));
    *(float *)(param_1 + 0x78) = (float)(fVar5 * (float10)0.5);
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
    if (0x32 < *(int *)(param_1 + 0xe8)) {
      *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + -0x14;
      FUN_0042c840(0);
      if (*(int *)(param_1 + 0xec) < 0) {
        *(undefined4 *)(param_1 + 0xec) = 0;
        FUN_005f5e00();
        return;
      }
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xec),0xff,0xff,0xff);
    cVar2 = FUN_005f6a90();
    if ((cVar2 == '\x01') && (*(int *)(param_1 + 0xe8) < 0x32)) {
      *(undefined4 *)(param_1 + 0xe8) = 0x32;
    }
    iVar1 = *(int *)(param_1 + 0x154);
    goto joined_r0x00612732;
  case 10:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42340000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0xff;
      *(undefined4 *)(param_1 + 0xf0) = 1;
    }
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 5;
    if (0x5a < *(int *)(param_1 + 0xf0)) {
      *(undefined4 *)(param_1 + 0xf0) = 0x5a;
    }
    if (*(int *)(param_1 + 0xf0) < 0) {
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    fVar5 = (float10)FUN_0065d010((float)*(int *)(param_1 + 0xf0));
    *(float *)(param_1 + 0x70) = (float)(fVar5 * (float10)0.85);
    fVar5 = (float10)FUN_0065d010((float)*(int *)(param_1 + 0xf0));
    *(float *)(param_1 + 0x74) = (float)(fVar5 * (float10)0.85);
    fVar5 = (float10)FUN_0065d010((float)*(int *)(param_1 + 0xf0));
    *(float *)(param_1 + 0x78) = (float)(fVar5 * (float10)0.85);
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
    if (0x5a < *(int *)(param_1 + 0xe8)) {
      *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + -0x14;
      FUN_0042c840(0);
      if (*(int *)(param_1 + 0xec) < 0) {
        *(undefined4 *)(param_1 + 0xec) = 0;
        FUN_005f5e00();
        return;
      }
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xec),0xff,0xff,0xff);
    cVar2 = FUN_005f6a90();
    if ((cVar2 == '\x01') && (*(int *)(param_1 + 0xe8) < 0x5a)) {
      *(undefined4 *)(param_1 + 0xe8) = 0x5a;
    }
    iVar1 = *(int *)(param_1 + 0x154);
    goto joined_r0x00612732;
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
      *(undefined4 *)(param_1 + 0x54) = 0x42480000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3e4ccccd);
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.2;
      }
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.2;
      }
    }
    if (*(int *)(param_1 + 0x154) == 0x28) {
      *(undefined4 *)(param_1 + 0xe8) = 1;
      FUN_005f6880(0);
    }
    if (0x28 < *(int *)(param_1 + 0x154)) {
      *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.15;
    }
    if ((0x1e0 < *(int *)(param_1 + 0x154)) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
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
      FUN_005f7450(0,0x42700000,0x19,1,0);
      *(undefined4 *)(param_1 + 0x54) = 0x42960000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3e99999a);
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.3;
      }
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.3;
      }
    }
    if (*(int *)(param_1 + 0x154) == 0x3c) {
      *(undefined4 *)(param_1 + 0xe8) = 1;
      FUN_005f6880(0);
    }
    if (0x3c < *(int *)(param_1 + 0x154)) {
      *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.15;
    }
    if ((0x1e0 < *(int *)(param_1 + 0x154)) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0xff;
      *(undefined4 *)(param_1 + 0x70) = 0x3f333333;
      *(undefined4 *)(param_1 + 0x74) = 0x3f333333;
      *(undefined4 *)(param_1 + 0x78) = 0x3f333333;
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + -0x14;
    if (*(int *)(param_1 + 0xec) < 0) {
      *(undefined4 *)(param_1 + 0xec) = 0;
      FUN_005f5e00();
      return;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xec),0xff,0xff,0xff);
    iVar1 = *(int *)(param_1 + 0x154);
joined_r0x00612732:
    if (iVar1 == 0x14) {
      return;
    }
    break;
  case 0x32:
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_005f6fd0(1,0,0,0);
      *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
      FUN_0042c840(1);
    }
    sVar3 = FUN_0042c7b0();
    if ((sVar3 != 0) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_005f6db0(8,0,0,0);
      FUN_005f5e00();
      return;
    }
    if (0x5a < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x3c:
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
      *(undefined4 *)(param_1 + 0x54) = 0x42820000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3e99999a);
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.3;
      }
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.3;
      }
    }
    if (*(int *)(param_1 + 0x154) == 0x3c) {
      *(undefined4 *)(param_1 + 0xe8) = 1;
      FUN_005f6880(0);
    }
    if (0x3c < *(int *)(param_1 + 0x154)) {
      *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.15;
    }
    if ((0x1e0 < *(int *)(param_1 + 0x154)) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x46:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42200000;
      FUN_0042c840(1);
      FUN_005f6fd0(4,0,0,0);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
    }
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 3;
    if (100 < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 100;
    }
    uVar4 = *(uint *)(param_1 + 0x154) & 0x80000001;
    if ((int)uVar4 < 0) {
      uVar4 = (uVar4 - 1 | 0xfffffffe) + 1;
    }
    if (uVar4 == 0) {
      FUN_005f6fd0(7,0,0,0);
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if ((*(int *)(param_1 + 0xe8) == 0) && (0 < *(int *)(param_1 + 0x154))) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xec) * 0.005);
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar5) {
        *(float *)(param_1 + 0x6c) =
             *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xec) * 0.005;
      }
      fVar5 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar5 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) =
             (float)*(int *)(param_1 + 0xec) * 0.005 + *(float *)(param_1 + 0x6c);
      }
    }
    if (((0x1e0 < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
       (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_005f6db0(3,0,0,0);
      FUN_0042c8b0(0x4a);
      FUN_005f5e00();
      return;
    }
    break;
  case 0x50:
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
  case 0x5a:
    if (5 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 100:
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_005f6fd0(1,0,0,0);
      *(undefined4 *)(param_1 + 0x54) = 0x42480000;
      FUN_0042c840(1);
    }
    if (((0xf0 < *(int *)(param_1 + 0x154)) || (sVar3 = FUN_0042c7b0(), sVar3 != 0)) ||
       (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
      FUN_005f6db0(8,0,0,0);
      FUN_005f5e00();
      return;
    }
    break;
  case 0x6e:
    if (0x1d < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x78:
    if (0xe < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x82:
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
  case 0x8c:
    if (*(int *)(param_1 + 0x154) == 0) {
      uVar4 = FUN_0065d150();
      *(float *)(param_1 + 0x54) = (float)(uVar4 % 0x50) * 0.1 + 4.0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      FUN_005f6880(0);
      uVar4 = FUN_0065d150();
      *(float *)(param_1 + 0x40) = (float)(uVar4 % 0x28) * 0.1 + 8.0;
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 0x32;
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) - 0.3;
    cVar2 = FUN_005f6a90();
    if (cVar2 == '\x01') {
      FUN_005f6db0(2,0,0,0);
      FUN_0042c8b0(0x4e);
      FUN_005f5e00();
      return;
    }
    if (0x708 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x96:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (0x1a < *(int *)(param_1 + 0x154)) {
      if ((*(int *)(param_1 + 0xe8) < 0xf) && (param_1 != -0x90)) {
        *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
        *(undefined4 *)(param_1 + 0x154) = 0x12;
        return;
      }
      FUN_005f5e00();
      return;
    }
    break;
  case 0xa0:
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_005f6fd0(4,0,0,0);
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
    if (0x168 < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0xaa:
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_005f6fd0(4,0,0,0);
      *(undefined4 *)(param_1 + 0x54) = 0x41f00000;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      FUN_0042c840(1);
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
    sVar3 = FUN_0042c7b0();
    if (((sVar3 != 0) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) &&
       ((uVar4 = FUN_0042c7b0(), (uVar4 & 2) != 0 || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')))) {
      FUN_005f5e00();
      return;
    }
    if (*(int *)(param_1 + 0x154) == 0x1e) {
      *(undefined4 *)(param_1 + 0x154) = 0x14;
      return;
    }
    if (0x5a < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0xb4:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x3c23d70a;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      FUN_0042c840(1);
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
    *(int *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + 2;
    if (*(int *)(param_1 + 0x154) == 0x29) {
      FUN_005f5e00();
      return;
    }
  }
switchD_00611ed6_caseD_1:
  *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
  FUN_005f75a0();
  return;
}

