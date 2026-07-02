// Function: FUN_005f7730
// Address:  0x005f7730
// Source:   batch_decompile (mass dump)
// Hash:     16a07892dedfee9a


undefined4 __thiscall FUN_005f7730(float *param_1,float *param_2)

{
  undefined4 local_c;
  
  if (((*param_1 == *param_2) && (param_1[1] == param_2[1])) && (param_1[2] == param_2[2])) {
    local_c = 0;
  }
  else {
    local_c = 1;
  }
  return local_c;
}

