// ============================================
// Address:  0x00645250
// Original: FUN_00645250
// Status:   unreviewed
// ============================================


void __thiscall FUN_00645250(undefined4 *param_1,float param_2,float param_3)

{
  char cVar1;
  float fVar2;
  float10 fVar3;
  float10 fVar4;
  int local_1c;
  
  fVar2 = (float)*(int *)param_1[0x28] / (float)(int)param_1[0x29];
  cVar1 = *(char *)(param_1 + 0x2a);
  if (cVar1 == '\0') {
    param_1[1] = (param_2 - (float)param_1[0x1f] * (float)param_1[0x21]) - 0.5;
    param_1[2] = (param_3 - (float)param_1[0x20] * (float)param_1[0x22]) - 0.5;
    param_1[8] = fVar2 * (float)param_1[0x1d] * (float)param_1[0x21] + (float)param_1[1];
    param_1[9] = param_1[2];
    param_1[0xf] = param_1[1];
    param_1[0x10] = (float)param_1[0x1e] * (float)param_1[0x22] + (float)param_1[2];
    param_1[0x16] = param_1[8];
    param_1[0x17] = param_1[0x10];
    param_1[0xd] = fVar2 * (float)param_1[0x26] + (float)param_1[6];
    param_1[0x1b] = param_1[0xd];
  }
  else if (cVar1 == '\x01') {
    param_1[1] = param_2 - 0.5;
    param_1[2] = ((1.0 - fVar2) * (float)param_1[0x1e] * (float)param_1[0x22] + param_3) - 0.5;
    param_1[8] = ((float)param_1[0x1d] * (float)param_1[0x21] + param_2) - 0.5;
    param_1[9] = ((1.0 - fVar2) * (float)param_1[0x1e] * (float)param_1[0x22] + param_3) - 0.5;
    param_1[0xf] = param_2 - 0.5;
    param_1[0x10] = ((float)param_1[0x1e] * (float)param_1[0x22] + param_3) - 0.5;
    param_1[0x16] = ((float)param_1[0x1d] * (float)param_1[0x21] + param_2) - 0.5;
    param_1[0x17] = ((float)param_1[0x1e] * (float)param_1[0x22] + param_3) - 0.5;
    param_1[0xe] = (float)param_1[0x15] - fVar2 * (float)param_1[0x27];
    param_1[7] = param_1[0xe];
  }
  else if (cVar1 == '\x02') {
    param_1[8] = (((float)param_1[0x1d] - (float)param_1[0x1f]) * (float)param_1[0x21] + param_2) -
                 0.5;
    param_1[9] = (param_3 - (float)param_1[0x20] * (float)param_1[0x22]) - 0.5;
    param_1[1] = (float)param_1[8] - fVar2 * (float)param_1[0x1d] * (float)param_1[0x21];
    param_1[2] = param_1[9];
    param_1[0x16] = param_1[8];
    param_1[0x17] = (float)param_1[0x1e] * (float)param_1[0x22] + (float)param_1[9];
    param_1[0xf] = param_1[1];
    param_1[0x10] = param_1[0x17];
    param_1[6] = (float)param_1[0xd] - fVar2 * (float)param_1[0x26];
    param_1[0x14] = param_1[6];
  }
  if ((float)param_1[0x25] != 0.0) {
    fVar3 = (float10)FUN_0065d050(param_1[0x25]);
    fVar4 = (float10)FUN_0065d010(param_1[0x25]);
    param_2 = (float)param_1[0x23] * (float)param_1[0x21] + param_2;
    param_3 = (float)param_1[0x24] * (float)param_1[0x22] + param_3;
    for (local_1c = 0; local_1c < 4; local_1c = local_1c + 1) {
      fVar2 = (float)param_1[local_1c * 7 + 1];
      param_1[local_1c * 7 + 1] =
           ((fVar2 - param_2) * (float)fVar3 + param_2) -
           ((float)param_1[local_1c * 7 + 2] - param_3) * (float)fVar4;
      param_1[local_1c * 7 + 2] =
           ((float)param_1[local_1c * 7 + 2] - param_3) * (float)fVar3 +
           (fVar2 - param_2) * (float)fVar4 + param_3;
    }
  }
  FUN_00656300(*param_1);
  (**(code **)(*DAT_006d16f8 + 0x164))(DAT_006d16f8,0x144);
  FUN_006517e0(5,2,param_1 + 1,0x1c);
  return;
}

