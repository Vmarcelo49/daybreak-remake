// ============================================
// Address:  0x004115f0
// Original: FUN_004115f0
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 * __fastcall FUN_004115f0(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined1 local_138 [4];
  undefined1 local_134 [4];
  undefined1 local_130 [4];
  undefined1 local_12c [4];
  undefined1 local_128 [4];
  int local_124;
  CHAR local_120 [268];
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069dd6b;
  local_10 = ExceptionList;
  local_14 = DAT_006b77f4;
  ExceptionList = &local_10;
  FUN_00403a50();
  local_8 = 0;
  *param_1 = &PTR_FUN_006a1c68;
  _vector_constructor_iterator_(param_1 + 1,0xa0,2,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0x51,0xa0,2,FUN_00403a70);
  _vector_constructor_iterator_(param_1 + 0xa1,0xa0,4,FUN_00403a70);
  FUN_00403a70();
  _vector_constructor_iterator_(param_1 + 0x169,4,4,FUN_00425ac0);
  _vector_constructor_iterator_(param_1 + 0x16d,4,4,FUN_00425ac0);
  puVar1 = (undefined4 *)FUN_006560c0(local_128,"data/vs/vs01.bmp");
  param_1[0x169] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_12c,"data/vs/vs02.bmp");
  param_1[0x16a] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_130,"data/vs/vs03.bmp");
  param_1[0x16b] = *puVar1;
  puVar1 = (undefined4 *)FUN_006560c0(local_134,"data/select/p03.bmp");
  param_1[0x16c] = *puVar1;
  for (local_124 = 0; local_124 < 4; local_124 = local_124 + 1) {
    wsprintfA(local_120,"data/select/%02d.bmp",(&DAT_006cfb28)[local_124]);
    puVar1 = (undefined4 *)FUN_006560c0(local_138,local_120);
    param_1[local_124 + 0x16d] = *puVar1;
    FUN_00655b20(param_1[local_124 + 0x16d],0,0,0x100,0x100,0x80,0x100);
    if (local_124 < 2) {
      FUN_0040da60(0xbf800000,0x3f800000);
    }
  }
  FUN_00655af0(param_1[0x169],0,0,0x100,0x100);
  FUN_00655af0(param_1[0x16a],0,0,0x100,0x100);
  FUN_00655b20(param_1[0x16b],0,0,0x100,0x100,0x80,0x80);
  FUN_006556c0(param_1[0x16c],0,0,0x100,0x40,0x80,0x20);
  param_1[0x171] = 0;
  param_1[0x174] = 0x44960000;
  param_1[0x175] = 0x44480000;
  param_1[0x176] = 0x44480000;
  param_1[0x177] = 0x44960000;
  param_1[0x178] = 0x40a00000;
  *(undefined1 *)(param_1 + 0x173) = 0;
  *(undefined1 *)((int)param_1 + 0x5cd) = 1;
  (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,7,0);
  (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x16,1);
  ExceptionList = local_10;
  return param_1;
}

