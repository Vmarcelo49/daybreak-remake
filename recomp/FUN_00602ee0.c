// ============================================
// Address:  0x00602ee0
// Original: FUN_00602ee0
// Status:   unreviewed
// ============================================


void __fastcall FUN_00602ee0(int param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  float10 fVar4;
  float fVar5;
  int local_c;
  int local_8;
  
  uVar3 = FUN_0042c7b0();
  if ((uVar3 & 0x100) != 0) {
    switch(*(undefined4 *)(param_1 + 0x150)) {
    case 0:
    case 10:
    case 0x14:
    case 0x1e:
    case 0x50:
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
      *(undefined4 *)(param_1 + 0x54) = 0x41dc0000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_005f7450(0,0x42700000,0x14,1,0);
    }
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
    if (0x3c < *(int *)(param_1 + 0xf0)) {
      *(undefined4 *)(param_1 + 0xf0) = 0x3c;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3f000000);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.25;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.25;
      }
    }
    if (((0x78 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
       (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1) {
        uVar3 = FUN_0065d150();
        fVar5 = (float)(uVar3 % 0x168);
        uVar3 = FUN_0065d150(fVar5);
        FUN_005f7110(4,0,0,0,(float)(uVar3 % 0x168),fVar5);
      }
      *(undefined4 *)(param_1 + 0xec) = 1;
      FUN_005f5e00();
      return;
    }
    break;
  case 10:
    if (*(int *)(param_1 + 0x154) == 0) {
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
      *(undefined4 *)(param_1 + 0x54) = 0x42200000;
      FUN_005f7450(3,0x42c80000,0x1e,1,0);
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
    if (0x3c < *(int *)(param_1 + 0xf0)) {
      *(undefined4 *)(param_1 + 0xf0) = 0x3c;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3f400000);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.5;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.5;
      }
    }
    if (((0xf0 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
       (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      for (local_c = 0; local_c < 0x10; local_c = local_c + 1) {
        uVar3 = FUN_0065d150();
        fVar5 = (float)(uVar3 % 0x168);
        uVar3 = FUN_0065d150(fVar5);
        FUN_005f7110(5,0,0,0,(float)(uVar3 % 0x168),fVar5);
      }
      *(undefined4 *)(param_1 + 0xec) = 1;
      FUN_005f5e00();
      return;
    }
    break;
  case 0x14:
    if (*(int *)(param_1 + 0x154) == 0) {
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
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0x28;
      *(undefined4 *)(param_1 + 0x54) = 0x425c0000;
      FUN_0042c840(1);
      FUN_005f7450(0,0x42b40000,0x14,1,0);
    }
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
    if (100 < *(int *)(param_1 + 0xf0)) {
      *(undefined4 *)(param_1 + 0xf0) = 100;
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
    if (*(int *)(param_1 + 0xec) == 1) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
      if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    if ((0x168 < *(int *)(param_1 + 0x154)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      *(undefined4 *)(param_1 + 0xec) = 1;
      return;
    }
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
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
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(undefined4 *)(param_1 + 0x54) = 0x425c0000;
      FUN_0042c840(1);
      FUN_005f7450(3,0x42b40000,0x1e,1,0);
    }
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
    if (100 < *(int *)(param_1 + 0xf0)) {
      *(undefined4 *)(param_1 + 0xf0) = 100;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xf0) * 0.005 + 0.2);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 0.3;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + 0.3;
      }
    }
    uVar3 = *(uint *)(param_1 + 0x154) & 0x80000001;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
    }
    if (uVar3 == 0) {
      FUN_005f6fd0(7,0,0,0);
    }
    if (*(int *)(param_1 + 0xec) == 1) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
      if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    if ((0x168 < *(int *)(param_1 + 0x154)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      *(undefined4 *)(param_1 + 0xec) = 1;
      return;
    }
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x54) = (float)(uVar3 % 0x14) + 10.0;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x70) = (float)(uVar3 % 10) * 0.1 + 0.25;
      *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x70);
      *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x70);
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 1.0;
    if (*(float *)(param_1 + 0x54) < 0.0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.01;
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.01;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.01;
    if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
      FUN_005f5e00();
      return;
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -10;
    if (*(int *)(param_1 + 0xe8) < 0) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),*(undefined1 *)(param_1 + 0xe8),
                 *(undefined1 *)(param_1 + 0xe8),0xff);
    break;
  case 0x32:
    if (*(int *)(param_1 + 0x154) == 0) {
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x54) = (float)(uVar3 % 0x14) + 10.0;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x70) = (float)(uVar3 % 10) * 0.1 + 0.25;
      *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x70);
      *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x70);
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 1.0;
    if (*(float *)(param_1 + 0x54) < 0.0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.01;
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.01;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.01;
    if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
      FUN_005f5e00();
      return;
    }
    *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -10;
    if (*(int *)(param_1 + 0xe8) < 0) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,*(undefined1 *)(param_1 + 0xe8),
                 *(undefined1 *)(param_1 + 0xe8));
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x41200000;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 100) = (float)(int)(short)((ulonglong)uVar3 % 0x168);
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x6c) = (float)(int)(short)((ulonglong)uVar3 % 0x168);
    }
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
    *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
    if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x46:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f333333;
      *(undefined4 *)(param_1 + 0x74) = 0x3f333333;
      *(undefined4 *)(param_1 + 0x78) = 0x3f333333;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x34) = (float)(uVar3 % 0x1e) - 15.0;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar3 % 0x1e) - 15.0;
      uVar3 = FUN_0065d150();
      *(float *)(param_1 + 0x2c) = (float)(uVar3 % 0x168);
    }
    if (0xe < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x50:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x78) = 0x3f800000;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(undefined4 *)(param_1 + 0x54) = 0x42340000;
      FUN_0042c840(1);
      FUN_005f7450(0,0x42f00000,0x1e,1,0);
    }
    if (*(int *)(param_1 + 0x154) % 5 == 0) {
      FUN_005f6fd0(9,0,0,0);
    }
    if (*(int *)(param_1 + 0xf0) == 0) {
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
      uVar3 = FUN_0042c7b0();
      if ((uVar3 & 1) != 0) {
        FUN_0042c840(1);
        FUN_0042c800(0);
        FUN_005f71f0();
        *(undefined4 *)(param_1 + 0xf0) = 0x3c;
      }
    }
    if (0 < *(int *)(param_1 + 0xf0)) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xf0) * 0.1);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)1.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) =
             *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xf0) * 0.1;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-1.0) {
        *(float *)(param_1 + 0x6c) =
             (float)*(int *)(param_1 + 0xf0) * 0.1 + *(float *)(param_1 + 0x6c);
      }
      *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + -1;
      if (*(int *)(param_1 + 0xf0) == 0) {
        *(undefined4 *)(param_1 + 0xf0) = 1;
      }
    }
    if (*(int *)(param_1 + 0xec) == 1) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
      if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    if ((0x168 < *(int *)(param_1 + 0x154)) || (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      *(undefined4 *)(param_1 + 0xec) = 1;
      return;
    }
    break;
  case 0x5a:
    if (0xc < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 100:
    *(undefined4 *)(param_1 + 0x70) = 0x40400000;
    *(undefined4 *)(param_1 + 0x74) = 0x40400000;
    *(undefined4 *)(param_1 + 0x78) = 0x40400000;
    if (0xe < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x6e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x420c0000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      FUN_005f7450(0,0x41f00000,10,1,0);
    }
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
    if (0x3c < *(int *)(param_1 + 0xf0)) {
      *(undefined4 *)(param_1 + 0xf0) = 0x3c;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,(float)*(int *)(param_1 + 0xf0) * 0.015);
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)3.0 < (float10)*(float *)(param_1 + 0x6c) - fVar4) {
        *(float *)(param_1 + 0x6c) =
             *(float *)(param_1 + 0x6c) - (float)*(int *)(param_1 + 0xf0) * 0.01;
      }
      fVar4 = (float10)FUN_0042dac0(2);
      if ((float10)*(float *)(param_1 + 0x6c) - fVar4 < (float10)-3.0) {
        *(float *)(param_1 + 0x6c) =
             (float)*(int *)(param_1 + 0xf0) * 0.01 + *(float *)(param_1 + 0x6c);
      }
    }
    if (((0xb4 < *(int *)(param_1 + 0x154)) || (sVar2 = FUN_0042c7b0(), sVar2 != 0)) ||
       (cVar1 = FUN_005f6a90(), cVar1 == '\x01')) {
      FUN_005f6fd0(4,0,0,0);
      *(undefined4 *)(param_1 + 0xec) = 1;
      FUN_005f5e00();
      return;
    }
  }
  *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
  FUN_005f75a0();
  return;
}

