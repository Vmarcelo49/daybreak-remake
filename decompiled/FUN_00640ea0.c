// Function: FUN_00640ea0
// Address:  0x00640ea0
// Source:   batch_decompile (mass dump)
// Hash:     305a8391cea678dc


int __fastcall FUN_00640ea0(int param_1)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  undefined1 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 local_7d;
  uint local_7c;
  undefined1 local_78 [8];
  undefined4 local_70;
  uint local_6c;
  uint local_68;
  uint local_64;
  uint local_60;
  uint local_5c;
  uint local_58;
  uint local_54;
  uint local_50;
  int local_4c;
  char local_45;
  int local_44;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e7a8;
  local_10 = ExceptionList;
  local_11 = '\0';
  for (local_18 = 0; local_18 < 4; local_18 = local_18 + 1) {
    if (*(int *)(*(int *)(param_1 + 0x129c + local_18 * 4) + 0xae0c) !=
        *(int *)(*(int *)(param_1 + 0x129c + local_18 * 4) + 0xae10)) {
      local_11 = '\x01';
    }
  }
  if (local_11 == '\0') {
    ExceptionList = &local_10;
    *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x1c);
    for (local_20 = 0; local_20 < 4; local_20 = local_20 + 1) {
      *(undefined4 *)(param_1 + 0x168 + local_20 * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_20 * 4) + 0x14);
      *(undefined4 *)(param_1 + 0x178 + local_20 * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_20 * 4) + 0x18);
      *(undefined4 *)(param_1 + 0x188 + local_20 * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_20 * 4) + 0x1c);
      *(undefined4 *)(param_1 + 0x198 + local_20 * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_20 * 4) + 0x5c);
      *(undefined4 *)(param_1 + 0x1a8 + local_20 * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_20 * 4) + 100);
      *(undefined4 *)(param_1 + 0x1b8 + local_20 * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_20 * 4) + 0xae0c);
      *(undefined4 *)(param_1 + 0x1c8 + local_20 * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_20 * 4) + 0xadec);
      *(undefined4 *)(param_1 + 0x1d8 + local_20 * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_20 * 4) + 0xadf4);
      *(undefined4 *)(param_1 + 0x1e8 + local_20 * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_20 * 4) + 0xae04);
    }
    FUN_00419370(0,param_1 + 0x15c,0x30,0x88);
  }
  else {
    ExceptionList = &local_10;
    *(undefined4 *)(param_1 + 0x200) = *(undefined4 *)(param_1 + 0x1c);
    for (local_1c = 0; local_1c < 4; local_1c = local_1c + 1) {
      *(undefined4 *)(param_1 + 0x204 + local_1c * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0x14);
      *(undefined4 *)(param_1 + 0x214 + local_1c * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0x18);
      *(undefined4 *)(param_1 + 0x224 + local_1c * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0x1c);
      *(undefined4 *)(param_1 + 0x234 + local_1c * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0x5c);
      *(undefined4 *)(param_1 + 0x244 + local_1c * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 100);
      *(undefined4 *)(param_1 + 0x254 + local_1c * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0xae0c);
      *(undefined4 *)(param_1 + 0x264 + local_1c * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0xadec);
      *(undefined4 *)(param_1 + 0x274 + local_1c * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0xadf4);
      *(undefined4 *)(param_1 + 0x284 + local_1c * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0xae04);
      *(undefined4 *)(param_1 + 0x294 + local_1c * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0xae10);
      *(undefined4 *)(param_1 + 0x2a4 + local_1c * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0xadf0);
      *(undefined4 *)(param_1 + 0x2b4 + local_1c * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0xadf8);
      *(undefined4 *)(param_1 + 0x2c4 + local_1c * 4) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_1c * 4) + 0xae08);
    }
    FUN_00419370(0,param_1 + 0x1f8,0x30,0x88);
  }
  for (local_24 = 0; local_24 < 4; local_24 = local_24 + 1) {
    if (((*(int *)(param_1 + 0x5f0 + local_24 * 0x18) !=
          *(int *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x6b8)) ||
        (*(int *)(param_1 + 0x5f4 + local_24 * 0x18) !=
         *(int *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x6bc))) ||
       (*(char *)(param_1 + 0x5f8 + local_24 * 0x18) !=
        *(char *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x79c))) {
      *(undefined4 *)(param_1 + 0x5f0 + local_24 * 0x18) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x6b8);
      *(undefined4 *)(param_1 + 0x5f4 + local_24 * 0x18) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x6bc);
      *(undefined1 *)(param_1 + 0x5f8 + local_24 * 0x18) =
           *(undefined1 *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x79c);
      FUN_00415d30(0,param_1 + 0x5e4 + local_24 * 0x18,0,8);
    }
    if (*(int *)(param_1 + 0x650 + local_24 * 0x10) <
        *(int *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0xa0)) {
      *(undefined4 *)(param_1 + 0x650 + local_24 * 0x10) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0xa0);
      FUN_00415d30(0,param_1 + 0x644 + local_24 * 0x10,0,8);
    }
    *(undefined4 *)(param_1 + 0x650 + local_24 * 0x10) =
         *(undefined4 *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0xa0);
    if ((int)*(short *)(param_1 + 0x400 + local_24 * 0x10) <
        *(int *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x7ac)) {
      *(undefined2 *)(param_1 + 0x400 + local_24 * 0x10) =
           *(undefined2 *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x7ac);
      FUN_00415d30(0,param_1 + 0x3f4 + local_24 * 0x10,0,8);
    }
    *(undefined2 *)(param_1 + 0x400 + local_24 * 0x10) =
         *(undefined2 *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x7ac);
    if (*(int *)(param_1 + 0x690 + local_24 * 0x10) !=
        *(int *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x300)) {
      *(undefined4 *)(param_1 + 0x690 + local_24 * 0x10) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x300);
      FUN_00415d30(0,param_1 + 0x684 + local_24 * 0x10,0,0x88);
    }
    if (*(int *)(param_1 + 0x6d0 + local_24 * 0x10) !=
        *(int *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x304)) {
      *(undefined4 *)(param_1 + 0x6d0 + local_24 * 0x10) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x304);
      FUN_00415d30(0,param_1 + 0x6c4 + local_24 * 0x10,0,0x88);
    }
    if (((*(float *)(param_1 + 0x2e0 + local_24 * 0x20) !=
          *(float *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x2c)) ||
        (*(float *)(param_1 + 0x2e4 + local_24 * 0x20) !=
         *(float *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x30))) ||
       ((*(float *)(param_1 + 0x2e8 + local_24 * 0x20) !=
         *(float *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x34) ||
        (*(float *)(param_1 + 0x2ec + local_24 * 0x20) !=
         *(float *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x68))))) {
      *(undefined4 *)(param_1 + 0x2e0 + local_24 * 0x20) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x2c);
      *(undefined4 *)(param_1 + 0x2e4 + local_24 * 0x20) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x30);
      *(undefined4 *)(param_1 + 0x2e8 + local_24 * 0x20) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x34);
      *(undefined4 *)(param_1 + 0x2ec + local_24 * 0x20) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x68);
      *(undefined4 *)(param_1 + 0x2f0 + local_24 * 0x20) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x2d8);
      FUN_00415d30(0,param_1 + 0x2d4 + local_24 * 0x20,0,8);
    }
    for (local_28 = 0; local_28 < 9; local_28 = local_28 + 1) {
      if (((int)*(short *)(param_1 + local_24 * 0x6c + 0x43e + local_28 * 0xc) <
           *(int *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x7dc + local_28 * 4)) ||
         ((2 < *(short *)(param_1 + local_24 * 0x6c + 0x43e + local_28 * 0xc) &&
          (*(int *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x7dc + local_28 * 4) == 0)))) {
        *(undefined1 *)(param_1 + local_24 * 0x6c + 0x43d + local_28 * 0xc) = (undefined1)local_28;
        *(undefined2 *)(param_1 + local_24 * 0x6c + 0x43e + local_28 * 0xc) =
             *(undefined2 *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x7dc + local_28 * 4);
        FUN_00415d30(0,param_1 + 0x434 + local_24 * 0x6c + local_28 * 0xc,0,8);
      }
      *(undefined2 *)(param_1 + local_24 * 0x6c + 0x43e + local_28 * 0xc) =
           *(undefined2 *)(*(int *)(param_1 + 0x129c + local_24 * 4) + 0x7dc + local_28 * 4);
    }
  }
  for (local_2c = 0; local_2c < 4; local_2c = local_2c + 1) {
    FUN_004248f0();
    local_8 = 0;
    FUN_00424940();
    for (local_44 = 1; local_44 < 8; local_44 = local_44 + 1) {
      if (((&DAT_006cfdd1)[local_44] != '\0') && (local_2c == (char)(&DAT_006cfdd9)[local_44])) {
        local_7d = (undefined1)local_44;
        FUN_004249a0(&local_7d);
      }
    }
    iVar1 = FUN_0063bf40();
    if (iVar1 != 0) {
      uVar3 = *(uint *)(param_1 + 0x1c) & 0x80000001;
      if ((int)uVar3 < 0) {
        uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
      }
      if (uVar3 != 0) {
        local_45 = '\0';
        for (local_4c = 0; local_4c < 4; local_4c = local_4c + 1) {
          if (*(int *)(param_1 + local_2c * 0x1c + 0x35c + local_4c * 4) !=
              *(int *)(*(int *)(param_1 + 0x129c + local_4c * 4) + 0x7a4)) {
            local_45 = '\x01';
          }
          *(undefined4 *)(param_1 + local_2c * 0x1c + 0x35c + local_4c * 4) =
               *(undefined4 *)(*(int *)(param_1 + 0x129c + local_4c * 4) + 0x7a4);
        }
        if (*(char *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x318) == '\x01') {
          if ((int)*(short *)(param_1 + 0x36c + local_2c * 0x1c) !=
              *(int *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x83c)) {
            local_45 = '\x01';
          }
          *(undefined2 *)(param_1 + 0x36c + local_2c * 0x1c) =
               *(undefined2 *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x83c);
        }
        else if (*(char *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x318) == '\x02') {
          if ((int)*(short *)(param_1 + 0x36c + local_2c * 0x1c) !=
              *(int *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x840)) {
            local_45 = '\x01';
          }
          *(undefined2 *)(param_1 + 0x36c + local_2c * 0x1c) =
               *(undefined2 *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x840);
        }
        else {
          if ((int)*(short *)(param_1 + 0x36c + local_2c * 0x1c) !=
              *(int *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x838)) {
            local_45 = '\x01';
          }
          *(undefined2 *)(param_1 + 0x36c + local_2c * 0x1c) =
               *(undefined2 *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x838);
        }
        if (local_45 != '\0') {
          local_50 = 0;
          while (uVar3 = FUN_0063bf40(), local_50 < uVar3) {
            uVar6 = 8;
            uVar5 = 0;
            iVar1 = param_1 + 0x354 + local_2c * 0x1c;
            pcVar2 = (char *)FUN_00424960(local_50);
            FUN_00419370((int)*pcVar2,iVar1,uVar5,uVar6);
            local_50 = local_50 + 1;
          }
        }
        if ((int)*(short *)(param_1 + 0x3cc + local_2c * 0xc) !=
            *(int *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x834)) {
          *(undefined2 *)(param_1 + 0x3cc + local_2c * 0xc) =
               *(undefined2 *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x834);
          if (*(short *)(param_1 + 0x3cc + local_2c * 0xc) == 1000) {
            local_54 = 0;
            while (uVar3 = FUN_0063bf40(), local_54 < uVar3) {
              uVar6 = 8;
              uVar5 = 0;
              iVar1 = param_1 + 0x3c4 + local_2c * 0xc;
              pcVar2 = (char *)FUN_00424960(local_54);
              FUN_00419370((int)*pcVar2,iVar1,uVar5,uVar6);
              local_54 = local_54 + 1;
            }
          }
          else {
            local_58 = 0;
            while (uVar3 = FUN_0063bf40(), local_58 < uVar3) {
              uVar6 = 0x42;
              uVar5 = 0;
              iVar1 = param_1 + 0x3c4 + local_2c * 0xc;
              pcVar2 = (char *)FUN_00424960(local_58);
              FUN_00419370((int)*pcVar2,iVar1,uVar5,uVar6);
              local_58 = local_58 + 1;
            }
          }
        }
      }
      if ((int)*(short *)(param_1 + 0x76c + local_2c * 0xc) !=
          *(int *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x684)) {
        *(undefined2 *)(param_1 + 0x76c + local_2c * 0xc) =
             *(undefined2 *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x684);
        local_5c = 0;
        while (uVar3 = FUN_0063bf40(), local_5c < uVar3) {
          uVar6 = 0x88;
          uVar5 = 0;
          iVar1 = param_1 + 0x764 + local_2c * 0xc;
          pcVar2 = (char *)FUN_00424960(local_5c);
          FUN_00415d30((int)*pcVar2,iVar1,uVar5,uVar6);
          local_5c = local_5c + 1;
        }
      }
      if ((int)*(short *)(param_1 + 0x79c + local_2c * 0xc) !=
          (int)*(char *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x310)) {
        *(short *)(param_1 + 0x79c + local_2c * 0xc) =
             (short)*(char *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x310);
        local_60 = 0;
        while (uVar3 = FUN_0063bf40(), local_60 < uVar3) {
          uVar6 = 0x88;
          uVar5 = 0;
          iVar1 = param_1 + 0x794 + local_2c * 0xc;
          pcVar2 = (char *)FUN_00424960(local_60);
          FUN_00415d30((int)*pcVar2,iVar1,uVar5,uVar6);
          local_60 = local_60 + 1;
        }
      }
      if (((int)*(short *)(param_1 + 0x70c + local_2c * 0xc) !=
           *(int *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x6dc)) ||
         ((int)*(short *)(param_1 + 0x70e + local_2c * 0xc) !=
          *(int *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x720))) {
        *(undefined2 *)(param_1 + 0x70c + local_2c * 0xc) =
             *(undefined2 *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x6dc);
        *(undefined2 *)(param_1 + 0x70e + local_2c * 0xc) =
             *(undefined2 *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x720);
        local_64 = 0;
        while (uVar3 = FUN_0063bf40(), local_64 < uVar3) {
          uVar6 = 8;
          uVar5 = 0;
          iVar1 = param_1 + 0x704 + local_2c * 0xc;
          pcVar2 = (char *)FUN_00424960(local_64);
          FUN_00419370((int)*pcVar2,iVar1,uVar5,uVar6);
          local_64 = local_64 + 1;
        }
      }
      if (((int)*(short *)(param_1 + 0x73c + local_2c * 0xc) !=
           *(int *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x724)) ||
         ((int)*(short *)(param_1 + 0x73e + local_2c * 0xc) !=
          *(int *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x728))) {
        *(undefined2 *)(param_1 + 0x73c + local_2c * 0xc) =
             *(undefined2 *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x724);
        *(undefined2 *)(param_1 + 0x73e + local_2c * 0xc) =
             *(undefined2 *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x728);
        if ((*(short *)(param_1 + 0x73c + local_2c * 0xc) == 0) ||
           (*(short *)(param_1 + 0x73e + local_2c * 0xc) == 0)) {
          local_68 = 0;
          while (uVar3 = FUN_0063bf40(), local_68 < uVar3) {
            uVar6 = 8;
            uVar5 = 0;
            iVar1 = param_1 + 0x734 + local_2c * 0xc;
            pcVar2 = (char *)FUN_00424960(local_68);
            FUN_00419370((int)*pcVar2,iVar1,uVar5,uVar6);
            local_68 = local_68 + 1;
          }
        }
        else {
          local_6c = 0;
          while (uVar3 = FUN_0063bf40(), local_6c < uVar3) {
            uVar6 = 0x42;
            uVar5 = 5;
            iVar1 = param_1 + 0x734 + local_2c * 0xc;
            pcVar2 = (char *)FUN_00424960(local_6c);
            FUN_00419370((int)*pcVar2,iVar1,uVar5,uVar6);
            local_6c = local_6c + 1;
          }
        }
      }
      if (*(char *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x2dc) != '\0') {
        FUN_0063f1e0();
        local_70 = *(undefined4 *)(*(int *)(param_1 + 0x129c + local_2c * 4) + 0x7a0);
        local_7c = 0;
        while (uVar3 = FUN_0063bf40(), local_7c < uVar3) {
          uVar6 = 2;
          uVar5 = 5;
          puVar4 = local_78;
          pcVar2 = (char *)FUN_00424960(local_7c);
          FUN_00419370((int)*pcVar2,puVar4,uVar5,uVar6);
          local_7c = local_7c + 1;
        }
      }
    }
    local_8 = 0xffffffff;
    FUN_00424940();
  }
  iVar1 = *(int *)(param_1 + 0x1c) / 0x3c;
  if (*(int *)(param_1 + 0x1c) % 0x3c != 0) {
    *(undefined2 *)(param_1 + 0x7cc) = *(undefined2 *)(param_1 + 0x12b0);
    *(undefined2 *)(param_1 + 0x7ce) = *(undefined2 *)(param_1 + 0x12bc);
    iVar1 = FUN_00415d30(0,param_1 + 0x7c4,0,8);
  }
  ExceptionList = local_10;
  return iVar1;
}

