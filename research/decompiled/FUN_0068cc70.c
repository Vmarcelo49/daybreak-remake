// Function: FUN_0068cc70
// Address:  0x0068cc70
// Source:   batch_decompile (mass dump)
// Hash:     ca508d77819a6483


undefined4 FUN_0068cc70(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f78e;
  local_10 = ExceptionList;
  if (param_1 == 0xc) {
    local_1c = 0;
  }
  else {
    local_1c = param_1 + 4;
  }
  ExceptionList = &local_10;
  FUN_0068d950(local_1c);
  local_8 = 0;
  iVar1 = *(int *)(param_1 + 0x2c);
  iVar2 = *(int *)(param_1 + 0x30);
  iVar3 = FUN_0068dc80();
  *param_2 = (iVar1 - iVar2) + iVar3;
  local_8 = 0xffffffff;
  FUN_0068d9a0();
  ExceptionList = local_10;
  return 0;
}

