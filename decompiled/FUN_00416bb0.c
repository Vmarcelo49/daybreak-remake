// Function: FUN_00416bb0
// Address:  0x00416bb0
// Source:   batch_decompile (mass dump)
// Hash:     453e121ab4fd6329


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FUN_00416bb0(int param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int local_278;
  int local_274;
  int local_270;
  undefined1 local_26c [8];
  undefined4 auStack_264 [4];
  undefined4 auStack_254 [4];
  undefined4 auStack_244 [4];
  int aiStack_234 [4];
  int aiStack_224 [4];
  int aiStack_214 [4];
  undefined4 local_204;
  undefined4 local_200;
  undefined4 local_1fc;
  undefined4 local_1f8;
  undefined4 local_1f4;
  undefined4 local_1f0;
  undefined1 local_1ec [8];
  undefined1 auStack_1e4 [8];
  undefined1 auStack_1dc [72];
  undefined1 auStack_194 [8];
  undefined1 auStack_18c [4];
  undefined1 local_188;
  undefined1 local_187;
  undefined1 local_186;
  char local_185;
  undefined1 local_184;
  undefined1 local_183;
  undefined1 local_17c [8];
  char local_174;
  undefined1 local_173;
  undefined1 local_172 [94];
  undefined1 local_114 [12];
  int local_108;
  undefined1 local_104 [8];
  undefined4 auStack_fc [4];
  undefined4 auStack_ec [4];
  undefined4 auStack_dc [4];
  int aiStack_cc [4];
  int aiStack_bc [8];
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  int local_78;
  undefined1 local_74 [8];
  char local_6c;
  undefined1 local_6b;
  undefined1 local_6a [86];
  undefined4 local_14;
  undefined2 local_8;
  
  local_14 = DAT_006b77f4;
  uVar1 = FUN_004165e0(param_3);
  switch(uVar1) {
  case 1:
    FUN_00416410();
    FUN_0041d7e0(param_3);
    if (local_78 == 0xd) {
      FUN_004177a0();
      for (local_108 = 0; local_108 < 4; local_108 = local_108 + 1) {
        auStack_ec[local_108] = (&DAT_006cfb28)[local_108];
        auStack_fc[local_108] = (&DAT_006cfaf8)[local_108];
        auStack_dc[local_108] = *(undefined4 *)(&DAT_006cfb38 + local_108 * 4);
        aiStack_cc[local_108] = (int)(char)(&DAT_006cfb48)[local_108];
        aiStack_bc[local_108] = (int)(char)(&DAT_006cfb4c)[local_108];
      }
      local_9c = DAT_006cfaf4;
      local_98 = DAT_006cf3c0;
      local_94 = DAT_006cf3b8;
      local_90 = DAT_006cf3bc;
      local_8c = DAT_006cf3b0;
      local_88 = DAT_006cf3b4;
      FUN_00415d30(param_2,local_104,0,8);
    }
    else if (local_78 == 0x13) {
      *(undefined4 *)(param_1 + 0x140 + param_2 * 4) = 1;
    }
    break;
  case 2:
    FUN_00417750();
    FUN_00417710(param_3);
    if (*(int *)(DAT_006cfa24 + param_2 * 4) == 0) {
      if ((-1 < (char)(&DAT_006cfde1)[param_2]) &&
         (-1 < *(int *)(&DAT_006cfb08 + (char)(&DAT_006cfde1)[param_2] * 4))) {
        FUN_00417730(local_8);
      }
    }
    else {
      FUN_00417730(local_8);
    }
    if (-1 < (char)(&DAT_006cfde1)[param_2]) {
      FUN_00417730(local_8);
    }
    break;
  case 10:
    FUN_00416670();
    FUN_00416500(param_3);
    if ((DAT_006cfdc8 != '\0') && (DAT_006cfe1e != '\0')) {
      FUN_00415d30(0,local_74,0,8);
      FUN_00646110((int)local_6c,local_6a,local_6b);
    }
    break;
  case 0xf:
    FUN_00416600();
    FUN_00416560(param_3);
    FUN_00415ea0();
    local_184 = 0;
    local_183 = 0;
    local_188 = DAT_006cfdd0;
    local_187 = DAT_006cfdf9;
    local_186 = DAT_006cfe1c;
    local_185 = DAT_006cfe1e;
    _memcpy(&DAT_006cfb58 + param_2 * 9,local_114,9);
    FUN_00645dc0(param_2,&DAT_006cfb58 + param_2 * 9);
    for (local_270 = 0; local_270 < 8; local_270 = local_270 + 1) {
      _memcpy(auStack_1dc + local_270 * 9,&DAT_006cfb58 + local_270 * 9,9);
      auStack_1e4[local_270] = (&DAT_006cfdd1)[local_270];
      auStack_194[local_270] = (&DAT_006cfde1)[local_270];
    }
    for (local_274 = 0; local_274 < 4; local_274 = local_274 + 1) {
      auStack_18c[local_274] = *(undefined1 *)(&DAT_006cfb18 + local_274);
    }
    FUN_00415d30(0,local_1ec,0,8);
    FUN_004177a0();
    for (local_278 = 0; local_278 < 4; local_278 = local_278 + 1) {
      auStack_254[local_278] = (&DAT_006cfb28)[local_278];
      auStack_264[local_278] = (&DAT_006cfaf8)[local_278];
      auStack_244[local_278] = *(undefined4 *)(&DAT_006cfb38 + local_278 * 4);
      aiStack_234[local_278] = (int)(char)(&DAT_006cfb48)[local_278];
      aiStack_224[local_278] = (int)(char)(&DAT_006cfb4c)[local_278];
      aiStack_214[local_278] = (int)(char)(&DAT_006cfb54)[local_278];
    }
    local_204 = DAT_006cfaf4;
    local_200 = DAT_006cf3c0;
    local_1fc = DAT_006cf3b8;
    local_1f8 = DAT_006cf3bc;
    local_1f4 = DAT_006cf3b0;
    local_1f0 = DAT_006cf3b4;
    FUN_00415d30(param_2,local_26c,0,8);
    FUN_00416670();
    local_174 = (char)param_2;
    local_173 = 2;
    FUN_0066b860(local_172,&DAT_006a1ecc);
    FUN_00415d30(0,local_17c,0,8);
    FUN_00646110((int)local_174,local_172,local_173);
    break;
  case 0x16:
    *(undefined4 *)(param_1 + 0x120 + param_2 * 4) = 1;
  }
  return;
}

