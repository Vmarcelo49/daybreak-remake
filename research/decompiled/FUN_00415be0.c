// Function: FUN_00415be0
// Address:  0x00415be0
// Source:   batch_decompile (mass dump)
// Hash:     e280ba5538743162


void __thiscall FUN_00415be0(int param_1,undefined4 param_2)

{
  int local_c;
  int local_8;
  
  FUN_0065d670();
  FUN_0064bd70(param_2);
  for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1) {
    *(undefined1 *)(param_1 + local_8 + 0x1e0) = (&DAT_006cfde1)[local_8];
  }
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    *(undefined1 *)(param_1 + local_c + 0x1e8) = *(undefined1 *)(&DAT_006cfb18 + local_c);
  }
  FUN_0065d6a0();
  FUN_00415d30(0,param_1 + 0x188,0,0x88);
  FUN_0064aed0(1);
  return;
}

