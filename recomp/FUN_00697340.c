// ============================================
// Address:  0x00697340
// Original: FUN_00697340
// Status:   unreviewed
// ============================================


/* WARNING: Removing unreachable block (ram,0x00697402) */

undefined4 __thiscall FUN_00697340(int param_1,int param_2)

{
  int iVar1;
  longlong lVar2;
  longlong lVar3;
  undefined1 *puVar4;
  undefined1 local_30 [8];
  undefined1 local_28 [12];
  int local_1c;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069fe05;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068d950(param_1 + 8);
  local_8 = 0;
  (**(code **)(*(int *)(param_2 + 0xc) + 4))(param_2 + 0xc);
  iVar1 = FUN_00698070();
  if (iVar1 == 0) {
    local_18 = param_1 + 0x20;
  }
  else {
    local_18 = param_1 + 0x38;
  }
  local_1c = FUN_0068de10();
  while (local_1c != 0) {
    puVar4 = local_28;
    FUN_006981f0(local_1c);
    FUN_006981a0(puVar4);
    lVar2 = FUN_00697fc0();
    FUN_006981a0(local_30);
    lVar3 = FUN_00697fc0();
    if (lVar3 < lVar2) break;
    FUN_006981d0(&local_1c);
  }
  if (local_1c == 0) {
    FUN_00698250(param_2);
  }
  else {
    FUN_00698230(local_1c,param_2);
  }
  FUN_00697630();
  local_8 = 0xffffffff;
  FUN_0068d9a0();
  ExceptionList = local_10;
  return 0;
}

