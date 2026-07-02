// ============================================
// Address:  0x0068f170
// Original: FUN_0068f170
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_0068f170(int *param_1,int *param_2,uint *param_3,uint *param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = (**(code **)(*param_2 + 0x14))(param_2,param_3,param_4);
  if (iVar1 < 0) {
    uVar2 = 0;
  }
  else if (((int)param_3[1] < (int)param_4[1]) ||
          (((int)param_3[1] <= (int)param_4[1] && (*param_3 <= *param_4)))) {
    if (param_1[6] == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = (**(code **)(*param_1 + 0x5c))(param_2,param_3,param_4);
    }
  }
  else {
    uVar2 = 0x80040228;
  }
  return uVar2;
}

