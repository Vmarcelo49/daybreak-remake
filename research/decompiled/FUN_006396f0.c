// Function: FUN_006396f0
// Address:  0x006396f0
// Source:   batch_decompile (mass dump)
// Hash:     21af3186a4f91d90


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_006396f0(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int local_80;
  tagRECT local_7c;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  tagRECT local_4c [4];
  int local_8;
  
  local_8 = 0;
  cVar1 = FUN_00650f70();
  if (cVar1 != '\0') {
    if ((*(int *)(param_1 + 0x4a3c) == 4) || (*(int *)(param_1 + 0x4a3c) == 5)) {
      _DAT_006c78c4 = *(undefined4 *)(param_1 + 0x4428);
      local_8 = 1;
      SetRect(local_4c,0,0,800,600);
      DAT_006cfd00 = 1;
    }
    else if (*(int *)(param_1 + 0x4a3c) == 3) {
      _DAT_006c78c4 = *(undefined4 *)(param_1 + 0x4424);
      local_8 = 1;
      SetRect(local_4c,0,0,800,600);
      DAT_006cfd00 = 1;
    }
    else {
      switch(DAT_006cfba0) {
      case 1:
        _DAT_006c78c4 = DAT_006cfba4;
        local_8 = 1;
        SetRect(local_4c,0,0,800,600);
        DAT_006cfd00 = 1;
        break;
      case 2:
        local_8 = 2;
        FUN_00650ab0(&DAT_006b7654);
        FUN_00650f40();
        _DAT_006c78c4 = DAT_006cfba4;
        _DAT_006c78c8 = DAT_006cfba8;
        _DAT_006c78cc = 0xffffffff;
        _DAT_006c78d0 = 0xffffffff;
        SetRect(local_4c,0,0,400,300);
        SetRect(local_4c + 1,400,300,800,600);
        SetRect(local_4c + 2,400,0,800,300);
        SetRect(local_4c + 3,0,300,400,600);
        DAT_006cfd00 = 0;
        break;
      case 3:
        FUN_00650ab0(&DAT_006b7654);
        FUN_00650f40();
        local_8 = 4;
        for (local_50 = 0; local_50 < 4; local_50 = local_50 + 1) {
          if ((*(char *)(*(int *)(param_1 + 0x129c + local_50 * 4) + 0x860) == '\0') &&
             ((int)(&DAT_006cfaf8)[local_50] < 4)) {
            *(int *)(&DAT_006c78c4 + local_50 * 4) = local_50;
          }
          else {
            *(undefined4 *)(&DAT_006c78c4 + local_50 * 4) = 0xffffffff;
          }
        }
        SetRect(local_4c,0,0,400,300);
        SetRect(local_4c + 1,0,300,400,600);
        SetRect(local_4c + 2,400,0,800,300);
        SetRect(local_4c + 3,400,300,800,600);
        DAT_006cfd00 = 0;
        break;
      case 4:
        local_8 = 4;
        for (local_54 = 0; local_54 < 4; local_54 = local_54 + 1) {
          *(int *)(&DAT_006c78c4 + local_54 * 4) = local_54;
        }
        SetRect(local_4c,0,0,400,300);
        SetRect(local_4c + 1,0,300,400,600);
        SetRect(local_4c + 2,400,0,800,300);
        SetRect(local_4c + 3,400,300,800,600);
        DAT_006cfd00 = 0;
      }
    }
    FUN_0065d670();
    FUN_00435d20();
    for (local_58 = 0; local_58 < 4; local_58 = local_58 + 1) {
      FUN_00421010();
      FUN_006333b0();
    }
    FUN_0065d6a0();
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xf,0);
    for (local_5c = 0; local_5c < local_8; local_5c = local_5c + 1) {
      if ((DAT_006cfba0 != 3) || (-1 < *(int *)(&DAT_006c78c4 + local_5c * 4))) {
        *(undefined4 *)(param_1 + 0x44b4) = *(undefined4 *)(&DAT_006c78c4 + local_5c * 4);
        FUN_00633860();
        FUN_00401a00(param_1 + 0x454e + *(int *)(param_1 + 0x44b4) * 0x160,1);
        FUN_006507c0();
        FUN_00651110(2);
        if (DAT_006cfcea != '\0') {
          for (local_60 = 0; local_60 < 4; local_60 = local_60 + 1) {
            FUN_004207d0();
          }
        }
        FUN_00651110(0);
        FUN_00650ab0(local_4c + local_5c);
        FUN_00650f40();
        if ((*(int *)(*(int *)(param_1 + 0x129c + *(int *)(param_1 + 0x44b4) * 4) + 0x7f0) == 0) &&
           (*(int *)(*(int *)(param_1 + 0x129c + *(int *)(param_1 + 0x44b4) * 4) + 0x7f8) == 0)) {
          FUN_00401b80();
          for (local_64 = 0; local_64 < 4; local_64 = local_64 + 1) {
            FUN_00651110(0);
            FUN_004205e0();
            if (DAT_006cfcec == '\0') {
              FUN_00651110(0);
            }
            else if (local_8 == 1) {
              FUN_00651110(1);
            }
            else {
              FUN_00651110(7);
            }
            FUN_004203f0();
          }
          for (local_68 = 0; local_68 < 4; local_68 = local_68 + 1) {
            FUN_00420800();
          }
          FUN_00401e80();
          FUN_00651110(0);
          for (local_6c = 0; local_6c < 4; local_6c = local_6c + 1) {
            FUN_00420830();
          }
          FUN_00435c20();
        }
        else {
          (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,7,0);
          if (*(int *)(*(int *)(param_1 + 0x129c + *(int *)(param_1 + 0x44b4) * 4) + 0x7f8) <
              *(int *)(*(int *)(param_1 + 0x129c + *(int *)(param_1 + 0x44b4) * 4) + 0x7f0)) {
            FUN_00651820(local_4c + local_5c,
                         (uint)*(byte *)(*(int *)(param_1 + 0x129c + *(int *)(param_1 + 0x44b4) * 4)
                                        + 0x824) << 0x18 | 0xffffff);
          }
          else {
            FUN_00651820(local_4c + local_5c,
                         (uint)*(byte *)(*(int *)(param_1 + 0x129c + *(int *)(param_1 + 0x44b4) * 4)
                                        + 0x824) << 0x18);
          }
          (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,7,1);
          FUN_00651110(0);
          FUN_004205e0();
          if (DAT_006cfcec == '\0') {
            FUN_00651110(0);
          }
          else if (local_8 == 1) {
            FUN_00651110(1);
          }
          else {
            FUN_00651110(7);
          }
          FUN_004203f0();
          FUN_00420800();
          FUN_00651110(0);
          FUN_00435c20();
        }
        if ((DAT_006cfdb0 != '\0') && (local_5c == 0)) {
          (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,7,0);
          FUN_00646870(0);
          FUN_00646500(0x43500000,0x44000000);
        }
        FUN_0063a130(*(undefined4 *)(param_1 + 0x44b4),(float)local_4c[local_5c].left,
                     (float)local_4c[local_5c].top);
      }
    }
    FUN_00650ab0(&DAT_006b7654);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,7,0);
    if (1 < local_8) {
      SetRect(&local_7c,399,0,400,599);
      FUN_00651820(&local_7c,0xff000000);
      SetRect(&local_7c,0,299,799,300);
      FUN_00651820(&local_7c,0xff000000);
      for (local_80 = 0; local_80 < 4; local_80 = local_80 + 1) {
        if (*(int *)(&DAT_006c78c4 + local_80 * 4) < 0) {
          FUN_00655d60((float)local_4c[local_80].left + 200.0,(float)local_4c[local_80].top + 150.0)
          ;
        }
      }
    }
    FUN_00431b20(DAT_006d18a4,0x44480000,0,0x3f000000,0);
    uVar7 = 0;
    uVar6 = 0x3f000000;
    uVar5 = 0;
    uVar4 = 0x41a00000;
    iVar2 = FUN_0063bf40(0x41a00000,0,0x3f000000,0);
    iVar3 = FUN_0063bf40();
    FUN_00431b20(iVar2 + iVar3,uVar4,uVar5,uVar6,uVar7);
    if ((*(char *)(param_1 + 0x4430) != '\0') && (*(char *)(param_1 + 0x4431) == '\0')) {
      FUN_00655d60(0x43c80000,0x43960000);
    }
    if (*(int *)(param_1 + 0x4a3c) == 4) {
      FUN_0063a740();
    }
    else if (*(int *)(param_1 + 0x4a3c) == 5) {
      FUN_0063aee0();
    }
    else {
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,7,1);
    }
    FUN_00651110(0);
    FUN_00650fd0();
  }
  return;
}

