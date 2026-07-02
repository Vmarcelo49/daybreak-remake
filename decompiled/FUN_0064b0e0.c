// Function: FUN_0064b0e0
// Address:  0x0064b0e0
// Source:   batch_decompile (mass dump)
// Hash:     9220bb25c9cdbb34


void __fastcall FUN_0064b0e0(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  undefined4 *puVar5;
  undefined1 local_12c [8];
  undefined1 local_124 [8];
  undefined1 local_11c [9];
  undefined1 local_113;
  undefined1 local_112;
  undefined1 local_111;
  undefined1 local_110 [8];
  undefined1 local_108 [8];
  undefined1 local_100 [11];
  undefined1 local_f5;
  undefined1 local_f4;
  undefined1 local_f3;
  undefined1 local_f2;
  undefined1 local_f1;
  undefined1 local_f0 [8];
  undefined1 local_e8 [8];
  undefined1 local_e0 [9];
  undefined1 local_d7;
  undefined1 local_d6;
  undefined1 local_d5;
  undefined1 local_d4 [8];
  undefined1 local_cc [8];
  undefined1 local_c4 [10];
  undefined1 local_ba;
  undefined1 local_b9;
  int local_b8;
  uint local_b4;
  char local_ad;
  int local_ac;
  int local_a8;
  int local_a4;
  uint local_a0;
  undefined1 local_99;
  int local_98;
  uint local_80;
  undefined1 local_79;
  int local_78;
  uint local_60;
  undefined1 local_59;
  int local_58;
  int local_54;
  int local_50;
  int local_38;
  int local_34;
  int local_30;
  char local_15;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069eb46;
  local_10 = ExceptionList;
  local_14 = 0;
  for (local_30 = 0; local_30 < 8; local_30 = local_30 + 1) {
    local_14 = local_14 + *(int *)(param_1 + 0x55dc + local_30 * 4);
  }
  if (local_14 != 0) {
    if (*(int *)(param_1 + 0x55ac) < 4) {
      if ('\0' < *(char *)(param_1 + 0x55d9)) {
        ExceptionList = &local_10;
        for (local_34 = 0; local_34 < 8; local_34 = local_34 + 1) {
          if (*(char *)(param_1 + local_34 + 0x55b1) == '\0') {
            *(undefined1 *)(param_1 + local_34 + 0x55c1) = 0xff;
          }
          else {
            *(undefined1 *)(param_1 + local_34 + 0x55c1) = 0;
          }
        }
        FUN_0064be90();
        if (*(char *)(param_1 + 0x5590) == '\x01') {
          for (local_38 = 0; local_38 < 4; local_38 = local_38 + 1) {
            if (*(int *)(param_1 + 0x52f8 + local_38 * 4) < 1) {
              FUN_00414670();
            }
            else {
              FUN_0040da90();
            }
          }
        }
      }
    }
    else {
      ExceptionList = &local_10;
      FUN_004248f0();
      local_8 = 0;
      local_15 = *(char *)(param_1 + 0x55d9);
      if (((local_15 == '\x02') || (local_15 == '\x03')) &&
         ((*(char *)(param_1 + 0x55ff) < '\0' || ('\x01' < *(char *)(param_1 + 0x55ff))))) {
        local_15 = '\x04';
      }
      switch(local_15) {
      case '\0':
        local_8 = 0xffffffff;
        FUN_00424940();
        ExceptionList = local_10;
        return;
      case '\x01':
        FUN_004248f0();
        local_8 = CONCAT31(local_8._1_3_,1);
        local_50 = 0;
        for (local_54 = 0; local_54 < 8; local_54 = local_54 + 1) {
          if ((local_50 < *(int *)(param_1 + 0x55dc + local_54 * 4)) &&
             (*(char *)(param_1 + local_54 + 0x55b1) != '\0')) {
            local_50 = *(int *)(param_1 + 0x55dc + local_54 * 4);
          }
        }
        for (local_58 = 0; local_58 < 8; local_58 = local_58 + 1) {
          if (*(char *)(param_1 + local_58 + 0x55b1) != '\0') {
            if (*(int *)(param_1 + 0x55dc + local_58 * 4) < local_50) {
              local_ba = (undefined1)local_58;
              FUN_004249a0(&local_ba);
            }
            else {
              local_b9 = (undefined1)local_58;
              FUN_004249a0(&local_b9);
            }
          }
        }
        while (iVar2 = FUN_0063bf40(), iVar2 != 0) {
          uVar3 = FUN_0065d150();
          local_60 = FUN_0063bf40();
          local_60 = uVar3 % local_60;
          puVar1 = (undefined1 *)FUN_00424960(local_60);
          local_59 = *puVar1;
          puVar1 = local_cc;
          uVar3 = local_60;
          FUN_00425ae0(local_c4);
          puVar5 = (undefined4 *)FUN_004372b0(puVar1,uVar3);
          FUN_0064cf00(local_d4,*puVar5,puVar5[1]);
          FUN_004249a0(&local_59);
        }
        local_8 = local_8 & 0xffffff00;
        FUN_00424940();
        break;
      case '\x02':
        FUN_004248f0();
        local_8 = CONCAT31(local_8._1_3_,2);
        for (local_78 = 0; local_78 < 8; local_78 = local_78 + 1) {
          if (*(char *)(param_1 + local_78 + 0x55b1) != '\0') {
            if (*(char *)(param_1 + local_78 + 0x55c1) == -1) {
              local_d5 = (undefined1)local_78;
              FUN_004249a0(&local_d5);
            }
            else if (((int)*(char *)(param_1 + local_78 + 0x55c1) ==
                      *(int *)(param_1 + 0x52d8 + (*(char *)(param_1 + 0x55ff) * -2 + 2) * 4)) ||
                    ((int)*(char *)(param_1 + local_78 + 0x55c1) ==
                     *(int *)(param_1 + 0x52dc + (*(char *)(param_1 + 0x55ff) * -2 + 2) * 4))) {
              local_d6 = (undefined1)local_78;
              FUN_004249a0(&local_d6);
            }
            else if (((int)*(char *)(param_1 + local_78 + 0x55c1) !=
                      *(int *)(param_1 + 0x52d8 + *(char *)(param_1 + 0x55ff) * 8)) &&
                    ((int)*(char *)(param_1 + local_78 + 0x55c1) !=
                     *(int *)(param_1 + 0x52dc + *(char *)(param_1 + 0x55ff) * 8))) {
              local_d7 = (undefined1)local_78;
              FUN_004249a0(&local_d7);
            }
          }
        }
        do {
          iVar2 = FUN_0063bf40();
          if (iVar2 == 0) break;
          uVar3 = FUN_0065d150();
          local_80 = FUN_0063bf40();
          local_80 = uVar3 % local_80;
          puVar1 = (undefined1 *)FUN_00424960(local_80);
          local_79 = *puVar1;
          puVar1 = local_e8;
          uVar3 = local_80;
          FUN_00425ae0(local_e0);
          puVar5 = (undefined4 *)FUN_004372b0(puVar1,uVar3);
          FUN_0064cf00(local_f0,*puVar5,puVar5[1]);
          FUN_004249a0(&local_79);
          uVar3 = FUN_0063bf40();
        } while (uVar3 < 4);
        uVar3 = FUN_0063bf40();
        if (uVar3 < 4) {
          uVar3 = FUN_0065d150();
          if (uVar3 % 2 == 0) {
            local_f2 = *(undefined1 *)
                        (param_1 + 0x52f8 +
                        *(int *)(param_1 + 0x52dc + *(char *)(param_1 + 0x55ff) * 8) * 4);
            FUN_004249a0(&local_f2);
          }
          else {
            local_f1 = *(undefined1 *)
                        (param_1 + 0x52f8 +
                        *(int *)(param_1 + 0x52d8 + *(char *)(param_1 + 0x55ff) * 8) * 4);
            FUN_004249a0(&local_f1);
          }
        }
        local_8 = local_8 & 0xffffff00;
        FUN_00424940();
        break;
      case '\x03':
        FUN_004248f0();
        local_8 = CONCAT31(local_8._1_3_,3);
        for (local_98 = 0; local_98 < 8; local_98 = local_98 + 1) {
          if (*(char *)(param_1 + local_98 + 0x55b1) != '\0') {
            if (*(char *)(param_1 + local_98 + 0x55c1) == -1) {
              local_f3 = (undefined1)local_98;
              FUN_004249a0(&local_f3);
            }
            else if (((int)*(char *)(param_1 + local_98 + 0x55c1) ==
                      *(int *)(param_1 + 0x52d8 + *(char *)(param_1 + 0x55ff) * 8)) ||
                    ((int)*(char *)(param_1 + local_98 + 0x55c1) ==
                     *(int *)(param_1 + 0x52dc + *(char *)(param_1 + 0x55ff) * 8))) {
              local_f4 = (undefined1)local_98;
              FUN_004249a0(&local_f4);
            }
            else if (((int)*(char *)(param_1 + local_98 + 0x55c1) !=
                      *(int *)(param_1 + 0x52d8 + (*(char *)(param_1 + 0x55ff) * -2 + 2) * 4)) &&
                    ((int)*(char *)(param_1 + local_98 + 0x55c1) !=
                     *(int *)(param_1 + 0x52dc + (*(char *)(param_1 + 0x55ff) * -2 + 2) * 4))) {
              local_f5 = (undefined1)local_98;
              FUN_004249a0(&local_f5);
            }
          }
        }
        do {
          iVar2 = FUN_0063bf40();
          if (iVar2 == 0) break;
          uVar3 = FUN_0065d150();
          local_a0 = FUN_0063bf40();
          local_a0 = uVar3 % local_a0;
          puVar1 = (undefined1 *)FUN_00424960(local_a0);
          local_99 = *puVar1;
          puVar1 = local_108;
          uVar3 = local_a0;
          FUN_00425ae0(local_100);
          puVar5 = (undefined4 *)FUN_004372b0(puVar1,uVar3);
          FUN_0064cf00(local_110,*puVar5,puVar5[1]);
          FUN_004249a0(&local_99);
          uVar3 = FUN_0063bf40();
        } while (uVar3 < 4);
        uVar3 = FUN_0063bf40();
        if (uVar3 < 4) {
          uVar3 = FUN_0065d150();
          if (uVar3 % 2 == 0) {
            local_112 = *(undefined1 *)
                         (param_1 + 0x52f8 +
                         *(int *)(param_1 + 0x52dc + (*(char *)(param_1 + 0x55ff) * -2 + 2) * 4) * 4
                         );
            FUN_004249a0(&local_112);
          }
          else {
            local_111 = *(undefined1 *)
                         (param_1 + 0x52f8 +
                         *(int *)(param_1 + 0x52d8 + (*(char *)(param_1 + 0x55ff) * -2 + 2) * 4) * 4
                         );
            FUN_004249a0(&local_111);
          }
        }
        local_8 = local_8 & 0xffffff00;
        FUN_00424940();
        break;
      case '\x04':
        for (local_a4 = 0; local_a4 < 8; local_a4 = local_a4 + 1) {
          if (*(char *)(param_1 + local_a4 + 0x55b1) != '\0') {
            local_113 = (undefined1)local_a4;
            FUN_004249a0(&local_113);
          }
        }
      }
      for (local_a8 = 0; local_a8 < 8; local_a8 = local_a8 + 1) {
        *(undefined1 *)(param_1 + local_a8 + 0x55c1) = 0xff;
      }
      for (local_ac = 0; local_ac < 4; local_ac = local_ac + 1) {
        iVar2 = FUN_0063bf40();
        if (iVar2 != 0) {
          uVar3 = FUN_0065d150();
          local_b4 = FUN_0063bf40();
          local_b4 = uVar3 % local_b4;
          pcVar4 = (char *)FUN_00424960(local_b4);
          local_ad = *pcVar4;
          puVar1 = local_124;
          uVar3 = local_b4;
          FUN_00425ae0(local_11c);
          puVar5 = (undefined4 *)FUN_004372b0(puVar1,uVar3);
          FUN_0064cf00(local_12c,*puVar5,puVar5[1]);
          *(undefined1 *)(param_1 + 0x55c1 + (int)local_ad) = 0;
        }
      }
      FUN_0064be90();
      if (*(char *)(param_1 + 0x5590) == '\x01') {
        for (local_b8 = 0; local_b8 < 4; local_b8 = local_b8 + 1) {
          if (*(int *)(param_1 + 0x52f8 + local_b8 * 4) < 1) {
            FUN_00414670();
          }
          else {
            FUN_0040da90();
          }
        }
      }
      *(undefined1 *)(param_1 + 0x55ff) = 0xff;
      local_8 = 0xffffffff;
      FUN_00424940();
    }
  }
  ExceptionList = local_10;
  return;
}

