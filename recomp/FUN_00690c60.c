// ============================================
// Address:  0x00690c60
// Original: FUN_00690c60
// Status:   unreviewed
// ============================================


undefined4 FUN_00690c60(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  if (param_4 < 1000) {
    *(int *)(param_1 + 0xc) = (int)(0x172dd680 / (longlong)(param_4 + 0xa7)) + -330000;
  }
  else {
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  return 0;
}

