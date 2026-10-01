// Function: FUN_0066cec4
// Address:  0x0066cec4
// Source:   batch_decompile (mass dump)
// Hash:     821ce480ba04b5ea


int FUN_0066cec4(short *param_1)

{
  short sVar1;
  short *psVar2;
  
  psVar2 = param_1;
  do {
    sVar1 = *psVar2;
    psVar2 = psVar2 + 1;
  } while (sVar1 != 0);
  return ((int)psVar2 - (int)param_1 >> 1) + -1;
}

