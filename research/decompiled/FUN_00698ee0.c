// Function: FUN_00698ee0
// Address:  0x00698ee0
// Source:   batch_decompile (mass dump)
// Hash:     735d24c12fc93fe2


int * __thiscall FUN_00698ee0(int *param_1,int param_2)

{
  int iVar1;
  int *local_c;
  
  iVar1 = (**(code **)(*param_1 + 0x18))();
  if ((iVar1 < 1) || (param_2 != 0)) {
    local_c = (int *)0x0;
  }
  else if (param_1 == (int *)0xffffff10) {
    local_c = (int *)0x0;
  }
  else {
    local_c = param_1 + 0x3e;
  }
  return local_c;
}

