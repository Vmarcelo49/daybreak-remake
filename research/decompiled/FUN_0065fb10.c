// Function: FUN_0065fb10
// Address:  0x0065fb10
// Source:   batch_decompile (mass dump)
// Hash:     7581836c3529ced4


void __thiscall
FUN_0065fb10(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if (*(char *)(param_1 + 0x1d) != '\0') {
    local_c = param_2;
    local_10 = param_3;
    local_8 = 0;
    (**(code **)(*(int *)*param_1 + 0x20))(*param_1,&local_10,1,param_4,0,&local_8,param_5);
  }
  return;
}

