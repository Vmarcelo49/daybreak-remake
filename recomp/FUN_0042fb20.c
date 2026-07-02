// ============================================
// Address:  0x0042fb20
// Original: FUN_0042fb20
// Status:   unreviewed
// ============================================


int FUN_0042fb20(void)

{
  undefined4 uVar1;
  undefined4 uStack_10;
  int local_c;
  
  std::allocator<char>::allocator<char>((allocator<char> *)&uStack_10);
  FUN_00425760();
  uStack_10 = 0x42fb41;
  uVar1 = FUN_0042fb60();
  *(undefined4 *)(local_c + 4) = uVar1;
  *(undefined4 *)(local_c + 8) = 0;
  return local_c;
}

