// ============================================
// Address:  0x00698090
// Original: FUN_00698090
// Status:   unreviewed
// ============================================


/* WARNING: Removing unreachable block (ram,0x00698115) */

undefined4 __thiscall FUN_00698090(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  longlong lVar1;
  longlong lVar2;
  undefined4 local_24;
  undefined1 local_c [8];
  
  if (*(int *)(param_1 + 0x60) == 0) {
    local_24 = 0;
  }
  else {
    if (param_4 != 0) {
      if (*(int *)(param_1 + 100) == 0) {
        return 0;
      }
      FUN_00697ee0(param_1 + 0x68);
    }
    FUN_0068d890();
    (**(code **)(**(int **)(param_1 + 0x60) + 0xc))(*(undefined4 *)(param_1 + 0x60),local_c);
    lVar1 = FUN_00697fc0();
    lVar2 = FUN_00697fc0();
    if (lVar2 < lVar1) {
      local_24 = 0;
    }
    else {
      local_24 = 1;
    }
  }
  return local_24;
}

