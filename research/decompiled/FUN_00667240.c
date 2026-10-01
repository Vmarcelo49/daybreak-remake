// Function: FUN_00667240
// Address:  0x00667240
// Source:   batch_decompile (mass dump)
// Hash:     7caf1e78441ae0a1


int FUN_00667240(void)

{
  undefined4 uVar1;
  undefined4 uStack_10;
  int local_c;
  
  std::allocator<char>::allocator<char>((allocator<char> *)&uStack_10);
  FUN_00425760();
  uStack_10 = 0x667261;
  uVar1 = FUN_00667360();
  *(undefined4 *)(local_c + 4) = uVar1;
  *(undefined4 *)(local_c + 8) = 0;
  return local_c;
}

