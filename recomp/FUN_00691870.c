// ============================================
// Address:  0x00691870
// Original: FUN_00691870
// Status:   unreviewed
// ============================================


void FUN_00691870(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int local_c;
  int local_8;
  
  iVar1 = FUN_006871b0(param_2,&DAT_006ad164);
  if (iVar1 == 0) {
    iVar1 = FUN_006871b0(param_2,&DAT_006acfc4);
    if (iVar1 == 0) {
      FUN_0068e600(param_1,param_2,param_3);
    }
    else {
      if (param_1 == 0) {
        local_c = 0;
      }
      else {
        local_c = param_1 + 0xe4;
      }
      FUN_0068e090(local_c,param_3);
    }
  }
  else {
    if (param_1 == 0) {
      local_8 = 0;
    }
    else {
      local_8 = param_1 + 0xe0;
    }
    FUN_0068e090(local_8,param_3);
  }
  return;
}

