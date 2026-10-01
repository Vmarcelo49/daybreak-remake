// Function: FUN_00430670
// Address:  0x00430670
// Source:   batch_decompile (mass dump)
// Hash:     b1cb5cd34b2f8511


undefined4 __thiscall FUN_00430670(float *param_1,float *param_2)

{
  undefined4 local_c;
  
  if ((((*param_1 == *param_2) && (param_1[1] == param_2[1])) && (param_1[2] == param_2[2])) &&
     (param_1[3] == param_2[3])) {
    local_c = 0;
  }
  else {
    local_c = 1;
  }
  return local_c;
}

