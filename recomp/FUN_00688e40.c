// ============================================
// Address:  0x00688e40
// Original: FUN_00688e40
// Status:   unreviewed
// ============================================


uint FUN_00688e40(int param_1,uint param_2,int *param_3,int *param_4)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  LPVOID pvVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 local_ac [18];
  int local_64;
  undefined4 local_60 [15];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f54f;
  local_10 = ExceptionList;
  if (param_3 == (int *)0x0) {
    uVar2 = 0x80004003;
  }
  else {
    ExceptionList = &local_10;
    iVar3 = FUN_0068db10();
    if (iVar3 == 1) {
      uVar2 = 0x80040203;
    }
    else {
      if (param_4 == (int *)0x0) {
        if (1 < param_2) {
          ExceptionList = local_10;
          return 0x80070057;
        }
      }
      else {
        *param_4 = 0;
      }
      local_14 = 0;
      while (param_2 != 0) {
        FUN_00686800();
        local_8 = 0;
        uVar1 = *(undefined4 *)(param_1 + 4);
        *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
        local_64 = (**(code **)(**(int **)(param_1 + 8) + 0x34))(uVar1,local_60);
        if (local_64 != 0) {
          local_8 = 0xffffffff;
          FUN_006867e0();
          break;
        }
        pvVar4 = CoTaskMemAlloc(0x48);
        *param_3 = (int)pvVar4;
        if (*param_3 == 0) {
          local_8 = 0xffffffff;
          FUN_006867e0();
          break;
        }
        puVar5 = local_60;
        puVar6 = local_ac;
        for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar6 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar6 = puVar6 + 1;
        }
        puVar5 = local_ac;
        puVar6 = (undefined4 *)*param_3;
        for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar6 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar6 = puVar6 + 1;
        }
        local_1c = 0;
        local_20 = 0;
        local_24 = 0;
        param_3 = param_3 + 1;
        local_14 = local_14 + 1;
        param_2 = param_2 - 1;
        local_8 = 0xffffffff;
        FUN_006867e0();
      }
      if (param_4 != (int *)0x0) {
        *param_4 = local_14;
      }
      uVar2 = (uint)(param_2 != 0);
    }
  }
  ExceptionList = local_10;
  return uVar2;
}

