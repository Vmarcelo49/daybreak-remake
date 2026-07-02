// Function: FUN_00692600
// Address:  0x00692600
// Source:   batch_decompile (mass dump)
// Hash:     2594d78de9e5baa8


void FUN_00692600(undefined4 param_1,LPWSTR param_2,int param_3)

{
  CHAR local_24 [32];
  
  FUN_00693480(local_24,0x20,&DAT_006ad6e8,param_1);
  MultiByteToWideChar(0,0,local_24,-1,param_2,param_3);
  return;
}

