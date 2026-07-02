// Function: FUN_0064d940
// Address:  0x0064d940
// Source:   batch_decompile (mass dump)
// Hash:     2fccfcbbf30f9849


/* WARNING: Removing unreachable block (ram,0x0064dc34) */

undefined4 __thiscall FUN_0064d940(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int *local_58;
  int local_54;
  int local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined8 local_3c;
  undefined4 local_34;
  undefined4 local_28;
  int local_24;
  int local_20;
  int local_1c;
  void *local_18;
  uint local_14;
  undefined1 local_10 [8];
  int *local_8;
  
  FUN_00661e70(param_1);
  local_8 = (int *)0x0;
  FUN_00655600(param_2,&DAT_006d11a8,&DAT_006d12b0);
  cVar1 = FUN_00653540(param_2);
  if (cVar1 == '\0') {
    uVar3 = 0;
  }
  else {
    local_14 = FUN_00653a40();
    local_18 = operator_new(local_14);
    FUN_00653760(local_18,local_14);
    FUN_0065d670();
    iVar2 = D3DXLoadMeshHierarchyFromXInMemory
                      (local_18,local_14,0x220,DAT_006d16f8,local_10,0,param_1 + 8,&local_8);
    if (iVar2 < 0) {
      FUN_0065d6a0();
      _free(local_18);
      uVar3 = 0;
    }
    else {
      FUN_0065d6a0();
      _free(local_18);
      if (local_8 != (int *)0x0) {
        local_20 = (**(code **)(*local_8 + 0x14))(local_8);
        local_1c = (**(code **)(*local_8 + 0x10))(local_8);
        if (local_20 < local_1c) {
          local_20 = local_1c;
        }
        for (local_24 = 0; local_24 < 2; local_24 = local_24 + 1) {
          uVar3 = (**(code **)(*local_8 + 0x18))(local_8,param_1 + 0xc + local_24 * 4);
          uVar3 = (**(code **)(*local_8 + 0x10))(local_8,local_20,uVar3);
          uVar3 = (**(code **)(*local_8 + 0xc))(local_8,uVar3);
          iVar2 = (**(code **)(*local_8 + 0xa4))(local_8,uVar3);
          if (iVar2 < 0) {
            return 0;
          }
        }
        if (local_8 != (int *)0x0) {
          local_28 = (**(code **)(*local_8 + 8))(local_8);
          local_8 = (int *)0x0;
        }
        if (1 < local_1c) {
          local_4c = 0;
          local_48 = 0x3f800000;
          local_44 = 0x3f800000;
          local_3c = 0;
          local_34 = 0;
          for (local_50 = 0; local_50 < 2; local_50 = local_50 + 1) {
            for (local_54 = 1; local_54 < local_1c; local_54 = local_54 + 1) {
              local_58 = (int *)0x0;
              iVar2 = (**(code **)(**(int **)(param_1 + 0xc + local_50 * 4) + 0x2c))
                                (*(undefined4 *)(param_1 + 0xc + local_50 * 4),local_54,&local_58);
              if (iVar2 < 0) {
                return 0;
              }
              iVar2 = (**(code **)(**(int **)(param_1 + 0xc + local_50 * 4) + 0x40))
                                (*(undefined4 *)(param_1 + 0xc + local_50 * 4),local_54,local_58);
              if (iVar2 < 0) {
                return 0;
              }
              if (local_58 != (int *)0x0) {
                (**(code **)(*local_58 + 8))(local_58);
              }
              iVar2 = (**(code **)(**(int **)(param_1 + 0xc + local_50 * 4) + 0x5c))
                                (*(undefined4 *)(param_1 + 0xc + local_50 * 4),local_54,&local_4c);
              if (iVar2 < 0) {
                return 0;
              }
            }
          }
        }
        FUN_0064ddd0(&DAT_006a5618,*(undefined4 *)(param_1 + 8));
      }
      FUN_0064e2e0(*(undefined4 *)(param_1 + 8));
      uVar3 = 1;
    }
  }
  return uVar3;
}

