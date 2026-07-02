// ============================================
// Address:  0x00658860
// Original: FUN_00658860
// Status:   unreviewed
// ============================================


bool FUN_00658860(int param_1)

{
  wchar_t *pwVar1;
  int iVar2;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_1c = 0x18;
  local_18 = 0x10;
  local_10 = 2;
  local_14 = *(undefined4 *)(param_1 + 0x18);
  local_c = 0xfffffc18;
  local_8 = 1000;
  pwVar1 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::back
                     ((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_> *)
                      &DAT_006d1918);
  iVar2 = (**(code **)(**(int **)pwVar1 + 0x18))(*(int **)pwVar1,4,&local_1c);
  return -1 < iVar2;
}

