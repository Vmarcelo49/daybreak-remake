// Function: FUN_00412110
// Address:  0x00412110
// Source:  06_top_dispatchers.txt


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 * __fastcall FUN_00412110(undefined4 *param_1)

{
  char cVar1;
  char *pcVar2;
  undefined4 *puVar3;
  CPane *local_87c;
  undefined1 local_874 [4];
  undefined1 local_870 [4];
  undefined1 local_86c [4];
  undefined1 local_868 [4];
  undefined1 local_864 [4];
  undefined1 local_860 [4];
  undefined1 local_85c [4];
  undefined1 local_858 [4];
  CPane *local_854;
  CPane *local_850;
  undefined1 local_84c [4];
  void *local_848;
  CPane *local_844;
  CPane *local_840;
  char *local_83c;
  undefined1 local_838 [2080];
  undefined4 local_18;
  FILE *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069dda9;
  local_10 = ExceptionList;
  local_18 = DAT_006b77f4;
  ExceptionList = &local_10;
  FUN_00403a50();
  local_8 = 0;
  *param_1 = &PTR_FUN_006a1dc4;
  _vector_constructor_iterator_(param_1 + 1,0xa0,2,FUN_00403a70);
  FUN_00403a70();
  FUN_00403a70();
  FUN_00403a70();
  FUN_00403a70();
  _vector_constructor_iterator_(param_1 + 0xf1,0xa0,2,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0x141,0xa0,2,FUN_00403a70);
  FUN_00403a70();
  FUN_00403a70();
  FUN_00403a70();
  FUN_004082b0();
  _vector_constructor_iterator_(param_1 + 0x413,4,5,FUN_00425ac0);
  _vector_constructor_iterator_(param_1 + 0x418,4,2,FUN_00425ac0);
  FUN_00425ac0();
  FUN_00425ac0();
  cVar1 = FUN_00414690();
  if (cVar1 == '\0') {
    FUN_0065b870("data/bgm/title.ogg");
  }
  _memset(&DAT_006cfdd1,0,8);
  _memset(&DAT_006cfb58,0,0x48);
  _memset(&DAT_006cfde1,-1,8);
  FUN_00414670();
  FUN_00414670();
  FUN_00414670();
  FUN_00414670();
  DAT_006cfb24 = 0xffffffff;
  DAT_006cfb20 = 0xffffffff;
  DAT_006cfb1c = 0xffffffff;
  DAT_006cfb18 = 0xffffffff;
  DAT_006cfdcc = 0;
  DAT_006cfdb0 = 0;
  FUN_00646360();
  local_838[0] = 0;
  *(undefined1 *)(param_1 + 0x62d) = 0;
  local_14 = (FILE *)FUN_0066c430("addresslist.txt",&DAT_006a1ca8);
  if (local_14 != (FILE *)0x0) {
    *(undefined1 *)(param_1 + 0x62d) = 0;
    while ((*(char *)(param_1 + 0x62d) < '\b' &&
           (pcVar2 = _fgets((char *)(param_1 + *(char *)(param_1 + 0x62d) * 0x41 + 0x425),0x104,
                            local_14), pcVar2 != (char *)0x0))) {
      local_83c = _strchr((char *)(param_1 + *(char *)(param_1 + 0x62d) * 0x41 + 0x425),10);
      if (local_83c != (char *)0x0) {
        *local_83c = '\0';
      }
      FUN_0066b870(local_838,param_1 + *(char *)(param_1 + 0x62d) * 0x41 + 0x425);
      FUN_0066b870(local_838,&DAT_006a1cbc);
      *(char *)(param_1 + 0x62d) = *(char *)(param_1 + 0x62d) + '\x01';
    }
    _fclose(local_14);
  }
  FUN_00660050();
  FUN_0065f8b0();
  FUN_00645b90();
  if (*(char *)(param_1 + 0x62d) != '\0') {
    local_848 = operator_new(0x148);
    local_8._0_1_ = 1;
    if (local_848 == (void *)0x0) {
      local_87c = (CPane *)0x0;
    }
    else {
      local_87c = (CPane *)FUN_0065d6f0(DAT_006d1850);
    }
    local_844 = local_87c;
    local_8 = (uint)local_8._1_3_ << 8;
    local_840 = local_87c;
    FUN_0065d7e0(&DAT_006a1cc0,0x14,0x96,0x96,0x96);
    FUN_00414650(1);
    CPane::SetBorders(local_840,500,0x10,0,0);
    puVar3 = (undefined4 *)FUN_00656190(local_84c,local_838,local_840);
    param_1[0x41b] = *puVar3;
    local_854 = local_840;
    local_850 = local_840;
    if (local_840 != (CPane *)0x0) {
      FUN_0040fb10(1);
    }
    FUN_00655690(param_1[0x41b],0,1,0x200,0x14);
  }
  puVar3 = (undefined4 *)FUN_006560c0(local_858,"data/network/nback01.bmp");
  param_1[0x413] = *puVar3;
  puVar3 = (undefined4 *)FUN_006560c0(local_85c,"data/network/menu.bmp");
  param_1[0x414] = *puVar3;
  puVar3 = (undefined4 *)FUN_006560c0(local_860,"data/network/nback00.bmp");
  param_1[0x415] = *puVar3;
  puVar3 = (undefined4 *)FUN_006560c0(local_864,"data/network/number.bmp");
  param_1[0x416] = *puVar3;
  puVar3 = (undefined4 *)FUN_006560c0(local_868,"data/network/menu2.bmp");
  param_1[0x417] = *puVar3;
  puVar3 = (undefined4 *)FUN_006560c0(local_86c,"data/chat/name_p1.bmp");
  param_1[0x418] = *puVar3;
  puVar3 = (undefined4 *)FUN_006560c0(local_870,"data/chat/name_p2.bmp");
  param_1[0x419] = *puVar3;
  puVar3 = (undefined4 *)FUN_006560c0(local_874,"data/network/nameMenu.bmp");
  param_1[0x41a] = *puVar3;
  FUN_00655af0(param_1[0x413],0,0,800,600);
  FUN_00655af0(param_1[0x415],0,0,800,600);
  FUN_00655b20(param_1[0x416],0,0xd0,0x30,0x30,0x18,0x18);
  FUN_00655af0(param_1[0x416],0x30,200,0xc0,0x30);
  FUN_00655af0(param_1[0x418],0,0,0x200,0x200);
  FUN_00655af0(param_1[0x419],0,0,0x200,0x200);
  FUN_006556c0(param_1[0x418],0,0,0x20,0x20,0x10,0x10);
  FUN_006556c0(param_1[0x419],0,0,0x20,0x20,0x10,0x10);
  FUN_00655690(param_1[0x41a],0x20,0,0x40,0x20);
  FUN_00655690(param_1[0x414],0,0,0x100,0x20);
  FUN_006556c0(param_1[0x417],0,0,0x200,0x40,0x100,0);
  FUN_006556c0(param_1[0x416],0,0x40,0x100,0x40,0x80,0x20);
  FUN_00431a50(param_1[0x416],0,0,0x20,0x20,7,0xc1200000);
  param_1[0x41c] = 0;
  param_1[0x41d] = 0;
  *(undefined1 *)((int)param_1 + 0x18b5) = 0;
  param_1[0x422] = 0;
  ExceptionList = local_10;
  return param_1;
}

