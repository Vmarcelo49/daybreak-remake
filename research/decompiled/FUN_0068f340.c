// Function: FUN_0068f340
// Address:  0x0068f340
// Source:   batch_decompile (mass dump)
// Hash:     493edfe25f95193b


undefined4 __thiscall FUN_0068f340(int *param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 1;
  }
  else if (param_1[0x19] == 0) {
    uVar1 = 1;
  }
  else {
    (**(code **)(*param_1 + 0x38))(param_2);
    (**(code **)(*param_1 + 0xac))(param_2);
    (**(code **)(*param_1 + 0x3c))(param_2);
    uVar1 = 0;
  }
  return uVar1;
}

