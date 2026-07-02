// Function: FUN_0066eaa1
// Address:  0x0066eaa1
// Source:   batch_decompile (mass dump)
// Hash:     8274cb21025cc598


int FUN_0066eaa1(FILE *param_1)

{
  int iVar1;
  
  iVar1 = __flush(param_1);
  if (iVar1 != 0) {
    return -1;
  }
  if ((param_1->_flag & 0x4000) != 0) {
    iVar1 = FUN_00674d58(param_1->_file);
    return -(uint)(iVar1 != 0);
  }
  return 0;
}

