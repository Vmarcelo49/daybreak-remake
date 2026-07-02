// Function: FUN_00691b10
// Address:  0x00691b10
// Source:   batch_decompile (mass dump)
// Hash:     86ac50be12c73db6


uint FUN_00691b10(uint param_1,uint param_2)

{
  if ((param_2 < 0x80000000) || ((-2 < (int)param_2 && (0xe2329aff < param_1)))) {
    if ((-1 < (int)param_2) && ((0 < (int)param_2 || (500000000 < param_1)))) {
      param_1 = 500000000;
    }
  }
  else {
    param_1 = 0xe2329b00;
  }
  return param_1;
}

