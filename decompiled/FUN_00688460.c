// Function: FUN_00688460
// Address:  0x00688460
// Source:   batch_decompile (mass dump)
// Hash:     7ec8e0c444cc14a7


undefined4 __thiscall FUN_00688460(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int *local_8;
  
  if (*(int *)(param_1 + 0x40) == 0) {
    uVar2 = 0x80004002;
  }
  else {
    iVar1 = (**(code **)**(undefined4 **)(param_1 + 0x40))
                      (*(undefined4 *)(param_1 + 0x40),&DAT_006acf94,&local_8);
    if (iVar1 < 0) {
      uVar2 = (**(code **)(**(int **)(param_1 + 0x40) + 0x20))
                        (*(undefined4 *)(param_1 + 0x40),param_2);
    }
    else {
      uVar2 = (**(code **)(*local_8 + 0x4c))(local_8,param_2,param_3);
      (**(code **)(*local_8 + 8))(local_8);
    }
  }
  return uVar2;
}

