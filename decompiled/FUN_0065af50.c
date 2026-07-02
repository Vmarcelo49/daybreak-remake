// Function: FUN_0065af50
// Address:  0x0065af50
// Source:   batch_decompile (mass dump)
// Hash:     a7f3b2f0abc6ede7


void __fastcall FUN_0065af50(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0069f01b;
  local_10 = ExceptionList;
  local_8 = 1;
  ExceptionList = &local_10;
  std::ctype<char>::~ctype<char>((ctype<char> *)(param_1 + 0x3c));
  local_8 = local_8 & 0xffffff00;
  FUN_006679d0();
  local_8 = 0xffffffff;
  FUN_0065a4c0();
  ExceptionList = local_10;
  return;
}

