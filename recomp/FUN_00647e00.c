// ============================================
// Address:  0x00647e00
// Original: FUN_00647e00
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __fastcall FUN_00647e00(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 local_130 [4];
  undefined1 local_12c [4];
  undefined1 local_128 [4];
  int local_124;
  int local_120;
  int local_11c;
  int local_118;
  CHAR local_114 [268];
  undefined4 local_8;
  
  local_8 = DAT_006b77f4;
  cVar1 = FUN_006486c0();
  if (cVar1 == '\0') {
    _memset((void *)(param_1 + 0x5600),0,0xd0);
    for (local_118 = 1; local_118 < 4; local_118 = local_118 + 1) {
      *(undefined1 *)(param_1 + 0x5600 + local_118 * 0x34) = (undefined1)local_118;
      *(undefined4 *)(param_1 + 0x5614 + local_118 * 0x34) = 0;
      *(undefined4 *)(param_1 + 0x5618 + local_118 * 0x34) = 1;
      *(undefined4 *)(param_1 + 0x561c + local_118 * 0x34) = 2;
      *(undefined4 *)(param_1 + 0x5620 + local_118 * 0x34) = 3;
      *(undefined4 *)(param_1 + 0x5624 + local_118 * 0x34) = 4;
      *(undefined4 *)(param_1 + 0x5628 + local_118 * 0x34) = 5;
      *(undefined4 *)(param_1 + 0x562c + local_118 * 0x34) = 6;
      *(undefined4 *)(param_1 + 0x5630 + local_118 * 0x34) = 7;
    }
    *(undefined1 *)(param_1 + 0x5600) = 0xff;
    *(undefined4 *)(param_1 + 0x5604) = 200;
    *(undefined4 *)(param_1 + 0x5608) = 0xd0;
    *(undefined4 *)(param_1 + 0x560c) = 0xcb;
    *(undefined4 *)(param_1 + 0x5610) = 0xcd;
    *(undefined4 *)(param_1 + 0x5614) = 0x2c;
    *(undefined4 *)(param_1 + 0x5618) = 0x2d;
    *(undefined4 *)(param_1 + 0x561c) = 0x2e;
    *(undefined4 *)(param_1 + 0x5620) = 0x1e;
    *(undefined4 *)(param_1 + 0x5624) = 0x1f;
    *(undefined4 *)(param_1 + 0x5628) = 0x20;
    *(undefined4 *)(param_1 + 0x562c) = 0x10;
    *(undefined4 *)(param_1 + 0x5630) = 0x11;
    *(undefined1 *)(param_1 + 0x54ca) = 1;
    *(undefined1 *)(param_1 + 0x54cc) = 1;
    *(undefined1 *)(param_1 + 0x54cb) = 1;
    *(undefined1 *)(param_1 + 0x54cd) = 0;
    *(undefined4 *)(param_1 + 0x54d0) = 100;
    *(undefined4 *)(param_1 + 0x54d4) = 0x60;
    *(undefined4 *)(param_1 + 0x54d8) = 0x5c;
    *(undefined4 *)(param_1 + 0x54dc) = 100;
    _memset((void *)(param_1 + 0x5598),0,9);
    _memset((void *)(param_1 + 0x55a1),0,4);
    *(undefined1 *)(param_1 + 0x55a5) = 3;
    *(undefined2 *)(param_1 + 0x55a6) = 0x92bc;
    *(undefined1 *)(param_1 + 0x55a8) = 0;
    *(undefined4 *)(param_1 + 0x54e4) = 0;
  }
  *(undefined1 *)(param_1 + 0x56d0) = 0xfe;
  FUN_00659bf0();
  FUN_0065a090(*(int *)(param_1 + 0x54d0) * *(int *)(param_1 + 0x54d8));
  FUN_0042eba0(0);
  for (local_11c = 0; local_11c < 0x100; local_11c = local_11c + 1) {
    wsprintfA(local_114,"data/se/%03d.wav",local_11c);
    puVar2 = (undefined4 *)FUN_00659eb0(local_128,local_114);
    *(undefined4 *)(param_1 + 0x98 + local_11c * 4) = *puVar2;
  }
  for (local_120 = 0; local_120 < 0x20; local_120 = local_120 + 1) {
    wsprintfA(local_114,"data/sysse/%03d.wav",local_120);
    puVar2 = (undefined4 *)FUN_00659d80(local_12c,local_114);
    *(undefined4 *)(param_1 + 0x18 + local_120 * 4) = *puVar2;
  }
  FUN_0065b680();
  FUN_0065b820(*(undefined4 *)(param_1 + 0xc));
  FUN_0065b9f0(*(int *)(param_1 + 0x54d0) * *(int *)(param_1 + 0x54d4));
  FUN_0065c050(*(undefined4 *)(param_1 + 0x10));
  FUN_0065afb0();
  FUN_0065b250(*(int *)(param_1 + 0x54d0) * *(int *)(param_1 + 0x54dc));
  _memset((void *)(param_1 + 0x5308),0,0x10);
  puVar2 = (undefined4 *)FUN_006560c0(local_130,"data/object/logo.bmp");
  *(undefined4 *)(param_1 + 0x498) = *puVar2;
  FUN_00655b20(*(undefined4 *)(param_1 + 0x498),0,0,0x100,0xa0,0x80,0x50);
  FUN_0064c060();
  FUN_00633ca0();
  for (local_124 = 0; local_124 < 4; local_124 = local_124 + 1) {
    FUN_00657330(param_1 + 0x5600 + local_124 * 0x34);
  }
  if (DAT_006cfceb == '\0') {
    FUN_00687260(2);
  }
  else {
    FUN_00687260(0);
  }
  if (*(char *)(param_1 + 0x54cd) != '\0') {
    FUN_00650ef0();
  }
  *(undefined1 *)(param_1 + 0x55b0) = 8;
  *(undefined1 *)(param_1 + 0x55ff) = 0xff;
  *(undefined1 *)(param_1 + 0x55fc) = 0;
  *(undefined1 *)(param_1 + 0x55fd) = 0;
  *(undefined1 *)(param_1 + 0x55d9) = 0;
  return;
}

