// ============================================
// Address:  0x0064f6c0
// Original: FUN_0064f6c0
// Status:   unreviewed
// ============================================


void FUN_0064f6c0(void)

{
  undefined1 local_54 [28];
  undefined1 local_38 [40];
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069ec08;
  pvStack_10 = ExceptionList;
  ExceptionList = &pvStack_10;
  basic_string<>("vector<T> too long");
  local_8 = 0;
  FID_conflict_length_error(local_54);
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_38,&DAT_006b1da0);
}

