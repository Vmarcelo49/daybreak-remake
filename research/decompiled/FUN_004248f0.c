// Function: FUN_004248f0
// Address:  0x004248f0
// Source:   batch_decompile (mass dump)
// Hash:     43f653cdf627562b


int FUN_004248f0(void)

{
  allocator<char> aaStack_10 [4];
  int local_c;
  
  std::allocator<char>::allocator<char>(aaStack_10);
  FUN_00424d60();
  *(undefined4 *)(local_c + 4) = 0;
  *(undefined4 *)(local_c + 8) = 0;
  *(undefined4 *)(local_c + 0xc) = 0;
  *(undefined4 *)(local_c + 0x10) = 0;
  return local_c;
}

