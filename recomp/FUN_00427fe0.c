// ============================================
// Address:  0x00427fe0
// Original: FUN_00427fe0
// Status:   unreviewed
// ============================================


undefined4 * FUN_00427fe0(undefined4 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 in_stack_00000018;
  undefined4 in_stack_0000001c;
  
  while( true ) {
    cVar1 = FUN_00433b00(&stack0x00000010);
    if (cVar1 == '\0') break;
    FUN_004280c0();
    uVar2 = FUN_004250c0();
    FUN_004280c0(uVar2);
    FUN_004250c0();
    FUN_00427f40(uVar2);
  }
  *param_1 = in_stack_00000018;
  param_1[1] = in_stack_0000001c;
  return param_1;
}

