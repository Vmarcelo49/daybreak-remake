// Function: FUN_0065f280
// Address:  0x0065f280
// Source:   batch_decompile (mass dump)
// Hash:     af6ba5698e295f6e


/* WARNING: Removing unreachable block (ram,0x0065f304) */
/* WARNING: Removing unreachable block (ram,0x0065f30a) */
/* WARNING: Removing unreachable block (ram,0x0065f313) */

int FUN_0065f280(int param_1,int *param_2)

{
  char cVar1;
  int local_8;
  
  local_8 = 0;
  while( true ) {
    cVar1 = *(char *)(param_1 + local_8);
    if (cVar1 == '\0') {
      if (param_2 != (int *)0x0) {
        *param_2 = 0;
      }
      return 0;
    }
    if (cVar1 == '\r') break;
    if (cVar1 == ',') {
      if (param_2 == (int *)0x0) {
        return local_8;
      }
      *param_2 = param_1 + 1 + local_8;
      return local_8;
    }
    local_8 = local_8 + 1;
  }
  if (param_2 == (int *)0x0) {
    return local_8;
  }
  *param_2 = 0;
  return local_8;
}

