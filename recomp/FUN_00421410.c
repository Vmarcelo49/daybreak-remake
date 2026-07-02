// ============================================
// Address:  0x00421410
// Original: FUN_00421410
// Status:   unreviewed
// ============================================


int __thiscall FUN_00421410(int *param_1,int param_2,int param_3)

{
  float fVar1;
  char cVar2;
  uint3 uVar4;
  int iVar3;
  int local_c;
  int local_8;
  
  FUN_0065d670();
  cVar2 = (**(code **)(*param_1 + 0x20))(param_1[param_2 + 0x2b83],param_3);
  if (cVar2 == '\0') {
    param_1[param_2 + 0x2b85] = 0;
  }
  else {
    param_1[param_2 + 0x2b85] = *(int *)(param_1[param_2 + 0x2b79] + 0x1c);
  }
  param_1[param_2 + 0x2b83] = param_3;
  param_1[param_2 + 0x2b79] = (int)(param_1 + param_3 * 0xe + 0x1d78);
  param_1[param_3 * 0xe + param_2 + 0x1d79] = 0;
  FUN_0064ebc0(param_2,param_3,param_1[param_3 * 0xe + param_2 + 0x1d79]);
  if (param_1[param_2 + 0x2b85] == 0) {
    for (local_8 = 0; local_8 < 0x100; local_8 = local_8 + 1) {
      param_1[local_8 * 0xe + param_2 + 0x1d7b] = 0;
      param_1[local_8 * 0xe + param_2 + 0x1d7d] = 0;
    }
    param_1[param_3 * 0xe + param_2 + 0x1d7b] = 0x3f800000;
    param_1[param_3 * 0xe + param_2 + 0x1d7d] = 0x3f800000;
    param_1[param_2 + 0x2b85] = param_1[param_2 + 0x2b85] + -1;
  }
  else {
    for (local_c = 0; local_c < 0x100; local_c = local_c + 1) {
      param_1[local_c * 0xe + param_2 + 0x1d7d] = param_1[local_c * 0xe + param_2 + 0x1d7b];
    }
  }
  FUN_0065d6a0();
  fVar1 = (float)param_1[param_3 * 0xe + 0x1d78] -
          (float)param_1[param_3 * 0xe + param_2 + 0x1d79] / 0.016;
  uVar4 = (uint3)(CONCAT22((short)((uint)param_2 >> 0x10),
                           (ushort)(fVar1 < 1.0) << 8 | (ushort)NAN(fVar1) << 10 |
                           (ushort)(fVar1 == 1.0) << 0xe) >> 8);
  if (fVar1 < 1.0 == (fVar1 == 1.0)) {
    iVar3 = (uint)uVar4 << 8;
  }
  else {
    iVar3 = CONCAT31(uVar4,1);
  }
  return iVar3;
}

