// ============================================
// Address:  0x00695280
// Original: FUN_00695280
// Status:   unreviewed
// ============================================


int FUN_00695280(undefined4 param_1,undefined8 param_2)

{
  int iVar1;
  undefined4 local_c;
  
  iVar1 = FUN_00694af0();
  if (-1 < iVar1) {
    iVar1 = (**(code **)(*local_c + 0x2c))(local_c,param_2);
    (**(code **)(*local_c + 8))(local_c);
  }
  return iVar1;
}

