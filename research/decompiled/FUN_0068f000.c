// Function: FUN_0068f000
// Address:  0x0068f000
// Source:   batch_decompile (mass dump)
// Hash:     e26aa90f499af73a


int __fastcall FUN_0068f000(int *param_1)

{
  int iVar1;
  
  param_1[0x18] = 0;
  iVar1 = FUN_0068e770();
  if (iVar1 == 2) {
    iVar1 = (**(code **)(*param_1 + 0x7c))();
    if (iVar1 < 0) {
      return iVar1;
    }
    FUN_0068fde0(0);
  }
  else {
    FUN_0068fde0(1);
  }
  return 0;
}

