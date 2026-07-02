// Function: FUN_006685d0
// Address:  0x006685d0
// Source:   batch_decompile (mass dump)
// Hash:     0663c73f5d9410bb


uint __thiscall FUN_006685d0(int param_1,int param_2,uint param_3)

{
  int iVar1;
  float10 fVar2;
  int local_28;
  uint local_8;
  
  local_8 = 0;
  do {
    if (param_3 <= local_8) {
      return param_3;
    }
    if (param_3 - local_8 < 0x1000) {
      local_28 = param_3 - local_8;
    }
    else {
      local_28 = 0x1000;
    }
    iVar1 = FUN_00679740(param_1 + 0x10,param_2 + local_8,local_28,0,2,1);
    fVar2 = (float10)FUN_00679610();
    if (iVar1 == 0) {
      if (*(double *)(param_1 + 0x12f0) == 0.0) {
        _memset((void *)(param_2 + local_8),0,param_3 - local_8);
        return local_8;
      }
      FUN_00679510(param_1 + 0x10,0);
    }
    else if ((0.0 < *(double *)(param_1 + 0x12f0)) &&
            (*(double *)(param_1 + 0x12f0) < (double)fVar2)) {
      FUN_00679510(param_1 + 0x10,
                   ((double)fVar2 - *(double *)(param_1 + 0x12f0)) + *(double *)(param_1 + 0x12e8));
    }
    local_8 = local_8 + iVar1;
  } while( true );
}

