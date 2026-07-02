// ============================================
// Address:  0x00653760
// Original: FUN_00653760
// Status:   unreviewed
// ============================================


void __thiscall FUN_00653760(undefined4 *param_1,LPVOID param_2,DWORD param_3)

{
  if (param_1[0x1f] == 0) {
    ReadFile((HANDLE)*param_1,param_2,param_3,param_1 + 1,(LPOVERLAPPED)0x0);
  }
  else {
    FUN_00663030(param_2,param_3);
  }
  return;
}

