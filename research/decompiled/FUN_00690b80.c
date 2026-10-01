// Function: FUN_00690b80
// Address:  0x00690b80
// Source:   batch_decompile (mass dump)
// Hash:     5ecb1c46f5bd1bee


void __fastcall FUN_00690b80(int *param_1)

{
  DWORD DVar1;
  
  (**(code **)(*param_1 + 0xb4))(param_1[0x54],param_1[0x55]);
  DVar1 = timeGetTime();
  param_1[0x3f] = DVar1;
  return;
}

