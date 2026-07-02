// Function: FUN_00419f10
// Address:  0x00419f10
// Source:   batch_decompile (mass dump)
// Hash:     c96d41f65755dc56


undefined4 * __fastcall FUN_00419f10(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *local_28;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069df98;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00403a50();
  local_8 = 0;
  FUN_0041af50();
  *param_1 = &PTR_FUN_006a2074;
  param_1[1] = &PTR_FUN_006a2068;
  FUN_00415ea0();
  _vector_constructor_iterator_(param_1 + 0x5d,0xa0,2,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0xad,0xa0,5,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0x175,4,5,FUN_00425ac0);
  FUN_004082b0();
  FUN_00403a70();
  FUN_00403a70();
  FUN_00403a70();
  FUN_00415da0();
  FUN_00646360();
  puVar1 = (undefined4 *)FUN_006560c0(local_14,"data/network/nback02.bmp");
  param_1[0x175] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_18,"data/network/number.bmp");
  param_1[0x177] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_1c,"data/network/menu.bmp");
  param_1[0x178] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_20,"data/network/object.bmp");
  param_1[0x179] = *puVar1;
  FUN_00655af0(param_1[0x175],0,0,800,600);
  FUN_00655b20(param_1[0x178],0,0x1c0,0x200,0x40,0x100,0x20);
  FUN_00655690(param_1[0x179],0,0,0x80,0x20);
  FUN_00655690(param_1[0x179],0x80,0,0x40,0x20);
  FUN_00655690(param_1[0x179],0x80,0,0x20,0x20);
  FUN_00431a50(param_1[0x177],0,0,0x20,0x20,8,0);
  param_1[0x401] = 0;
  DAT_006cfdd1 = 0;
  FUN_00415d70(2,(undefined1)DAT_006d7648);
  if (param_1 == (undefined4 *)0x0) {
    local_28 = (undefined4 *)0x0;
  }
  else {
    local_28 = param_1 + 1;
  }
  FUN_0065f780(local_28);
  ExceptionList = local_10;
  return param_1;
}

