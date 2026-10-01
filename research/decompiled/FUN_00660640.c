// Function: FUN_00660640
// Address:  0x00660640
// Source:   batch_decompile (mass dump)
// Hash:     e5fd16d3f5ebde3b


undefined4 FUN_00660640(undefined4 *param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  int iVar2;
  undefined4 local_28 [6];
  undefined4 local_10;
  int local_c;
  int local_8;
  
  switch(param_3) {
  case 0xffff0007:
    local_10 = 0x18;
    local_28[0] = 0x18;
    iVar2 = (**(code **)(*(int *)*param_1 + 0x24))
                      (*param_1,*(undefined4 *)(param_4 + 4),local_28,&local_10,0);
    if (iVar2 == -0x7fea7be0) {
      param_1[2] = *(undefined4 *)(param_4 + 4);
    }
    else {
      param_1[**(int **)(param_4 + 8) + 2] = *(undefined4 *)(param_4 + 4);
    }
    break;
  case 0xffff0009:
    if (*(int *)(param_4 + 8) != 0) {
      FUN_00660310(**(undefined4 **)(param_4 + 8));
    }
    break;
  case 0xffff000e:
    FUN_0065d670();
    if (param_1[0x19] != 0) {
      for (local_8 = 1; local_8 < 8; local_8 = local_8 + 1) {
        if ((param_1[local_8 + 10] == -1) &&
           (cVar1 = (**(code **)(*(int *)param_1[0x19] + 0xc))(local_8), cVar1 != '\0')) {
          local_c = param_4;
          param_1[local_8 + 10] = local_8;
          param_1[local_8 + 0x1e] = 0;
          *(undefined4 **)(param_4 + 0x18) = param_1 + local_8 + 10;
          *(undefined4 **)(param_4 + 0xc) = param_1 + local_8 + 10;
          *(undefined4 *)(param_4 + 0x10) = 4;
          FUN_0065d6a0();
          return 0;
        }
      }
    }
    FUN_0065d6a0();
    return 0x80158230;
  case 0xffff0011:
    if (*(char *)(param_1 + 0x1a) == '\0') {
      return 0;
    }
    FUN_0065d670();
    iVar2 = **(int **)(param_4 + 8);
    if (param_1[0x19] != 0) {
      (**(code **)(*(int *)param_1[0x19] + 4))
                (iVar2,*(undefined4 *)(param_4 + 0xc),*(undefined4 *)(param_4 + 0x10));
    }
    param_1[iVar2 + 0x1e] = 0;
    FUN_0065d6a0();
  }
  return 0;
}

