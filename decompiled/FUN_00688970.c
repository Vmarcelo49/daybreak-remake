// Function: FUN_00688970
// Address:  0x00688970
// Source:   batch_decompile (mass dump)
// Hash:     9e20fea47bc8ffdc


uint FUN_00688970(int param_1,uint param_2,int *param_3,uint *param_4)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int local_1c;
  uint local_14;
  uint local_c;
  uint local_8;
  
  if (param_3 == (int *)0x0) {
    uVar2 = 0x80004003;
  }
  else {
    if (param_4 == (uint *)0x0) {
      if (1 < param_2) {
        return 0x80070057;
      }
    }
    else {
      *param_4 = 0;
    }
    local_8 = 0;
    iVar3 = FUN_0068dae0();
    if (iVar3 == 1) {
      FUN_00688b90(param_1);
    }
    if (*(int *)(param_1 + 8) - *(int *)(param_1 + 4) < (int)param_2) {
      local_14 = *(int *)(param_1 + 8) - *(int *)(param_1 + 4);
    }
    else {
      local_14 = param_2;
    }
    local_c = local_14;
    if (local_14 == 0) {
      uVar2 = 1;
    }
    else {
      while ((local_c != 0 && (*(int *)(param_1 + 8) != *(int *)(param_1 + 4)))) {
        uVar1 = *(undefined4 *)(param_1 + 4);
        *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
        iVar3 = (**(code **)(**(int **)(param_1 + 0xc) + 0x1c))(uVar1);
        if (iVar3 == 0) {
          return 0x80040203;
        }
        iVar4 = FUN_0068ddc0(iVar3);
        if (iVar4 == 0) {
          if (iVar3 == 0) {
            local_1c = 0;
          }
          else {
            local_1c = iVar3 + 0xc;
          }
          *param_3 = local_1c;
          (**(code **)(*(int *)(iVar3 + 0xc) + 4))(iVar3 + 0xc);
          local_8 = local_8 + 1;
          param_3 = param_3 + 1;
          FUN_00698250(iVar3);
          local_c = local_c - 1;
        }
      }
      if (param_4 != (uint *)0x0) {
        *param_4 = local_8;
      }
      uVar2 = (uint)(param_2 != local_8);
    }
  }
  return uVar2;
}

