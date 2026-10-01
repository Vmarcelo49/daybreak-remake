// Function: FUN_00690900
// Address:  0x00690900
// Source:   batch_decompile (mass dump)
// Hash:     f44bd5c4cd810922


undefined4 __fastcall FUN_00690900(int param_1)

{
  DWORD DVar1;
  
  DVar1 = timeGetTime();
  *(DWORD *)(param_1 + 0x158) = DVar1 - *(int *)(param_1 + 0x158);
  return 0;
}

