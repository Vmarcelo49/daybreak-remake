// Function: FUN_00415ae0
// Address:  0x00415ae0
// Source:   batch_decompile (mass dump)
// Hash:     ca90b6d15191f3c0


void __thiscall FUN_00415ae0(int param_1,int param_2)

{
  int local_14;
  int local_10;
  undefined1 local_c [8];
  
  FUN_0064aed0(0);
  if ((&DAT_006cfde1)[param_2] == '\0') {
    FUN_004167c0();
    FUN_00415d30(0,local_c,0,8);
    *(undefined4 *)(param_1 + 0x1088) = 1;
  }
  else {
    FUN_0065d670();
    FUN_0064bc20(param_2);
    FUN_0065d6a0();
    for (local_10 = 0; local_10 < 8; local_10 = local_10 + 1) {
      *(undefined1 *)(param_1 + local_10 + 0x1e0) = (&DAT_006cfde1)[local_10];
    }
    for (local_14 = 0; local_14 < 4; local_14 = local_14 + 1) {
      *(undefined1 *)(param_1 + local_14 + 0x1e8) = *(undefined1 *)(&DAT_006cfb18 + local_14);
    }
    FUN_00415d30(0,param_1 + 0x188,0,0x88);
  }
  return;
}

