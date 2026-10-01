// Function: FUN_00669a80
// Address:  0x00669a80
// Source:   batch_decompile (mass dump)
// Hash:     3ed5cbf271a38663


void __fastcall FUN_00669a80(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_006ab36c;
  if (param_1[4] != 0) {
    _free((void *)param_1[4]);
    param_1[4] = 0;
  }
  return;
}

