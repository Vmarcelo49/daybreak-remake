// ============================================
// Address:  0x005f7ad0
// Original: FUN_005f7ad0
// Status:   unreviewed
// ============================================


void FUN_005f7ad0(void)

{
  undefined1 local_54 [28];
  undefined1 local_38 [40];
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e668;
  pvStack_10 = ExceptionList;
  ExceptionList = &pvStack_10;
  basic_string<>("invalid vector<T> subscript");
  local_8 = 0;
  FID_conflict_length_error(local_54);
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_38,&DAT_006b2d40);
}

