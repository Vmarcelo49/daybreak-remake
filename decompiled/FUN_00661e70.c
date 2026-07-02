// Function: FUN_00661e70
// Address:  0x00661e70
// Source:   batch_decompile (mass dump)
// Hash:     9a72cc5771fe1b9e


allocator<char> * __thiscall FUN_00661e70(allocator<char> *param_1,undefined4 param_2)

{
  std::allocator<char>::allocator<char>(param_1);
  *(undefined ***)param_1 = &PTR_FUN_006ab0e8;
  *(undefined4 *)(param_1 + 4) = param_2;
  return param_1;
}

