// ============================================
// Address:  0x00418c30
// Original: FUN_00418c30
// Status:   unreviewed
// ============================================


int __thiscall FUN_00418c30(int param_1,undefined1 *param_2)

{
  int local_c;
  undefined1 *local_8;
  
  *param_2 = 0x12;
  param_2[1] = *(undefined1 *)(param_1 + 8);
  local_8 = param_2 + 2;
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    *local_8 = *(undefined1 *)(param_1 + 0xc + local_c * 4);
    local_8[1] = *(undefined1 *)(param_1 + 0x1c + local_c * 4);
    local_8[2] = *(undefined1 *)(param_1 + 0x2c + local_c * 4);
    local_8[3] = *(undefined1 *)(param_1 + 0x3c + local_c * 4);
    local_8[4] = *(undefined1 *)(param_1 + 0x4c + local_c * 4);
    local_8[5] = *(undefined1 *)(param_1 + 0x5c + local_c * 4);
    local_8[6] = *(undefined1 *)(param_1 + local_c + 0x6c);
    local_8[7] = *(undefined1 *)(param_1 + 0x70 + local_c * 4);
    local_8[8] = *(undefined1 *)(param_1 + 0x80 + local_c * 4);
    local_8[9] = *(undefined1 *)(param_1 + 0x90 + local_c * 4);
    local_8[10] = *(undefined1 *)(param_1 + 0xa0 + local_c * 4);
    local_8[0xb] = *(undefined1 *)(param_1 + 0xb0 + local_c * 4);
    local_8[0xc] = *(undefined1 *)(param_1 + 0xc0 + local_c * 4);
    local_8 = local_8 + 0xd;
  }
  return (int)local_8 - (int)param_2;
}

