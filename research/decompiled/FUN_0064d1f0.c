// Function: FUN_0064d1f0
// Address:  0x0064d1f0
// Source:   batch_decompile (mass dump)
// Hash:     4359c714083ba536


undefined4 * FUN_0064d1f0(undefined4 *param_1)

{
  char cVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined4 in_stack_00000018;
  undefined4 in_stack_0000001c;
  
  while( true ) {
    cVar1 = FUN_00433b00(&stack0x00000010);
    if (cVar1 == '\0') break;
    puVar2 = (undefined1 *)FUN_00425e50();
    puVar3 = (undefined1 *)FUN_00425e50();
    *puVar3 = *puVar2;
    iterator__operator__();
    iterator__operator__();
  }
  *param_1 = in_stack_00000018;
  param_1[1] = in_stack_0000001c;
  return param_1;
}

