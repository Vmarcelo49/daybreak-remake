// ============================================
// Address:  0x00640ca0
// Original: FUN_00640ca0
// Status:   unreviewed
// ============================================


void __thiscall FUN_00640ca0(int param_1,int param_2)

{
  int local_c;
  short *local_8;
  
  *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_2 + 1);
  local_8 = (short *)(param_2 + 5);
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    *(float *)(param_1 + 0xc + local_c * 4) = (float)(int)*local_8;
    *(float *)(param_1 + 0x1c + local_c * 4) = (float)(int)local_8[1];
    *(float *)(param_1 + 0x2c + local_c * 4) = (float)(int)local_8[2];
    *(float *)(param_1 + 0x3c + local_c * 4) = (float)(int)local_8[3] / 100.0;
    *(float *)(param_1 + 0x4c + local_c * 4) = (float)(int)local_8[4] / 100.0;
    *(uint *)(param_1 + 0x5c + local_c * 4) = (uint)*(byte *)(local_8 + 5);
    *(int *)(param_1 + 0x6c + local_c * 4) = (int)*(short *)((int)local_8 + 0xb);
    *(uint *)(param_1 + 0x7c + local_c * 4) = (uint)*(byte *)((int)local_8 + 0xd);
    *(int *)(param_1 + 0x8c + local_c * 4) = (int)local_8[7];
    *(uint *)(param_1 + 0x9c + local_c * 4) = (uint)*(byte *)(local_8 + 8);
    *(int *)(param_1 + 0xac + local_c * 4) = (int)*(short *)((int)local_8 + 0x11);
    *(uint *)(param_1 + 0xbc + local_c * 4) = (uint)*(byte *)((int)local_8 + 0x13);
    *(int *)(param_1 + 0xcc + local_c * 4) = (int)local_8[10];
    local_8 = local_8 + 0xb;
  }
  return;
}

