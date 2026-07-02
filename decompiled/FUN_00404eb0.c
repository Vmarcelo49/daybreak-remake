// Function: FUN_00404eb0
// Address:  0x00404eb0
// Source:   batch_decompile (mass dump)
// Hash:     b3ac958307ceb827


undefined4 * __fastcall FUN_00404eb0(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069dae8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00403a50();
  local_8 = 0;
  *param_1 = &PTR_FUN_006a14ec;
  FUN_00403a70();
  FUN_00425ac0();
  FUN_00425ac0();
  FUN_00403a70();
  param_1[0x2b] = 0;
  FUN_0065c080("movie/op.mpg");
  uVar5 = 0x1e0;
  uVar4 = 0x280;
  uVar3 = 0;
  uVar2 = 0;
  puVar1 = (undefined4 *)FUN_00405200(local_14);
  FUN_00655af0(*puVar1,uVar2,uVar3,uVar4,uVar5);
  FUN_00408250(0x3fa00000);
  ExceptionList = local_10;
  return param_1;
}

