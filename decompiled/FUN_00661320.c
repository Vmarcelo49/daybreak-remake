// Function: FUN_00661320
// Address:  0x00661320
// Source:   batch_decompile (mass dump)
// Hash:     b5227cab03f4d19d


bool __fastcall FUN_00661320(int param_1)

{
  bool bVar1;
  
  bVar1 = *(char *)(param_1 + 0xa0c) != '\0';
  if (bVar1) {
    *(undefined1 *)(param_1 + 0xa0c) = 0;
  }
  return bVar1;
}

