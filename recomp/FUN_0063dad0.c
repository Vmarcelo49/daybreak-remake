// ============================================
// Address:  0x0063dad0
// Original: FUN_0063dad0
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_0063dad0(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int *piVar6;
  float10 fVar7;
  allocator<char> local_64 [12];
  allocator<char> local_58 [12];
  int local_4c;
  int local_48;
  allocator<char> local_44 [16];
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  char local_7;
  char local_6;
  char local_5;
  
  *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + 1;
  if (*(char *)(param_1 + 0x7f4) == '\0') {
    while ((iVar1 = FUN_0063bf40(), iVar1 != 0 &&
           (iVar1 = FUN_0063f9f0(),
           *(int *)(iVar1 + 8) < (int)((*(int *)(param_1 + 0x1c) - (uint)DAT_006cfdc5) + -1)))) {
      FUN_0063fa10();
    }
    while ((iVar1 = FUN_0063bf40(), iVar1 != 0 &&
           (iVar1 = FUN_0063fb90(),
           *(int *)(iVar1 + 8) < (int)((*(int *)(param_1 + 0x1c) - (uint)DAT_006cfdc5) + -1)))) {
      FUN_0063fbb0();
    }
    iVar1 = FUN_0063bf40();
    iVar2 = FUN_0063bf40();
    if (iVar1 + iVar2 == 0) {
      *(byte *)(param_1 + 0x7f4) = DAT_006cfdc5;
    }
    else {
      local_7 = '\0';
      iVar1 = FUN_0063bf40();
      if (iVar1 == 0) {
        local_7 = '\x01';
      }
      else {
        iVar1 = FUN_0063bf40();
        if (iVar1 != 0) {
          iVar1 = FUN_0063f9f0();
          iVar2 = FUN_0063fb90();
          if (*(int *)(iVar2 + 8) < *(int *)(iVar1 + 8)) {
            local_7 = '\x01';
          }
        }
      }
      if (local_7 == '\0') {
        for (local_c = 0; local_c < 4; local_c = local_c + 1) {
          iVar1 = FUN_0063f9f0();
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0x14) =
               *(undefined4 *)(iVar1 + 0xc + local_c * 4);
          iVar1 = FUN_0063f9f0();
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0x18) =
               *(undefined4 *)(iVar1 + 0x1c + local_c * 4);
          iVar1 = FUN_0063f9f0();
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0x1c) =
               *(undefined4 *)(iVar1 + 0x2c + local_c * 4);
          iVar1 = FUN_0063f9f0();
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0x5c) =
               *(undefined4 *)(iVar1 + 0x3c + local_c * 4);
          iVar1 = FUN_0063f9f0();
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_c * 4) + 100) =
               *(undefined4 *)(iVar1 + 0x4c + local_c * 4);
          iVar1 = *(int *)(param_1 + 0x129c + local_c * 4);
          iVar2 = FUN_0063f9f0();
          if (*(int *)(iVar1 + 0xae0c) != *(int *)(iVar2 + 0x5c + local_c * 4)) {
            iVar1 = FUN_0063f9f0();
            FUN_00421410(0,*(undefined4 *)(iVar1 + 0x5c + local_c * 4));
            iVar1 = FUN_0063f9f0();
            FUN_00421410(1,*(undefined4 *)(iVar1 + 0x5c + local_c * 4));
          }
          iVar1 = FUN_0063f9f0();
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xadf0) =
               *(undefined4 *)(iVar1 + 0x6c + local_c * 4);
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xadec) =
               *(undefined4 *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xadf0);
          iVar1 = FUN_0063f9f0();
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xadf8) =
               *(undefined4 *)(iVar1 + 0x7c + local_c * 4);
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xadf4) =
               *(undefined4 *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xadf8);
          iVar1 = FUN_0063f9f0();
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xae08) =
               *(undefined4 *)(iVar1 + 0x8c + local_c * 4);
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xae04) =
               *(undefined4 *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xae08);
          if ((*(int *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xae04) <
               **(int **)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xade4)) ||
             (*(int *)(*(int *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xade4) + 0x20) != 0)) {
            *(int *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xae04) =
                 *(int *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xae04) + 1;
          }
          if ((*(int *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xae08) <
               **(int **)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xade8)) ||
             (*(int *)(*(int *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xade8) + 0x20) != 0)) {
            *(int *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xae08) =
                 *(int *)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xae08) + 1;
          }
        }
        FUN_0063fa10();
      }
      else {
        for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
          iVar1 = FUN_0063fb90();
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0x14) =
               *(undefined4 *)(iVar1 + 0xc + local_10 * 4);
          iVar1 = FUN_0063fb90();
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0x18) =
               *(undefined4 *)(iVar1 + 0x1c + local_10 * 4);
          iVar1 = FUN_0063fb90();
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0x1c) =
               *(undefined4 *)(iVar1 + 0x2c + local_10 * 4);
          iVar1 = FUN_0063fb90();
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0x5c) =
               *(undefined4 *)(iVar1 + 0x3c + local_10 * 4);
          iVar1 = FUN_0063fb90();
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 100) =
               *(undefined4 *)(iVar1 + 0x4c + local_10 * 4);
          iVar1 = *(int *)(param_1 + 0x129c + local_10 * 4);
          iVar2 = FUN_0063fb90();
          if (*(int *)(iVar1 + 0xae0c) != *(int *)(iVar2 + 0x5c + local_10 * 4)) {
            *(undefined4 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0xae04) = 0;
            iVar1 = FUN_0063fb90();
            FUN_00421410(0,*(undefined4 *)(iVar1 + 0x5c + local_10 * 4));
          }
          iVar1 = FUN_0063fb90();
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0xadec) =
               *(undefined4 *)(iVar1 + 0x6c + local_10 * 4);
          iVar1 = FUN_0063fb90();
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0xadf4) =
               *(undefined4 *)(iVar1 + 0x7c + local_10 * 4);
          iVar1 = FUN_0063fb90();
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0xae04) =
               *(undefined4 *)(iVar1 + 0x8c + local_10 * 4);
          iVar1 = *(int *)(param_1 + 0x129c + local_10 * 4);
          iVar2 = FUN_0063fb90();
          if (*(int *)(iVar1 + 0xae10) != *(int *)(iVar2 + 0x9c + local_10 * 4)) {
            *(undefined4 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0xae08) = 0;
            iVar1 = FUN_0063fb90();
            FUN_00421410(1,*(undefined4 *)(iVar1 + 0x9c + local_10 * 4));
          }
          iVar1 = FUN_0063fb90();
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0xadf0) =
               *(undefined4 *)(iVar1 + 0xac + local_10 * 4);
          iVar1 = FUN_0063fb90();
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0xadf8) =
               *(undefined4 *)(iVar1 + 0xbc + local_10 * 4);
          iVar1 = FUN_0063fb90();
          *(undefined4 *)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0xae08) =
               *(undefined4 *)(iVar1 + 0xcc + local_10 * 4);
        }
        FUN_0063fbb0();
      }
    }
  }
  else {
    *(char *)(param_1 + 0x7f4) = *(char *)(param_1 + 0x7f4) + -1;
  }
  for (local_14 = 0; local_14 < 4; local_14 = local_14 + 1) {
    *(undefined1 *)(*(int *)(param_1 + 0x129c + local_14 * 4) + 0x6fc) = 1;
    *(undefined1 *)(*(int *)(param_1 + 0x129c + local_14 * 4) + 0x740) = 1;
  }
  local_6 = -1;
  for (local_18 = 0; local_18 < 4; local_18 = local_18 + 1) {
    if (*(int *)(*(int *)(param_1 + 0x129c + local_18 * 4) + 0x828) != 0) {
      local_6 = (char)local_18;
    }
  }
  if (local_6 < '\0') {
    for (local_20 = 0; local_20 < 4; local_20 = local_20 + 1) {
      FUN_00420850();
    }
    FUN_00635d40();
    for (local_24 = 0; local_24 < 4; local_24 = local_24 + 1) {
      FUN_0041f580();
    }
    for (local_28 = 0; local_28 < 4; local_28 = local_28 + 1) {
      FUN_004201a0();
    }
    for (local_2c = 0; local_2c < 4; local_2c = local_2c + 1) {
      FUN_0042e110();
    }
  }
  else {
    FUN_00635d40();
    FUN_0041f580();
    for (local_1c = 0; local_1c < 4; local_1c = local_1c + 1) {
      FUN_004201a0();
    }
    FUN_0042e110();
  }
  FUN_006430f0();
  for (local_30 = 0; local_30 < 4; local_30 = local_30 + 1) {
    Concurrency::details::CollectionTypes::Count::Increment
              ((Count *)(param_1 + 0x140c + local_30 * 0xb74));
  }
  FUN_00435a20();
  FUN_0065d670();
  for (local_34 = 0; local_34 < 4; local_34 = local_34 + 1) {
    FUN_0065d670();
    FUN_00420b30();
    if (*(char *)(*(int *)(param_1 + 0x129c + local_34 * 4) + 0xaecc) != '\0') {
      std::allocator<char>::allocator<char>(local_44);
      uVar4 = *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x129c + local_34 * 4) + 0xaed0) + 0xaed4)
      ;
      uVar3 = FUN_00423750(0,0,0);
      D3DXVec3Transform(local_44,uVar3,uVar4);
      uVar4 = std::allocator<char>::allocator<char>(local_44);
      puVar5 = (undefined4 *)FUN_004237f0(uVar4);
      iVar1 = *(int *)(param_1 + 0x129c + local_34 * 4);
      *(undefined4 *)(iVar1 + 0x14) = *puVar5;
      *(undefined4 *)(iVar1 + 0x18) = puVar5[1];
      *(undefined4 *)(iVar1 + 0x1c) = puVar5[2];
    }
    uVar4 = *(undefined4 *)(*(int *)(param_1 + 0x129c + local_34 * 4) + 0x380);
    uVar3 = FUN_00423750(0,0,0);
    D3DXVec3Transform(*(int *)(param_1 + 0x129c + local_34 * 4) + 0xa4,uVar3,uVar4);
    uVar4 = *(undefined4 *)(*(int *)(param_1 + 0x129c + local_34 * 4) + 900);
    uVar3 = FUN_00423750(0xc1c80000,0,0);
    D3DXVec3Transform(*(int *)(param_1 + 0x129c + local_34 * 4) + 0xb4,uVar3,uVar4);
    uVar4 = std::allocator<char>::allocator<char>
                      ((allocator<char> *)(*(int *)(param_1 + 0x129c + local_34 * 4) + 0xa4));
    puVar5 = (undefined4 *)FUN_004237f0(uVar4);
    iVar1 = *(int *)(param_1 + 0x129c + local_34 * 4);
    *(undefined4 *)(iVar1 + 0x2c0) = *puVar5;
    *(undefined4 *)(iVar1 + 0x2c4) = puVar5[1];
    *(undefined4 *)(iVar1 + 0x2c8) = puVar5[2];
    uVar4 = std::allocator<char>::allocator<char>
                      ((allocator<char> *)(*(int *)(param_1 + 0x129c + local_34 * 4) + 0xb4));
    puVar5 = (undefined4 *)FUN_004237f0(uVar4);
    iVar1 = *(int *)(param_1 + 0x129c + local_34 * 4);
    *(undefined4 *)(iVar1 + 0x2cc) = *puVar5;
    *(undefined4 *)(iVar1 + 0x2d0) = puVar5[1];
    *(undefined4 *)(iVar1 + 0x2d4) = puVar5[2];
    FUN_00434840();
    FUN_0065d6a0();
    FUN_00420880();
    if (local_6 < '\0') {
      FUN_004348c0();
    }
  }
  FUN_00435b20();
  local_5 = '\0';
  if (*(int *)(*(int *)(param_1 + 19000) + DAT_006cfdb4 * 4) != 0) {
    FUN_00657390();
    if ((*(int *)(*(int *)(*(int *)(param_1 + 19000) + DAT_006cfdb4 * 4) + 0x44) != 0) ||
       (*(int *)(*(int *)(*(int *)(param_1 + 19000) + DAT_006cfdb4 * 4) + 0x48) != 0)) {
      *(undefined1 *)(*(int *)(*(int *)(param_1 + 19000) + DAT_006cfdb4 * 4) + 1) = 1;
    }
    if (*(int *)(*(int *)(*(int *)(param_1 + 19000) + DAT_006cfdb4 * 4) + 0x4c) != 0) {
      *(undefined1 *)(*(int *)(*(int *)(param_1 + 19000) + DAT_006cfdb4 * 4) + 1) = 0;
    }
    if (*(char *)(*(int *)(*(int *)(param_1 + 19000) + DAT_006cfdb4 * 4) + 1) != '\0') {
      local_5 = '\x01';
      FUN_0063b650();
      uVar4 = *(undefined4 *)(param_1 + 0x129c + DAT_006cfba4 * 4);
      uVar3 = FUN_004233c0(uVar4);
      FUN_0063b750(uVar3,uVar4);
    }
  }
  for (local_48 = 0; iVar1 = DAT_006cfba4, local_48 < 4; local_48 = local_48 + 1) {
    local_4c = *(int *)(param_1 + 0x129c + local_48 * 4);
    if (*(char *)(local_4c + 0xaecc) != '\0') {
      local_4c = *(int *)(local_4c + 0xaed0);
    }
    if (local_5 == '\0') {
      if (*(char *)(local_4c + 0x2dc) == '\0') {
        if (*(int *)(local_4c + 0x304) < 0) {
          uVar4 = 0;
          piVar6 = (int *)FUN_00658a10(*(undefined4 *)(local_4c + 0x300));
          FUN_00632e70(*piVar6 + 0x14,uVar4);
        }
        else {
          uVar4 = 0;
          piVar6 = (int *)FUN_00658a10(0);
          FUN_00632e70(*piVar6 + 0x14,uVar4);
        }
        FUN_00632ed0(local_4c + 0x14,0);
        if (*(int *)(local_4c + 0x684) < 0) {
          FUN_006331e0();
        }
        else {
          FUN_00633140(*(undefined4 *)(local_4c + 0x684),
                       *(float *)(local_4c + 0x5c) + *(float *)(local_4c + 100));
        }
      }
      else {
        std::allocator<char>::allocator<char>(local_58);
        std::allocator<char>::allocator<char>(local_64);
        FUN_00422f90(local_58,local_64);
        FUN_0063b820();
        FUN_006330e0(local_64);
        FUN_00633110(local_58);
      }
    }
    else {
      FUN_00632e70(local_4c + 0x14,0);
      FUN_00632ed0(*(int *)(*(int *)(param_1 + 19000) + DAT_006cfdb4 * 4) + 0x7c,0);
    }
    FUN_00633220();
  }
  if (local_5 == '\0') {
    (**(code **)(*DAT_006d8428 + 0x38))
              (DAT_006d8428,*(undefined4 *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x14),
               *(float *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x18) + 150.0,
               *(undefined4 *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x1c),1);
    fVar7 = (float10)FUN_0065d010(*(undefined4 *)(*(int *)(param_1 + 0x129c + iVar1 * 4) + 0x5c),0,
                                  0x3f800000,0,1);
    fVar7 = (float10)FUN_0065d050(*(undefined4 *)(*(int *)(param_1 + 0x129c + iVar1 * 4) + 0x5c),0,
                                  (float)fVar7);
    (**(code **)(*DAT_006d8428 + 0x34))(DAT_006d8428,(float)fVar7);
  }
  else {
    (**(code **)(*DAT_006d8428 + 0x38))
              (DAT_006d8428,
               *(undefined4 *)(*(int *)(*(int *)(param_1 + 19000) + DAT_006cfdb4 * 4) + 0x7c),
               *(float *)(*(int *)(*(int *)(param_1 + 19000) + DAT_006cfdb4 * 4) + 0x80) + 150.0,
               *(undefined4 *)(*(int *)(*(int *)(param_1 + 19000) + DAT_006cfdb4 * 4) + 0x84),1);
    fVar7 = (float10)FUN_0065d010(*(undefined4 *)
                                   (*(int *)(*(int *)(param_1 + 19000) + DAT_006cfdb4 * 4) + 0xc4),0
                                  ,0x3f800000,0,1);
    fVar7 = (float10)FUN_0065d050(*(undefined4 *)
                                   (*(int *)(*(int *)(param_1 + 19000) + DAT_006cfdb4 * 4) + 0xc4),0
                                  ,(float)fVar7);
    (**(code **)(*DAT_006d8428 + 0x34))(DAT_006d8428,(float)fVar7);
  }
  (**(code **)(*DAT_006d8428 + 0x44))(DAT_006d8428);
  FUN_0065d6a0();
  return *(undefined4 *)(param_1 + 0x4a3c);
}

