// ============================================
// Address:  0x00650b40
// Original: FUN_00650b40
// Status:   unreviewed
// ============================================


void __thiscall FUN_00650b40(undefined4 param_1,int param_2)

{
  if (DAT_006b77ac != param_2) {
    if (param_2 == 0) {
      (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,0,5,1,0,param_1);
      (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,0,6,1);
      (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,0,7,1);
    }
    else if (param_2 == 1) {
      (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,0,5,2);
      (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,0,6,2);
      (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,0,7,2);
    }
    DAT_006b77ac = param_2;
  }
  return;
}

