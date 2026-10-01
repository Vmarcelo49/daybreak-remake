// Function: FUN_006897f0
// Address:  0x006897f0
// Source:   batch_decompile (mass dump)
// Hash:     d1e5573a169c0fe3


undefined4 __thiscall FUN_006897f0(int param_1,int *param_2)

{
  undefined4 uVar1;
  int local_8;
  
  (**(code **)(*param_2 + 0x24))(param_2,&local_8);
  if (local_8 == *(int *)(param_1 + 0x1c)) {
    uVar1 = 0x80040208;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

