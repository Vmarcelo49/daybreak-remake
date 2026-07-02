// Function: FUN_00670308
// Address:  0x00670308
// Source:   batch_decompile (mass dump)
// Hash:     b426b37266096910


uint FUN_00670308(undefined4 param_1,uint param_2)

{
  if ((param_2 & 0x7ff00000) != 0x7ff00000) {
    return param_2 & 0x7ff00000;
  }
  return param_2;
}

