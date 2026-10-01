// Function: FUN_00646ee0
// Address:  0x00646ee0
// Source:   batch_decompile (mass dump)
// Hash:     435cb65e9376083e


void __thiscall FUN_00646ee0(int param_1,int param_2)

{
  undefined4 local_c;
  
  if (param_2 < 0x3ff) {
    local_c = param_2;
  }
  else {
    local_c = 0x3ff;
  }
  *(int *)(param_1 + 0xa08) = local_c;
  return;
}

