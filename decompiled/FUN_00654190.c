// Function: FUN_00654190
// Address:  0x00654190
// Source:   batch_decompile (mass dump)
// Hash:     1e376d2ebc5acdbc


void FUN_00654190(void)

{
  undefined1 local_54 [28];
  undefined1 local_38 [40];
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069ed38;
  pvStack_10 = ExceptionList;
  ExceptionList = &pvStack_10;
  basic_string<>("vector<T> too long");
  local_8 = 0;
  FID_conflict_length_error(local_54);
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_38,&DAT_006b1da0);
}

