// ============================================
// Address:  0x00698a70
// Original: FUN_00698a70
// Status:   unreviewed
// ============================================


/* WARNING: Removing unreachable block (ram,0x00698b1c) */
/* WARNING: Removing unreachable block (ram,0x00698b7d) */

int FUN_00698a70(undefined4 param_1,int *param_2)

{
  int iVar1;
  bool bVar2;
  uint local_48;
  undefined8 local_44;
  int local_3c;
  undefined4 local_38;
  undefined1 local_34 [8];
  uint local_2c;
  int local_28;
  longlong local_24;
  int local_18;
  uint local_14;
  uint local_10;
  undefined4 local_8;
  
  if (param_2 == (int *)0x0) {
    local_3c = -0x7fffbffd;
  }
  else {
    local_3c = (**(code **)(*param_2 + 0x14))(param_2,&local_2c,&local_44);
    if (-1 < local_3c) {
      local_24 = __alldiv(local_2c,local_28,10000000,0);
      local_18 = __alldiv((uint)local_44 - local_2c,
                          (local_44._4_4_ - local_28) - (uint)((uint)local_44 < local_2c),10000000,0
                         );
      local_3c = FUN_006997e0(&local_14,local_34);
      if (CONCAT44(local_10,local_14) < local_24 + local_18) {
        FUN_00699ef0(&local_48);
        bVar2 = CARRY4(local_48,local_14);
        iVar1 = local_48 + local_14;
        local_14 = iVar1 - 1U & ~(local_48 - 1);
        local_10 = (local_10 + ((int)local_48 >> 0x1f) + (uint)bVar2) - (uint)(iVar1 == 0) &
                   (int)~(local_48 - 1) >> 0x1f;
        if (CONCAT44(local_10,local_14) < local_24 + local_18) {
          local_18 = local_14 - (int)local_24;
          local_44 = __allmul(local_14,local_10,10000000,0);
          (**(code **)(*param_2 + 0x18))(param_2,&local_2c,&local_44);
        }
      }
      local_3c = (**(code **)(*param_2 + 0xc))(param_2,&local_8);
      if (-1 < local_3c) {
        local_3c = FUN_00699730(local_24,local_18,local_8,&local_38,param_2);
        (**(code **)(*param_2 + 0x30))(param_2,local_38);
      }
    }
  }
  return local_3c;
}

