// Function: FUN_004356b0
// Address:  0x004356b0
// Source:   batch_decompile (mass dump)
// Hash:     bda332f879e6a76b


void __fastcall FUN_004356b0(int *param_1)

{
  if (param_1[6] != 0) {
    *(undefined1 *)((int)param_1 + 0x39) = 0;
  }
  if (*param_1 == 2) {
    if (param_1[6] == 0) {
      param_1[0x10] = param_1[0x10] + 1;
      if (param_1[2] / 2 <= param_1[0x10]) {
        param_1[0x10] = 0;
        param_1[0xf] = param_1[0xf] + param_1[5];
      }
      if (param_1[3] <= param_1[0xf]) {
        param_1[6] = param_1[2];
        param_1[0x10] = param_1[4];
        *(undefined1 *)((int)param_1 + 0x39) = 1;
      }
    }
    else if ((param_1[6] < param_1[2]) &&
            (param_1[0xf] = param_1[0xf] + param_1[5], param_1[3] <= param_1[0xf])) {
      param_1[6] = param_1[6] + 1;
      param_1[0xf] = 0;
    }
    param_1[0xc] = param_1[6] * param_1[3] + param_1[0xf];
  }
  else if (*param_1 == 1) {
    if ((param_1[6] < param_1[2]) &&
       (param_1[0xf] = param_1[0xf] + param_1[5], param_1[3] <= param_1[0xf])) {
      param_1[6] = param_1[6] + 1;
      param_1[0xf] = 0;
    }
    param_1[0xc] = param_1[6] * param_1[3] + param_1[0xf];
  }
  else {
    if ((param_1[6] == 0) && (param_1[0xf] = param_1[0xf] + param_1[5], param_1[3] <= param_1[0xf]))
    {
      param_1[6] = param_1[2];
      param_1[0x10] = param_1[4];
      *(undefined1 *)((int)param_1 + 0x39) = 1;
    }
    param_1[0xc] = param_1[6];
  }
  if (param_1[0x10] < param_1[4]) {
    param_1[0x10] = param_1[0x10] + 1;
  }
  if ((char)param_1[0xe] == '\0') {
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[10] = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0xe) = 0;
  }
  return;
}

