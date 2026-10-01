// Function: FUN_00687010
// Address:  0x00687010
// Source:   batch_decompile (mass dump)
// Hash:     dd205357ac1ad79e


undefined4 FUN_00687010(short *param_1,undefined4 *param_2,int param_3)

{
  undefined4 *puVar1;
  LPVOID pvVar2;
  
  *param_2 = 0x73647561;
  param_2[1] = 0x100000;
  param_2[2] = 0xaa000080;
  param_2[3] = 0x719b3800;
  if (*param_1 == -2) {
    param_2[4] = *(undefined4 *)(param_1 + 0xc);
    param_2[5] = *(undefined4 *)(param_1 + 0xe);
    param_2[6] = *(undefined4 *)(param_1 + 0x10);
    param_2[7] = *(undefined4 *)(param_1 + 0x12);
  }
  else {
    puVar1 = (undefined4 *)FUN_006871f0(*param_1);
    param_2[4] = *puVar1;
    param_2[5] = puVar1[1];
    param_2[6] = puVar1[2];
    param_2[7] = puVar1[3];
  }
  param_2[0xb] = 0x5589f81;
  param_2[0xc] = 0x11cec356;
  param_2[0xd] = 0xaa0001bf;
  param_2[0xe] = 0x5a595500;
  param_2[8] = 1;
  param_2[9] = 0;
  param_2[10] = (uint)(ushort)param_1[6];
  param_2[0xf] = 0;
  if (param_3 != 0) {
    if (*param_1 == 1) {
      param_2[0x10] = 0x12;
    }
    else {
      param_2[0x10] = (ushort)param_1[8] + 0x12;
    }
    pvVar2 = CoTaskMemAlloc(param_2[0x10]);
    param_2[0x11] = pvVar2;
    if (param_2[0x11] == 0) {
      return 0x8007000e;
    }
    if (*param_1 == 1) {
      _memcpy((void *)param_2[0x11],param_1,0x10);
      *(undefined2 *)(param_2[0x11] + 0x10) = 0;
    }
    else {
      _memcpy((void *)param_2[0x11],param_1,param_2[0x10]);
    }
  }
  return 0;
}

