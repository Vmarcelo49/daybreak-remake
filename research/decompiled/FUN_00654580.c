// Function: FUN_00654580
// Address:  0x00654580
// Source:   batch_decompile (mass dump)
// Hash:     04fa902750c25674


void __fastcall FUN_00654580(int param_1)

{
  char cVar1;
  
  cVar1 = FUN_006544f0();
  if (cVar1 == '\0') {
    FUN_006541f0(*(int *)(param_1 + 8) + -4,*(undefined4 *)(param_1 + 8));
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -4;
  }
  return;
}

