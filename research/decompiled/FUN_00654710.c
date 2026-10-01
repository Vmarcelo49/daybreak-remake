// Function: FUN_00654710
// Address:  0x00654710
// Source:   batch_decompile (mass dump)
// Hash:     9da2e4c179b6c78b


void FUN_00654710(void)

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
  basic_string<>("invalid vector<T> subscript");
  local_8 = 0;
  FID_conflict_length_error(local_54);
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_38,&DAT_006b2d40);
}

