// Function: FUN_00659956
// Address:  0x00659956
// Source:   batch_decompile (mass dump)
// Hash:     2393e9bf849ecf84


void FUN_00659956(void)

{
  int unaff_EBP;
  
  if (*(int *)(unaff_EBP + -0x14) != *(int *)(unaff_EBP + 8)) {
    std::allocator<std::_Container_proxy>::destroy
              (*(allocator<std::_Container_proxy> **)(unaff_EBP + 0x14),
               *(_Container_proxy **)(unaff_EBP + -0x14));
    FUN_0065994d();
    return;
  }
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(0,0);
}

