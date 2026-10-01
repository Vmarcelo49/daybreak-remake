// Function: FUN_006995a0
// Address:  0x006995a0
// Source:   batch_decompile (mass dump)
// Hash:     7e926b6413af97bc


int __thiscall
FUN_006995a0(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4,
            undefined4 *param_5)

{
  int iVar1;
  void *_Memory;
  undefined4 uVar2;
  longlong lVar3;
  longlong lVar4;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_006a005b;
  local_10 = ExceptionList;
  if (param_3 == (undefined4 *)0x0) {
    iVar1 = -0x7fffbffd;
  }
  else if (param_4 == (undefined4 *)0x0) {
    iVar1 = -0x7fffbffd;
  }
  else if (param_5 == (undefined4 *)0x0) {
    iVar1 = -0x7fffbffd;
  }
  else {
    ExceptionList = &local_10;
    *param_3 = 0;
    while (iVar1 = FUN_00693320(param_2), iVar1 != 0) {
      _Memory = (void *)FUN_00699b60();
      if (_Memory != (void *)0x0) {
        local_18 = FUN_0063b630();
        if (local_18 == 1) {
          iVar1 = FUN_0068dac0();
          lVar3 = FUN_00699f60();
          lVar4 = FUN_00699f80();
          if (lVar3 + iVar1 == lVar4) {
            local_18 = 0;
          }
          else {
            local_18 = -0x7fffbffb;
          }
        }
        uVar2 = FUN_0068dac0();
        *param_5 = uVar2;
        uVar2 = FUN_00699f40();
        *param_3 = uVar2;
        uVar2 = FUN_004233c0();
        *param_4 = uVar2;
        _free(_Memory);
        ExceptionList = local_10;
        return local_18;
      }
      FUN_0068d950(param_1 + 0x1c);
      if ((*(int *)(param_1 + 0x34) != 0) && (*(int *)(param_1 + 0x74) == 0)) {
        local_8 = 0xffffffff;
        FUN_0068d9a0();
        ExceptionList = local_10;
        return -0x7ffbfdd9;
      }
      local_8 = 0xffffffff;
      FUN_0068d9a0();
    }
    iVar1 = -0x7ffbfdd2;
  }
  ExceptionList = local_10;
  return iVar1;
}

