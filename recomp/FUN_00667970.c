// ============================================
// Address:  0x00667970
// Original: FUN_00667970
// Status:   unreviewed
// ============================================


ctype<char> * __thiscall FUN_00667970(ctype<char> *param_1,uint param_2)

{
  std::ctype<char>::~ctype<char>(param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

