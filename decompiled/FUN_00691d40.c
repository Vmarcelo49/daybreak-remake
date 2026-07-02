// Function: FUN_00691d40
// Address:  0x00691d40
// Source:   batch_decompile (mass dump)
// Hash:     f91e115ba039c9e3


undefined4 * __thiscall FUN_00691d40(undefined4 *param_1,BOOL param_2)

{
  HANDLE pvVar1;
  
  pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,param_2,0,(LPCSTR)0x0);
  *param_1 = pvVar1;
  return param_1;
}

