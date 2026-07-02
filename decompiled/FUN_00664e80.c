// Function: FUN_00664e80
// Address:  0x00664e80
// Source:   batch_decompile (mass dump)
// Hash:     af2ce314416fcb0e


undefined4 FUN_00664e80(undefined4 param_1)

{
  undefined4 *puVar1;
  char *pcVar2;
  
  while( true ) {
    puVar1 = (undefined4 *)FUN_00663590(param_1);
    pcVar2 = (char *)FUN_00663560(*puVar1);
    if (*pcVar2 != '\0') break;
    puVar1 = (undefined4 *)FUN_00663590(param_1);
    param_1 = *puVar1;
  }
  return param_1;
}

