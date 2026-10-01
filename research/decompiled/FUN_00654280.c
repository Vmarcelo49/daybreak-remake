// Function: FUN_00654280
// Address:  0x00654280
// Source:   batch_decompile (mass dump)
// Hash:     d51a20d25c4aaee7


void __fastcall FUN_00654280(int param_1)

{
  char cVar1;
  wchar_t *pwVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  cVar1 = FUN_006544f0();
  if (cVar1 == '\0') {
    pwVar2 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::back
                       ((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_> *)
                        (param_1 + 0x20));
    local_8 = *(undefined4 *)pwVar2;
    FUN_00654340(local_8);
    FUN_00654580();
    uVar3 = FUN_00654390();
    puVar4 = (undefined4 *)FUN_00658a10(local_8);
    *puVar4 = uVar3;
  }
  else {
    local_8 = FUN_0064f010();
    FUN_00654340(local_8);
    local_c = 0;
    FUN_00654510(&local_c);
    local_10 = FUN_00654390();
    FUN_00654510(&local_10);
  }
  FUN_006545d0(local_8);
  return;
}

