// Function: FUN_0042fce0
// Address:  0x0042fce0
// Source:   batch_decompile (mass dump)
// Hash:     97ec0d70a9b33a4b


undefined4 * __fastcall FUN_0042fce0(undefined4 *param_1)

{
  int local_8;
  
  *param_1 = &PTR_FUN_006a2574;
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 2));
  _vector_constructor_iterator_(param_1 + 6,0x10,2,std::allocator<char>::allocator<char>);
  FUN_00425ac0();
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 0x12));
  _vector_constructor_iterator_(param_1 + 0x22,0x10,0xd,std::allocator<char>::allocator<char>);
  _vector_constructor_iterator_(param_1 + 0x56,0x10,0x2f,std::allocator<char>::allocator<char>);
  _vector_constructor_iterator_(param_1 + 0x112,0x1c,0x2f,FUN_0068d8d0);
  param_1[0x10] = 0;
  param_1[0x25b] = 0;
  param_1[1] = 0;
  *(undefined1 *)(param_1 + 0xe) = 0;
  param_1[0xf] = 0;
  param_1[0x117] = 0;
  param_1[0x118] = 0;
  param_1[0x116] = 0xffffffff;
  for (local_8 = 0; local_8 < 0x29; local_8 = local_8 + 1) {
    param_1[(local_8 + 1) * 7 + 0x117] = 0x3f800000;
    param_1[(local_8 + 1) * 7 + 0x116] = 0xffffffff;
  }
  return param_1;
}

