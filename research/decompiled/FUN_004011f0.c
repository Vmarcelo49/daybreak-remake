// Function: FUN_004011f0
// Address:  0x004011f0
// Source:   batch_decompile (mass dump)
// Hash:     43856b8e7f370eb0


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __thiscall FUN_004011f0(int *param_1,char *param_2)

{
  char cVar1;
  void *pvVar2;
  int iVar3;
  undefined4 uVar4;
  int local_1bc;
  int local_1b4;
  int local_1ac;
  int local_19c;
  int local_140;
  int local_13c;
  int local_138;
  uint local_134;
  CHAR local_130 [264];
  undefined4 local_28;
  uint local_24;
  uint local_20;
  int local_1c;
  int local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069d8f8;
  local_10 = ExceptionList;
  local_28 = DAT_006b77f4;
  ExceptionList = &local_10;
  wsprintfA(local_130,"%s/env.dat",param_2);
  FUN_00653540(local_130);
  FUN_00653760(&local_1c,4);
  FUN_00653760(&local_18,4);
  FUN_00653760(&local_134,4);
  FUN_00653760(&local_24,4);
  FUN_00653760(&local_20,4);
  local_14 = (local_134 & 0xff) << 0x10 | (local_24 & 0xff) << 8 | local_20 & 0xff;
  FUN_00650a30((float)local_1c,(float)local_18,local_14);
  FUN_00653760(&local_138,4);
  param_1[0xd] = local_138;
  FUN_00653760(&local_138,4);
  param_1[0xe] = local_138;
  FUN_00653760(&local_138,4);
  param_1[0xf] = local_138;
  FUN_00653760(&local_138,4);
  param_1[0x10] = local_138;
  for (local_13c = 0; local_13c < 4; local_13c = local_13c + 1) {
    FUN_00653760(&local_138,4);
    param_1[local_13c * 3 + 0x11] = (int)(float)local_138;
    FUN_00653760(&local_138,4);
    param_1[local_13c * 3 + 0x12] = (int)(float)local_138;
    FUN_00653760(&local_138,4);
    param_1[local_13c * 3 + 0x13] = (int)(float)local_138;
  }
  for (local_140 = 0; local_140 < 8; local_140 = local_140 + 1) {
    if (param_1[local_140] != 0) {
      if (param_1[local_140] != 0) {
        FUN_00402010(1);
      }
      param_1[local_140] = 0;
    }
    pvVar2 = operator_new(0x9c);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_19c = 0;
    }
    else {
      local_19c = FUN_0064d7a0();
    }
    local_8 = 0xffffffff;
    param_1[local_140] = local_19c;
    if ((char)param_1[0xb] == '\0') {
      wsprintfA(local_130,"%s/%02db.x",param_2,local_140);
    }
    else {
      wsprintfA(local_130,"%s/%02d.x",param_2,local_140);
    }
    if ((local_140 == 0) && (iVar3 = __stricmp(param_2,"data/stage15"), iVar3 == 0)) {
      cVar1 = FUN_0064d940(local_130);
      if ((cVar1 == '\0') && (*param_1 != 0)) {
        if (*param_1 != 0) {
          FUN_00402010(1);
        }
        *param_1 = 0;
      }
    }
    else {
      cVar1 = FUN_0064d940(local_130);
      if ((cVar1 == '\0') && (param_1[local_140] != 0)) {
        if (param_1[local_140] != 0) {
          FUN_00402010(1);
        }
        param_1[local_140] = 0;
      }
    }
  }
  if (param_1[8] != 0) {
    if (param_1[8] != 0) {
      FUN_00402010(1);
    }
    param_1[8] = 0;
  }
  pvVar2 = operator_new(0x9c);
  local_8 = 1;
  if (pvVar2 == (void *)0x0) {
    local_1ac = 0;
  }
  else {
    local_1ac = FUN_0064d7a0();
  }
  local_8 = 0xffffffff;
  param_1[8] = local_1ac;
  wsprintfA(local_130,"%s/collision.x",param_2);
  cVar1 = FUN_0064d940(local_130);
  if (cVar1 == '\0') {
    MessageBoxA((HWND)0x0,&DAT_006a1350,"",0);
    uVar4 = 0;
  }
  else {
    if (param_1[9] != 0) {
      if (param_1[9] != 0) {
        FUN_00402010(1);
      }
      param_1[9] = 0;
    }
    pvVar2 = operator_new(0x9c);
    local_8 = 2;
    if (pvVar2 == (void *)0x0) {
      local_1b4 = 0;
    }
    else {
      local_1b4 = FUN_0064d7a0();
    }
    local_8 = 0xffffffff;
    param_1[9] = local_1b4;
    wsprintfA(local_130,"%s/collision_camera.x",param_2);
    cVar1 = FUN_0064d940(local_130);
    if (cVar1 == '\0') {
      MessageBoxA((HWND)0x0,&DAT_006a1388,"",0);
      uVar4 = 0;
    }
    else {
      if (param_1[10] != 0) {
        if (param_1[10] != 0) {
          FUN_00402010(1);
        }
        param_1[10] = 0;
      }
      pvVar2 = operator_new(0x9c);
      local_8 = 3;
      if (pvVar2 == (void *)0x0) {
        local_1bc = 0;
      }
      else {
        local_1bc = FUN_0064d7a0();
      }
      local_8 = 0xffffffff;
      param_1[10] = local_1bc;
      wsprintfA(local_130,"%s/collision_tama.x",param_2);
      cVar1 = FUN_0064d940(local_130);
      if (cVar1 == '\0') {
        MessageBoxA((HWND)0x0,&DAT_006a13c0,"",0);
        uVar4 = 0;
      }
      else {
        uVar4 = 1;
      }
    }
  }
  ExceptionList = local_10;
  return uVar4;
}

