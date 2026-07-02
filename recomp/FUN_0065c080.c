// ============================================
// Address:  0x0065c080
// Original: FUN_0065c080
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined1 __thiscall FUN_0065c080(undefined4 *param_1,LPCSTR param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int local_e8;
  int local_e0;
  int local_dc;
  int local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined1 local_b8 [6];
  undefined1 local_b2;
  undefined1 local_b1;
  void *local_b0;
  int local_ac;
  undefined1 local_a8;
  undefined1 local_a7;
  undefined1 local_a6;
  undefined1 local_a5;
  void *local_a4;
  undefined4 local_a0;
  undefined1 local_99;
  void *local_98;
  undefined4 local_94;
  void *local_90;
  undefined4 local_8c;
  undefined4 *local_88;
  undefined4 *local_84;
  undefined1 local_80;
  undefined1 local_7f;
  undefined1 local_7e;
  undefined1 local_7d;
  LPCSTR local_7c;
  undefined4 local_78;
  HRESULT local_74;
  int *local_70;
  int local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f0c0;
  local_10 = ExceptionList;
  local_1c = DAT_006b77f4;
  local_78 = 1000;
  ExceptionList = &local_10;
  FUN_00686800();
  local_8 = 0;
  local_68 = 0xe436eb83;
  local_64 = 0x11ce524f;
  local_60 = 0x2000539f;
  local_5c = 0x70a70baf;
  local_6c = lstrlenA(param_2);
  if ((local_6c < 4) || (param_2[local_6c + -4] != '.')) {
    local_7d = 0;
    local_8 = 0xffffffff;
    FUN_006867e0();
    local_99 = local_7d;
  }
  else {
    local_7c = param_2 + local_6c + -3;
    iVar2 = lstrcmpiA(local_7c,"avi");
    if (iVar2 == 0) {
      local_58 = 0xe436eb88;
    }
    else {
      iVar2 = lstrcmpiA(local_7c,"mpg");
      if (iVar2 == 0) {
        local_58 = 0xe436eb84;
      }
      else {
        iVar2 = lstrcmpiA(local_7c,"mpv");
        if (iVar2 == 0) {
          local_58 = 0xe436eb86;
        }
        else {
          iVar2 = lstrcmpiA(local_7c,"mov");
          if (iVar2 != 0) {
            local_7e = 0;
            local_8 = 0xffffffff;
            FUN_006867e0();
            ExceptionList = local_10;
            return local_7e;
          }
          local_58 = 0xe436eb89;
        }
      }
    }
    local_4c = 0x70a70baf;
    local_50 = 0x2000539f;
    local_54 = 0x11ce524f;
    local_18 = *param_1;
    cVar1 = FUN_0064d6e0();
    if (cVar1 == '\0') {
      cVar1 = FUN_00653620(param_1,param_2);
      if (cVar1 == '\0') {
        local_80 = 0;
        local_8 = 0xffffffff;
        FUN_006867e0();
        ExceptionList = local_10;
        return local_80;
      }
    }
    else {
      cVar1 = FUN_00653620(param_1 + 1,param_2);
      if (cVar1 == '\0') {
        FUN_00654170(0);
        local_7f = 0;
        local_8 = 0xffffffff;
        FUN_006867e0();
        ExceptionList = local_10;
        return local_7f;
      }
    }
    local_74 = 0;
    if ((param_1[3] != 0) &&
       (local_88 = (undefined4 *)param_1[3], local_84 = local_88, local_88 != (undefined4 *)0x0)) {
      (**(code **)*local_88)(1);
    }
    cVar1 = FUN_0064d6e0();
    if (cVar1 == '\0') {
      local_98 = operator_new(0x40);
      local_8._0_1_ = 2;
      if (local_98 == (void *)0x0) {
        local_d0 = 0;
      }
      else {
        local_d0 = FUN_0065ca70(*param_1,local_78);
      }
      local_94 = local_d0;
      param_1[3] = local_d0;
    }
    else {
      local_90 = operator_new(0x40);
      local_8._0_1_ = 1;
      if (local_90 == (void *)0x0) {
        local_cc = 0;
      }
      else {
        local_cc = FUN_0065ca70(param_1[1],local_78);
      }
      local_8c = local_cc;
      param_1[3] = local_cc;
    }
    local_8 = (uint)local_8._1_3_ << 8;
    if (param_1[3] == 0) {
      local_99 = 0;
      local_8 = 0xffffffff;
      FUN_006867e0();
    }
    else {
      if (param_1[4] != 0) {
        (**(code **)(*(int *)(param_1[4] + 0xc) + 8))(param_1[4] + 0xc);
      }
      local_a4 = operator_new(0x1e8);
      local_8._0_1_ = 3;
      if (local_a4 == (void *)0x0) {
        local_d4 = 0;
      }
      else {
        local_d4 = FUN_0065ce60(param_1[3],&local_68,&local_74);
      }
      local_a0 = local_d4;
      local_8._0_1_ = 0;
      param_1[4] = local_d4;
      if (param_1[4] == 0) {
        local_a5 = 0;
        local_8 = 0xffffffff;
        FUN_006867e0();
        local_99 = local_a5;
      }
      else {
        (**(code **)(*(int *)(param_1[4] + 0xc) + 4))(param_1[4] + 0xc);
        local_74 = CoCreateInstance((IID *)&DAT_006ad1c4,(LPUNKNOWN)0x0,3,(IID *)&LAB_006ad071_3,
                                    (LPVOID *)(param_1 + 6));
        if (local_74 < 0) {
          local_a6 = 0;
          local_8 = 0xffffffff;
          FUN_006867e0();
          local_99 = local_a6;
        }
        else {
          if (param_1[4] == 0) {
            local_d8 = 0;
          }
          else {
            local_d8 = param_1[4] + 0xc;
          }
          local_74 = (**(code **)(*(int *)param_1[6] + 0xc))(param_1[6],local_d8,0);
          if (local_74 < 0) {
            local_a7 = 0;
            local_8 = 0xffffffff;
            FUN_006867e0();
            local_99 = local_a7;
          }
          else {
            local_74 = (*(code *)**(undefined4 **)param_1[6])(param_1[6],&DAT_006acfa4,&local_70);
            if (local_74 < 0) {
              local_a8 = 0;
              local_8 = 0xffffffff;
              FUN_006867e0();
              local_99 = local_a8;
            }
            else {
              local_14 = 0;
              local_b0 = operator_new(0x180);
              local_8._0_1_ = 4;
              if (local_b0 == (void *)0x0) {
                local_dc = 0;
              }
              else {
                local_dc = FUN_00668aa0(0,&local_74);
              }
              local_ac = local_dc;
              local_8 = (uint)local_8._1_3_ << 8;
              local_14 = local_dc;
              if ((local_74 < 0) || (local_dc == 0)) {
                local_b1 = 0;
                local_8 = 0xffffffff;
                FUN_006867e0();
                local_99 = local_b1;
              }
              else {
                if (local_dc == 0) {
                  local_e0 = 0;
                }
                else {
                  local_e0 = local_dc + 0xc;
                }
                param_1[5] = local_e0;
                (**(code **)(*(int *)param_1[5] + 4))(param_1[5]);
                local_74 = (**(code **)(*local_70 + 0xc))(local_70,param_1[5],L"TextureRenderer");
                if (local_74 < 0) {
                  local_b2 = 0;
                  local_8 = 0xffffffff;
                  FUN_006867e0();
                  local_99 = local_b2;
                }
                else {
                  local_e8 = (**(code **)(*(int *)param_1[4] + 0x1c))(0);
                  if (local_e8 == 0) {
                    local_e8 = 0;
                  }
                  else {
                    local_e8 = local_e8 + 0xc;
                  }
                  local_74 = (**(code **)(*local_70 + 0x30))(local_70,local_e8);
                  iVar2 = FUN_0068de10();
                  if (iVar2 != 0) {
                    FUN_00656200(param_1[2]);
                  }
                  uVar6 = 0;
                  uVar5 = 0;
                  uVar3 = FUN_0065ca50(0,0);
                  puVar4 = (undefined4 *)FUN_00656130(local_b8,uVar3,uVar5,uVar6);
                  param_1[2] = *puVar4;
                  (**(code **)(*local_70 + 8))(local_70);
                  if (local_74 < 0) {
                    local_8 = 0xffffffff;
                    FUN_006867e0();
                    local_99 = 0;
                  }
                  else {
                    local_74 = (*(code *)**(undefined4 **)param_1[6])
                                         (param_1[6],&LAB_006ad131_3,param_1 + 7);
                    if (local_74 < 0) {
                      local_8 = 0xffffffff;
                      FUN_006867e0();
                      local_99 = 0;
                    }
                    else {
                      local_74 = (*(code *)**(undefined4 **)param_1[6])
                                           (param_1[6],&LAB_006ad111_3,param_1 + 8);
                      if (local_74 < 0) {
                        (**(code **)(*(int *)param_1[7] + 8))(param_1[7]);
                        local_8 = 0xffffffff;
                        FUN_006867e0();
                        local_99 = 0;
                      }
                      else {
                        local_74 = (**(code **)(*(int *)param_1[8] + 0x1c))(param_1[8],param_1 + 9);
                        if (local_74 < 0) {
                          local_8 = 0xffffffff;
                          FUN_006867e0();
                          local_99 = 0;
                        }
                        else {
                          local_8 = 0xffffffff;
                          FUN_006867e0();
                          local_99 = 1;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  ExceptionList = local_10;
  return local_99;
}

