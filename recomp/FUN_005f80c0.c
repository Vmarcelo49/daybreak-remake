// ============================================
// Address:  0x005f80c0
// Original: FUN_005f80c0
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __thiscall
FUN_005f80c0(int param_1,undefined4 param_2,undefined4 param_3,int param_4,char param_5)

{
  void *pvVar1;
  int iVar2;
  int *local_180;
  int *local_17c;
  int *local_178;
  int local_124;
  CHAR local_120 [268];
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e6bc;
  local_10 = ExceptionList;
  local_14 = DAT_006b77f4;
  ExceptionList = &local_10;
  *(undefined4 *)(param_1 + 0x2c) = param_3;
  *(undefined4 *)(param_1 + 0x30) = param_2;
  if (*(int *)(param_1 + 0x34) != 0) {
    if (*(int *)(param_1 + 0x34) != 0) {
      FID_conflict__vector_deleting_destructor_(3);
    }
    *(undefined4 *)(param_1 + 0x34) = 0;
  }
  if (*(int *)(param_1 + 0x38) != 0) {
    if (*(int *)(param_1 + 0x38) != 0) {
      FID_conflict__vector_deleting_destructor_(3);
    }
    *(undefined4 *)(param_1 + 0x38) = 0;
  }
  if (*(int *)(param_1 + 0x3c) != 0) {
    if (*(int *)(param_1 + 0x3c) != 0) {
      FUN_005f8e50(3);
    }
    *(undefined4 *)(param_1 + 0x3c) = 0;
  }
  iVar2 = (int)param_5;
  local_178 = operator_new(iVar2 * 0x1c + 4);
  local_8 = 0;
  if (local_178 == (int *)0x0) {
    local_178 = (int *)0x0;
  }
  else {
    *local_178 = iVar2;
    _eh_vector_constructor_iterator_(local_178 + 1,0x1c,iVar2,FUN_00423350,FUN_004232c0);
    local_178 = local_178 + 1;
  }
  local_8 = 0xffffffff;
  *(int **)(param_1 + 0x34) = local_178;
  iVar2 = (int)param_5;
  local_17c = operator_new(iVar2 * 0x38 + 4);
  local_8 = 1;
  if (local_17c == (int *)0x0) {
    local_17c = (int *)0x0;
  }
  else {
    *local_17c = iVar2;
    _eh_vector_constructor_iterator_(local_17c + 1,0x38,iVar2,FUN_004231c0,FUN_00423270);
    local_17c = local_17c + 1;
  }
  local_8 = 0xffffffff;
  *(int **)(param_1 + 0x38) = local_17c;
  iVar2 = (int)param_5;
  local_180 = operator_new(iVar2 * 0x9c + 4);
  local_8 = 2;
  if (local_180 == (int *)0x0) {
    local_180 = (int *)0x0;
  }
  else {
    *local_180 = iVar2;
    _eh_vector_constructor_iterator_
              (local_180 + 1,0x9c,iVar2,FUN_0064d7a0,CPropertySection::~CPropertySection);
    local_180 = local_180 + 1;
  }
  local_8 = 0xffffffff;
  *(int **)(param_1 + 0x3c) = local_180;
  pvVar1 = operator_new((int)param_5 << 2);
  *(void **)(param_1 + 0x40) = pvVar1;
  for (local_124 = 0; local_124 < param_5; local_124 = local_124 + 1) {
    *(undefined4 *)(*(int *)(param_1 + 0x40) + local_124 * 4) =
         *(undefined4 *)(param_4 + local_124 * 4);
    wsprintfA(local_120,"data/bullet/%03d/%03d.dat",param_2,*(int *)(param_4 + local_124 * 4) / 10);
    FUN_005f8510(local_124,local_120,local_124 * 0x9c + *(int *)(param_1 + 0x3c),
                 *(int *)(param_4 + local_124 * 4) % 10);
  }
  ExceptionList = local_10;
  return 1;
}

