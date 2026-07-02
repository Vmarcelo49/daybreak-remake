// Function: FUN_0042eec0
// Address:  0x0042eec0
// Source:   batch_decompile (mass dump)
// Hash:     0aa04c38fea00bd9


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __thiscall FUN_0042eec0(int param_1,int param_2,undefined4 param_3,int *param_4)

{
  char cVar1;
  void *pvVar2;
  undefined4 uVar3;
  wchar_t *pwVar4;
  int local_4d8;
  undefined1 local_4bc [20];
  undefined4 local_4a8;
  uint local_4a4;
  undefined4 *local_4a0;
  uint local_49c;
  int local_498;
  wchar_t *local_494;
  undefined1 local_490 [128];
  uint local_410;
  wchar_t *local_40c;
  uint local_408;
  undefined1 local_404 [24];
  uint local_3ec;
  int local_3e8;
  uint local_3e4;
  undefined1 local_3e0 [4];
  uint local_3dc;
  undefined1 local_3d8 [60];
  undefined1 local_39c [32];
  int local_37c;
  undefined1 local_378 [268];
  undefined1 local_26c [4];
  undefined1 local_268 [4];
  undefined1 local_264 [60];
  CHAR local_228 [264];
  undefined1 local_120 [264];
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e3f1;
  local_10 = ExceptionList;
  local_18 = DAT_006b77f4;
  ExceptionList = &local_10;
  cVar1 = FUN_00653540(param_3);
  if (cVar1 == '\0') {
    uVar3 = 0;
  }
  else {
    FUN_00655600(param_3,local_378,local_228);
    FUN_00653760(local_26c,4);
    FUN_00653760(local_120,0x104);
    wsprintfA(local_228,"%s%s",local_378,local_120);
    pvVar2 = operator_new(0x9c);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_4d8 = 0;
    }
    else {
      local_4d8 = FUN_0064d7a0();
    }
    local_8 = 0xffffffff;
    *param_4 = local_4d8;
    cVar1 = FUN_0064d940(local_228);
    if (cVar1 == '\0') {
      if (*param_4 != 0) {
        if (*param_4 != 0) {
          FUN_00402010(1);
        }
        *param_4 = 0;
      }
      uVar3 = 0;
    }
    else {
      FUN_00653540(param_3);
      FUN_00653960(0x108,0);
      FUN_00653760(&local_14,4);
      for (local_3dc = 0; local_3dc < local_14; local_3dc = local_3dc + 1) {
        FUN_00653760(local_3e0,4);
        local_3e8 = (param_2 * 10 + local_3dc) * 0x1c + *(int *)(param_1 + 0x30);
        FUN_00653760(local_3e8,4);
        FUN_00653760(local_3e8 + 4,4);
        FUN_00653760(&local_3e4,4);
        FUN_004244c0();
        for (local_3ec = 0; local_3ec < local_3e4; local_3ec = local_3ec + 1) {
          FUN_00423560();
          local_8 = 1;
          FUN_00424550(local_404);
          local_40c = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                      ::back((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                              *)(local_3e8 + 8));
          FUN_00653760(local_40c,4);
          local_408 = FUN_0063bf40();
          FUN_00653760(&local_408,4);
          for (local_410 = 0; local_410 < local_408; local_410 = local_410 + 1) {
            FUN_00423480();
            FUN_004243e0(local_490);
            local_494 = std::
                        basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::
                        back((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                              *)(local_40c + 2));
            FUN_00653760(local_39c,0x1e);
            uVar3 = FUN_0064e6c0(local_39c);
            *(undefined4 *)local_494 = uVar3;
            FUN_00653760(local_494 + 2,4);
            FUN_00653760(&local_37c,4);
            *(float *)(local_494 + 6) = (float)local_37c;
            FUN_00653760(&local_37c,4);
            *(float *)(local_494 + 8) = (float)local_37c;
            FUN_00653760(&local_37c,4);
            *(float *)(local_494 + 10) = (float)local_37c;
            FUN_00653760(local_494 + 0x12,4);
            FUN_00653760(local_494 + 0x18,0x50);
            FUN_00653760(local_494 + 0x14,4);
            FUN_00653760(local_494 + 0x16,4);
            FUN_00653760(local_494 + 4,4);
            FUN_00653760(&local_37c,4);
            *(float *)(local_494 + 0xc) = (float)local_37c;
            FUN_00653760(&local_37c,4);
            *(float *)(local_494 + 0xe) = (float)local_37c;
            FUN_00653760(&local_37c,4);
            *(float *)(local_494 + 0x10) = (float)local_37c;
          }
          local_8 = 0xffffffff;
          FUN_004234c0();
        }
      }
      FUN_00653760(local_268,4);
      for (local_498 = 0; local_498 == 0; local_498 = local_498 + 1) {
        local_4a0 = (undefined4 *)(param_2 * 0x38 + *(int *)(param_1 + 0x34));
        FUN_0064e8b0(0);
        uVar3 = FUN_0066b668();
        *local_4a0 = uVar3;
        FUN_00653760(local_4a0 + 7,4);
        FUN_00653760(local_4a0 + 8,4);
        local_49c = FUN_0063bf40();
        FUN_00653760(&local_49c,4);
        for (local_4a4 = 0; local_4a4 < local_49c; local_4a4 = local_4a4 + 1) {
          FUN_00423460();
          FUN_00424270(local_4bc);
          pwVar4 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::
                   back((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_> *)
                        (local_4a0 + 9));
          FUN_00653760(pwVar4,4);
          FUN_00653760(pwVar4 + 2,4);
          FUN_00653760(pwVar4 + 4,4);
          FUN_00653760(local_3d8,0x3c);
          uVar3 = FUN_0064e7c0(local_3d8);
          *(undefined4 *)(pwVar4 + 6) = uVar3;
          FUN_00653760(local_264,0x3c);
          local_4a8 = FUN_00653960(0,1);
          FUN_0064ecd0(local_264,pwVar4 + 8);
          FUN_00653540(param_3);
          local_4a8 = FUN_00653960(local_4a8,0);
        }
      }
      uVar3 = 1;
    }
  }
  ExceptionList = local_10;
  return uVar3;
}

