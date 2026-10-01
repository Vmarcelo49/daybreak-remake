// Function: FUN_00423370
// Address:  0x00423370
// Source:   batch_decompile (mass dump)
// Hash:     bcd7002e3b2925c2


void * __thiscall FUN_00423370(void *param_1,uint param_2)

{
  FUN_00431da0();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

