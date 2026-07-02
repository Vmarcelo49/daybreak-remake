// ============================================
// Address:  0x00647000
// Original: FUN_00647000
// Status:   unreviewed
// ============================================


void __thiscall FUN_00647000(int param_1,void *param_2,undefined4 param_3,undefined1 param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 local_a0 [38];
  wchar_t *local_8;
  
  puVar3 = local_a0;
  for (iVar2 = 0x26; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  FUN_00647510(local_a0);
  *(int *)(param_1 + 0x414) = *(int *)(param_1 + 0x414) + 1;
  local_8 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::back
                      ((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_> *)
                       (param_1 + 0x400));
  _memcpy(local_8 + 0x40,param_2,9);
  FUN_0066b860(local_8,param_3);
  FUN_0066b870(local_8,&DAT_006a4d70);
  local_8[0x46] = L'ɘ';
  local_8[0x47] = L'\0';
  *(undefined1 *)(local_8 + 0x4a) = param_4;
  uVar1 = FUN_0065d150();
  *(float *)(local_8 + 0x48) = (float)(uVar1 % 0xa0);
  uVar1 = FUN_0063bf40();
  if (100 < uVar1) {
    FUN_00647470();
    *(int *)(param_1 + 0x414) = *(int *)(param_1 + 0x414) + -1;
  }
  return;
}

