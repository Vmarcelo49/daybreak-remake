// ============================================
// Address:  0x00433eb0
// Original: FUN_00433eb0
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __thiscall
FUN_00433eb0(uint *param_1,uint param_2,undefined4 param_3,uint param_4,uint param_5)

{
  uint uVar1;
  void *pvVar2;
  undefined4 uVar3;
  void *local_6c0;
  uint *local_6bc;
  int local_68c;
  int local_688;
  int local_680;
  int local_67c;
  CHAR local_678 [264];
  CHAR local_570 [271];
  undefined1 local_461;
  undefined1 local_460 [268];
  void *local_354;
  undefined1 local_350 [264];
  CHAR local_248 [264];
  char local_140 [268];
  undefined4 local_34;
  int local_30;
  undefined1 local_2c [4];
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e584;
  local_10 = ExceptionList;
  local_34 = DAT_006b77f4;
  ExceptionList = &local_10;
  param_1[8] = param_2;
  *(undefined1 *)(param_1 + 0x3f) = 0;
  local_461 = 1;
  wsprintfA(local_570,"data/item/%03d.dat",param_3);
  FUN_00653540(local_570);
  _vector_constructor_iterator_(&local_28,0xc,2,std::allocator<char>::allocator<char>);
  param_1[4] = param_4;
  param_1[5] = param_5;
  FUN_00653760(param_1,4);
  FUN_00653760(param_1 + 0x3e,4);
  FUN_00653760(local_350,0x1e);
  FUN_00653760(local_2c,4);
  FUN_00653760(local_2c,4);
  if (*param_1 != 0) {
    uVar1 = *param_1;
    local_6bc = operator_new(uVar1 * 0x970 + 4);
    local_8 = 0;
    if (local_6bc == (uint *)0x0) {
      local_6bc = (uint *)0x0;
    }
    else {
      *local_6bc = uVar1;
      _eh_vector_constructor_iterator_(local_6bc + 1,0x970,uVar1,FUN_0042fce0,FUN_0042fe20);
      local_6bc = local_6bc + 1;
    }
    local_8 = 0xffffffff;
    param_1[1] = (uint)local_6bc;
    uVar1 = *param_1;
    local_6c0 = operator_new(uVar1 * 0xc);
    local_8 = 1;
    if (local_6c0 == (void *)0x0) {
      local_6c0 = (void *)0x0;
    }
    else {
      _vector_constructor_iterator_(local_6c0,0xc,uVar1,std::allocator<char>::allocator<char>);
    }
    local_8 = 0xffffffff;
    param_1[2] = (uint)local_6c0;
    pvVar2 = operator_new(*param_1);
    param_1[3] = (uint)pvVar2;
  }
  _memset((void *)param_1[3],0,*param_1);
  for (local_680 = 0; local_680 < (int)*param_1; local_680 = local_680 + 1) {
    FUN_00653760(local_140,0x1e);
    FUN_00653760(local_460,0x1e);
    FUN_00653760(&local_67c,4);
    *(float *)(local_680 * 0xc + param_1[2]) = (float)local_67c;
    FUN_00653760(&local_67c,4);
    *(float *)(param_1[2] + 4 + local_680 * 0xc) = (float)local_67c;
    FUN_00653760(&local_67c,4);
    *(float *)(param_1[2] + 8 + local_680 * 0xc) = (float)local_67c;
    FUN_00653760(&local_67c,4);
    local_28 = (float)local_67c;
    FUN_00653760(&local_67c,4);
    local_24 = (float)local_67c;
    FUN_00653760(&local_67c,4);
    local_20 = (float)local_67c;
    FUN_00653760(&local_67c,4);
    local_1c = (float)local_67c;
    FUN_00653760(&local_67c,4);
    local_18 = (float)local_67c;
    FUN_00653760(&local_67c,4);
    local_14 = (float)local_67c;
    if (local_140[0] != '\0') {
      wsprintfA(local_248,"data/item/%s",local_140);
      wsprintfA(local_678,"data/item/%s",local_460);
      uVar3 = FUN_00653960(0,1);
      FUN_0042fe90(local_248,local_678,&local_28,&local_1c);
      FUN_00653540(local_570);
      FUN_00653960(uVar3,0);
      *(undefined1 *)(param_1[3] + local_680) = 1;
    }
  }
  for (local_688 = 0; local_688 < 2; local_688 = local_688 + 1) {
    wsprintfA(local_570,"Magazine%01d",local_688);
    FUN_00653760(param_1 + local_688 * 0x11 + 0xb,4);
    param_1[local_688 * 0x11 + 0xf] = param_1[local_688 * 0x11 + 0xb];
    FUN_00653760(param_1 + local_688 * 0x11 + 9,4);
    FUN_00653760(param_1 + local_688 * 0x11 + 0xc,4);
    FUN_00653760(param_1 + local_688 * 0x11 + 0xd,4);
    param_1[local_688 * 0x11 + 0x19] = param_1[local_688 * 0x11 + 0xd];
    FUN_00653760(param_1 + local_688 * 0x11 + 0x12,4);
    FUN_00653760(param_1 + local_688 * 0x11 + 0x14,4);
    uVar1 = param_1[local_688 * 0x11 + 9];
    if (uVar1 == 0) {
      param_1[local_688 * 0x11 + 0x16] = param_1[local_688 * 0x11 + 0xb];
      param_1[local_688 * 0x11 + 0x15] = param_1[local_688 * 0x11 + 0x16];
    }
    else if ((0 < (int)uVar1) && ((int)uVar1 < 3)) {
      param_1[local_688 * 0x11 + 0x16] =
           param_1[local_688 * 0x11 + 0xb] * param_1[local_688 * 0x11 + 0xc];
      param_1[local_688 * 0x11 + 0x15] = param_1[local_688 * 0x11 + 0x16];
    }
  }
  local_354 = operator_new(param_1[0x3e] << 2);
  pvVar2 = operator_new(param_1[0x3e] * 0xc);
  param_1[0x3d] = (uint)pvVar2;
  for (local_68c = 0; local_68c < (int)param_1[0x3e]; local_68c = local_68c + 1) {
    FUN_00653760(param_1[0x3d] + 8 + local_68c * 0xc,4);
    FUN_00653760(param_1[0x3d] + 4 + local_68c * 0xc,4);
    FUN_00653760(&local_67c,4);
    FUN_00653760(&local_30,4);
    *(int *)((int)local_354 + local_68c * 4) = local_67c * 10 + local_30;
  }
  FUN_005f80c0(param_3,param_1[8],local_354,
               CONCAT31((int3)((uint)local_68c >> 8),(char)param_1[0x3e]));
  _free(local_354);
  FUN_00434a70(0,0);
  FUN_00434a70(1,1);
  ExceptionList = local_10;
  return 1;
}

