// Function: FUN_00691640
// Address:  0x00691640
// Source:   batch_decompile (mass dump)
// Hash:     cf9ba07add9a045f


int FUN_00691640(int param_1)

{
  undefined4 local_8;
  
  local_8 = 1;
  if (param_1 < 0x40000001) {
    for (; local_8 * local_8 < param_1; local_8 = local_8 << 1) {
    }
    if (param_1 == 0) {
      local_8 = 0;
    }
    else {
      local_8 = (local_8 * local_8 + param_1) / (local_8 << 1);
      if (-1 < local_8) {
        local_8 = (local_8 * local_8 + param_1) / (local_8 << 1);
      }
      if (-1 < local_8) {
        local_8 = (local_8 * local_8 + param_1) / (local_8 << 1);
      }
    }
  }
  else {
    local_8 = 0x8000;
  }
  return local_8;
}

