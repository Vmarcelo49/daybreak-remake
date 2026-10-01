// Function: FUN_004263e0
// Address:  0x004263e0
// Source:   batch_decompile (mass dump)
// Hash:     2cf3884d599f71a7


void __thiscall FUN_004263e0(int param_1,uint param_2)

{
  int iVar1;
  undefined1 local_54 [28];
  undefined1 local_38 [40];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e328;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar1 = FUN_00426e30();
  if ((uint)(iVar1 - *(int *)(param_1 + 8)) < param_2) {
    basic_string<>("list<T> too long");
    local_8 = 0;
    FID_conflict_length_error(local_54);
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(local_38,&DAT_006b1da0);
  }
  *(uint *)(param_1 + 8) = *(int *)(param_1 + 8) + param_2;
  ExceptionList = local_10;
  return;
}

