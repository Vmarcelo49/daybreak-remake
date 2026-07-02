// ============================================
// Address:  0x00658550
// Original: FUN_00658550
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __fastcall FUN_00658550(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  undefined1 local_5c [84];
  undefined4 local_8;
  
  local_8 = DAT_006b77f4;
  if (*(int *)(param_1 + 8) != 0) {
    iVar2 = (**(code **)(**(int **)(param_1 + 8) + 0x10))
                      (*(undefined4 *)(param_1 + 8),4,FUN_00658740,0,1);
    if (iVar2 != 0) {
      FUN_006583f0(&DAT_006aad84);
      return 0;
    }
    uVar1 = FUN_0064f010();
    *(undefined1 *)(param_1 + 0x120) = uVar1;
    _memset(local_5c,0,0x50);
    FUN_006589a0(*(undefined1 *)(param_1 + 0x120),local_5c);
  }
  return 1;
}

