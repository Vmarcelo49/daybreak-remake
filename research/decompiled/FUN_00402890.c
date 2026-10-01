// Function: FUN_00402890
// Address:  0x00402890
// Source:   batch_decompile (mass dump)
// Hash:     d14f189afafa406d


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 * __fastcall FUN_00402890(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined2 local_12e;
  undefined1 local_128 [4];
  int local_124;
  CHAR local_120 [268];
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069da3b;
  local_10 = ExceptionList;
  local_14 = DAT_006b77f4;
  ExceptionList = &local_10;
  FUN_00403a50();
  local_8 = 0;
  *param_1 = &PTR_FUN_006a13fc;
  _vector_constructor_iterator_(param_1 + 1,0xa0,2,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0x51,0xa0,4,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0xf1,4,3,FUN_00425ac0);
  for (local_124 = 0; local_124 < 3; local_124 = local_124 + 1) {
    wsprintfA(local_120,"data/config/%04d.bmp",local_124 + 1);
    puVar1 = (undefined4 *)FUN_006560c0(local_128,local_120);
    param_1[local_124 + 0xf1] = *puVar1;
  }
  FUN_00655af0(param_1[0xf1],0,0,800,600);
  FUN_00655af0(param_1[0xf2],0x100,0x1c0,0x20,0x20);
  FUN_00655690(param_1[0xf2],0,0,0xc0,0x20);
  FUN_00655690(param_1[0xf2],0xc0,0,0x60,0x20);
  FUN_00655690(param_1[0xf2],0x120,0,0x80,0x20);
  FUN_00655690(param_1[0xf3],0,0,0x200,0x30);
  param_1[0xf4] = 0;
  waveOutGetVolume((HWAVEOUT)0x0,param_1 + 0xfa);
  if ((param_1[0xfa] & 0xffff) < (uint)param_1[0xfa] >> 0x10) {
    local_12e = (undefined2)((uint)param_1[0xfa] >> 0x10);
  }
  else {
    local_12e = (undefined2)param_1[0xfa];
  }
  *(undefined2 *)(param_1 + 0xfb) = local_12e;
  *(undefined1 *)((int)param_1 + 0x3ee) = 0;
  ExceptionList = local_10;
  return param_1;
}

