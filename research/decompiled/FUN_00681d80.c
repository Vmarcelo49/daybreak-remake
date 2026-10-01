// Function: FUN_00681d80
// Address:  0x00681d80
// Source:   batch_decompile (mass dump)
// Hash:     977445d01982abe2


void FUN_00681d80(int param_1,int *param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  
  if (*param_2 < 2) {
    FUN_0069d4c0(param_3,0,1);
  }
  else {
    FUN_0069d4c0(param_3,1,1);
    FUN_0069d4c0(param_3,*param_2 + -1,4);
  }
  if (param_2[0x121] < 1) {
    FUN_0069d4c0(param_3,0,1);
  }
  else {
    FUN_0069d4c0(param_3,1,1);
    FUN_0069d4c0(param_3,param_2[0x121] + -1,8);
    iVar3 = 0;
    if (0 < param_2[0x121]) {
      piVar2 = param_2 + 0x222;
      do {
        uVar1 = FUN_00681ed0(*(undefined4 *)(param_1 + 4));
        FUN_0069d4c0(param_3,piVar2[-0x100],uVar1);
        uVar1 = FUN_00681ed0(*(undefined4 *)(param_1 + 4));
        FUN_0069d4c0(param_3,*piVar2,uVar1);
        iVar3 = iVar3 + 1;
        piVar2 = piVar2 + 1;
      } while (iVar3 < param_2[0x121]);
    }
  }
  FUN_0069d4c0(param_3,0,2);
  if ((1 < *param_2) && (iVar3 = 0, piVar2 = param_2, 0 < *(int *)(param_1 + 4))) {
    do {
      FUN_0069d4c0(param_3,piVar2[1],4);
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar3 < *(int *)(param_1 + 4));
  }
  iVar3 = 0;
  if (0 < *param_2) {
    piVar2 = param_2 + 0x111;
    do {
      FUN_0069d4c0(param_3,0,8);
      FUN_0069d4c0(param_3,piVar2[-0x10],8);
      FUN_0069d4c0(param_3,*piVar2,8);
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar3 < *param_2);
  }
  return;
}

