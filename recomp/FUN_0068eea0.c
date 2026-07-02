// ============================================
// Address:  0x0068eea0
// Original: FUN_0068eea0
// Status:   unreviewed
// ============================================


undefined4 FUN_0068eea0(int param_1,undefined4 param_2,int *param_3)

{
  undefined4 uVar1;
  int iVar2;
  int local_c;
  
  if (param_3 == (int *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    iVar2 = FUN_006924c0(param_2,&DAT_006ad434);
    if (iVar2 == 0) {
      local_c = (**(code **)(*(int *)(param_1 + -0xc) + 0x1c))(0);
      if (local_c == 0) {
        local_c = 0;
      }
      else {
        local_c = local_c + 0xc;
      }
      *param_3 = local_c;
      (**(code **)(*(int *)*param_3 + 4))(*param_3);
      uVar1 = 0;
    }
    else {
      *param_3 = 0;
      uVar1 = 0x80040216;
    }
  }
  return uVar1;
}

