// ============================================
// Address:  0x0065bb70
// Original: FUN_0065bb70
// Status:   unreviewed
// ============================================


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __fastcall FUN_0065bb70(int param_1)

{
  void *local_8024;
  size_t local_8020;
  size_t local_801c;
  void *local_8018;
  uint local_8014;
  uint local_8010;
  undefined1 local_800c [32768];
  undefined4 local_c;
  uint local_8;
  
  local_8 = 0x65bb7d;
  local_c = DAT_006b77f4;
  FUN_0065d670();
  (**(code **)(**(int **)(param_1 + 0x10) + 0x10))
            (*(undefined4 *)(param_1 + 0x10),&local_8010,&local_8);
  if (*(int *)(param_1 + 0x1358) == -1) {
    if ((*(uint *)(param_1 + 0x1354) <= local_8) &&
       (local_8 < (uint)(*(uint *)(param_1 + 0x1350) <= *(uint *)(param_1 + 0x1354)) * 0x100000 +
                  *(int *)(param_1 + 0x1350))) {
      local_8014 = FUN_006685d0(local_800c,0x8000);
      if (local_8014 < 0x8000) {
        *(uint *)(param_1 + 0x1358) = (*(int *)(param_1 + 0x1354) + local_8014) % 0x100000;
      }
      (**(code **)(**(int **)(param_1 + 0x10) + 0x2c))
                (*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x1350),0x8000,
                 &local_8024,&local_8020,&local_8018,&local_801c,0);
      _memcpy(local_8024,local_800c,local_8020);
      if (local_8018 != (void *)0x0) {
        _memcpy(local_8018,local_800c + local_8020,local_801c);
      }
      (**(code **)(**(int **)(param_1 + 0x10) + 0x4c))
                (*(undefined4 *)(param_1 + 0x10),local_8024,local_8020,local_8018,local_801c);
      *(undefined4 *)(param_1 + 0x1354) = *(undefined4 *)(param_1 + 0x1350);
      *(uint *)(param_1 + 0x1350) = (*(int *)(param_1 + 0x1350) + 0x8000U) % 0x100000;
    }
  }
  else if ((*(uint *)(param_1 + 0x1358) < local_8010) &&
          (local_8010 <
           (uint)(*(uint *)(param_1 + 0x1350) < *(uint *)(param_1 + 0x1354)) * 0x100000 +
           *(int *)(param_1 + 0x1350))) {
    *(undefined1 *)(param_1 + 0x134d) = 0;
    FUN_00667f20();
  }
  FUN_0065d6a0();
  return;
}

