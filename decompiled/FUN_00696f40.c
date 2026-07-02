// Function: FUN_00696f40
// Address:  0x00696f40
// Source:   batch_decompile (mass dump)
// Hash:     b2f8c3f943fc4469


int __fastcall FUN_00696f40(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int **ppiVar4;
  int *local_34;
  int local_30;
  undefined1 local_2c [4];
  undefined1 local_28 [32];
  int *local_8;
  
  if (*(int *)(param_1 + 0x10) == 0) {
    local_30 = -0x7ffbfdcc;
  }
  else {
    ppiVar4 = &local_8;
    uVar3 = 0;
    uVar2 = 0;
    uVar1 = FUN_004233c0(0,0,ppiVar4);
    local_30 = FUN_006942c0(param_1 + 0x48,uVar1,uVar2,uVar3,ppiVar4);
    if (-1 < local_30) {
      uVar1 = FUN_004233c0(&local_34);
      local_30 = (**(code **)**(undefined4 **)(param_1 + 0x14))
                           (*(undefined4 *)(param_1 + 0x14),uVar1);
      if (local_30 < 0) {
        (**(code **)(*local_8 + 8))(local_8);
      }
      else {
        uVar1 = FUN_00698180(local_28,local_2c);
        uVar1 = FUN_00698160(uVar1);
        uVar1 = FUN_00698140(uVar1);
        uVar1 = FUN_0063b630(uVar1);
        uVar1 = (**(code **)(*local_8 + 0x2c))(local_8,local_34,uVar1);
        *(undefined4 *)(param_1 + 0x4c) = uVar1;
        (**(code **)(*local_34 + 8))(local_34);
        (**(code **)(*local_8 + 8))(local_8);
        local_30 = (**(code **)(**(int **)(param_1 + 0x10) + 0xc))(param_1);
        *(undefined4 *)(param_1 + 0x10) = 0;
      }
    }
  }
  return local_30;
}

