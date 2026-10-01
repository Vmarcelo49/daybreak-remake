// Function: FUN_00660a10
// Address:  0x00660a10
// Source:   batch_decompile (mass dump)
// Hash:     4b59698332b08630


bool __fastcall FUN_00660a10(undefined4 *param_1)

{
  bool bVar1;
  BOOL BVar2;
  
  BVar2 = ImmGetOpenStatus((HIMC)*param_1);
  bVar1 = 0 < BVar2;
  if (((bool)DAT_006d7a00 != bVar1) && (!bVar1)) {
    _memset(param_1 + 2,0,0x400);
    _memset(param_1 + 0x202,0,0x100);
    *(undefined1 *)(param_1 + 0x283) = 0;
    *(undefined1 *)((int)param_1 + 0xa0d) = 0;
    *(undefined1 *)((int)param_1 + 0xa0e) = 0;
    param_1[0x284] = 0;
  }
  DAT_006d7a00 = bVar1;
  return bVar1;
}

