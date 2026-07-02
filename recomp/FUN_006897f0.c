// ============================================
// Address:  0x006897f0
// Original: FUN_006897f0
// Status:   unreviewed
// ============================================


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

