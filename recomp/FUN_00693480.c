// ============================================
// Address:  0x00693480
// Original: FUN_00693480
// Status:   unreviewed
// ============================================


undefined4 FUN_00693480(undefined4 param_1,uint param_2,undefined4 param_3)

{
  undefined4 local_8;
  
  if (param_2 < 0x80000000) {
    local_8 = FUN_006934d0(param_1,param_2,param_3,&stack0x00000010);
  }
  else {
    local_8 = 0x80070057;
  }
  return local_8;
}

