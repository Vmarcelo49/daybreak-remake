// Function: FUN_00410d60
// Address:  0x00410d60
// Source:   batch_decompile (mass dump)
// Hash:     9607ba3239b70796


undefined4 * __fastcall FUN_00410d60(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069dd38;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00403a50();
  local_8 = 0;
  *param_1 = &PTR_FUN_006a1bdc;
  _vector_constructor_iterator_(param_1 + 1,0xa0,2,FUN_00403a70);
  FUN_00403a70();
  _vector_constructor_iterator_(param_1 + 0x79,4,3,FUN_00425ac0);
  puVar1 = (undefined4 *)FUN_006560c0(local_14,"data/title/back00.bmp");
  param_1[0x79] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_18,"data/title/logo.bmp");
  param_1[0x7a] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_1c,"data/title/title.bmp");
  param_1[0x7b] = *puVar1;
  FUN_00655af0(param_1[0x79],0,0,800,600);
  FUN_00655b20(param_1[0x7a],0,0,0x200,300,0x100,0);
  FUN_006556c0(param_1[0x7b],0,0,0xc0,0x30,0x60,0);
  param_1[0x7c] = 0;
  ExceptionList = local_10;
  return param_1;
}

