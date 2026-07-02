// Function: FUN_006926a0
// Address:  0x006926a0
// Source:   batch_decompile (mass dump)
// Hash:     c7b265926729aeed


longlong FUN_006926a0(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6,
                     uint param_7,uint param_8)

{
  ulonglong uVar1;
  bool bVar2;
  byte bVar3;
  byte bVar4;
  bool bVar5;
  byte bVar6;
  byte bVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  uint extraout_EDX;
  bool bVar13;
  longlong lVar14;
  undefined8 uVar15;
  uint local_a8;
  uint local_98;
  uint local_94;
  uint local_90;
  uint local_8c;
  uint local_88;
  uint local_84;
  int local_80;
  uint local_64;
  uint local_60;
  uint local_5c;
  int local_58;
  int local_24;
  int local_20;
  uint local_1c;
  uint local_14;
  uint local_10;
  undefined8 local_c;
  
  if ((int)param_2 < 0) {
    local_88 = -param_1;
    local_84 = -(param_2 + (param_1 != 0));
  }
  else {
    local_88 = param_1;
    local_84 = param_2;
  }
  if ((int)param_4 < 0) {
    local_90 = -param_3;
    local_8c = -(param_4 + (param_3 != 0));
  }
  else {
    local_90 = param_3;
    local_8c = param_4;
  }
  if ((int)param_6 < 0) {
    local_98 = -param_5;
    local_94 = -(param_6 + (param_5 != 0));
  }
  else {
    local_98 = param_5;
    local_94 = param_6;
  }
  if (((int)param_2 < 1) && ((int)param_2 < 0)) {
    bVar7 = 1;
    bVar4 = 1;
  }
  else {
    bVar7 = 0;
    bVar4 = 0;
  }
  if (((int)param_4 < 1) && ((int)param_4 < 0)) {
    bVar6 = 1;
    bVar3 = 1;
  }
  else {
    bVar6 = 0;
    bVar3 = 0;
  }
  bVar5 = (bool)(bVar7 ^ bVar6);
  bVar2 = (bool)(bVar4 ^ bVar3);
  uVar1 = (ulonglong)local_84 * (ulonglong)local_90 + (ulonglong)local_88 * (ulonglong)local_8c +
          ((ulonglong)local_88 * (ulonglong)local_90 >> 0x20);
  local_1c = (uint)uVar1;
  local_14 = (uint)((ulonglong)local_88 * (ulonglong)local_90);
  local_10 = local_1c;
  local_c = (ulonglong)local_84 * (ulonglong)local_8c + (uVar1 >> 0x20);
  if (param_7 != 0 || param_8 != 0) {
    if (bVar2) {
      local_64 = -param_7;
      local_60 = -(param_8 + (param_7 != 0));
      if (((int)param_8 < 0) || (((int)param_8 < 1 && (param_7 == 0)))) {
        local_5c = 0;
        local_58 = 0;
      }
      else {
        local_5c = 0xffffffff;
        local_58 = -1;
      }
    }
    else {
      local_64 = param_7;
      local_60 = param_8;
      if (((int)param_8 < 1) && ((int)param_8 < 0)) {
        local_5c = 0xffffffff;
        local_58 = -1;
      }
      else {
        local_5c = 0;
        local_58 = 0;
      }
    }
    bVar13 = CARRY4(local_64,local_14);
    local_14 = local_64 + local_14;
    local_10 = local_60 + local_1c + (uint)bVar13;
    uVar11 = (uint)CARRY4(local_60,local_1c) + (uint)CARRY4(local_60 + local_1c,(uint)bVar13);
    local_c = local_c + CONCAT44(local_58 + (uint)CARRY4(local_5c,uVar11),local_5c + uVar11);
    if (local_c < 0) {
      bVar2 = !bVar5;
      uVar11 = ~local_14;
      local_14 = uVar11 + 1;
      local_10 = ~local_10 + (uint)(0xfffffffe < uVar11);
      local_a8 = (uint)(local_14 == 0 && local_10 == 0);
      local_c = CONCAT44(~(uint)((ulonglong)local_c >> 0x20) + (uint)CARRY4(~(uint)local_c,local_a8)
                         ,~(uint)local_c + local_a8);
      bVar5 = bVar2;
    }
  }
  if (((int)param_6 < 1) && ((int)param_6 < 0)) {
    bVar2 = !bVar5;
  }
  if ((local_c._4_4_ < local_94) || ((local_c._4_4_ <= local_94 && ((uint)local_c < local_98)))) {
    if ((uint)local_c == 0 && local_c._4_4_ == 0) {
      lVar14 = __aulldiv(local_14,local_10,local_98,local_94);
      if (bVar2) {
        lVar14 = CONCAT44(-((int)((ulonglong)lVar14 >> 0x20) + (uint)((int)lVar14 != 0)),
                          -(int)lVar14);
      }
    }
    else if (local_94 == 0) {
      iVar8 = __aulldiv(local_10,(uint)local_c,local_98,0);
      uVar9 = __aullrem(local_10,(uint)local_c,local_98,0);
      uVar15 = __aulldiv(local_14,uVar9,local_98,0);
      iVar10 = (int)uVar15;
      iVar8 = (int)((ulonglong)uVar15 >> 0x20) + iVar8;
      lVar14 = CONCAT44(iVar8,iVar10);
      if (bVar2) {
        lVar14 = CONCAT44(-(iVar8 + (uint)(iVar10 != 0)),-iVar10);
      }
    }
    else {
      lVar14 = 0;
      local_80 = 0;
      while( true ) {
        local_20 = (int)((ulonglong)lVar14 >> 0x20);
        local_24 = (int)lVar14;
        if (0x3f < local_80) break;
        lVar14 = __allshl();
        uVar15 = __allshl();
        uVar12 = (uint)((ulonglong)uVar15 >> 0x20);
        uVar11 = (uint)uVar15;
        if ((local_10 & 0x80000000) != 0) {
          uVar11 = uVar11 + 1;
        }
        __allshl();
        if ((local_94 <= uVar12) && ((local_94 < uVar12 || (local_98 <= uVar11)))) {
          lVar14 = lVar14 + 1;
        }
        local_80 = local_80 + 1;
        local_10 = extraout_EDX;
      }
      if (bVar2) {
        lVar14 = CONCAT44(-(local_20 + (uint)(local_24 != 0)),-local_24);
      }
    }
  }
  else if (bVar2) {
    lVar14 = -0x8000000000000000;
  }
  else {
    lVar14 = 0x7fffffffffffffff;
  }
  return lVar14;
}

