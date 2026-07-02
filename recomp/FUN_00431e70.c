// ============================================
// Address:  0x00431e70
// Original: FUN_00431e70
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FUN_00431e70(int param_1,undefined4 param_2,char param_3)

{
  int iVar1;
  basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_> *this;
  wchar_t *pwVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined4 local_150 [6];
  undefined1 local_138 [4];
  undefined1 local_134 [4];
  undefined1 local_130 [4];
  undefined4 local_12c;
  int local_128;
  int local_124;
  CHAR local_120 [268];
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e4e1;
  local_10 = ExceptionList;
  local_14 = DAT_006b77f4;
  ExceptionList = &local_10;
  while (iVar1 = FUN_0063bf40(), iVar1 != 0) {
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
  FUN_004326d0();
  FUN_0040fbb0();
  local_124 = 0;
  do {
    if (0x27 < local_124) {
      ExceptionList = local_10;
      return;
    }
    local_12c = 0;
    uVar3 = FUN_004248f0();
    local_8 = 0;
    FUN_00432550(uVar3);
    local_8 = 0xffffffff;
    FUN_0040fbb0();
    local_150[0] = 0;
    FUN_00432810(local_150);
    if ((((local_124 == 4) || (local_124 == 7)) || (local_124 == 10)) || (local_124 == 0x1a)) {
      local_128 = (int)param_3;
    }
    else {
      local_128 = 0;
    }
    while( true ) {
      while( true ) {
        while (local_128 != 2) {
          if (local_128 == 1) {
            pwVar2 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::
                     back((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                           *)(param_1 + 0x84));
            wsprintfA(local_120,"%s/%s_B/%03d.wav",param_2,s_addattack_006b73b0 + local_124 * 0x10,
                      *(undefined4 *)pwVar2);
            FUN_0065b0d0(local_134,local_120);
            iVar1 = FUN_0068de10();
            if (iVar1 == 0) {
              pwVar2 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                       ::back((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                               *)(param_1 + 0x84));
              if (*(int *)pwVar2 != 0) goto LAB_00431f3c;
              local_128 = 0;
            }
            else {
              puVar4 = local_134;
              std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::back
                        ((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_> *
                         )(param_1 + 0x70));
              FUN_004326f0(puVar4);
              pwVar2 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                       ::back((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                               *)(param_1 + 0x84));
              *(int *)pwVar2 = *(int *)pwVar2 + 1;
            }
          }
          else {
            pwVar2 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::
                     back((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                           *)(param_1 + 0x84));
            wsprintfA(local_120,"%s/%s/%03d.wav",param_2,s_addattack_006b73b0 + local_124 * 0x10,
                      *(undefined4 *)pwVar2);
            FUN_0065b0d0(local_138,local_120);
            iVar1 = FUN_0068de10();
            if (iVar1 == 0) goto LAB_00431f3c;
            puVar4 = local_138;
            std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::back
                      ((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_> *)
                       (param_1 + 0x70));
            FUN_004326f0(puVar4);
            pwVar2 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::
                     back((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                           *)(param_1 + 0x84));
            *(int *)pwVar2 = *(int *)pwVar2 + 1;
          }
        }
        pwVar2 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::back
                           ((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                             *)(param_1 + 0x84));
        wsprintfA(local_120,"%s/%s_C/%03d.wav",param_2,s_addattack_006b73b0 + local_124 * 0x10,
                  *(undefined4 *)pwVar2);
        FUN_0065b0d0(local_130,local_120);
        iVar1 = FUN_0068de10();
        if (iVar1 == 0) break;
        puVar4 = local_130;
        std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::back
                  ((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_> *)
                   (param_1 + 0x70));
        FUN_004326f0(puVar4);
        pwVar2 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::back
                           ((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                             *)(param_1 + 0x84));
        *(int *)pwVar2 = *(int *)pwVar2 + 1;
      }
      pwVar2 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::back
                         ((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                           *)(param_1 + 0x84));
      if (*(int *)pwVar2 != 0) break;
      local_128 = 0;
    }
LAB_00431f3c:
    local_124 = local_124 + 1;
  } while( true );
}

