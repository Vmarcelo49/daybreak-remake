// ============================================
// Address:  0x00431da0
// Original: FUN_00431da0
// Status:   unreviewed
// ============================================


void __fastcall FUN_00431da0(int param_1)

{
  int iVar1;
  basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_> *this;
  wchar_t *pwVar2;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0069e4cc;
  local_10 = ExceptionList;
  local_8 = 2;
  ExceptionList = &local_10;
  while( true ) {
    iVar1 = FUN_0063bf40();
    if (iVar1 == 0) break;
    while( true ) {
      std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::back
                ((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_> *)
                 (param_1 + 0x70));
      iVar1 = FUN_0063bf40();
      if (iVar1 == 0) break;
      this = (basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_> *)
             std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::back
                       ((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_> *)
                        (param_1 + 0x70));
      pwVar2 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::back
                         (this);
      FUN_0065b1d0(*(undefined4 *)pwVar2);
      std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::back
                ((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_> *)
                 (param_1 + 0x70));
      FUN_00432fa0();
    }
    FUN_00432630();
  }
  FUN_0065b0a0();
  local_8._0_1_ = 1;
  FUN_0040fbb0();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004326d0();
  local_8 = 0xffffffff;
  FUN_0065af50();
  ExceptionList = local_10;
  return;
}

