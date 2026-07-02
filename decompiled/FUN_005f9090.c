// Function: FUN_005f9090
// Address:  0x005f9090
// Source:   batch_decompile (mass dump)
// Hash:     71f33cc3ebedec9d


undefined4 * __thiscall
FUN_005f9090(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 *param_8,
            undefined4 *param_9,undefined4 param_10)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e708;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0042f950();
  local_8 = 0;
  *param_1 = &PTR_FUN_006a4814;
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 0x4c));
  param_1[0x47] = param_2;
  param_1[0x54] = param_3;
  param_1[0x48] = param_4;
  param_1[1] = param_5;
  param_1[0x4a] = param_7;
  param_1[0x49] = param_6;
  param_1[5] = *param_8;
  param_1[6] = param_8[1];
  param_1[7] = param_8[2];
  param_1[0xf] = *param_9;
  param_1[0x10] = param_9[1];
  param_1[0x11] = param_9[2];
  param_1[0xe] = param_10;
  ExceptionList = local_10;
  return param_1;
}

