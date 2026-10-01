// Function: FUN_006951e0
// Address:  0x006951e0
// Source:   batch_decompile (mass dump)
// Hash:     b5551eb152c841c8


int FUN_006951e0(undefined4 param_1,undefined8 param_2)

{
  int iVar1;
  undefined4 local_c;
  
  iVar1 = FUN_00694af0();
  if (-1 < iVar1) {
    iVar1 = (**(code **)(*local_c + 0x20))(local_c,param_2);
    (**(code **)(*local_c + 8))(local_c);
  }
  return iVar1;
}

