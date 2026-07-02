// ============================================
// Address:  0x00690b80
// Original: FUN_00690b80
// Status:   unreviewed
// ============================================


void __fastcall FUN_00690b80(int *param_1)

{
  DWORD DVar1;
  
  (**(code **)(*param_1 + 0xb4))(param_1[0x54],param_1[0x55]);
  DVar1 = timeGetTime();
  param_1[0x3f] = DVar1;
  return;
}

