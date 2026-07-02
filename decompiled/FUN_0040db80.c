// Function: FUN_0040db80
// Address:  0x0040db80
// Source:   batch_decompile (mass dump)
// Hash:     74ba991bca2119d0


undefined4 * __fastcall FUN_0040db80(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_006a19f4;
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 5));
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 8));
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 0xf));
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 0x12));
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 0x1c));
  _vector_constructor_iterator_(param_1 + 0x29,0x10,2,std::allocator<char>::allocator<char>);
  _vector_constructor_iterator_(param_1 + 0x31,0x10,2,std::allocator<char>::allocator<char>);
  return param_1;
}

