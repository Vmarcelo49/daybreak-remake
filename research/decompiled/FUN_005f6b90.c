// Function: FUN_005f6b90
// Address:  0x005f6b90
// Source:   batch_decompile (mass dump)
// Hash:     ac076e7191355580


uint __fastcall FUN_005f6b90(uint param_1)

{
  float fVar1;
  float fVar2;
  float10 fVar3;
  int iVar4;
  undefined4 uVar5;
  ushort uVar6;
  float10 fVar7;
  float local_20;
  float local_1c;
  float local_18;
  float local_10;
  float local_c;
  float local_8;
  
  if (*(int *)(param_1 + 4) == 0) {
    param_1 = param_1 & 0xffffff00;
  }
  else {
    if (*(char *)(param_1 + 0x148) != '\0') {
      fVar1 = *(float *)(param_1 + 0x54);
      if (fVar1 == 0.0) {
        return (uint)(ushort)((ushort)(fVar1 < 0.0) << 8 | (ushort)NAN(fVar1) << 10 |
                             (ushort)(fVar1 == 0.0) << 0xe);
      }
    }
    iVar4 = FUN_005f7730(param_1 + 0x130);
    if (iVar4 != 0) {
      *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x3c);
      *(undefined4 *)(param_1 + 0x134) = *(undefined4 *)(param_1 + 0x40);
      *(undefined4 *)(param_1 + 0x138) = *(undefined4 *)(param_1 + 0x44);
      DAT_006c78a4 = 10000.0;
      local_10 = 10000.0;
      iVar4 = FUN_005f7790(1);
      if (iVar4 != 0) {
        iVar4 = param_1 + 0x3c;
        FUN_005f7790(1);
        uVar5 = FUN_0064ecb0(iVar4);
        FUN_0042d2c0(uVar5,iVar4);
        local_10 = DAT_006c78a4;
      }
      DAT_006c78a4 = 10000.0;
      local_c = 10000.0;
      iVar4 = FUN_005f7790(5);
      if (iVar4 != 0) {
        iVar4 = param_1 + 0x3c;
        FUN_005f7790(5);
        uVar5 = FUN_0064ecb0(iVar4);
        FUN_0042d2c0(uVar5,iVar4);
        local_c = DAT_006c78a4;
      }
      DAT_006c78a4 = 10000.0;
      local_8 = 10000.0;
      iVar4 = FUN_005f7790(6);
      if (iVar4 != 0) {
        iVar4 = param_1 + 0x3c;
        FUN_005f7790(6);
        uVar5 = FUN_0064ecb0(iVar4);
        FUN_0042d2c0(uVar5,iVar4);
        local_8 = DAT_006c78a4;
      }
      if (local_c <= local_10) {
        local_18 = local_c;
      }
      else {
        local_18 = local_10;
      }
      if (local_8 <= local_18) {
        local_20 = local_8;
      }
      else {
        if (local_c <= local_10) {
          local_1c = local_c;
        }
        else {
          local_1c = local_10;
        }
        local_20 = local_1c;
      }
      *(float *)(param_1 + 0x80) = local_20;
    }
    if (*(char *)(param_1 + 0x148) == '\0') {
      fVar7 = (float10)FUN_0042df50(param_1 + 0x3c);
      fVar3 = (float10)*(float *)(param_1 + 0x80);
      uVar6 = (ushort)(fVar7 < fVar3) << 8 | (ushort)(NAN(fVar7) || NAN(fVar3)) << 10 |
              (ushort)(fVar7 == fVar3) << 0xe;
      if (fVar7 >= fVar3) {
        return CONCAT31((uint3)(byte)(uVar6 >> 8),1);
      }
    }
    else {
      fVar1 = *(float *)(param_1 + 0x80);
      fVar2 = *(float *)(param_1 + 0x54);
      uVar6 = (ushort)(fVar1 < fVar2) << 8 | (ushort)(NAN(fVar1) || NAN(fVar2)) << 10 |
              (ushort)(fVar1 == fVar2) << 0xe;
      if (fVar1 < fVar2 != (fVar1 == fVar2)) {
        return CONCAT31((uint3)(byte)(uVar6 >> 8),1);
      }
    }
    param_1 = (uint)uVar6;
  }
  return param_1;
}

