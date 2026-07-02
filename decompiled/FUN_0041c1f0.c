// Function: FUN_0041c1f0
// Address:  0x0041c1f0
// Source:   batch_decompile (mass dump)
// Hash:     600985b469a765d8


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FUN_0041c1f0(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined1 local_1cd;
  undefined1 local_1c4 [4];
  int local_1c0;
  undefined4 auStack_1b4 [4];
  undefined4 auStack_1a4 [4];
  undefined4 auStack_194 [4];
  undefined1 auStack_184 [16];
  undefined1 auStack_174 [16];
  undefined1 auStack_164 [16];
  int local_154;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined1 local_13c [8];
  undefined1 local_134 [8];
  undefined4 local_12c;
  undefined1 local_128 [8];
  undefined4 local_120;
  undefined4 local_114;
  int local_108;
  int local_104;
  int local_100;
  undefined1 auStack_f4 [8];
  undefined1 auStack_ec [72];
  undefined1 auStack_a4 [8];
  char acStack_9c [20];
  int local_88;
  char local_7c;
  undefined1 local_7a [86];
  undefined4 local_24;
  short local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_24 = DAT_006b77f4;
  uVar1 = FUN_004165e0(param_2);
  switch(uVar1) {
  case 1:
    FUN_00416410();
    FUN_0041d7e0(param_2);
    switch(local_114) {
    case 0xc:
      FUN_00416410();
      local_120 = 0xd;
      FUN_0041afb0(local_128,0,8);
      *(undefined4 *)(param_1 + 0x234) = 2;
      break;
    case 0xe:
      FUN_00416410();
      local_12c = 0xf;
      FUN_0041afb0(local_134,0,8);
      break;
    case 0x10:
    case 0x12:
      *(undefined4 *)(param_1 + 0x234) = 3;
    }
    break;
  case 4:
    (**(code **)(*(int *)(param_1 + 0x220) + 4))(param_2);
    for (local_10 = 0; local_10 < 8; local_10 = local_10 + 1) {
      (&DAT_006cfde1)[local_10] = *(undefined1 *)(param_1 + local_10 + 0x228);
    }
    for (local_14 = 0; local_14 < 4; local_14 = local_14 + 1) {
      (&DAT_006cfb18)[local_14] = (int)*(char *)(param_1 + local_14 + 0x230);
    }
    FUN_0064bf60();
    break;
  case 5:
    *(undefined4 *)(param_1 + 0x234) = 1;
    break;
  case 6:
    FUN_00416470();
    FUN_0041afb0(local_13c,0,8);
    *(undefined4 *)(param_1 + 0x234) = 2;
    break;
  case 8:
    FUN_0041d090();
    FUN_0063efb0(param_2);
    FUN_0064aed0((int)local_18);
    break;
  case 10:
    FUN_00416670();
    FUN_00416500(param_2);
    if (((char)(&DAT_006cfde1)[local_7c] < '\0') || (*(char *)(param_1 + -0x158) != '\0')) {
      local_1cd = 0;
    }
    else {
      local_1cd = 1;
    }
    FUN_00646110((int)local_7c,local_7a,CONCAT31((char)(&DAT_006cfde1)[local_7c] >> 7,local_1cd));
    break;
  case 0xb:
    FUN_00416760();
    FUN_0041d7e0(param_2);
    (&DAT_006cfdd1)[local_108] = 0;
    _memset(&DAT_006cfb58 + local_108 * 9,0,9);
    FUN_00645dc0(local_108,&DAT_006cfb58 + local_108 * 9);
    if (-1 < (char)(&DAT_006cfde1)[local_108]) {
      (&DAT_006cfb18)[(char)(&DAT_006cfde1)[local_108]] = 0xffffffff;
      (&DAT_006cfde1)[local_108] = 0xff;
    }
    break;
  case 0xc:
    FUN_004177a0();
    FUN_00417920(param_2);
    for (local_1c0 = 0; local_1c0 < 4; local_1c0 = local_1c0 + 1) {
      (&DAT_006cfb28)[local_1c0] = auStack_1a4[local_1c0];
      *(undefined4 *)(&DAT_006cfb38 + local_1c0 * 4) = auStack_194[local_1c0];
      (&DAT_006cfaf8)[local_1c0] = auStack_1b4[local_1c0];
      (&DAT_006cfb48)[local_1c0] = auStack_184[local_1c0 * 4];
      (&DAT_006cfb4c)[local_1c0] = auStack_174[local_1c0 * 4];
      (&DAT_006cfb54)[local_1c0] = auStack_164[local_1c0 * 4];
    }
    DAT_006cfaf4 = local_154;
    DAT_006cf3c0 = local_150;
    DAT_006cf3b8 = local_14c;
    DAT_006cf3bc = local_148;
    DAT_006cf3b0 = local_144;
    DAT_006cf3b4 = local_140;
    *(undefined4 *)(param_1 + 0x234) = 1;
    break;
  case 0x10:
    FUN_00415ea0();
    FUN_00416030(param_2);
    local_88 = -1;
    for (local_100 = 0; local_100 < 8; local_100 = local_100 + 1) {
      (&DAT_006cfdd1)[local_100] = auStack_f4[local_100];
      if ((&DAT_006cfdd1)[local_100] == '\0') {
        _memset(&DAT_006cfb58 + local_100 * 9,0,9);
      }
      else {
        _memcpy(&DAT_006cfb58 + local_100 * 9,auStack_ec + local_100 * 9,9);
        local_88 = local_88 + 1;
      }
      FUN_00645dc0(local_100,&DAT_006cfb58 + local_100 * 9);
      (&DAT_006cfde1)[local_100] = auStack_a4[local_100];
    }
    DAT_006cfdcc = local_88;
    for (local_104 = 0; local_104 < 4; local_104 = local_104 + 1) {
      (&DAT_006cfb18)[local_104] = (int)acStack_9c[local_104];
    }
    FUN_0064bf60();
    break;
  case 0x12:
    (**(code **)(*(int *)(param_1 + 0x104) + 4))(param_2);
    *(undefined1 *)(param_1 + -0x158) = *(undefined1 *)(param_1 + 0x10c);
    for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
      *(undefined4 *)(&DAT_006cfb08 + local_8 * 4) = 0xffffffff;
    }
    for (local_c = 0; local_c < 4; local_c = local_c + 1) {
      if (*(int *)(param_1 + 0x184 + local_c * 4) < 0) {
        *(undefined4 *)(param_1 + -0x80 + local_c * 4) = 0xffffffff;
      }
      else if (((-1 < *(int *)(param_1 + 0x184 + local_c * 4)) &&
               (*(int *)(param_1 + -0x80 + local_c * 4) == -1)) &&
              (-1 < *(int *)(param_1 + 0x194 + local_c * 4))) {
        *(undefined4 *)(param_1 + -0x80 + local_c * 4) =
             *(undefined4 *)(param_1 + 0x194 + local_c * 4);
        *(undefined4 *)(&DAT_006cfb38 + local_c * 4) =
             *(undefined4 *)(param_1 + -0x80 + local_c * 4);
        FUN_0040d700(local_c,*(undefined4 *)(param_1 + 0x184 + local_c * 4));
      }
      *(undefined4 *)(param_1 + -0x90 + local_c * 4) =
           *(undefined4 *)(param_1 + 0x184 + local_c * 4);
      (&DAT_006cfb28)[local_c] = *(undefined4 *)(param_1 + -0x90 + local_c * 4);
      *(undefined4 *)(param_1 + -0x80 + local_c * 4) =
           *(undefined4 *)(param_1 + 0x194 + local_c * 4);
      *(undefined4 *)(&DAT_006cfb38 + local_c * 4) = *(undefined4 *)(param_1 + -0x80 + local_c * 4);
      *(undefined4 *)(param_1 + -0xa0 + local_c * 4) =
           *(undefined4 *)(param_1 + 0x174 + local_c * 4);
      (&DAT_006cfaf8)[local_c] = *(undefined4 *)(param_1 + -0xa0 + local_c * 4);
      *(undefined4 *)(param_1 + -0x70 + local_c * 4) =
           *(undefined4 *)(param_1 + 0x1a4 + local_c * 4);
      (&DAT_006cfb48)[local_c] = *(undefined1 *)(param_1 + -0x70 + local_c * 4);
      *(undefined4 *)(param_1 + -0x60 + local_c * 4) =
           *(undefined4 *)(param_1 + 0x1b4 + local_c * 4);
      (&DAT_006cfb4c)[local_c] = *(undefined1 *)(param_1 + -0x60 + local_c * 4);
      *(undefined1 *)(param_1 + local_c + -0xc4) = *(undefined1 *)(param_1 + 0x1c4 + local_c * 4);
      (&DAT_006cfb54)[local_c] = *(undefined1 *)(param_1 + local_c + -0xc4);
      *(undefined4 *)(param_1 + -0x150 + local_c * 4) =
           *(undefined4 *)(param_1 + 0x110 + local_c * 4);
      *(undefined4 *)(param_1 + -0x140 + local_c * 4) =
           *(undefined4 *)(param_1 + 0x120 + local_c * 4);
      *(undefined4 *)(param_1 + -0x130 + local_c * 4) =
           *(undefined4 *)(param_1 + 0x130 + local_c * 4);
      *(undefined4 *)(param_1 + -0x118 + local_c * 4) =
           *(undefined4 *)(param_1 + 0x140 + local_c * 4);
      *(undefined4 *)(param_1 + -0xf8 + local_c * 4) =
           *(undefined4 *)(param_1 + 0x160 + local_c * 4);
      if ((*(char *)(param_1 + local_c + -0xe8) != *(char *)(param_1 + local_c + 0x170)) &&
         (*(char *)(param_1 + local_c + 0x170) != '\0')) {
        *(undefined4 *)(param_1 + -0xe4 + local_c * 4) = 0x40800000;
        FUN_0065b1d0(*(undefined4 *)(param_1 + -0x160));
        if (*(char *)(param_1 + local_c + -0xc4) == '\x02') {
          uVar2 = FUN_0065d150();
          uVar2 = uVar2 % 2;
          uVar1 = FUN_00649770(*(undefined4 *)(param_1 + -0x90 + local_c * 4));
          wsprintfA((LPSTR)(param_1 + -0x264),"data/voice/entry/%s_C%02d.wav",uVar1,uVar2);
        }
        else if (*(char *)(param_1 + local_c + -0xc4) == '\x01') {
          if (((*(int *)(param_1 + -0x90 + local_c * 4) == 0) ||
              (*(int *)(param_1 + -0x90 + local_c * 4) == 4)) &&
             (*(int *)(param_1 + -0x80 + local_c * 4) == 2)) {
            uVar2 = FUN_0065d150();
            uVar2 = uVar2 % 2;
            uVar1 = FUN_00649770(*(undefined4 *)(param_1 + -0x90 + local_c * 4));
            wsprintfA((LPSTR)(param_1 + -0x264),"data/voice/entry/%sB_B%02d.wav",uVar1,uVar2);
          }
          else {
            uVar2 = FUN_0065d150();
            uVar2 = uVar2 % 2;
            uVar1 = FUN_00649770(*(undefined4 *)(param_1 + -0x90 + local_c * 4));
            wsprintfA((LPSTR)(param_1 + -0x264),"data/voice/entry/%s_B%02d.wav",uVar1,uVar2);
          }
        }
        else if (((*(int *)(param_1 + -0x90 + local_c * 4) == 0) ||
                 (*(int *)(param_1 + -0x90 + local_c * 4) == 4)) &&
                (*(int *)(param_1 + -0x80 + local_c * 4) == 2)) {
          uVar1 = FUN_00649770(*(undefined4 *)(param_1 + -0x90 + local_c * 4));
          wsprintfA((LPSTR)(param_1 + -0x264),"data/voice/entry/%sB.wav",uVar1);
        }
        else {
          uVar1 = FUN_00649770(*(undefined4 *)(param_1 + -0x90 + local_c * 4));
          wsprintfA((LPSTR)(param_1 + -0x264),"data/voice/entry/%s.wav",uVar1);
        }
        puVar3 = (undefined4 *)FUN_0065b0d0(local_1c4,param_1 + -0x264);
        *(undefined4 *)(param_1 + -0x160) = *puVar3;
        FUN_0065b330(*(undefined4 *)(param_1 + -0x160),0);
      }
      *(undefined1 *)(param_1 + local_c + -0xe8) = *(undefined1 *)(param_1 + local_c + 0x170);
      if (*(int *)(param_1 + -0x108 + local_c * 4) != *(int *)(param_1 + 0x150 + local_c * 4)) {
        *(undefined4 *)(param_1 + -0x108 + local_c * 4) =
             *(undefined4 *)(param_1 + 0x150 + local_c * 4);
        *(undefined4 *)(param_1 + -0xd4 + local_c * 4) = 0x43960000;
      }
      if ((-1 < *(int *)(param_1 + -0xa0 + local_c * 4)) &&
         (*(int *)(param_1 + -0xa0 + local_c * 4) < 4)) {
        *(int *)(&DAT_006cfb08 + *(int *)(param_1 + -0xa0 + local_c * 4) * 4) = local_c;
      }
    }
    break;
  case 0x13:
    (**(code **)(*(int *)(param_1 + 0x1d4) + 4))(param_2);
    *(undefined1 *)(param_1 + -0x158) = *(undefined1 *)(param_1 + 0x1dc);
    *(undefined4 *)(param_1 + -0x50) = *(undefined4 *)(param_1 + 0x1e0);
    *(undefined4 *)(param_1 + -0x4c) = *(undefined4 *)(param_1 + 0x1e4);
    if (*(int *)(param_1 + -0x50) == 0) {
      DAT_006cfaf4 = *(int *)(param_1 + -0x4c);
    }
    else {
      DAT_006cfaf4 = *(int *)(param_1 + -0x4c) * 10 + *(int *)(param_1 + -0x50);
    }
    *(int *)(param_1 + -0x120) = (int)*(char *)(param_1 + 0x1e8);
    *(int *)(param_1 + -0x11c) = (int)*(char *)(param_1 + 0x1e9);
    DAT_006cf3c0 = *(undefined4 *)(param_1 + 0x1ec);
    DAT_006cf3b8 = *(undefined4 *)(param_1 + 0x1f0);
    DAT_006cf3bc = *(undefined4 *)(param_1 + 500);
    DAT_006cf3b0 = *(undefined4 *)(param_1 + 0x1f8);
    DAT_006cf3b4 = *(undefined4 *)(param_1 + 0x1fc);
    break;
  case 0x14:
    (**(code **)(*(int *)(param_1 + 0x200) + 4))(param_2);
    *(undefined4 *)(param_1 + -0xc0 + *(char *)(param_1 + 0x210) * 4) =
         *(undefined4 *)(param_1 + 0x208);
    *(undefined4 *)(param_1 + -0xb0 + *(char *)(param_1 + 0x210) * 4) =
         *(undefined4 *)(param_1 + 0x20c);
  }
  return;
}

