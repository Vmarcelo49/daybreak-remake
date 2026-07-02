// ============================================
// Address:  0x00634520
// Original: FUN_00634520
// Status:   unreviewed
// ============================================


void __fastcall FUN_00634520(int param_1)

{
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
    FUN_00632dc0();
  }
  for (local_c = 0; local_c < 7; local_c = local_c + 1) {
    if (*(int *)(param_1 + 0x4498 + local_c * 4) != 0) {
      if (*(int *)(param_1 + 0x4498 + local_c * 4) != 0) {
        FUN_00402010(1);
      }
      *(undefined4 *)(param_1 + 0x4498 + local_c * 4) = 0;
    }
  }
  for (local_10 = 0; local_10 < 8; local_10 = local_10 + 1) {
    if (*(int *)(*(int *)(param_1 + 19000) + local_10 * 4) != 0) {
      if (*(int *)(*(int *)(param_1 + 19000) + local_10 * 4) != 0) {
        FUN_0040dce0(1);
      }
      *(undefined4 *)(*(int *)(param_1 + 19000) + local_10 * 4) = 0;
    }
  }
  _free(*(void **)(param_1 + 19000));
  FUN_006429c0();
  for (local_14 = 0; local_14 < 6; local_14 = local_14 + 1) {
    FUN_00656200(*(undefined4 *)(param_1 + 0x4434 + local_14 * 4));
  }
  FUN_00656200(*(undefined4 *)(param_1 + 0x4484));
  FUN_00656200(*(undefined4 *)(param_1 + 0x4488));
  FUN_00656200(*(undefined4 *)(param_1 + 0x448c));
  FUN_00656200(*(undefined4 *)(param_1 + 0x4490));
  if (*(int *)(param_1 + 0xf78) != 0) {
    FUN_0040fb10(1);
  }
  FUN_0065b1d0(*(undefined4 *)(param_1 + 0x4494));
  for (local_18 = 0; local_18 < 10; local_18 = local_18 + 1) {
    FUN_00656200(*(undefined4 *)(param_1 + 0x445c + local_18 * 4));
  }
  return;
}

