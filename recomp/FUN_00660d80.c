// ============================================
// Address:  0x00660d80
// Original: FUN_00660d80
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __fastcall FUN_00660d80(int param_1)

{
  int iVar1;
  size_t sVar2;
  size_t local_420;
  size_t local_41c;
  char local_414 [1028];
  undefined4 local_10;
  int local_c;
  size_t local_8;
  
  local_10 = DAT_006b77f4;
  sVar2 = _strlen((char *)(param_1 + 0x808));
  if (sVar2 == 0) {
    local_c = 1;
    *(undefined1 *)(param_1 + 0x809) = 0;
    FUN_0066b860(local_414,param_1 + 8 + *(int *)(param_1 + 0xa10));
    if (0x400 - *(int *)(param_1 + 0xa10) < 1) {
      local_41c = 0x400 - *(int *)(param_1 + 0xa10);
    }
    else {
      local_41c = 1;
    }
    local_8 = local_41c;
    _strncpy((char *)(param_1 + 8 + *(int *)(param_1 + 0xa10))," ",local_41c);
    *(int *)(param_1 + 0xa10) = *(int *)(param_1 + 0xa10) + local_c;
    iVar1 = *(int *)(param_1 + 0xa10);
    sVar2 = _strlen(local_414);
    if (0x400 - iVar1 < (int)sVar2) {
      local_420 = 0x400 - *(int *)(param_1 + 0xa10);
    }
    else {
      local_420 = _strlen(local_414);
    }
    local_8 = local_420;
    _strncpy((char *)(param_1 + 8 + *(int *)(param_1 + 0xa10)),local_414,local_420);
    if (*(int *)(param_1 + 0xa08) < *(int *)(param_1 + 0xa10)) {
      *(undefined4 *)(param_1 + 0xa10) = *(undefined4 *)(param_1 + 0xa08);
    }
    *(undefined1 *)(param_1 + 8 + *(int *)(param_1 + 0xa08)) = 0;
    *(undefined1 *)(param_1 + 0xa0d) = 1;
  }
  return;
}

