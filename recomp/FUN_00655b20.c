// ============================================
// Address:  0x00655b20
// Original: FUN_00655b20
// Status:   unreviewed
// ============================================


void __thiscall
FUN_00655b20(undefined4 *param_1,undefined4 param_2,int param_3,int param_4,int param_5,int param_6,
            int param_7,int param_8)

{
  uint local_c;
  uint local_8;
  
  *param_1 = param_2;
  param_1[0x1d] = (float)param_5;
  param_1[0x1e] = (float)param_6;
  param_1[0x1f] = (float)param_7;
  param_1[0x20] = (float)param_8;
  FUN_00656380(*param_1,&local_8,&local_c);
  param_1[0x1a] = 0xffffffff;
  param_1[0x13] = 0xffffffff;
  param_1[0xc] = 0xffffffff;
  param_1[5] = 0xffffffff;
  param_1[6] = (float)param_3 / (float)local_8;
  param_1[7] = (float)param_4 / (float)local_c;
  param_1[0xd] = (float)(param_3 + param_5) / (float)local_8;
  param_1[0xe] = (float)param_4 / (float)local_c;
  param_1[0x14] = (float)param_3 / (float)local_8;
  param_1[0x15] = (float)(param_4 + param_6) / (float)local_c;
  param_1[0x1b] = (float)(param_3 + param_5) / (float)local_8;
  param_1[0x1c] = (float)(param_4 + param_6) / (float)local_c;
  param_1[0x26] = (float)param_1[0x1b] - (float)param_1[6];
  param_1[0x27] = (float)param_1[0x1c] - (float)param_1[7];
  param_1[3] = 0;
  param_1[4] = 0x3f800000;
  param_1[10] = 0;
  param_1[0xb] = 0x3f800000;
  param_1[0x11] = 0;
  param_1[0x12] = 0x3f800000;
  param_1[0x18] = 0;
  param_1[0x19] = 0x3f800000;
  param_1[0x24] = 0;
  param_1[0x23] = 0;
  param_1[0x22] = 0x3f800000;
  param_1[0x21] = 0x3f800000;
  param_1[0x25] = 0;
  return;
}

