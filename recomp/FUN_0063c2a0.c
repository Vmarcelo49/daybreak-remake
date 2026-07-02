// ============================================
// Address:  0x0063c2a0
// Original: FUN_0063c2a0
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FUN_0063c2a0(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined1 local_874 [4];
  undefined1 local_870 [4];
  undefined1 local_86c [4];
  undefined1 local_868 [4];
  undefined1 local_864 [4];
  undefined1 local_860 [4];
  undefined4 *local_85c;
  undefined4 *local_858;
  undefined1 local_854 [24];
  char local_83c;
  undefined1 local_83b;
  undefined1 local_83a [94];
  char local_7dc;
  int local_7d8;
  undefined4 auStack_7cc [4];
  undefined1 local_7bc [1024];
  int local_3bc;
  char local_3b0;
  int local_3ac;
  undefined1 local_3a8 [4];
  undefined1 local_3a4 [4];
  int local_3a0;
  char local_393;
  int local_390;
  short local_38c;
  undefined4 local_388;
  undefined4 local_384;
  undefined4 local_380;
  undefined4 local_37c;
  undefined4 local_378;
  undefined4 local_374;
  undefined4 local_370;
  undefined1 local_36c [4];
  undefined1 local_368 [16];
  int local_358;
  undefined4 local_354;
  undefined4 local_350 [3];
  char local_343;
  undefined4 local_340;
  short local_33c;
  undefined4 local_338;
  undefined4 local_334;
  undefined4 local_330;
  undefined1 local_32c [20];
  char local_318;
  short local_316;
  undefined4 local_314;
  undefined4 local_310;
  undefined4 local_30c;
  undefined1 local_308 [20];
  char local_2f4;
  short local_2f2;
  short local_2f0;
  undefined4 local_2ec;
  undefined4 local_2e8;
  undefined4 local_2e4;
  undefined1 local_2e0 [20];
  byte local_2cc;
  short local_2c0;
  short local_2be;
  undefined1 local_2b4;
  short local_2a8;
  int local_2a4;
  short asStack_298 [2];
  int local_294;
  short asStack_288 [6];
  char local_27c;
  undefined4 local_278;
  undefined4 local_274;
  undefined4 local_270;
  undefined4 local_26c;
  undefined4 local_268;
  char local_25c;
  char local_25b;
  short local_25a;
  short local_250;
  int local_24c;
  undefined4 auStack_240 [4];
  short local_230;
  int local_224;
  short local_220;
  int local_214;
  undefined4 local_210;
  int local_204;
  undefined4 local_200;
  undefined4 local_1f0;
  undefined4 local_1e0;
  undefined4 local_1d0;
  undefined4 local_1cc;
  char local_1c8;
  int local_1bc;
  undefined4 local_1b0;
  char local_1a4;
  char local_1a3;
  undefined4 local_1a0;
  int local_190;
  int local_184;
  int local_180;
  undefined1 local_17c;
  char local_170;
  undefined4 local_164;
  char local_14b;
  char local_14a;
  short local_148;
  undefined1 local_146;
  char local_13b;
  char local_13a;
  short local_138;
  undefined1 local_136;
  short local_12c;
  undefined1 local_128 [12];
  undefined1 local_11c;
  short local_110;
  undefined4 local_8;
  
  local_8 = DAT_006b77f4;
  uVar2 = FUN_004165e0(param_2);
  switch(uVar2) {
  case 5:
  case 0x12:
  case 0x13:
  case 0x14:
    *(undefined1 *)(param_1 + 0x4a40) = 1;
    break;
  case 8:
    FUN_0041d090();
    FUN_0063efb0(param_2);
    FUN_0064aed0((int)local_110);
    break;
  case 9:
    FUN_0063f110();
    FUN_0063ed30(param_2);
    FUN_0064b060((int)local_12c,local_128,local_11c);
    break;
  case 10:
    FUN_00416670();
    FUN_00416500(param_2);
    FUN_00646110((int)local_83c,local_83a,local_83b);
    break;
  case 0xd:
    FUN_00423cc0();
    FUN_00423d70(param_2);
    if (local_13a < '\0') {
      FUN_00422240((int)local_13b,(int)local_138,local_136);
    }
    else {
      FUN_00422300((int)local_13b,(int)local_13a,(int)local_138,local_136);
    }
    break;
  case 0xe:
    FUN_00423df0();
    FUN_00423d70(param_2);
    if (local_14a < '\0') {
      FUN_004223d0((int)local_14b,(int)local_148,local_146);
    }
    else {
      FUN_00422490((int)local_14b,(int)local_14a,(int)local_148,local_146);
    }
    break;
  case 0x15:
    FUN_0063b770();
    FUN_0063b7e0(param_2);
    DAT_006cfba4 = (int)local_7dc;
    break;
  case 0x18:
    (**(code **)(*(int *)(param_1 + 0x15c) + 4))(param_2);
    FUN_0063fab0(param_1 + 0x15c);
    *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x164);
    break;
  case 0x19:
    (**(code **)(*(int *)(param_1 + 0x1f8) + 4))(param_2);
    FUN_0063fc50(param_1 + 0x1f8);
    *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x200);
    break;
  case 0x1a:
    FUN_0063f620();
    FUN_0063edc0(param_2);
    *(undefined4 *)(*(int *)(param_1 + 0x129c + local_27c * 4) + 0x2c) = local_278;
    *(undefined4 *)(*(int *)(param_1 + 0x129c + local_27c * 4) + 0x30) = local_274;
    *(undefined4 *)(*(int *)(param_1 + 0x129c + local_27c * 4) + 0x34) = local_270;
    *(undefined4 *)(*(int *)(param_1 + 0x129c + local_27c * 4) + 0x68) = local_26c;
    *(undefined4 *)(*(int *)(param_1 + 0x129c + local_27c * 4) + 0x2d8) = local_268;
    break;
  case 0x1c:
    FUN_0063f4a0();
    FUN_0063ef00(param_2);
    for (local_24c = 0; local_24c < 4; local_24c = local_24c + 1) {
      *(undefined4 *)(*(int *)(param_1 + 0x129c + local_24c * 4) + 0x7a4) = auStack_240[local_24c];
    }
    if (*(char *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x318) == '\x01') {
      *(int *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x83c) = (int)local_230;
    }
    else if (*(char *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x318) == '\x02') {
      *(int *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x840) = (int)local_230;
    }
    else {
      *(int *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x838) = (int)local_230;
    }
    break;
  case 0x1d:
    FUN_0063f530();
    FUN_0063efb0(param_2);
    *(int *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x834) = (int)local_250;
    break;
  case 0x1e:
    FUN_0063f590();
    FUN_0063ef60(param_2);
    *(int *)(*(int *)(param_1 + 0x129c + local_25c * 4) + 0x7dc + local_25b * 4) = (int)local_25a;
    break;
  case 0x1f:
    FUN_00423ea0();
    FUN_00423f00(param_2);
    FUN_00422900();
    break;
  case 0x20:
    FUN_00423f30();
    FUN_00423fb0(param_2);
    FUN_0065d670();
    *(undefined1 *)(*(int *)(param_1 + 0x129c + local_180 * 4) + 0xaecc) = 1;
    *(undefined4 *)(*(int *)(param_1 + 0x129c + local_180 * 4) + 0xaed0) =
         *(undefined4 *)(param_1 + 0x129c + local_184 * 4);
    *(undefined1 *)(*(int *)(*(int *)(param_1 + 0x129c + local_180 * 4) + 0xaed0) + 0xaed8) =
         local_17c;
    FUN_0065d6a0();
    break;
  case 0x21:
    FUN_00424000();
    FUN_00424070(param_2);
    FUN_0065d670();
    *(undefined1 *)(*(int *)(param_1 + 0x129c + local_190 * 4) + 0xaecc) = 0;
    *(undefined4 *)(*(int *)(param_1 + 0x129c + local_190 * 4) + 0xaed0) = 0;
    FUN_0065d6a0();
    break;
  case 0x22:
    FUN_004240b0();
    FUN_00424130(param_2);
    if (local_1a3 == '\0') {
      FUN_00422f40();
    }
    else {
      FUN_00422ed0();
      *(undefined4 *)(*(int *)(param_1 + 0x129c + local_1a4 * 4) + 0x7a0) = local_1a0;
    }
    break;
  case 0x23:
    FUN_0063f1e0();
    FUN_0041d7e0(param_2);
    *(undefined4 *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x7a0) = local_1b0;
    break;
  case 0x24:
    FUN_00423b80();
    FUN_00423be0(param_2);
    if (*(char *)(*(int *)(param_1 + 0x129c + local_1bc * 4) + 0x318) == '\0') {
      FUN_00421fe0();
    }
    else if (*(char *)(*(int *)(param_1 + 0x129c + local_1bc * 4) + 0x318) == '\x02') {
      FUN_00422160();
    }
    else {
      FUN_004220e0();
    }
    break;
  case 0x26:
    FUN_0063f240();
    FUN_0063ee90(param_2);
    FUN_0065d670();
    FUN_00434a70(0,local_1d0);
    FUN_00434a70(1,local_1cc);
    if (local_1c8 == '\0') {
      FUN_00434bd0();
    }
    else {
      FUN_00434b30();
    }
    FUN_0065d6a0();
    break;
  case 0x27:
    FUN_0063f3c0();
    FUN_00423c80(param_2);
    FUN_0065d670();
    *(undefined4 *)(*(int *)(param_1 + 0x129c + local_204 * 4) + 0xa0) = local_200;
    if (*(int *)(*(int *)(param_1 + 0x129c + local_204 * 4) + 0xa0) < 0x3c) {
      *(undefined4 *)(*(int *)(param_1 + 0x129c + local_204 * 4) + 0x82c) = 0;
    }
    else {
      *(undefined4 *)(*(int *)(param_1 + 0x129c + local_204 * 4) + 0x82c) =
           *(undefined4 *)(*(int *)(param_1 + 0x129c + local_204 * 4) + 0xa0);
    }
    FUN_0065d6a0();
    break;
  case 0x28:
    FUN_00423c10();
    FUN_00423c80(param_2);
    FUN_0065d670();
    *(undefined4 *)(*(int *)(param_1 + 0x129c + local_214 * 4) + 0x828) = local_210;
    FUN_0065d6a0();
    break;
  case 0x29:
    FUN_0063f430();
    FUN_0063efe0(param_2);
    FUN_0065d670();
    *(int *)(*(int *)(param_1 + 0x129c + local_224 * 4) + 0x7ac) = (int)local_220;
    FUN_0065d6a0();
    break;
  case 0x2a:
    FUN_0063f2e0();
    FUN_00424070(param_2);
    FUN_0065d670();
    FUN_00421e30(local_1e0);
    FUN_0065d6a0();
    break;
  case 0x2b:
    FUN_0063f350();
    FUN_00424070(param_2);
    FUN_0065d670();
    FUN_00421f30(local_1f0);
    FUN_0065d6a0();
    break;
  case 0x2c:
    FUN_0063f820();
    FUN_0063efb0(param_2);
    FUN_0065d670();
    *(int *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x684) = (int)local_2a8;
    FUN_0065d6a0();
    break;
  case 0x2d:
    FUN_0063f880();
    FUN_0063efb0(param_2);
    FUN_0065d670();
    *(undefined1 *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x310) = local_2b4;
    *(undefined4 *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x314) = 0x40000000;
    FUN_0065d6a0();
    break;
  case 0x2e:
    FUN_0063f720();
    FUN_0063f060(param_2);
    for (local_294 = 0; local_294 < 2; local_294 = local_294 + 1) {
      if (*(int *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x6dc + local_294 * 0x44) <
          (int)asStack_288[local_294]) {
        *(undefined4 *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x700 + local_294 * 0x44) =
             0;
      }
      else if ((asStack_288[local_294] == 0) &&
              (0 < *(int *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x6dc + local_294 * 0x44
                           ))) {
        *(undefined4 *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x700 + local_294 * 0x44) =
             0;
      }
      *(int *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x6dc + local_294 * 0x44) =
           (int)asStack_288[local_294];
    }
    break;
  case 0x2f:
    FUN_0063f7a0();
    FUN_0063f060(param_2);
    for (local_2a4 = 0; local_2a4 < 2; local_2a4 = local_2a4 + 1) {
      *(int *)(*(int *)(param_1 + 0x129c + DAT_006cfba4 * 4) + 0x724 + local_2a4 * 4) =
           (int)asStack_298[local_2a4];
    }
    break;
  case 0x30:
    FUN_0063f8e0();
    FUN_0063f020(param_2);
    if (*(int *)(param_1 + 0x12b0) < (int)local_2c0) {
      FUN_006431d0(0,(int)local_2c0 - *(int *)(param_1 + 0x12b0));
    }
    if (*(int *)(param_1 + 0x12bc) < (int)local_2be) {
      FUN_006431d0(1,(int)local_2be - *(int *)(param_1 + 0x12bc));
    }
    *(int *)(param_1 + 0x12b0) = (int)local_2c0;
    *(int *)(param_1 + 0x12bc) = (int)local_2be;
    break;
  case 0x31:
    FUN_0063be00();
    FUN_0063b7e0(param_2);
    *(uint *)(param_1 + 0x4428) = (uint)local_2cc;
    *(undefined1 *)(*(int *)(param_1 + 0x129c + (uint)local_2cc * 4) + 0xaec9) = 1;
    FUN_00421960();
    break;
  case 0x33:
    FUN_0063b8a0();
    FUN_0041d7e0(param_2);
    *(undefined4 *)(param_1 + 0x43d8) = local_164;
    break;
  case 0x34:
    FUN_0063b900();
    FUN_004165b0(param_2);
    if (local_170 == '\0') {
      *(undefined4 *)(param_1 + 0x442c) = 0;
      *(undefined4 *)(param_1 + 0x4424) = 0;
      *(undefined4 *)(param_1 + 0x4428) = 1;
    }
    else {
      *(undefined4 *)(param_1 + 0x442c) = 1;
      *(undefined4 *)(param_1 + 0x4424) = 2;
      *(undefined4 *)(param_1 + 0x4428) = 3;
    }
    *(undefined4 *)(param_1 + 0x4414) = 0xb4;
    *(undefined4 *)(param_1 + 0x441c) = 0x41000000;
    *(undefined4 *)(param_1 + 0x4a3c) = 3;
    break;
  case 0x35:
    FUN_0063bba0();
    FUN_0063bcf0(param_2);
    FUN_00435990((int)local_2f2,local_2ec,local_2e8,local_2e4,local_2e0,
                 *(undefined4 *)(param_1 + 0x129c + local_2f4 * 4));
    uVar6 = 1;
    uVar2 = FUN_00423750(local_2ec,local_2e8,local_2e4);
    FUN_0064ae70((int)local_2f0,uVar2,uVar6);
    break;
  case 0x36:
    FUN_00423960();
    FUN_00423a90(param_2);
    FUN_00435990((int)local_316,local_314,local_310,local_30c,local_308,
                 *(undefined4 *)(param_1 + 0x129c + local_318 * 4));
    break;
  case 0x38:
    FUN_005f8ec0();
    FUN_005f8fd0(param_2);
    FUN_005f8cb0(local_340,(int)local_33c,local_338,local_334,local_330,local_32c,
                 *(undefined4 *)(param_1 + 0x129c + local_343 * 4));
    break;
  case 0x39:
    FUN_005f7690();
    FUN_005f7820(param_2);
    FUN_0065d670();
    FUN_00653d10(local_350);
    FUN_00654620(&local_354);
    while (cVar1 = const_iterator__operator__(&local_354), cVar1 != '\0') {
      piVar4 = (int *)FUN_00653d70();
      if (*(int *)(*piVar4 + 0x160) == local_358) {
        FUN_00653d70();
        iVar3 = FUN_00435e40();
        if (iVar3 == 0) {
          piVar4 = (int *)FUN_00653d70();
          local_85c = (undefined4 *)*piVar4;
          local_858 = local_85c;
          if (local_85c != (undefined4 *)0x0) {
            (**(code **)*local_85c)(1);
          }
          puVar5 = (undefined4 *)FUN_00425500(local_860,local_350[0]);
          local_350[0] = *puVar5;
          puVar5 = (undefined4 *)FUN_00654620(local_864);
          local_354 = *puVar5;
        }
        else {
          FUN_0042fc40(local_854,0);
        }
      }
      else {
        FUN_0042fc40(local_868,0);
      }
    }
    FUN_0065d6a0();
    break;
  case 0x3a:
    FUN_005f77b0();
    FUN_005f7820(param_2);
    FUN_0065d670();
    FUN_00653d10(local_3a4);
    FUN_00654620(local_3a8);
    while (cVar1 = const_iterator__operator__(local_3a8), cVar1 != '\0') {
      piVar4 = (int *)FUN_00653d70();
      local_3bc = *piVar4;
      if ((*(int *)(local_3bc + 0x160) == local_3ac) &&
         (FUN_005f71f0(), *(int *)(*(int *)(param_1 + 0x129c + local_3b0 * 4) + 0x77c) == 10)) {
        *(undefined4 *)(local_3bc + 0xf0) = 0x3c;
      }
      FUN_0042fc40(local_870,0);
    }
    FUN_0065d6a0();
    break;
  case 0x3b:
    FUN_005f7860();
    FUN_005f7990(param_2);
    FUN_0065d670();
    FUN_00653d10(local_368);
    FUN_00654620(local_36c);
    while (cVar1 = const_iterator__operator__(local_36c), cVar1 != '\0') {
      piVar4 = (int *)FUN_00653d70();
      local_3a0 = *piVar4;
      if (*(int *)(local_3a0 + 0x160) == local_390) {
        *(int *)(local_3a0 + 8) = (int)local_38c;
        *(undefined4 *)(local_3a0 + 0x38) = *(undefined4 *)(param_1 + 0x129c + local_393 * 4);
        *(undefined4 *)(local_3a0 + 0x14) = local_388;
        *(undefined4 *)(local_3a0 + 0x18) = local_384;
        *(undefined4 *)(local_3a0 + 0x1c) = local_380;
        *(undefined4 *)(local_3a0 + 0x5c) = local_37c;
        *(undefined4 *)(local_3a0 + 100) = local_378;
        *(undefined4 *)(local_3a0 + 0x6c) = local_374;
        *(undefined4 *)(local_3a0 + 0x54) = local_370;
      }
      FUN_0042fc40(local_86c,0);
    }
    FUN_0065d6a0();
    break;
  case 0x3d:
    FUN_0063f950();
    if ((*(int *)(param_1 + 0x4a3c) == 4) && (*(int *)(param_1 + 0x41e0) != 0)) {
      FUN_00656200(*(undefined4 *)(param_1 + 0x4490));
      FUN_0063f0b0(param_2);
      local_7bc[0] = 0;
      for (local_7d8 = 0; local_7d8 < 4; local_7d8 = local_7d8 + 1) {
        if (0 < local_7d8) {
          FUN_0066b870(local_7bc,&DAT_006a4b1c);
        }
        uVar2 = FUN_00430860(auStack_7cc[local_7d8]);
        FUN_0066b870(local_7bc,uVar2);
      }
      puVar5 = (undefined4 *)FUN_00656190(local_874,local_7bc,*(undefined4 *)(param_1 + 0xf78));
      *(undefined4 *)(param_1 + 0x4490) = *puVar5;
      FUN_00655690(*(undefined4 *)(param_1 + 0x4490),0,0,0x200,0x25);
      *(undefined4 *)(param_1 + 0x4a3c) = 4;
      *(undefined4 *)(param_1 + 0x41e0) = 5;
      *(undefined4 *)(param_1 + 0x41dc) = 0;
    }
  }
  return;
}

