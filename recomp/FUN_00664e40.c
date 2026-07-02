// ============================================
// Address:  0x00664e40
// Original: FUN_00664e40
// Status:   unreviewed
// ============================================


undefined4 FUN_00664e40(undefined4 param_1)

{
  undefined4 *puVar1;
  char *pcVar2;
  
  while( true ) {
    puVar1 = (undefined4 *)FUN_00654020(param_1);
    pcVar2 = (char *)FUN_00663560(*puVar1);
    if (*pcVar2 != '\0') break;
    puVar1 = (undefined4 *)FUN_00654020(param_1);
    param_1 = *puVar1;
  }
  return param_1;
}

