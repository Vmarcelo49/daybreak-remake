// Function: FUN_00657330
// Address:  0x00657330
// Source:   batch_decompile (mass dump)
// Hash:     07eed6f885c7dab5


void __thiscall FUN_00657330(char *param_1,void *param_2)

{
  _memcpy(param_1,param_2,0x34);
  if ((int)(uint)DAT_006d1a28 <= (int)*param_1) {
    _memset(param_1,0,0x34);
    *param_1 = -2;
  }
  _memset(param_1 + 0x38,0,0x28);
  return;
}

