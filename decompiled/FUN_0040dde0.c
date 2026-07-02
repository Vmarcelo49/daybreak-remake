// Function: FUN_0040dde0
// Address:  0x0040dde0
// Source:   batch_decompile (mass dump)
// Hash:     9a861399c7161da5


undefined4 * __fastcall FUN_0040dde0(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069dc08;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00403a50();
  local_8 = 0;
  *param_1 = &PTR_FUN_006a1ad4;
  _vector_constructor_iterator_(param_1 + 1,4,3,FUN_00425ac0);
  _vector_constructor_iterator_(param_1 + 4,0xa0,2,FUN_00403a70);
  FUN_00403a70();
  FUN_00403a70();
  puVar1 = (undefined4 *)FUN_006560c0(local_14,"data/teamselect/add0.bmp");
  param_1[1] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_18,"data/teamselect/add1.bmp");
  param_1[2] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_1c,"data/network/nback00.bmp");
  param_1[3] = *puVar1;
  FUN_00655af0(param_1[3],0,0,800,600);
  FUN_004082f0(0xff808080);
  FUN_006556c0(param_1[1],0,0,0x200,0x40,0x100,0x20);
  FUN_006556c0(param_1[2],0,0,0x200,0x20,0x100,0);
  param_1[0x7c] = 0;
  param_1[0x7d] = 0;
  param_1[0x7e] = 0xffffffff;
  param_1[0x7f] = 0xffffffff;
  param_1[0x80] = 0xffffffff;
  if (DAT_006cfbc6 == '\x01') {
    FUN_0065c050(DAT_006ca830);
    FUN_0065c080("movie/staffroll2.mpg");
  }
  else {
    FUN_0065c050(DAT_006ca834);
    FUN_0065c080("movie/staffroll.mpg");
  }
  uVar5 = 0x1e0;
  uVar4 = 0x280;
  uVar3 = 0;
  uVar2 = 0;
  puVar1 = (undefined4 *)FUN_00405200(local_20);
  FUN_00655af0(*puVar1,uVar2,uVar3,uVar4,uVar5);
  FUN_00408250(0x3fa00000);
  ExceptionList = local_10;
  return param_1;
}

