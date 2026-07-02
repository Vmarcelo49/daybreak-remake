// Function: FUN_0068c430
// Address:  0x0068c430
// Source:   batch_decompile (mass dump)
// Hash:     6b328f2b9e919483


undefined4 __thiscall FUN_0068c430(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 local_10;
  
  if ((*(int *)(param_1 + 0xd4) == 0) || (*(int *)(param_1 + 0xd0) == 0)) {
    uVar1 = 0x80004005;
  }
  else {
    if (param_1 == 0) {
      local_10 = 0;
    }
    else {
      local_10 = param_1 + 0xc;
    }
    uVar1 = (**(code **)(**(int **)(param_1 + 0xd4) + 0xc))
                      (*(undefined4 *)(param_1 + 0xd4),local_10,0,param_2,0,
                       *(undefined4 *)(param_1 + 0xd0),2);
  }
  return uVar1;
}

