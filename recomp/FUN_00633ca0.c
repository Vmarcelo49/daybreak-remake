// ============================================
// Address:  0x00633ca0
// Original: FUN_00633ca0
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __fastcall FUN_00633ca0(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  void *pvVar3;
  undefined4 local_178;
  undefined4 local_170;
  undefined1 local_14c [4];
  undefined1 local_148 [4];
  undefined1 local_144 [4];
  undefined1 local_140 [4];
  undefined1 local_13c [4];
  undefined1 local_138 [4];
  undefined1 local_134 [4];
  int local_130;
  int local_12c;
  int local_128;
  int local_124;
  CHAR local_120 [268];
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e75c;
  local_10 = ExceptionList;
  local_14 = DAT_006b77f4;
  ExceptionList = &local_10;
  puVar2 = (undefined4 *)FUN_006560c0(local_134,"data/object/system.bmp");
  *(undefined4 *)(param_1 + 0x4434) = *puVar2;
  puVar2 = (undefined4 *)FUN_006560c0(local_138,&DAT_006a4944);
  *(undefined4 *)(param_1 + 0x4438) = *puVar2;
  puVar2 = (undefined4 *)FUN_006560c0(local_13c,"data/object/P04.bmp");
  *(undefined4 *)(param_1 + 0x443c) = *puVar2;
  puVar2 = (undefined4 *)FUN_006560c0(local_140,"data/object/P05.bmp");
  *(undefined4 *)(param_1 + 0x4440) = *puVar2;
  puVar2 = (undefined4 *)FUN_006560c0(local_144,"data/object/P08.bmp");
  *(undefined4 *)(param_1 + 0x4444) = *puVar2;
  puVar2 = (undefined4 *)FUN_006560c0(local_148,"data/object/P09.bmp");
  *(undefined4 *)(param_1 + 0x4448) = *puVar2;
  for (local_124 = 0; local_124 < 10; local_124 = local_124 + 1) {
    wsprintfA(local_120,"data/trail/%02d.bmp",local_124);
    puVar2 = (undefined4 *)FUN_006560c0(local_14c,local_120);
    *(undefined4 *)(param_1 + 0x445c + local_124 * 4) = *puVar2;
  }
  for (local_128 = 0; local_128 < 7; local_128 = local_128 + 1) {
    wsprintfA(local_120,"data/aura/%02d.x",local_128);
    pvVar3 = operator_new(0x9c);
    local_8 = 0;
    if (pvVar3 == (void *)0x0) {
      local_170 = 0;
    }
    else {
      local_170 = FUN_0064d7a0();
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x4498 + local_128 * 4) = local_170;
    cVar1 = FUN_0064d940(local_120);
    if ((cVar1 == '\0') && (*(int *)(param_1 + 0x4498 + local_128 * 4) != 0)) {
      if (*(int *)(param_1 + 0x4498 + local_128 * 4) != 0) {
        FUN_00402010(1);
      }
      *(undefined4 *)(param_1 + 0x4498 + local_128 * 4) = 0;
    }
  }
  FUN_00655b20(*(undefined4 *)(param_1 + 0x4448),0,0x100,0x200,0x100,0x100,0x80);
  FUN_00655b20(*(undefined4 *)(param_1 + 0x443c),0,0,0x200,0x100,0x100,0x80);
  FUN_00655b20(*(undefined4 *)(param_1 + 0x443c),0,0x120,0x200,0xc0,0x100,0x60);
  FUN_00655b20(*(undefined4 *)(param_1 + 0x4448),0,0,0xc0,0x100,0x60,0x80);
  FUN_00655b20(*(undefined4 *)(param_1 + 0x4448),0xc0,0,0xc0,0x100,0x60,0x80);
  FUN_00655b20(*(undefined4 *)(param_1 + 0x4448),0x180,0,0x80,0x100,0x40,0x80);
  FUN_00655b20(*(undefined4 *)(param_1 + 0x443c),0,0x100,0x200,0x100,0x100,0x80);
  FUN_00655b20(*(undefined4 *)(param_1 + 0x4440),0,0,0x200,0x100,0x100,0x80);
  FUN_00655b20(*(undefined4 *)(param_1 + 0x4440),0,0x100,0x200,0x100,0x100,0x80);
  FUN_00655b20(*(undefined4 *)(param_1 + 0x4444),0,0,0x200,0x100,0x100,0x80);
  FUN_00655b20(*(undefined4 *)(param_1 + 0x4444),0,0x100,0x200,0x100,0x100,0x80);
  FUN_00655af0(*(undefined4 *)(param_1 + 0x4438),0,0,0x100,1);
  FUN_00655af0(*(undefined4 *)(param_1 + 0x4438),0xff,0,1,1);
  FUN_00655b20(*(undefined4 *)(param_1 + 0x4434),0x100,0x40,0x100,0x40,0x80,0x20);
  FUN_00655b20(*(undefined4 *)(param_1 + 0x4434),0,0x80,0x1a0,0x40,0xd0,0x20);
  FUN_00655690(*(undefined4 *)(param_1 + 0x4434),0,0xc0,0x100,0x40);
  (**(code **)(*DAT_006d8428 + 0x2c))(DAT_006d8428,0x3c23d70a,0);
  (**(code **)(*DAT_006d8428 + 0x3c))(DAT_006d8428,0x3951b717,0);
  FUN_00655b20(*(undefined4 *)(param_1 + 0x4434),0,0x140,0x120,0x40,0x90,0x20);
  FUN_00655690(*(undefined4 *)(param_1 + 0x4434),0,0x180,0x40,0x20);
  FUN_00642510();
  for (local_12c = 0; local_12c < 4; local_12c = local_12c + 1) {
    FUN_00642a00();
  }
  pvVar3 = operator_new(0x148);
  local_8 = 1;
  if (pvVar3 == (void *)0x0) {
    local_178 = 0;
  }
  else {
    local_178 = FUN_0065d6f0(DAT_006d1850);
  }
  local_8 = 0xffffffff;
  *(undefined4 *)(param_1 + 0xf78) = local_178;
  FUN_0065d7e0(&DAT_006a49d8,0x1e,0xff,0xff,0xff);
  CPane::SetBorders(*(CPane **)(param_1 + 0xf78),0x2a8,5,0,7);
  *(undefined4 *)(param_1 + 0x43d4) = 0;
  *(undefined4 *)(param_1 + 0x43c8) = 100;
  *(undefined4 *)(param_1 + 0x43c4) = 100;
  *(undefined4 *)(param_1 + 0x43cc) = 100;
  *(undefined4 *)(param_1 + 0x43d0) = 100;
  for (local_130 = 0; local_130 < 4; local_130 = local_130 + 1) {
    FUN_00632cd0();
  }
  pvVar3 = operator_new(0x20);
  *(void **)(param_1 + 19000) = pvVar3;
  _memset(*(void **)(param_1 + 19000),0,0x20);
  ExceptionList = local_10;
  return;
}

