// Function: FUN_0066baa6
// Address:  0x0066baa6
// Source:   batch_decompile (mass dump)
// Hash:     4eaba84592a8c464


exception * __thiscall FUN_0066baa6(exception *param_1,byte param_2)

{
  exception::~exception(param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

