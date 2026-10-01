// Function: FUN_00650fd0
// Address:  0x00650fd0
// Source:   batch_decompile (mass dump)
// Hash:     02a6ee1bb5ae138f


void __fastcall FUN_00650fd0(int param_1)

{
  tagRECT local_18;
  int local_8;
  
  if ((*(uint *)(param_1 + 0x278) & 0xff000000) != 0) {
    SetRect(&local_18,0,0,DAT_006d16fc,DAT_006d1700);
    FUN_00650ab0(&local_18);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,7,0);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xe,0);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x13,5);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x14,6);
    FUN_00651820(&local_18,*(undefined4 *)(param_1 + 0x278));
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xe,1);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,7,1);
  }
  (**(code **)(*DAT_006d16f8 + 0xa8))(DAT_006d16f8);
  local_8 = (**(code **)(*DAT_006d16f8 + 0x44))(DAT_006d16f8,0,0,0,0);
  if (local_8 == -0x7789f798) {
    *(undefined1 *)(param_1 + 0x59) = 1;
  }
  FUN_0065d6a0();
  return;
}

