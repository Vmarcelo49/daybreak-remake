// Function: FUN_0068dca0
// Address:  0x0068dca0
// Source:   batch_decompile (mass dump)
// Hash:     63aac71f29915c5d


int __fastcall FUN_0068dca0(int *param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    piVar2 = (int *)FUN_0068dce0(*param_1);
    *param_1 = *piVar2;
    param_1[1] = param_1[1] + -1;
  }
  return iVar1;
}

