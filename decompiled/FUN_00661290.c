// Function: FUN_00661290
// Address:  0x00661290
// Source:   batch_decompile (mass dump)
// Hash:     63ef90d9b685fc02


void __fastcall FUN_00661290(int param_1)

{
  if ((*(char *)(param_1 + 0xa0d) == '\0') && (*(char *)(param_1 + 0xa0e) == '\0')) {
    FUN_0066b860(param_1 + 0x408,param_1 + 8);
    _memset((void *)(param_1 + 8),0,0x400);
    _memset((void *)(param_1 + 0x808),0,0x100);
    *(undefined4 *)(param_1 + 0xa10) = 0;
    *(undefined1 *)(param_1 + 0xa0c) = 1;
  }
  return;
}

