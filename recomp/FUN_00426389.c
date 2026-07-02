// ============================================
// Address:  0x00426389
// Original: FUN_00426389
// Status:   unreviewed
// ============================================


void FUN_00426389(void)

{
  undefined4 *puVar1;
  int unaff_EBP;
  
  *(int *)(unaff_EBP + 0xc) = *(int *)(unaff_EBP + 0xc) + 1;
  if (*(uint *)(unaff_EBP + 0xc) < *(uint *)(unaff_EBP + -0x14)) {
    *(undefined4 *)(unaff_EBP + -0x18) = *(undefined4 *)(unaff_EBP + 8);
    puVar1 = (undefined4 *)FUN_00435f10();
    FUN_00425500(unaff_EBP + -0x1c,*puVar1);
    FUN_00426389();
    return;
  }
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(0,0);
}

