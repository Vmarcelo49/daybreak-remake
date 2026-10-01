// Function: FUN_00659ae0
// Address:  0x00659ae0
// Source:   batch_decompile (mass dump)
// Hash:     b45554c181480bbc


int __fastcall FUN_00659ae0(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069ef09;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0065a460();
  local_8 = 0;
  FUN_0065a520();
  local_8._0_1_ = 1;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x60),0xc,0x20,FUN_006679a0,FUN_006679d0);
  local_8 = CONCAT31(local_8._1_3_,2);
  _eh_vector_constructor_iterator_
            ((void *)(param_1 + 0x1e0),0x10,0x20,FUN_006675d0,std::ctype<char>::~ctype<char>);
  ExceptionList = local_10;
  return param_1;
}

