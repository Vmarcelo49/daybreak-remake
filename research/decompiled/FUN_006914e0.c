// Function: FUN_006914e0
// Address:  0x006914e0
// Source:   batch_decompile (mass dump)
// Hash:     d76ba4beb8300a3a


undefined4 FUN_006914e0(int param_1,int *param_2)

{
  undefined4 uVar1;
  DWORD DVar2;
  int iVar3;
  undefined4 local_c;
  
  if (param_2 == (int *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    FUN_0068d950(param_1 + -100);
    if (*(int *)(param_1 + -0x7c) == 0) {
      local_c = *(int *)(param_1 + 0x78);
    }
    else {
      DVar2 = timeGetTime();
      local_c = DVar2 - *(int *)(param_1 + 0x78);
    }
    if (local_c < 1) {
      *param_2 = 0;
    }
    else {
      iVar3 = MulDiv(100000,*(int *)(param_1 + 0x44),local_c);
      *param_2 = iVar3;
    }
    FUN_0068d9a0();
    uVar1 = 0;
  }
  return uVar1;
}

