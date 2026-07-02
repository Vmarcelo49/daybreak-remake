// ============================================
// Address:  0x00414750
// Original: FUN_00414750
// Status:   unreviewed
// ============================================


undefined4 * __fastcall FUN_00414750(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *local_30;
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069ddf1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00403a50();
  local_8 = 0;
  FUN_00415dc0();
  local_8._0_1_ = 1;
  *param_1 = &PTR_FUN_006a1e60;
  param_1[1] = &PTR_FUN_006a1e4c;
  FUN_0065d610();
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_00415ea0();
  _vector_constructor_iterator_(param_1 + 0x7d,0xa0,2,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0xcd,0xa0,5,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0x195,4,5,FUN_00425ac0);
  FUN_004082b0();
  FUN_00403a70();
  FUN_00403a70();
  FUN_00403a70();
  param_1[0x41c] = 0;
  param_1[0x422] = 0;
  param_1[0x424] = 0;
  *(undefined1 *)(param_1 + 0x423) = 0;
  FUN_0040da20(0);
  FUN_00646360();
  FUN_00415da0();
  DAT_006cfdd1 = 1;
  _memset(&DAT_006cfdfc,0,0x20);
  *(undefined1 *)(param_1 + 100) = 1;
  _memcpy(&DAT_006cfb58,&DAT_006cfdb8,9);
  _memcpy(param_1 + 0x66,&DAT_006cfdb8,9);
  FUN_00645dc0(0,&DAT_006cfb58);
  for (local_14 = 0; local_14 < 4; local_14 = local_14 + 1) {
    FUN_00414670();
  }
  for (local_18 = 0; local_18 < 8; local_18 = local_18 + 1) {
    if (0 < local_18) {
      if ((&DAT_006cfdd1)[local_18] == '\0') {
        *(undefined1 *)((int)param_1 + local_18 + 400) = 0;
        _memset(&DAT_006cfb58 + local_18 * 9,0,9);
      }
      else {
        *(undefined1 *)((int)param_1 + local_18 + 400) = 1;
      }
      _memcpy((void *)((int)param_1 + local_18 * 9 + 0x198),&DAT_006cfb58 + local_18 * 9,9);
      FUN_00645dc0(local_18,&DAT_006cfb58 + local_18 * 9);
    }
    *(undefined1 *)((int)param_1 + local_18 + 0x1e0) = (&DAT_006cfde1)[local_18];
  }
  *(undefined1 *)(param_1 + 0x7b) = DAT_006cfdd0;
  *(undefined1 *)((int)param_1 + 0x1ed) = DAT_006cfdf9;
  *(undefined1 *)((int)param_1 + 0x1ee) = DAT_006cfe1c;
  *(undefined1 *)((int)param_1 + 0x1ef) = DAT_006cfe1e;
  *(undefined1 *)(param_1 + 0x7c) = *(undefined1 *)(param_1 + 0x423);
  *(undefined1 *)((int)param_1 + 0x1f1) = *(undefined1 *)(param_1 + 0x41c);
  FUN_00415cb0();
  DAT_006cfdb4 = 0;
  if (DAT_006cfdc8 == '\0') {
    FUN_00415d70(0,0);
  }
  else {
    FUN_00415d70(1,0);
  }
  if (param_1 == (undefined4 *)0x0) {
    local_30 = (undefined4 *)0x0;
  }
  else {
    local_30 = param_1 + 1;
  }
  FUN_0065fee0(local_30);
  FUN_00415d30(0,param_1 + 0x62,0,0x88);
  puVar1 = (undefined4 *)FUN_006560c0(local_1c,"data/network/nback02.bmp");
  param_1[0x195] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_20,"data/network/number.bmp");
  param_1[0x197] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_24,"data/network/menu.bmp");
  param_1[0x198] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_28,"data/network/object.bmp");
  param_1[0x199] = *puVar1;
  FUN_00655af0(param_1[0x195],0,0,800,600);
  FUN_00655b20(param_1[0x198],0,0x1c0,0x200,0x40,0x100,0x20);
  FUN_00431a50(param_1[0x197],0,0,0x20,0x20,8,0);
  FUN_00655690(param_1[0x199],0,0,0x80,0x20);
  FUN_00655690(param_1[0x199],0x80,0,0x40,0x20);
  FUN_00655690(param_1[0x199],0x80,0,0x20,0x20);
  ExceptionList = local_10;
  return param_1;
}

