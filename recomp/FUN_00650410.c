// ============================================
// Address:  0x00650410
// Original: FUN_00650410
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __fastcall FUN_00650410(int param_1)

{
  int iVar1;
  CHAR local_124 [268];
  undefined4 local_18;
  tagRECT local_14;
  
  local_18 = DAT_006b77f4;
  if (*(int *)(param_1 + 0x30) == 0) {
    wsprintfA(local_124,"%s/toon.bmp","data/directx");
    FUN_00656c80(local_124,param_1 + 0x30);
  }
  (**(code **)(*DAT_006d16f8 + 0x5c))(DAT_006d16f8,0x400,0x400,1,1,0x15,0,param_1 + 0x34,0);
  iVar1 = (**(code **)(*DAT_006d16f8 + 0x5c))(DAT_006d16f8,0x400,0x400,1,1,0x50,0,param_1 + 0x38,0);
  if (iVar1 < 0) {
    iVar1 = (**(code **)(*DAT_006d16f8 + 0x5c))
                      (DAT_006d16f8,0x400,0x400,1,1,0x51,0,param_1 + 0x38,0);
    if (iVar1 < 0) {
      (**(code **)(*DAT_006d16f8 + 0x5c))(DAT_006d16f8,0x400,0x400,1,1,0x15,0,param_1 + 0x38,0);
    }
  }
  (**(code **)(*DAT_006d16f8 + 0x98))(DAT_006d16f8,0,param_1 + 0x27c);
  (**(code **)(*DAT_006d16f8 + 0xa0))(DAT_006d16f8,param_1 + 0x280);
  (**(code **)(**(int **)(param_1 + 0x34) + 0x48))
            (*(undefined4 *)(param_1 + 0x34),0,param_1 + 0x284);
  (**(code **)(**(int **)(param_1 + 0x38) + 0x48))
            (*(undefined4 *)(param_1 + 0x38),0,param_1 + 0x288);
  SetRect(&local_14,0,0,DAT_006d16fc,DAT_006d1700);
  FUN_00650ab0(&local_14);
  (**(code **)(*DAT_006d16f8 + 0x94))(DAT_006d16f8,0,*(undefined4 *)(param_1 + 0x27c));
  (**(code **)(*DAT_006d16f8 + 0x9c))(DAT_006d16f8,*(undefined4 *)(param_1 + 0x280));
  return 1;
}

