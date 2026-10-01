// Function: FUN_00622ab0
// Address:  0x00622ab0
// Source:   batch_decompile (mass dump)
// Hash:     83f7a198b6832b75


void __fastcall FUN_00622ab0(int param_1)

{
  float fVar1;
  char cVar2;
  short sVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  float10 fVar9;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  float local_c;
  float local_8;
  
  uVar4 = FUN_0042c7b0();
  if ((uVar4 & 0x100) != 0) {
    switch(*(undefined4 *)(param_1 + 0x150)) {
    case 0x14:
    case 0x1e:
    case 0x28:
    case 0x32:
    case 0x46:
    case 0x50:
    case 0x5a:
    case 100:
    case 0x6e:
    case 0x78:
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
        fVar9 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar9 < (float10)10.0) {
          fVar9 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar9;
        }
        fVar9 = (float10)FUN_0042dac0(2);
        if ((float10)-10.0 < (float10)*(float *)(param_1 + 0x6c) - fVar9) {
          fVar9 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar9;
        }
      }
      FUN_005f7450(0,0x41a00000,10,1,0);
      FUN_0042db10(0,0x41200000);
      *(undefined4 *)(param_1 + 0x54) = 0x42a00000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf4) = 0;
      *(undefined4 *)(param_1 + 0x108) = 0;
      FUN_005f6db0(6,0,0,0);
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
    }
    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) =
         *(float *)(param_1 + 0x3c) * 40.0 + *(float *)(param_1 + 0x14);
    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64) =
         *(float *)(param_1 + 0x40) * 40.0 + *(float *)(param_1 + 0x18);
    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68) =
         *(float *)(param_1 + 0x44) * 40.0 + *(float *)(param_1 + 0x1c);
    if (((99 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
        (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 300)) ||
       (((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 400 &&
         ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x191 &&
          (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x192)))) &&
        ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1a4 &&
         (((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1a5 &&
           (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1a6)) &&
          (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1a7)))))))) {
      FUN_005f5e00();
      return;
    }
    if ((*(int *)(param_1 + 0xec) == 0) &&
       (((*(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0,
         *(float *)(param_1 + 0x54) < 0.0 != (*(float *)(param_1 + 0x54) == 0.0) ||
         (sVar3 = FUN_0042c7b0(), sVar3 != 0)) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')))) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      uVar4 = FUN_0042c7b0();
      if ((uVar4 & 1) == 0) {
        *(undefined4 *)(param_1 + 0xec) = 2;
        FUN_005f7430();
        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xf8) = 1;
      }
      else {
        *(undefined4 *)(param_1 + 0xec) = 1;
        if (10.0 < *(float *)(param_1 + 0x54)) {
          *(undefined4 *)(param_1 + 0x54) = 0x41200000;
        }
      }
    }
    if (*(int *)(param_1 + 0xec) == 1) {
      FUN_0042c840(0);
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 1.0;
      if (*(float *)(param_1 + 0x54) < 0.0) {
        *(undefined4 *)(param_1 + 0x54) = 0;
      }
      *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
      if (*(int *)(param_1 + 0xe8) == 0x14) {
        if (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x278) == 0) {
          *(undefined4 *)(param_1 + 0xec) = 2;
          FUN_005f6ef0(0xd,0,0,0,0x43340000,0);
          FUN_005f7430();
          *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xf8) = 1;
        }
        if (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x278) < 0) {
          *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xf8) = 2;
        }
        if (0 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x278)) {
          *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xf8) = 3;
        }
      }
      if (((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0x1a4) ||
          (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0x1a6)) &&
         (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xae04) == 0xf)) {
        *(undefined4 *)(param_1 + 0xec) = 3;
        FUN_005f6ef0(0xe,0,0,0,0x42b40000,0);
        FUN_005f7430();
      }
      if (((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0x1a5) ||
          (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0x1a7)) &&
         (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xae04) == 0xf)) {
        *(undefined4 *)(param_1 + 0xec) = 5;
        FUN_005f6ef0(0xe,0,0,0,0xc2b40000,0);
        FUN_005f7430();
      }
    }
    if (*(int *)(param_1 + 0xec) == 2) {
      FUN_0042c840(0);
      *(undefined4 *)(param_1 + 0x54) = 0x42c80000;
      FUN_0042db10(0,0x43340000);
      fVar9 = (float10)FUN_0042dac0(2);
      *(float *)(param_1 + 0x6c) = (float)fVar9;
      if (*(int *)(param_1 + 0xf4) == 2) {
        *(undefined4 *)(param_1 + 0x54) = 0x42c80000;
      }
      fVar9 = (float10)FUN_0042d980();
      fVar7 = (float10)FUN_0042da30();
      fVar8 = (float10)FUN_0042da30();
      if ((fVar8 * (float10)(float)fVar7 + (float10)(float)fVar9 < (float10)10000.0) &&
         (1 < *(int *)(param_1 + 0xf4))) {
        FUN_005f5e00();
        return;
      }
      *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + 1;
    }
    if (*(int *)(param_1 + 0xec) == 3) {
      *(float *)(param_1 + 100) = *(float *)(param_1 + 100) + 90.0;
      *(undefined4 *)(param_1 + 0xec) = 4;
      *(undefined4 *)(param_1 + 0x54) = 0x42c80000;
      FUN_0042c840(0);
      fVar9 = (float10)FUN_0042dac0(2);
      *(float *)(param_1 + 0x6c) = (float)fVar9;
      *(float *)(param_1 + 0x108) = *(float *)(param_1 + 0x108) + 6.0;
      if (180.0 < *(float *)(param_1 + 0x108)) {
        *(undefined4 *)(param_1 + 0x108) = 0x43340000;
      }
      FUN_0042db10(0,*(undefined4 *)(param_1 + 0x108));
    }
    if (*(int *)(param_1 + 0xec) == 4) {
      fVar9 = (float10)FUN_0042dac0(2);
      *(float *)(param_1 + 0x6c) = (float)fVar9;
      *(float *)(param_1 + 0x108) = *(float *)(param_1 + 0x108) + 6.0;
      if (180.0 < *(float *)(param_1 + 0x108)) {
        *(undefined4 *)(param_1 + 0x108) = 0x43340000;
      }
      FUN_0042db10(0,*(undefined4 *)(param_1 + 0x108));
      fVar9 = (float10)FUN_0042d980();
      fVar7 = (float10)FUN_0042da30();
      fVar8 = (float10)FUN_0042da30();
      if ((fVar8 * (float10)(float)fVar7 + (float10)(float)fVar9 < (float10)10000.0) &&
         (1 < *(int *)(param_1 + 0xf4))) {
        FUN_005f5e00();
        return;
      }
      *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + 1;
    }
    if (*(int *)(param_1 + 0xec) == 5) {
      *(undefined4 *)(param_1 + 0x54) = 0x42c80000;
      *(float *)(param_1 + 100) = *(float *)(param_1 + 100) - 90.0;
      *(undefined4 *)(param_1 + 0xec) = 6;
      FUN_0042c840(0);
      fVar9 = (float10)FUN_0042dac0(2);
      *(float *)(param_1 + 0x6c) = (float)fVar9;
      *(float *)(param_1 + 0x108) = *(float *)(param_1 + 0x108) + 6.0;
      if (180.0 < *(float *)(param_1 + 0x108)) {
        *(undefined4 *)(param_1 + 0x108) = 0x43340000;
      }
      FUN_0042db10(0,*(undefined4 *)(param_1 + 0x108));
    }
    if (*(int *)(param_1 + 0xec) == 6) {
      fVar9 = (float10)FUN_0042dac0(2);
      *(float *)(param_1 + 0x6c) = (float)fVar9;
      *(float *)(param_1 + 0x108) = *(float *)(param_1 + 0x108) + 6.0;
      if (180.0 < *(float *)(param_1 + 0x108)) {
        *(undefined4 *)(param_1 + 0x108) = 0x43340000;
      }
      FUN_0042db10(0,*(undefined4 *)(param_1 + 0x108));
      fVar9 = (float10)FUN_0042d980();
      fVar7 = (float10)FUN_0042da30();
      fVar8 = (float10)FUN_0042da30();
      if ((fVar8 * (float10)(float)fVar7 + (float10)(float)fVar9 < (float10)10000.0) &&
         (1 < *(int *)(param_1 + 0xf4))) {
        FUN_005f5e00();
        return;
      }
      *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + 1;
    }
    break;
  case 10:
    if (*(int *)(param_1 + 0x154) == 0) {
      if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
          (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
         (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd)) {
        fVar9 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar9 < (float10)10.0) {
          fVar9 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar9;
        }
        fVar9 = (float10)FUN_0042dac0(2);
        if ((float10)-10.0 < (float10)*(float *)(param_1 + 0x6c) - fVar9) {
          fVar9 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar9;
        }
      }
      FUN_005f7450(1,0x41a00000,10,1,0);
      FUN_0042db10(0,0x41200000);
      *(undefined4 *)(param_1 + 0x54) = 0x42f00000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf4) = 0;
      *(undefined4 *)(param_1 + 0x108) = 0;
      FUN_005f6db0(6,0,0,0);
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
    }
    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) =
         *(float *)(param_1 + 0x3c) * 40.0 + *(float *)(param_1 + 0x14);
    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64) =
         *(float *)(param_1 + 0x40) * 40.0 + *(float *)(param_1 + 0x18);
    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68) =
         *(float *)(param_1 + 0x44) * 40.0 + *(float *)(param_1 + 0x1c);
    if (((99 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
        (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 300)) ||
       ((((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 400 &&
          ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x191 &&
           (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x192)))) &&
         (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1a4)) &&
        (((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1a5 &&
          (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1a6)) &&
         (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1a7)))))) {
      FUN_005f5e00();
      return;
    }
    if (*(int *)(param_1 + 0xec) == 0) {
      uVar4 = *(uint *)(param_1 + 0x154) & 0x80000003;
      if ((int)uVar4 < 0) {
        uVar4 = (uVar4 - 1 | 0xfffffffc) + 1;
      }
      if (uVar4 == 0) {
        FUN_005f6fd0(0x11,0,0,0);
      }
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 4.0;
      if (((*(float *)(param_1 + 0x54) < 0.0 != (*(float *)(param_1 + 0x54) == 0.0)) ||
          (sVar3 = FUN_0042c7b0(), sVar3 != 0)) || (cVar2 = FUN_005f6a90(), cVar2 == '\x01')) {
        *(undefined4 *)(param_1 + 0x54) = 0;
        uVar4 = FUN_0042c7b0();
        if ((uVar4 & 1) == 0) {
          *(undefined4 *)(param_1 + 0xec) = 2;
          FUN_005f7430();
          *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xf8) = 1;
        }
        else {
          *(undefined4 *)(param_1 + 0xec) = 1;
          if (10.0 < *(float *)(param_1 + 0x54)) {
            *(undefined4 *)(param_1 + 0x54) = 0x41200000;
          }
        }
      }
    }
    if (*(int *)(param_1 + 0xec) == 1) {
      FUN_0042c840(0);
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 1.0;
      if (*(float *)(param_1 + 0x54) < 0.0) {
        *(undefined4 *)(param_1 + 0x54) = 0;
      }
      *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
      if (*(int *)(param_1 + 0xe8) == 0x14) {
        if (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x278) == 0) {
          *(undefined4 *)(param_1 + 0xec) = 2;
          FUN_005f6ef0(0xf,0,0,0,0x43340000,0);
          FUN_005f7430();
          *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xf8) = 1;
        }
        if (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x278) < 0) {
          *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xf8) = 2;
        }
        if (0 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0x278)) {
          *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xf8) = 3;
        }
      }
      if (((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0x1a4) ||
          (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0x1a6)) &&
         (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xae04) == 0xf)) {
        *(undefined4 *)(param_1 + 0xec) = 3;
        FUN_005f6ef0(0x10,0,0,0,0x42b40000,0);
        FUN_005f7430();
      }
      if (((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0x1a5) ||
          (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) == 0x1a7)) &&
         (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xae04) == 0xf)) {
        *(undefined4 *)(param_1 + 0xec) = 5;
        FUN_005f6ef0(0x10,0,0,0,0xc2b40000,0);
        FUN_005f7430();
      }
    }
    if (*(int *)(param_1 + 0xec) == 2) {
      FUN_0042c840(0);
      *(undefined4 *)(param_1 + 0x54) = 0x42c80000;
      FUN_0042db10(0,0x43340000);
      fVar9 = (float10)FUN_0042dac0(2);
      *(float *)(param_1 + 0x6c) = (float)fVar9;
      if (*(int *)(param_1 + 0xf4) == 2) {
        *(undefined4 *)(param_1 + 0x54) = 0x42c80000;
      }
      fVar9 = (float10)FUN_0042d980();
      fVar7 = (float10)FUN_0042da30();
      fVar8 = (float10)FUN_0042da30();
      if ((fVar8 * (float10)(float)fVar7 + (float10)(float)fVar9 < (float10)10000.0) &&
         (1 < *(int *)(param_1 + 0xf4))) {
        FUN_005f5e00();
        return;
      }
      *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + 1;
    }
    if (*(int *)(param_1 + 0xec) == 3) {
      *(float *)(param_1 + 100) = *(float *)(param_1 + 100) + 90.0;
      *(undefined4 *)(param_1 + 0xec) = 4;
      *(undefined4 *)(param_1 + 0x54) = 0x42c80000;
      FUN_0042c840(0);
      fVar9 = (float10)FUN_0042dac0(2);
      *(float *)(param_1 + 0x6c) = (float)fVar9;
      *(float *)(param_1 + 0x108) = *(float *)(param_1 + 0x108) + 6.0;
      if (180.0 < *(float *)(param_1 + 0x108)) {
        *(undefined4 *)(param_1 + 0x108) = 0x43340000;
      }
      FUN_0042db10(0,*(undefined4 *)(param_1 + 0x108));
    }
    if (*(int *)(param_1 + 0xec) == 4) {
      fVar9 = (float10)FUN_0042dac0(2);
      *(float *)(param_1 + 0x6c) = (float)fVar9;
      *(float *)(param_1 + 0x108) = *(float *)(param_1 + 0x108) + 6.0;
      if (180.0 < *(float *)(param_1 + 0x108)) {
        *(undefined4 *)(param_1 + 0x108) = 0x43340000;
      }
      FUN_0042db10(0,*(undefined4 *)(param_1 + 0x108));
      fVar9 = (float10)FUN_0042d980();
      fVar7 = (float10)FUN_0042da30();
      fVar8 = (float10)FUN_0042da30();
      if ((fVar8 * (float10)(float)fVar7 + (float10)(float)fVar9 < (float10)10000.0) &&
         (1 < *(int *)(param_1 + 0xf4))) {
        FUN_005f5e00();
        return;
      }
      *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + 1;
    }
    if (*(int *)(param_1 + 0xec) == 5) {
      *(undefined4 *)(param_1 + 0x54) = 0x42c80000;
      *(float *)(param_1 + 100) = *(float *)(param_1 + 100) - 90.0;
      *(undefined4 *)(param_1 + 0xec) = 6;
      FUN_0042c840(0);
      fVar9 = (float10)FUN_0042dac0(2);
      *(float *)(param_1 + 0x6c) = (float)fVar9;
      *(float *)(param_1 + 0x108) = *(float *)(param_1 + 0x108) + 6.0;
      if (180.0 < *(float *)(param_1 + 0x108)) {
        *(undefined4 *)(param_1 + 0x108) = 0x43340000;
      }
      FUN_0042db10(0,*(undefined4 *)(param_1 + 0x108));
    }
    if (*(int *)(param_1 + 0xec) == 6) {
      fVar9 = (float10)FUN_0042dac0(2);
      *(float *)(param_1 + 0x6c) = (float)fVar9;
      *(float *)(param_1 + 0x108) = *(float *)(param_1 + 0x108) + 6.0;
      if (180.0 < *(float *)(param_1 + 0x108)) {
        *(undefined4 *)(param_1 + 0x108) = 0x43340000;
      }
      FUN_0042db10(0,*(undefined4 *)(param_1 + 0x108));
      fVar9 = (float10)FUN_0042d980();
      fVar7 = (float10)FUN_0042da30();
      fVar8 = (float10)FUN_0042da30();
      if ((fVar8 * (float10)(float)fVar7 + (float10)(float)fVar9 < (float10)10000.0) &&
         (1 < *(int *)(param_1 + 0xf4))) {
        FUN_005f5e00();
        return;
      }
      *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + 1;
    }
    break;
  case 0x14:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42700000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x30) = 0xc2340000;
      *(undefined4 *)(param_1 + 0x70) = 0x40200000;
      *(undefined4 *)(param_1 + 0x74) = 0x40200000;
      *(undefined4 *)(param_1 + 0x78) = 0x40200000;
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 4.0;
    if (*(float *)(param_1 + 0x54) < 5.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x40a00000;
    }
    cVar2 = FUN_005f6a90();
    if ((cVar2 == '\x01') || (0x28 < *(int *)(param_1 + 0x154))) {
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.5;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.5;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.5;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42700000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x30) = 0x42340000;
      *(undefined4 *)(param_1 + 0x70) = 0x40200000;
      *(undefined4 *)(param_1 + 0x74) = 0x40200000;
      *(undefined4 *)(param_1 + 0x78) = 0x40200000;
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 4.0;
    if (*(float *)(param_1 + 0x54) < 5.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x40a00000;
    }
    cVar2 = FUN_005f6a90();
    if ((cVar2 == '\x01') || (0x18 < *(int *)(param_1 + 0x154))) {
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.5;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.5;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.5;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42b40000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x30) = 0xc2340000;
      *(undefined4 *)(param_1 + 0x70) = 0x40600000;
      *(undefined4 *)(param_1 + 0x74) = 0x40600000;
      *(undefined4 *)(param_1 + 0x78) = 0x40600000;
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 2.0;
    if (*(float *)(param_1 + 0x54) < 5.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x40a00000;
    }
    cVar2 = FUN_005f6a90();
    if ((cVar2 == '\x01') || (0x3c < *(int *)(param_1 + 0x154))) {
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.5;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.5;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.5;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x32:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42b40000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x30) = 0x42340000;
      *(undefined4 *)(param_1 + 0x70) = 0x40600000;
      *(undefined4 *)(param_1 + 0x74) = 0x40600000;
      *(undefined4 *)(param_1 + 0x78) = 0x40600000;
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 2.0;
    if (*(float *)(param_1 + 0x54) < 5.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x40a00000;
    }
    cVar2 = FUN_005f6a90();
    if ((cVar2 == '\x01') || (0x2c < *(int *)(param_1 + 0x154))) {
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.5;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.5;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.5;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
    if (((99 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
        (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 300)) ||
       ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 400 &&
        (((((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x191 &&
            (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x192)) &&
           (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1a4)) &&
          ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1a5 &&
           (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1a6)))) &&
         (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1a7)))))) {
      FUN_005f5e00();
      return;
    }
    local_8 = (*(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) -
              *(float *)(param_1 + 0x14)) *
              (*(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) -
              *(float *)(param_1 + 0x14)) +
              (*(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68) -
              *(float *)(param_1 + 0x1c)) *
              (*(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68) -
              *(float *)(param_1 + 0x1c));
    fVar9 = (float10)FUN_0042de80((*(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64) -
                                  *(float *)(param_1 + 0x18)) *
                                  (*(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64) -
                                  *(float *)(param_1 + 0x18)) + local_8);
    local_c = (float)fVar9;
    *(float *)(param_1 + 0x70) = (float)(fVar9 / (float10)107.0);
    *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
    *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
    std::allocator<char>::allocator<char>((allocator<char> *)&local_1c);
    uVar5 = FUN_0064e6c0("Bip01_R_Hand");
    uVar6 = FUN_00423750(0,0,0);
    D3DXVec3Transform(&local_1c,uVar6,uVar5);
    *(undefined4 *)(param_1 + 0x14) = local_1c;
    *(undefined4 *)(param_1 + 0x18) = local_18;
    *(undefined4 *)(param_1 + 0x1c) = local_14;
    fVar1 = *(float *)(param_1 + 0x5c);
    fVar9 = (float10)FUN_00423580(*(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68) -
                                  *(float *)(param_1 + 0x1c),
                                  *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) -
                                  *(float *)(param_1 + 0x14));
    *(float *)(param_1 + 100) =
         (float)((fVar9 / (float10)3.1415927) * (float10)180.0 + (float10)-fVar1);
    fVar9 = (float10)FUN_0042de80(local_8);
    fVar9 = (float10)FUN_00423580(*(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64) -
                                  *(float *)(param_1 + 0x18),(float)fVar9);
    *(float *)(param_1 + 0x6c) = (float)((fVar9 / (float10)3.1415927) * (float10)180.0);
    break;
  case 0x46:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42700000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x30) = 0xc1f00000;
      *(undefined4 *)(param_1 + 0x70) = 0x40200000;
      *(undefined4 *)(param_1 + 0x74) = 0x40200000;
      *(undefined4 *)(param_1 + 0x78) = 0x40200000;
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 2.0;
    if (*(float *)(param_1 + 0x54) < 5.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x40a00000;
    }
    cVar2 = FUN_005f6a90();
    if ((cVar2 == '\x01') || (0x3c < *(int *)(param_1 + 0x154))) {
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.5;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.5;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.5;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x50:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42700000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x30) = 0x41f00000;
      *(undefined4 *)(param_1 + 0x70) = 0x40200000;
      *(undefined4 *)(param_1 + 0x74) = 0x40200000;
      *(undefined4 *)(param_1 + 0x78) = 0x40200000;
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 2.0;
    if (*(float *)(param_1 + 0x54) < 5.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x40a00000;
    }
    cVar2 = FUN_005f6a90();
    if ((cVar2 == '\x01') || (0x3c < *(int *)(param_1 + 0x154))) {
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.5;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.5;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.5;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x5a:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42700000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x30) = 0xc2340000;
      *(undefined4 *)(param_1 + 0x70) = 0x40200000;
      *(undefined4 *)(param_1 + 0x74) = 0x40200000;
      *(undefined4 *)(param_1 + 0x78) = 0x40200000;
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 2.0;
    if (*(float *)(param_1 + 0x54) < 5.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x40a00000;
    }
    cVar2 = FUN_005f6a90();
    if ((cVar2 == '\x01') || (0x3c < *(int *)(param_1 + 0x154))) {
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.5;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.5;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.5;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 100:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42700000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x30) = 0x42340000;
      *(undefined4 *)(param_1 + 0x70) = 0x40200000;
      *(undefined4 *)(param_1 + 0x74) = 0x40200000;
      *(undefined4 *)(param_1 + 0x78) = 0x40200000;
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 2.0;
    if (*(float *)(param_1 + 0x54) < 5.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x40a00000;
    }
    cVar2 = FUN_005f6a90();
    if ((cVar2 == '\x01') || (0x3c < *(int *)(param_1 + 0x154))) {
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.5;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.5;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.5;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x6e:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42700000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x30) = 0xc2700000;
      *(undefined4 *)(param_1 + 0x70) = 0x40200000;
      *(undefined4 *)(param_1 + 0x74) = 0x40200000;
      *(undefined4 *)(param_1 + 0x78) = 0x40200000;
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 2.0;
    if (*(float *)(param_1 + 0x54) < 5.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x40a00000;
    }
    cVar2 = FUN_005f6a90();
    if ((cVar2 == '\x01') || (0x3c < *(int *)(param_1 + 0x154))) {
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.5;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.5;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.5;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x78:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x42700000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x30) = 0x42700000;
      *(undefined4 *)(param_1 + 0x70) = 0x40200000;
      *(undefined4 *)(param_1 + 0x74) = 0x40200000;
      *(undefined4 *)(param_1 + 0x78) = 0x40200000;
    }
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 2.0;
    if (*(float *)(param_1 + 0x54) < 5.0) {
      *(undefined4 *)(param_1 + 0x54) = 0x40a00000;
    }
    cVar2 = FUN_005f6a90();
    if ((cVar2 == '\x01') || (0x3c < *(int *)(param_1 + 0x154))) {
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.5;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.5;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.5;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x82:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x3f800000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x40200000;
      *(undefined4 *)(param_1 + 0x74) = 0x40200000;
      *(undefined4 *)(param_1 + 0x78) = 0x40200000;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      *(undefined4 *)(param_1 + 0x54) = 0x42700000;
    }
    cVar2 = FUN_005f6a90();
    if ((cVar2 == '\x01') || (6 < *(int *)(param_1 + 0x154))) {
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.5;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.5;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.5;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x8c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x3f800000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x40200000;
      *(undefined4 *)(param_1 + 0x74) = 0x40200000;
      *(undefined4 *)(param_1 + 0x78) = 0x40200000;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      *(undefined4 *)(param_1 + 0x54) = 0x42700000;
    }
    cVar2 = FUN_005f6a90();
    if ((cVar2 == '\x01') || (6 < *(int *)(param_1 + 0x154))) {
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.5;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.5;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.5;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x96:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x3f800000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x40200000;
      *(undefined4 *)(param_1 + 0x74) = 0x40200000;
      *(undefined4 *)(param_1 + 0x78) = 0x40200000;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      *(undefined4 *)(param_1 + 0x54) = 0x42b40000;
    }
    cVar2 = FUN_005f6a90();
    if ((cVar2 == '\x01') || (6 < *(int *)(param_1 + 0x154))) {
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.5;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.5;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.5;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0xa0:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0x3f800000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x40200000;
      *(undefined4 *)(param_1 + 0x74) = 0x40200000;
      *(undefined4 *)(param_1 + 0x78) = 0x40200000;
    }
    if (*(int *)(param_1 + 0x154) == 1) {
      *(undefined4 *)(param_1 + 0x54) = 0x42f00000;
    }
    cVar2 = FUN_005f6a90();
    if ((cVar2 == '\x01') || (6 < *(int *)(param_1 + 0x154))) {
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 3.0;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.5;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.5;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.5;
      if (*(float *)(param_1 + 0x70) < 0.0 != (*(float *)(param_1 + 0x70) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0xaa:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x70) = 0x3f333333;
      *(undefined4 *)(param_1 + 0x74) = 0x3f333333;
      *(undefined4 *)(param_1 + 0x78) = 0x3f333333;
      uVar4 = FUN_0065d150();
      *(float *)(param_1 + 0x34) = (float)(uVar4 % 0x1e) - 15.0;
      uVar4 = FUN_0065d150();
      *(float *)(param_1 + 0x30) = (float)(uVar4 % 0x1e) - 15.0;
      uVar4 = FUN_0065d150();
      *(float *)(param_1 + 0x2c) = (float)(uVar4 % 0x168);
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

