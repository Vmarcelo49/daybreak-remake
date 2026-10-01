// Function: FUN_00686b70
// Address:  0x00686b70
// Source:   batch_decompile (mass dump)
// Hash:     2f3fc5d95127b6cf


bool __thiscall FUN_00686b70(int param_1,void *param_2,size_t param_3)

{
  int iVar1;
  
  iVar1 = FUN_00686c20(param_3);
  if (iVar1 != 0) {
    _memcpy(*(void **)(param_1 + 0x44),param_2,param_3);
  }
  return iVar1 != 0;
}

