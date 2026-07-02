// Function: FUN_0065afb0
// Address:  0x0065afb0
// Source:   batch_decompile (mass dump)
// Hash:     824f79c12386cad0


undefined4 __fastcall FUN_0065afb0(int param_1)

{
  void *_Dst;
  undefined2 local_18;
  undefined2 local_16;
  undefined4 local_14;
  undefined4 local_10;
  undefined2 local_c;
  undefined2 local_a;
  undefined2 local_8;
  
  _Dst = operator_new(0x180000);
  _memset(_Dst,0,0x180000);
  local_8 = 0;
  local_18 = 1;
  local_14 = 0xac44;
  local_a = 0x10;
  local_16 = 1;
  local_c = 2;
  local_10 = 0x15888;
  FUN_00667b00(_Dst,0x180000,&local_18);
  FUN_00667b00(_Dst,0x180000,&local_18);
  FUN_00654170(0);
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined1 *)(param_1 + 0x58) = 0;
  *(undefined4 *)(param_1 + 0x68) = 10000;
  *(undefined4 *)(param_1 + 0x6c) = 10000;
  _free(_Dst);
  return 1;
}

