// Function: FUN_00410d20
// Address:  0x00410d20
// Source:   batch_decompile (mass dump)
// Hash:     5be35e76a7869f33


void * FUN_00410d20(void *param_1,int param_2,void *param_3)

{
  int iVar1;
  void *pvVar2;
  
  iVar1 = param_2 - (int)param_1 >> 2;
  pvVar2 = _memmove(param_3,param_1,iVar1 << 2);
  return (void *)((int)pvVar2 + iVar1 * 4);
}

