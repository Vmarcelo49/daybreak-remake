// ============================================
// Address:  0x0065e500
// Original: FUN_0065e500
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __thiscall FUN_0065e500(int param_1,undefined4 param_2)

{
  char *pcVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  wchar_t *pwVar5;
  long lVar6;
  undefined4 *puVar7;
  undefined4 local_520;
  undefined4 local_51c;
  undefined4 local_518;
  undefined4 local_514;
  undefined4 local_510;
  undefined4 local_50c;
  undefined4 local_508;
  undefined4 local_504;
  undefined1 local_4fc [8];
  char *local_4f4;
  void *local_4f0;
  void *local_4ec;
  undefined4 local_4e8;
  undefined4 local_4e4;
  void *local_4e0;
  undefined4 local_4dc;
  undefined4 local_4d8;
  void *local_4d4;
  undefined4 local_4d0;
  undefined4 local_4cc;
  void *local_4c8;
  undefined4 local_4c4;
  undefined4 local_4c0;
  void *local_4bc;
  undefined4 local_4b8;
  undefined4 local_4b4;
  void *local_4b0;
  undefined4 local_4ac;
  undefined4 local_4a8;
  void *local_4a4;
  undefined4 local_4a0;
  undefined4 local_49c;
  TaskStack *local_498;
  undefined4 local_494;
  undefined4 local_490;
  char *local_48c;
  size_t local_488;
  int local_484;
  size_t local_480;
  size_t local_47c;
  int local_478;
  int local_474;
  int local_470;
  size_t local_46c;
  int local_468;
  size_t local_464;
  int local_460;
  size_t local_45c;
  int local_458;
  size_t local_454;
  int local_450;
  char *local_44c;
  char *local_448;
  char *local_444;
  char local_440 [268];
  int local_334;
  undefined1 local_330;
  char local_228 [264];
  char local_120 [264];
  undefined4 local_18;
  char *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f1a0;
  local_10 = ExceptionList;
  local_18 = DAT_006b77f4;
  ExceptionList = &local_10;
  cVar2 = FUN_00653540(param_2);
  if (cVar2 == '\0') {
    uVar3 = 0;
  }
  else {
    local_334 = FUN_00653a40();
    if (local_334 == 0) {
      uVar3 = 0;
    }
    else {
      local_48c = operator_new(local_334 + 1);
      local_448 = local_48c;
      FUN_00653760(local_48c,local_334);
      local_448[local_334] = '\0';
      local_330 = 0;
      local_440[0] = '\0';
      local_120[0] = '\0';
      FUN_0065e4b0();
      local_444 = local_448;
      local_14 = (char *)0x0;
      do {
        iVar4 = __strnicmp(local_444,"character ",10);
        if (iVar4 == 0) {
          local_498 = operator_new(0x114);
          local_8 = 0;
          if (local_498 == (TaskStack *)0x0) {
            local_504 = 0;
          }
          else {
            local_504 = Concurrency::details::TaskStack::TaskStack(local_498);
          }
          local_494 = local_504;
          local_8 = 0xffffffff;
          local_490 = local_504;
          FUN_0065f350(&local_490);
          pwVar5 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::
                   back((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_> *)
                        (param_1 + 4));
          local_450 = *(int *)pwVar5;
          for (local_444 = local_444 + 10; *local_444 == ' '; local_444 = local_444 + 1) {
          }
          local_454 = FUN_0065f280(local_444,&local_14);
          _strncpy(local_228,local_444,local_454);
          local_228[local_454] = '\0';
          wsprintfA((LPSTR)(local_450 + 0xd),"%s%s",local_120,local_228);
          if (local_14 != (char *)0x0) {
            local_444 = local_14;
            lVar6 = _atol(local_14);
            *(long *)(local_450 + 4) = lVar6;
            FUN_0065f280(local_444,&local_14);
            if (local_14 != (char *)0x0) {
              local_444 = local_14;
              lVar6 = _atol(local_14);
              *(char *)(local_450 + 0xc) = (char)lVar6;
              if ((*(char *)(local_450 + 0xc) != '\0') &&
                 (FUN_0065f280(local_444,&local_14), local_14 != (char *)0x0)) {
                local_444 = local_14;
                lVar6 = _atol(local_14);
                *(long *)(local_450 + 8) = lVar6;
              }
            }
          }
        }
        else {
          iVar4 = __strnicmp(local_444,"bg ",3);
          if (iVar4 == 0) {
            local_4a4 = operator_new(0x108);
            local_8 = 1;
            if (local_4a4 == (void *)0x0) {
              local_508 = 0;
            }
            else {
              local_508 = FUN_0065f180();
            }
            local_4a0 = local_508;
            local_8 = 0xffffffff;
            local_49c = local_508;
            FUN_0065f350(&local_49c);
            pwVar5 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::
                     back((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                           *)(param_1 + 4));
            local_458 = *(int *)pwVar5;
            for (local_444 = local_444 + 3; *local_444 == ' '; local_444 = local_444 + 1) {
            }
            local_45c = FUN_0065f280(local_444,&local_14);
            _strncpy((char *)(local_458 + 4),local_444,local_45c);
            *(undefined1 *)(local_458 + local_45c + 4) = 0;
          }
          else {
            iVar4 = __strnicmp(local_444,"bgm ",4);
            if (iVar4 == 0) {
              local_4b0 = operator_new(0x108);
              local_8 = 2;
              if (local_4b0 == (void *)0x0) {
                local_50c = 0;
              }
              else {
                local_50c = FUN_0065f1a0();
              }
              local_4ac = local_50c;
              local_8 = 0xffffffff;
              local_4a8 = local_50c;
              FUN_0065f350(&local_4a8);
              pwVar5 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                       ::back((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                               *)(param_1 + 4));
              local_460 = *(int *)pwVar5;
              for (local_444 = local_444 + 4; *local_444 == ' '; local_444 = local_444 + 1) {
              }
              local_464 = FUN_0065f280(local_444,&local_14);
              _strncpy((char *)(local_460 + 4),local_444,local_464);
              *(undefined1 *)(local_460 + local_464 + 4) = 0;
            }
            else {
              iVar4 = __strnicmp(local_444,"voice ",6);
              if (iVar4 == 0) {
                local_4bc = operator_new(0x108);
                local_8 = 3;
                if (local_4bc == (void *)0x0) {
                  local_510 = 0;
                }
                else {
                  local_510 = FUN_0065f200();
                }
                local_4b8 = local_510;
                local_8 = 0xffffffff;
                local_4b4 = local_510;
                FUN_0065f350(&local_4b4);
                pwVar5 = std::
                         basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::
                         back((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                               *)(param_1 + 4));
                local_468 = *(int *)pwVar5;
                for (local_444 = local_444 + 6; *local_444 == ' '; local_444 = local_444 + 1) {
                }
                local_46c = FUN_0065f280(local_444,&local_14);
                _strncpy(local_228,local_444,local_46c);
                local_228[local_46c] = '\0';
                wsprintfA((LPSTR)(local_468 + 4),"%s%s",local_440,local_228);
              }
              else {
                iVar4 = __strnicmp(local_444,"sleep ",6);
                if (iVar4 == 0) {
                  local_4c8 = operator_new(8);
                  local_8 = 4;
                  if (local_4c8 == (void *)0x0) {
                    local_514 = 0;
                  }
                  else {
                    local_514 = FUN_0065f220();
                  }
                  local_4c4 = local_514;
                  local_8 = 0xffffffff;
                  local_4c0 = local_514;
                  FUN_0065f350(&local_4c0);
                  pwVar5 = std::
                           basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                           ::back((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                                   *)(param_1 + 4));
                  local_470 = *(int *)pwVar5;
                  local_444 = local_444 + 6;
                  lVar6 = _atol(local_444);
                  *(long *)(local_470 + 4) = lVar6;
                }
                else {
                  iVar4 = __strnicmp(local_444,"move ",5);
                  if (iVar4 == 0) {
                    local_4d4 = operator_new(0x10);
                    local_8 = 5;
                    if (local_4d4 == (void *)0x0) {
                      local_518 = 0;
                    }
                    else {
                      local_518 = FUN_0065f240();
                    }
                    local_4d0 = local_518;
                    local_8 = 0xffffffff;
                    local_4cc = local_518;
                    FUN_0065f350(&local_4cc);
                    pwVar5 = std::
                             basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                             ::back((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                                     *)(param_1 + 4));
                    local_474 = *(int *)pwVar5;
                    local_444 = local_444 + 5;
                    lVar6 = _atol(local_444);
                    *(long *)(local_474 + 4) = lVar6;
                    FUN_0065f280(local_444,&local_14);
                    if (local_14 != (char *)0x0) {
                      local_444 = local_14;
                      lVar6 = _atol(local_14);
                      *(long *)(local_474 + 8) = lVar6;
                      FUN_0065f280(local_444,&local_14);
                      if (local_14 != (char *)0x0) {
                        local_444 = local_14;
                        lVar6 = _atol(local_14);
                        *(long *)(local_474 + 0xc) = lVar6;
                      }
                    }
                  }
                  else {
                    iVar4 = __strnicmp(local_444,"front ",6);
                    if (iVar4 == 0) {
                      local_4e0 = operator_new(8);
                      local_8 = 6;
                      if (local_4e0 == (void *)0x0) {
                        local_51c = 0;
                      }
                      else {
                        local_51c = FUN_0065f260();
                      }
                      local_4dc = local_51c;
                      local_8 = 0xffffffff;
                      local_4d8 = local_51c;
                      FUN_0065f350(&local_4d8);
                      pwVar5 = std::
                               basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                               ::back((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                                       *)(param_1 + 4));
                      local_478 = *(int *)pwVar5;
                      local_444 = local_444 + 6;
                      lVar6 = _atol(local_444);
                      *(long *)(local_478 + 4) = lVar6;
                    }
                    else if (*local_444 != '#') {
                      iVar4 = __strnicmp(local_444,"characterdir ",0xd);
                      if (iVar4 == 0) {
                        for (local_444 = local_444 + 0xd; *local_444 == ' ';
                            local_444 = local_444 + 1) {
                        }
                        local_47c = FUN_0065f280(local_444,&local_14);
                        _strncpy(local_120,local_444,local_47c);
                        local_120[local_47c] = '\0';
                      }
                      else {
                        iVar4 = __strnicmp(local_444,"voicedir ",9);
                        if (iVar4 == 0) {
                          for (local_444 = local_444 + 9; *local_444 == ' ';
                              local_444 = local_444 + 1) {
                          }
                          local_480 = FUN_0065f280(local_444,&local_14);
                          _strncpy(local_440,local_444,local_480);
                          local_440[local_480] = '\0';
                        }
                        else {
                          local_4ec = operator_new(8);
                          local_8 = 7;
                          if (local_4ec == (void *)0x0) {
                            local_520 = 0;
                          }
                          else {
                            local_520 = FUN_0068dc50();
                          }
                          local_4e8 = local_520;
                          local_8 = 0xffffffff;
                          local_4e4 = local_520;
                          FUN_0065f350(&local_4e4);
                          pwVar5 = std::
                                   basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                                   ::back((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                                           *)(param_1 + 4));
                          local_484 = *(int *)pwVar5;
                          local_488 = FUN_0065f280(local_444,&local_14);
                          local_4f0 = operator_new(local_488 + 1);
                          *(void **)(local_484 + 4) = local_4f0;
                          _strncpy(*(char **)(local_484 + 4),local_444,local_488);
                          *(undefined1 *)(*(int *)(local_484 + 4) + local_488) = 0;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
        local_44c = _strchr(local_444,0xd);
        pcVar1 = local_44c;
        if (local_44c == (char *)0x0) break;
        do {
          local_444 = pcVar1 + 2;
          pcVar1 = local_444;
        } while (*local_444 == '\r');
      } while (*local_444 != '\0');
      local_4f4 = local_448;
      _free(local_448);
      puVar7 = (undefined4 *)FUN_00425ae0(local_4fc);
      uVar3 = puVar7[1];
      *(undefined4 *)(param_1 + 0x18) = *puVar7;
      *(undefined4 *)(param_1 + 0x1c) = uVar3;
      uVar3 = 1;
    }
  }
  ExceptionList = local_10;
  return uVar3;
}

