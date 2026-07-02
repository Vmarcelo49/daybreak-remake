// Function: FUN_006925d0
// Address:  0x006925d0
// Source:   batch_decompile (mass dump)
// Hash:     b897644949ea7301


int FUN_006925d0(int param_1)

{
  undefined4 local_8;
  
  local_8 = -1;
  do {
    local_8 = local_8 + 1;
  } while (*(short *)(param_1 + local_8 * 2) != 0);
  return local_8;
}

