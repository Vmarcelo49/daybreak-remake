// ============================================
// Address:  0x0068b470
// Original: FUN_0068b470
// Status:   unreviewed
// ============================================


undefined4 FUN_0068b470(int param_1,uint param_2,uint *param_3)

{
  int local_8;
  
  local_8 = 0;
  if (3 < param_2) {
    if (param_3 == (uint *)0x0) {
      return 0x80004003;
    }
    if (*param_3 < param_2) {
      param_2 = *param_3;
    }
    if ((0x30 < param_2) || (0x30 < *param_3)) {
      return 0x80070057;
    }
    if (0xb < param_2) {
      if ((param_3[2] & 0xfffffe20) != 0) {
        return 0x80070057;
      }
      if ((((param_3[2] & 0x10) != 0) && ((*(uint *)(param_1 + 4) & 0x10) == 0)) && (param_2 < 0x20)
         ) {
        return 0x80070057;
      }
    }
    if (((0x2b < param_2) && (param_3[10] != 0)) && (param_3[10] != *(uint *)(param_1 + 0xc))) {
      return 0x80070057;
    }
    if (((0x2f < param_2) && (param_3[0xb] != 0)) && (param_3[0xb] != *(uint *)(param_1 + 0x14))) {
      return 0x80070057;
    }
    if (((0x2f < param_2) && (0xf < param_2)) && ((int)param_3[0xb] < (int)param_3[3])) {
      return 0x80070057;
    }
    if ((0x27 < param_2) && ((param_3[2] & 8) != 0)) {
      if (param_3[9] == 0) {
        return 0x80004003;
      }
      local_8 = FUN_00686ed0(param_3[9]);
      if (local_8 == 0) {
        return 0x8007000e;
      }
    }
    if (0x23 < param_2) {
      *(uint *)(param_1 + 0x40) = param_3[8];
    }
    if (param_2 < 0xc) {
      if (7 < param_2) {
        *(uint *)(param_1 + 8) = param_3[1];
      }
    }
    else {
      *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) & 0x20 | param_3[2];
      *(uint *)(param_1 + 8) = param_3[1];
    }
    if (0xf < param_2) {
      *(uint *)(param_1 + 0x10) = param_3[3];
    }
    if (0x1f < param_2) {
      *(uint *)(param_1 + 0x28) = param_3[6];
      *(uint *)(param_1 + 0x2c) = param_3[7];
    }
    if (0x17 < param_2) {
      *(uint *)(param_1 + 0x20) = param_3[4];
      *(uint *)(param_1 + 0x24) = param_3[5];
    }
    if ((0x27 < param_2) && ((param_3[2] & 8) != 0)) {
      if (*(int *)(param_1 + 0x3c) != 0) {
        FUN_00686ea0(*(undefined4 *)(param_1 + 0x3c));
      }
      *(int *)(param_1 + 0x3c) = local_8;
    }
    if (*(int *)(param_1 + 0x3c) == 0) {
      *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) & 0xfffffff7;
    }
    else {
      *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | 8;
    }
  }
  return 0;
}

