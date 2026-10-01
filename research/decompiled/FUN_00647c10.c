// Function: FUN_00647c10
// Address:  0x00647c10
// Source:   batch_decompile (mass dump)
// Hash:     e59dc23336659232


int __fastcall FUN_00647c10(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e842;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00425ac0();
  FUN_00425ac0();
  FUN_00425ac0();
  FUN_00425ac0();
  FUN_00425ac0();
  _vector_constructor_iterator_((void *)(param_1 + 0x18),4,0x20,FUN_00425ac0);
  _vector_constructor_iterator_((void *)(param_1 + 0x98),4,0x100,FUN_00425ac0);
  FUN_00425ac0();
  FUN_00403a70();
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x63c),100,4,FUN_006572d0,FUN_00657320);
  local_8 = 0;
  FUN_0064c2c0();
  local_8._0_1_ = 1;
  FUN_0042e9a0();
  local_8._0_1_ = 2;
  FUN_0065aed0();
  local_8 = CONCAT31(local_8._1_3_,3);
  FUN_0064c270();
  FUN_006456c0();
  _memset((void *)(param_1 + 0x52c0),0,0x10);
  *(undefined4 *)(param_1 + 0x52d0) = 0;
  ExceptionList = local_10;
  return param_1;
}

