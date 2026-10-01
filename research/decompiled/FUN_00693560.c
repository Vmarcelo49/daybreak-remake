// Function: FUN_00693560
// Address:  0x00693560
// Source:   batch_decompile (mass dump)
// Hash:     109250f1f38e4392


undefined4 * __thiscall FUN_00693560(undefined4 *param_1,undefined4 param_2,HKEY__ *param_3)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  ATL::CRegKey::CRegKey((CRegKey *)(param_1 + 3),param_3);
  return param_1;
}

