// Function: FUN_005fdee0
// Address:  0x005fdee0
// Source:   batch_decompile (mass dump)
// Hash:     d2caaadcac6fda42


void __fastcall FUN_005fdee0(int param_1)

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
  if (((uVar4 & 0x100) != 0) &&
     ((*(int *)(param_1 + 0x150) == 0 || (*(int *)(param_1 + 0x150) == 0x14)))) {
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
        fVar7 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar7 < (float10)10.0) {
          fVar7 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar7;
        }
        fVar7 = (float10)FUN_0042dac0(2);
        if ((float10)-10.0 < (float10)*(float *)(param_1 + 0x6c) - fVar7) {
          fVar7 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar7;
        }
      }
      *(undefined4 *)(param_1 + 0x54) = 0x420c0000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
    if (0x3c < *(int *)(param_1 + 0xf0)) {
      *(undefined4 *)(param_1 + 0xf0) = 0x3c;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3dcccccd);
    }
    if ((*(int *)(param_1 + 0xec) == 0) &&
       (((0x3c < *(int *)(param_1 + 0x154) ||
         ((sVar3 = FUN_0042c7b0(), sVar3 != 0 && (sVar3 = FUN_0042c7b0(), sVar3 != 1)))) ||
        (cVar2 = FUN_005f6a90(), cVar2 == '\x01')))) {
      *(undefined4 *)(param_1 + 0xec) = 1;
    }
    if (*(int *)(param_1 + 0xec) == 1) {
      *(undefined4 *)(param_1 + 0x54) = 0x40000000;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
      if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 10:
    if (*(int *)(param_1 + 0x154) == 0) {
      if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
          (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
         (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd)) {
        fVar7 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar7 < (float10)10.0) {
          fVar7 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar7;
        }
        fVar7 = (float10)FUN_0042dac0(2);
        if ((float10)-10.0 < (float10)*(float *)(param_1 + 0x6c) - fVar7) {
          fVar7 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar7;
        }
      }
      FUN_0042db10(0,0x41200000);
      *(undefined4 *)(param_1 + 0x54) = 0x425c0000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      FUN_005f6db0(5,0,0,0);
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
    }
    if ((*(int *)(param_1 + 0xec) == 0) &&
       (((*(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 2.0,
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
        FUN_005f6db0(4,0,0,0);
      }
    }
    if (*(int *)(param_1 + 0xec) == 1) {
      FUN_0042c840(0);
      *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 5.0;
      if (*(float *)(param_1 + 0x54) < 2.0) {
        *(undefined4 *)(param_1 + 0x54) = 0x40000000;
      }
      *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
      if (0x1e < *(int *)(param_1 + 0xe8)) {
        *(undefined4 *)(param_1 + 0xec) = 2;
        FUN_005f7430();
        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xf8) = 1;
      }
    }
    if (*(int *)(param_1 + 0xec) == 2) {
      uVar4 = FUN_0042c7b0();
      if ((uVar4 & 1) != 0) {
        FUN_005f6db0(7,0,0,0);
        FUN_005f5e00();
        return;
      }
      FUN_0042c840(0);
      *(undefined4 *)(param_1 + 0x54) = 0x42200000;
      FUN_0042db10(0,0x43340000);
      fVar7 = (float10)FUN_0042dac0(2);
      *(float *)(param_1 + 0x6c) = (float)fVar7;
      fVar7 = (float10)FUN_0042d980();
      fVar8 = (float10)FUN_0042da30();
      fVar9 = (float10)FUN_0042da30();
      if (fVar9 * (float10)(float)fVar8 + (float10)(float)fVar7 < (float10)10000.0) {
        FUN_005f5e00();
        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xf8) = 3;
        return;
      }
    }
    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) =
         *(float *)(param_1 + 0x3c) * 40.0 + *(float *)(param_1 + 0x14);
    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64) =
         *(float *)(param_1 + 0x40) * 40.0 + *(float *)(param_1 + 0x18);
    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68) =
         *(float *)(param_1 + 0x44) * 40.0 + *(float *)(param_1 + 0x1c);
    if (((99 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
        (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 300)) ||
       ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1c2 &&
        (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1cc)))) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x14:
    if (*(int *)(param_1 + 0x154) == 0) {
      if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
          (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
         (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd)) {
        fVar7 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar7 < (float10)10.0) {
          fVar7 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar7;
        }
        fVar7 = (float10)FUN_0042dac0(2);
        if ((float10)-10.0 < (float10)*(float *)(param_1 + 0x6c) - fVar7) {
          fVar7 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar7;
        }
      }
      *(undefined4 *)(param_1 + 0x54) = 0x42700000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0xf0) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x3fa00000;
      *(undefined4 *)(param_1 + 0x74) = 0x3fa00000;
      *(undefined4 *)(param_1 + 0x78) = 0x3fa00000;
    }
    *(float *)(param_1 + 0x30) = *(float *)(param_1 + 0x30) + 15.0;
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    *(int *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + 1;
    if (0x3c < *(int *)(param_1 + 0xf0)) {
      *(undefined4 *)(param_1 + 0xf0) = 0x3c;
    }
    if (*(int *)(param_1 + 0xe8) == 0) {
      FUN_0042db10(0,0x3dcccccd);
    }
    if ((*(int *)(param_1 + 0xec) == 0) &&
       (((0x3c < *(int *)(param_1 + 0x154) ||
         ((sVar3 = FUN_0042c7b0(), sVar3 != 0 && (sVar3 = FUN_0042c7b0(), sVar3 != 1)))) ||
        (cVar2 = FUN_005f6a90(), cVar2 == '\x01')))) {
      *(undefined4 *)(param_1 + 0xec) = 1;
    }
    if (*(int *)(param_1 + 0xec) == 1) {
      *(undefined4 *)(param_1 + 0x54) = 0x40000000;
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
      if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x1e:
    if (*(int *)(param_1 + 0x154) == 0) {
      if (((0x75 < *(int *)(*(int *)(param_1 + 0x38) + 0xadec)) &&
          (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) < 0x7a)) ||
         (*(int *)(*(int *)(param_1 + 0x38) + 0xadec) == 0xdd)) {
        fVar7 = (float10)FUN_0042dac0(2);
        if ((float10)*(float *)(param_1 + 0x6c) - fVar7 < (float10)10.0) {
          fVar7 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar7;
        }
        fVar7 = (float10)FUN_0042dac0(2);
        if ((float10)-10.0 < (float10)*(float *)(param_1 + 0x6c) - fVar7) {
          fVar7 = (float10)FUN_0042dac0(2);
          *(float *)(param_1 + 0x6c) = (float)fVar7;
        }
      }
      FUN_0042db10(0,0x41a00000);
      *(undefined4 *)(param_1 + 0x54) = 0x42a00000;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      FUN_005f6db0(5,0,0,0);
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
    }
    if ((*(int *)(param_1 + 0xec) == 0) &&
       (((*(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) - 4.0,
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
        FUN_005f6db0(4,0,0,0);
      }
    }
    if (*(int *)(param_1 + 0xec) == 1) {
      if (*(int *)(param_1 + 0xe8) % 10 == 0) {
        FUN_005f6fd0(6,0,0,0);
      }
      FUN_0042c840(0);
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
      if (0x1e < *(int *)(param_1 + 0xe8)) {
        *(undefined4 *)(param_1 + 0xec) = 2;
        FUN_005f7430();
        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xf8) = 1;
      }
    }
    if (*(int *)(param_1 + 0xec) == 2) {
      uVar4 = FUN_0042c7b0();
      if ((uVar4 & 1) != 0) {
        FUN_005f6db0(7,0,0,0);
        FUN_005f5e00();
        return;
      }
      FUN_0042c840(0);
      *(undefined4 *)(param_1 + 0x54) = 0x42200000;
      FUN_0042db10(0,0x43340000);
      fVar7 = (float10)FUN_0042dac0(2);
      *(float *)(param_1 + 0x6c) = (float)fVar7;
      fVar7 = (float10)FUN_0042d980();
      fVar8 = (float10)FUN_0042da30();
      fVar9 = (float10)FUN_0042da30();
      if (fVar9 * (float10)(float)fVar8 + (float10)(float)fVar7 < (float10)10000.0) {
        FUN_005f5e00();
        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xf8) = 3;
        return;
      }
    }
    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) =
         *(float *)(param_1 + 0x3c) * 40.0 + *(float *)(param_1 + 0x14);
    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64) =
         *(float *)(param_1 + 0x40) * 40.0 + *(float *)(param_1 + 0x18);
    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68) =
         *(float *)(param_1 + 0x44) * 40.0 + *(float *)(param_1 + 0x1c);
    if (((99 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
        (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 300)) ||
       ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1c2 &&
        (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1cc)))) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x28:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 0;
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
    }
    if (*(int *)(param_1 + 0x154) == 0) {
      FUN_0042c800(0);
      FUN_0042c840(1);
    }
    if ((90.0 < *(float *)(param_1 + 100)) || (*(float *)(param_1 + 100) < -90.0)) {
      *(undefined4 *)(param_1 + 0xe8) = 0xffffffff;
    }
    if (0x3c < *(int *)(param_1 + 0x154)) {
      *(undefined4 *)(param_1 + 0xec) = 1;
    }
    if (*(int *)(param_1 + 0xec) == 1) {
      FUN_0042c840(0);
      *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - 0.1;
      *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 0.1;
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) - 0.1;
      if (*(float *)(param_1 + 0x78) < 0.0 != (*(float *)(param_1 + 0x78) == 0.0)) {
        FUN_005f5e00();
        return;
      }
    }
    break;
  case 0x32:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x54) = 0;
    }
    if ((((99 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
         (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 300)) ||
        ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1c2 &&
         (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1cc)))) ||
       (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xf8) == 3)) {
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
    fVar7 = (float10)FUN_0042de80((*(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64) -
                                  *(float *)(param_1 + 0x18)) *
                                  (*(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64) -
                                  *(float *)(param_1 + 0x18)) + local_8);
    local_c = (float)fVar7;
    *(float *)(param_1 + 0x70) = (float)(fVar7 / (float10)105.0);
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
    fVar7 = (float10)FUN_00423580(*(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68) -
                                  *(float *)(param_1 + 0x1c),
                                  *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) -
                                  *(float *)(param_1 + 0x14));
    *(float *)(param_1 + 100) =
         (float)((fVar7 / (float10)3.1415927) * (float10)180.0 + (float10)-fVar1);
    fVar7 = (float10)FUN_0042de80(local_8);
    fVar7 = (float10)FUN_00423580(*(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64) -
                                  *(float *)(param_1 + 0x18),(float)fVar7);
    *(float *)(param_1 + 0x6c) = (float)((fVar7 / (float10)3.1415927) * (float10)180.0);
    break;
  case 0x3c:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0x78) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x74) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x70) = 0x3f000000;
      *(undefined4 *)(param_1 + 0x54) = 0;
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0xe8) = 0xff;
    }
    fVar7 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) << 2));
    *(float *)(param_1 + 0x70) = (float)(fVar7 * (float10)0.2 + (float10)*(float *)(param_1 + 0x70))
    ;
    fVar7 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) << 2));
    *(float *)(param_1 + 0x74) = (float)(fVar7 * (float10)0.2 + (float10)*(float *)(param_1 + 0x74))
    ;
    fVar7 = (float10)FUN_0065d050((float)(*(int *)(param_1 + 0x154) << 2));
    *(float *)(param_1 + 0x78) = (float)(fVar7 * (float10)0.2 + (float10)*(float *)(param_1 + 0x78))
    ;
    if ((0 < *(int *)(param_1 + 0x154)) &&
       (*(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + -0x14, *(int *)(param_1 + 0xe8) < 0))
    {
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (0xd < *(int *)(param_1 + 0x154)) {
      FUN_005f5e00();
      return;
    }
    FUN_005fafc0(*(undefined1 *)(param_1 + 0xe8),0xff,0xff,0xff);
    break;
  case 0x46:
    if (*(int *)(param_1 + 0x154) == 0) {
      *(undefined4 *)(param_1 + 0xe8) = 0;
      *(undefined4 *)(param_1 + 0xec) = 2;
      FUN_005f6db0(5,0,0,0);
      *(undefined4 *)(param_1 + 0x70) = 0x40000000;
      *(undefined4 *)(param_1 + 0x74) = 0x40000000;
      *(undefined4 *)(param_1 + 0x78) = 0x40000000;
    }
    if (*(int *)(param_1 + 0xec) == 2) {
      FUN_0042c840(1);
      *(undefined4 *)(param_1 + 0x54) = 0x42480000;
      FUN_0042db10(0,0x43340000);
      fVar7 = (float10)FUN_0042dac0(2);
      *(float *)(param_1 + 0x6c) = (float)fVar7;
      fVar7 = (float10)FUN_0042d980();
      fVar8 = (float10)FUN_0042da30();
      fVar9 = (float10)FUN_0042da30();
      if (fVar9 * (float10)(float)fVar8 + (float10)(float)fVar7 < (float10)10000.0) {
        FUN_005f5e00();
        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xf8) = 3;
        return;
      }
    }
    if (*(int *)(param_1 + 0x154) == 5) {
      FUN_0042c840(0);
    }
    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf60) =
         *(float *)(param_1 + 0x3c) * 40.0 + *(float *)(param_1 + 0x14);
    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf64) =
         *(float *)(param_1 + 0x40) * 40.0 + *(float *)(param_1 + 0x18);
    *(float *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xaf68) =
         *(float *)(param_1 + 0x44) * 40.0 + *(float *)(param_1 + 0x1c);
    if (((99 < *(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec)) &&
        (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) < 300)) ||
       ((*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1c2 &&
        (*(int *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 0xadec) != 0x1cc)))) {
      FUN_005f5e00();
      return;
    }
    break;
  case 0x5a:
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

