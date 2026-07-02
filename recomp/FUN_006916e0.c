// ============================================
// Address:  0x006916e0
// Original: FUN_006916e0
// Status:   unreviewed
// ============================================


undefined4 __thiscall
FUN_006916e0(int param_1,int param_2,undefined4 *param_3,uint param_4,int param_5,undefined4 param_6
            ,undefined4 param_7)

{
  undefined4 uVar1;
  undefined8 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069faac;
  local_10 = ExceptionList;
  if (param_3 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    ExceptionList = &local_10;
    FUN_0068d950(param_1 + 0x7c);
    local_8 = 0;
    if (*(int *)(param_1 + 0x18) == 0) {
      *param_3 = 0;
      local_8 = 0xffffffff;
      FUN_0068d9a0();
      uVar1 = 0;
    }
    else {
      if (param_2 < 2) {
        *param_3 = 0;
      }
      else {
        uVar2 = FUN_006926a0(param_6,param_7,param_6,param_7,param_2,param_2 >> 0x1f,0,0);
        uVar1 = __alldiv(param_4 - (uint)uVar2,
                         (param_5 - (int)((ulonglong)uVar2 >> 0x20)) - (uint)(param_4 < (uint)uVar2)
                         ,param_2 + -1,param_2 + -1 >> 0x1f);
        uVar1 = FUN_00691640(uVar1);
        *param_3 = uVar1;
      }
      local_8 = 0xffffffff;
      FUN_0068d9a0();
      uVar1 = 0;
    }
  }
  ExceptionList = local_10;
  return uVar1;
}

