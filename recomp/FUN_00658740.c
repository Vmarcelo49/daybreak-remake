// ============================================
// Address:  0x00658740
// Original: FUN_00658740
// Status:   unreviewed
// ============================================


undefined4 FUN_00658740(int param_1)

{
  undefined4 uVar1;
  wchar_t *pwVar2;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34 [4];
  undefined4 local_24;
  int local_8;
  
  if (DAT_006d1910 == (int *)0x0) {
    uVar1 = 0;
  }
  else {
    local_38 = 0;
    FUN_00658900(&local_38);
    uVar1 = 0;
    pwVar2 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::back
                       ((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_> *)
                        &DAT_006d1918);
    local_8 = (**(code **)(*DAT_006d1910 + 0xc))(DAT_006d1910,param_1 + 4,pwVar2,uVar1);
    if (local_8 < 0) {
      FUN_00654580();
      uVar1 = 0;
    }
    else {
      pwVar2 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::back
                         ((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                           *)&DAT_006d1918);
      (**(code **)(**(int **)pwVar2 + 0x2c))(*(int **)pwVar2,&DAT_006ab7cc);
      pwVar2 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::back
                         ((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                           *)&DAT_006d1918);
      (**(code **)(**(int **)pwVar2 + 0x34))(*(int **)pwVar2,DAT_006d1908,5);
      local_34[0] = 0x2c;
      pwVar2 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::back
                         ((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                           *)&DAT_006d1918);
      (**(code **)(**(int **)pwVar2 + 0xc))(*(int **)pwVar2,local_34);
      local_3c = local_24;
      FUN_00658900(&local_3c);
      pwVar2 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::back
                         ((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                           *)&DAT_006d1918);
      (**(code **)(**(int **)pwVar2 + 0x10))(*(int **)pwVar2,FUN_00658860,0,3);
      uVar1 = 1;
    }
  }
  return uVar1;
}

