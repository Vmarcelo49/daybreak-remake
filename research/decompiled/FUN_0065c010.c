// Function: FUN_0065c010
// Address:  0x0065c010
// Source:   batch_decompile (mass dump)
// Hash:     f07e6778403074a0


bool __thiscall FUN_0065c010(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 local_8 [4];
  
  puVar2 = (undefined4 *)FUN_006532f0(local_8,param_2);
  *param_1 = *puVar2;
  cVar1 = FUN_0064d6e0();
  return cVar1 == '\0';
}

