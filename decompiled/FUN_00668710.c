// Function: FUN_00668710
// Address:  0x00668710
// Source:   batch_decompile (mass dump)
// Hash:     7a5e852e194479ff


int FUN_00668710(undefined4 *param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 local_c;
  int local_8;
  
  if (param_4 == 1) {
    local_c = 1;
    local_8 = param_2;
  }
  else if (param_4 == 2) {
    local_c = 0;
    local_8 = param_2 + param_1[3] + param_1[2];
  }
  else {
    if (param_4 != 0) {
      return -1;
    }
    local_c = 0;
    local_8 = param_2 + param_1[3];
  }
  iVar1 = FUN_006539b0(*param_1,local_8,local_c);
  return (iVar1 != -1) - 1;
}

