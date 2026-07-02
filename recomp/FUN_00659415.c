// ============================================
// Address:  0x00659415
// Original: FUN_00659415
// Status:   unreviewed
// ============================================


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_00659415(void)

{
  int unaff_EBP;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  *(int *)(*(int *)(unaff_EBP + -0x7c) + 8) =
       *(int *)(unaff_EBP + 0xc) * 0x50 + *(int *)(*(int *)(unaff_EBP + -0x7c) + 8);
  FUN_00659750(*(undefined4 *)(unaff_EBP + 8),
               *(int *)(*(int *)(unaff_EBP + -0x7c) + 8) + *(int *)(unaff_EBP + 0xc) * -0x50,
               unaff_EBP + -0x68);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}

