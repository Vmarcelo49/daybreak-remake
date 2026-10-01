// Function: FUN_00421960
// Address:  0x00421960
// Source:   batch_decompile (mass dump)
// Hash:     1f5d90c235e17153


int __fastcall FUN_00421960(int param_1)

{
  *(undefined1 *)(param_1 + 0xaeca) = 1;
  return *(int *)(*(int *)(param_1 + 0x23c) + 0x43c4 + **(int **)(param_1 + 0xc) * 4) -
         *(int *)(*(int *)(param_1 + 0xc) + 4);
}

