// ============================================
// Address:  0x00690ca0
// Original: FUN_00690ca0
// Status:   unreviewed
// ============================================


undefined4 __thiscall
FUN_00690ca0(int param_1,uint param_2,uint param_3,undefined4 param_4,undefined4 param_5)

{
  uint uVar1;
  undefined4 uVar2;
  int local_30;
  undefined4 local_28;
  undefined4 *local_24;
  int local_20;
  undefined4 local_1c;
  int local_18;
  int local_14;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = param_4;
  local_8 = param_5;
  if (*(int *)(param_1 + 0x10c) < 0) {
    local_1c = 0;
  }
  else if (*(int *)(param_1 + 0xf4) * 2 < *(int *)(param_1 + 0x10c)) {
    local_1c = 0;
  }
  else {
    local_1c = 1;
  }
  local_18 = 1000;
  if (-1 < *(int *)(param_1 + 0x10c)) {
    if (((int)param_3 < 0) || (((int)param_3 < 1 && (param_2 == 0)))) {
      if ((20000 < *(int *)(param_1 + 0x108)) &&
         ((0x7fffffff < param_3 && (((int)param_3 < -1 || (param_2 < 0xffffb1e0)))))) {
        if (*(int *)(param_1 + 0x108) < *(int *)(param_1 + 0x10c)) {
          if (*(int *)(param_1 + 0x108) < *(int *)(param_1 + 0x10c) + 20000) {
            local_18 = (*(int *)(param_1 + 0x10c) /
                       ((*(int *)(param_1 + 0x10c) + 20000) - *(int *)(param_1 + 0x108))) * 1000;
          }
          else {
            local_18 = 2000;
          }
        }
        else {
          local_18 = 2000;
        }
        if (2000 < local_18) {
          local_18 = 2000;
        }
      }
    }
    else {
      local_18 = __alldiv(param_2,param_3,10000,0);
      local_18 = 1000 - local_18;
      if (local_18 < 500) {
        local_18 = 500;
      }
    }
  }
  uVar1 = *(int *)(param_1 + 0xf4) / 2;
  local_14 = uVar1 + param_2;
  local_10 = param_3 + ((int)uVar1 >> 0x1f) + (uint)CARRY4(uVar1,param_2);
  if (*(int *)(param_1 + 0xac) == 0) {
    local_28 = 0;
    local_24 = (undefined4 *)FUN_00691af0();
    local_20 = (**(code **)*local_24)(local_24,&DAT_006acfc4,&local_28);
    if (-1 < local_20) {
      *(undefined4 *)(param_1 + 0xac) = local_28;
    }
  }
  if (*(int *)(param_1 + 0xac) == 0) {
    uVar2 = 1;
  }
  else {
    if (param_1 == 0) {
      local_30 = 0;
    }
    else {
      local_30 = param_1 + 0xc;
    }
    uVar2 = (**(code **)(**(int **)(param_1 + 0xac) + 0xc))
                      (*(undefined4 *)(param_1 + 0xac),local_30,local_1c,local_18,local_14,local_10,
                       local_c,local_8);
  }
  return uVar2;
}

