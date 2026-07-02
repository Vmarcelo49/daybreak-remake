// Function: FUN_00408330
// Address:  0x00408330
// Source:   batch_decompile (mass dump)
// Hash:     9a51b635e82d1453


undefined4 * __fastcall FUN_00408330(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined1 local_64 [4];
  undefined1 local_60 [4];
  undefined1 local_5c [4];
  undefined1 local_58 [4];
  undefined1 local_54 [4];
  undefined1 local_50 [4];
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
  puStack_c = &LAB_0069dba8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00403a50();
  local_8 = 0;
  *param_1 = &PTR_FUN_006a1974;
  _vector_constructor_iterator_(param_1 + 1,4,7,FUN_00425ac0);
  _vector_constructor_iterator_(param_1 + 8,4,3,FUN_00425ac0);
  _vector_constructor_iterator_(param_1 + 0xb,4,4,FUN_00425ac0);
  _vector_constructor_iterator_(param_1 + 0xf,4,4,FUN_00425ac0);
  _vector_constructor_iterator_(param_1 + 0x13,4,0x10,FUN_00425ac0);
  _vector_constructor_iterator_(param_1 + 0x23,4,0x10,FUN_00425ac0);
  _vector_constructor_iterator_(param_1 + 0x33,4,0x10,FUN_00425ac0);
  _vector_constructor_iterator_(param_1 + 0x43,0xa0,3,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0xbb,0xa0,4,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0x15b,0xa0,3,FUN_00403a70);
  FUN_00403a70();
  FUN_00403a70();
  _vector_constructor_iterator_(param_1 + 0x223,0xa0,4,FUN_00403a70);
  FUN_00403a70();
  FUN_00403a70();
  FUN_00403a70();
  FUN_00403a70();
  _vector_constructor_iterator_(param_1 + 0x363,0xa0,4,FUN_00403a70);
  FUN_00403a70();
  FUN_00403a70();
  FUN_00403a70();
  _vector_constructor_iterator_(param_1 + 0x47b,0xa0,2,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0x4cb,0xa0,2,FUN_00403a70);
  FUN_00403a70();
  _vector_constructor_iterator_(param_1 + 0x543,0xa0,0x10,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0x7c3,0xa0,0x10,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0xa43,0xa0,0x10,FUN_00403a70);
  FUN_004082b0();
  FUN_00425ac0();
  puVar1 = (undefined4 *)FUN_006560c0(local_24,"data/select/bg00.bmp");
  param_1[8] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_28,"data/select/bg01.bmp");
  param_1[9] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_2c,"data/select/sbg00.bmp");
  param_1[10] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_30,"data/select/p00.bmp");
  param_1[1] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_34,"data/select/p01.bmp");
  param_1[2] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_38,"data/select/p02.bmp");
  param_1[3] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_3c,"data/select/pbg00.bmp");
  param_1[4] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_40,"data/select/pbg02.bmp");
  param_1[6] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_44,"data/select/pbg01.bmp");
  param_1[5] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_48,"data/select/p03.bmp");
  param_1[7] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_4c,"data/select/s1p.bmp");
  param_1[0xf] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_50,"data/select/s2p.bmp");
  param_1[0x10] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_54,"data/select/s3p.bmp");
  param_1[0x11] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_58,"data/select/s4p.bmp");
  param_1[0x12] = *puVar1;
  FUN_00655af0(param_1[8],0,0,800,600);
  FUN_00655af0(param_1[9],0,0,800,600);
  FUN_00655af0(param_1[10],0,0,800,600);
  for (local_14 = 0; local_14 < 4; local_14 = local_14 + 1) {
    FUN_006556c0(param_1[local_14 + 0xf],0,0,400,300,200,0);
  }
  FUN_006556c0(param_1[1],0,0x180,0x80,0x80,0x40,0x40);
  FUN_006556c0(param_1[2],0x100,0,0x80,0x40,0x40,0x20);
  FUN_006556c0(param_1[2],0,0x140,0x100,0x40,0x80,0x20);
  FUN_006556c0(param_1[3],0,0,0x100,0x40,0x80,0x20);
  FUN_006556c0(param_1[2],0,0,0x100,0x40,0x80,0x20);
  FUN_006556c0(param_1[1],0,0,0x80,0x40,0x40,0x20);
  FUN_006556c0(param_1[1],0,0,0x140,0x20,0xa0,0x10);
  FUN_00655b20(param_1[1],0x180,0xc0,0x40,0x80,0x20,0x40);
  FUN_00655b20(param_1[2],0,0x80,0x100,0x40,0x80,0x20);
  FUN_006556c0(param_1[3],0x100,0x80,0x40,0x40,0x20,0x20);
  FUN_006556c0(param_1[3],0,0x140,0x100,0x40,0x80,0x20);
  FUN_006556c0(param_1[1],0x140,0,0xc0,0x40,0x60,0x20);
  FUN_006556c0(param_1[7],0,0,0x100,0x40,0x80,0x20);
  FUN_00408250(0x3f000000);
  FUN_006556c0(param_1[4],0,0,0x140,0x40,0xa0,0x20);
  FUN_006556c0(param_1[6],0,0,0x140,0x40,0xa0,0x20);
  FUN_006556c0(param_1[4],0x180,0,0x80,0x40,0x40,0x20);
  FUN_006556c0(param_1[6],0x180,0,0x80,0x40,0x40,0x20);
  FUN_006556c0(param_1[5],0,0,0xfa,0x32,0x7d,0x19);
  FUN_00431a50(param_1[2],0,0xc0,0x40,0x100,8,0xc1a00000);
  for (local_18 = 0; local_18 < 0x10; local_18 = local_18 + 1) {
    wsprintfA((LPSTR)(param_1 + 0xecd),"data/select/%02d.bmp",local_18);
    puVar1 = (undefined4 *)FUN_006560c0(local_5c,param_1 + 0xecd);
    param_1[local_18 + 0x33] = *puVar1;
    FUN_00655b20(param_1[local_18 + 0x33],0,0,0x100,0x100,0x80,0x100);
  }
  for (local_1c = 0; local_1c < 0x10; local_1c = local_1c + 1) {
    wsprintfA((LPSTR)(param_1 + 0xecd),"data/select/i%02d.bmp",local_1c);
    puVar1 = (undefined4 *)FUN_006560c0(local_60,param_1 + 0xecd);
    param_1[local_1c + 0x13] = *puVar1;
    FUN_006556c0(param_1[local_1c + 0x13],0,0,0x50,0x80,0x28,0x50);
    wsprintfA((LPSTR)(param_1 + 0xecd),"data/select/cos%02d.bmp",local_1c);
    puVar1 = (undefined4 *)FUN_006560c0(local_64,param_1 + 0xecd);
    param_1[local_1c + 0x23] = *puVar1;
    FUN_006556c0(param_1[local_1c + 0x23],0,0,0x50,0x80,0x28,0x50);
    param_1[local_1c + 0xf54] = 0;
  }
  for (local_20 = 0; local_20 < 4; local_20 = local_20 + 1) {
    param_1[local_20 + 0xf12] = 0xffffffff;
    param_1[local_20 + 0xf16] = 0;
    param_1[local_20 + 0xf1a] = 0;
    param_1[local_20 + 0xf20] = 0xffffffff;
    param_1[local_20 + 0xf24] = 0;
    param_1[local_20 + 0xf28] = 0xffffffff;
    param_1[local_20 + 0xf42] = 0xffffffff;
    param_1[local_20 + 0xf3e] = 0xffffffff;
    param_1[local_20 + 0xf46] = 0xffffffff;
    param_1[local_20 + 0xf4a] = 0xffffffff;
    param_1[local_20 + 0xf4e] = 0;
    *(undefined1 *)((int)param_1 + local_20 + 0x3cd4) = 0;
    *(undefined1 *)((int)param_1 + local_20 + 0x3cb0) = 0;
    *(undefined1 *)((int)param_1 + local_20 + 0x3d91) = (undefined1)local_20;
  }
  param_1[0xf52] = 0;
  param_1[0xf53] = 0;
  if (DAT_006cfdb0 == '\0') {
    param_1[0xf12] = 0;
  }
  else {
    if (DAT_006cfdb0 == '\x01') {
      FUN_0064b0e0();
    }
    if (-1 < DAT_006cfb18) {
      param_1[0xf12] = 0;
    }
    if (-1 < DAT_006cfb1c) {
      param_1[0xf13] = 1;
    }
    if (-1 < DAT_006cfb20) {
      param_1[0xf14] = 3;
    }
    if (-1 < DAT_006cfb24) {
      param_1[0xf15] = 4;
    }
    if (DAT_006cfdb0 == '\x01') {
      if (DAT_006cfe1c == '\x01') {
        FUN_0040d910();
      }
      else if (DAT_006cfe1c == '\x02') {
        FUN_0040d7b0();
      }
    }
  }
  _memset(param_1 + 0xf36,0,0x10);
  _memset(param_1 + 0xf3a,0,0x10);
  *(undefined1 *)((int)param_1 + 0x3c41) = 0;
  *(undefined1 *)(param_1 + 0xf10) = 0;
  param_1[0xf1e] = 0;
  param_1[0xf1f] = 0;
  *(undefined1 *)((int)param_1 + 0x3c43) = 0;
  *(undefined1 *)(param_1 + 0xf11) = 0;
  *(undefined1 *)((int)param_1 + 0x3c42) = 0;
  param_1[0xf0f] = 0;
  *(undefined1 *)(param_1 + 0xf64) = 1;
  FUN_0065b870("data/bgm/select01.ogg");
  ExceptionList = local_10;
  return param_1;
}

