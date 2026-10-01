// Function: FUN_006883f0
// Address:  0x006883f0
// Source:   batch_decompile (mass dump)
// Hash:     dbfbb2addf13078d


undefined4 __thiscall FUN_006883f0(int param_1,int param_2,undefined4 param_3,int param_4)

{
  int *piVar1;
  undefined4 uVar2;
  undefined4 local_10;
  
  piVar1 = *(int **)(param_1 + 0x44);
  if (piVar1 == (int *)0x0) {
    uVar2 = 0x80004001;
  }
  else {
    if (param_2 == 1) {
      if (param_1 == 0) {
        local_10 = 0;
      }
      else {
        local_10 = param_1 + 0xc;
      }
      param_4 = local_10;
    }
    uVar2 = (**(code **)(*piVar1 + 0xc))(piVar1,param_2,param_3,param_4);
  }
  return uVar2;
}

