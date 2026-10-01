// Function: FUN_004057c0
// Address:  0x004057c0
// Source:   batch_decompile (mass dump)
// Hash:     6873069ef8f988ba


undefined4 * __fastcall FUN_004057c0(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined1 local_4c [4];
  undefined1 local_48 [4];
  undefined1 local_44 [4];
  undefined1 local_40 [4];
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069db78;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00403a50();
  local_8 = 0;
  *param_1 = &PTR_FUN_006a16b4;
  FUN_00425ac0();
  _vector_constructor_iterator_(param_1 + 0x43,4,4,FUN_00425ac0);
  _vector_constructor_iterator_(param_1 + 0x47,4,0xe,FUN_00425ac0);
  _vector_constructor_iterator_(param_1 + 0x55,4,2,FUN_00425ac0);
  _vector_constructor_iterator_(param_1 + 0x57,4,2,FUN_00425ac0);
  _vector_constructor_iterator_(param_1 + 0x59,4,2,FUN_00425ac0);
  _vector_constructor_iterator_(param_1 + 0x5b,4,2,FUN_00425ac0);
  _vector_constructor_iterator_(param_1 + 0x5d,4,10,FUN_00425ac0);
  _vector_constructor_iterator_(param_1 + 0x67,4,2,FUN_00425ac0);
  FUN_00425ac0();
  FUN_00403a70();
  FUN_004082b0();
  _vector_constructor_iterator_(param_1 + 0x29c,0xa0,0xe,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0x4cc,0xa0,2,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0x51c,0xa0,2,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0x56c,0xa0,2,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0x5bc,0xa0,4,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0x65c,0xa0,3,FUN_00403a70);
  FUN_00403a70();
  FUN_00403a70();
  FUN_00403a70();
  _vector_constructor_iterator_(param_1 + 0x74c,0xa0,10,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0x8dc,0xa0,10,FUN_00403a70);
  FUN_00403a70();
  FUN_00403a70();
  FUN_00403a70();
  _vector_constructor_iterator_(param_1 + 0xae4,0xa0,2,FUN_00403a70);
  FUN_00403a70();
  FUN_00403a70();
  puVar1 = (undefined4 *)FUN_006560c0(local_24,"data/teamselect/bg00.bmp");
  param_1[0x42] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_28,"data/select/p00.bmp");
  param_1[0x43] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_2c,"data/select/p01.bmp");
  param_1[0x44] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_30,"data/select/p02.bmp");
  param_1[0x45] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_34,"data/select/p03.bmp");
  param_1[0x46] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_38,"data/select/s1p.bmp");
  param_1[0x5b] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_3c,"data/select/s2p.bmp");
  param_1[0x5c] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_40,"data/teamselect/p00.bmp");
  param_1[0x67] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_44,"data/teamselect/p01.bmp");
  param_1[0x68] = *puVar1;
  FUN_00655af0(param_1[0x42],0,0,800,600);
  for (local_14 = 0; local_14 < 0xe; local_14 = local_14 + 1) {
    wsprintfA((LPSTR)(param_1 + 1),"data/select/i%02d.bmp",(int)(char)(&DAT_006b70f0)[local_14]);
    puVar1 = (undefined4 *)FUN_006560c0(local_48,param_1 + 1);
    param_1[local_14 + 0x47] = *puVar1;
    FUN_006556c0(param_1[local_14 + 0x47],0,0,0x50,0x80,0x28,0x50);
  }
  for (local_18 = 0; local_18 < 10; local_18 = local_18 + 1) {
    wsprintfA((LPSTR)(param_1 + 1),"data/teamselect/t%02d.bmp",local_18);
    puVar1 = (undefined4 *)FUN_006560c0(local_4c,param_1 + 1);
    param_1[local_18 + 0x5d] = *puVar1;
    FUN_00655b20(param_1[local_18 + 0x5d],0,0,0x200,0x200,0x100,0x100);
    if (local_18 < 6) {
      FUN_00655b20(param_1[0x67],local_18 / 3 << 8,(local_18 % 3) * 0xa0,0x100,0xa0,0x80,0);
    }
    else {
      FUN_00655b20(param_1[0x68],local_18 / 3 << 8,(local_18 % 3) * 0xa0,0x100,0xa0,0x80,0);
    }
  }
  for (local_1c = 0; local_1c < 2; local_1c = local_1c + 1) {
    FUN_006556c0(param_1[local_1c + 0x5b],0,0,400,300,200,0);
  }
  FUN_006556c0(param_1[0x43],0,0x180,0x80,0x80,0x40,0x40);
  FUN_006556c0(param_1[0x44],0x100,0,0x80,0x40,0x40,0x20);
  FUN_006556c0(param_1[0x44],0,0x140,0x100,0x40,0x80,0x20);
  FUN_006556c0(param_1[0x45],0,0,0x100,0x40,0x80,0x20);
  FUN_006556c0(param_1[0x44],0,0,0x100,0x40,0x80,0x20);
  FUN_006556c0(param_1[0x43],0,0,0x80,0x40,0x40,0x20);
  FUN_006556c0(param_1[0x43],0,0,0x140,0x20,0xa0,0x10);
  FUN_00655b20(param_1[0x43],0x180,0xc0,0x40,0x80,0x20,0x40);
  FUN_00655b20(param_1[0x44],0,0x80,0x100,0x40,0x80,0x20);
  FUN_006556c0(param_1[0x45],0x100,0x80,0x40,0x40,0x20,0x20);
  FUN_006556c0(param_1[0x45],0,0x140,0x100,0x40,0x80,0x20);
  FUN_006556c0(param_1[0x43],0x140,0,0xc0,0x40,0x60,0x20);
  FUN_006556c0(param_1[0x46],0,0,0x100,0x40,0x80,0x20);
  FUN_00408250(0x3f000000);
  param_1[0xb84] = 1;
  DAT_006cfbc4 = 0;
  param_1[0xb86] = 0;
  param_1[0xb85] = 0;
  param_1[0xb88] = 0;
  for (local_20 = 0; local_20 < 2; local_20 = local_20 + 1) {
    param_1[local_20 + 0xb8a] = 0xffffffff;
    param_1[local_20 + 0xb8c] = 0;
    param_1[local_20 + 0xb8e] = 0;
    param_1[local_20 + 0xba4] = 0xffffffff;
    param_1[local_20 + 0xba6] = 0;
    param_1[local_20 + 0xba8] = 0xffffffff;
    param_1[local_20 + 0xb90] = 0xffffffff;
    param_1[local_20 + 0xb98] = 0xffffffff;
    *(undefined1 *)((int)param_1 + local_20 + 0x2ea8) = 0;
  }
  param_1[0xb8a] = 0;
  *(undefined1 *)(param_1 + 0xbaf) = 0;
  param_1[0xb89] = 10;
  FUN_0065b870("data/bgm/select01.ogg");
  ExceptionList = local_10;
  return param_1;
}

