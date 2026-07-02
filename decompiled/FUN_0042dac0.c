// Function: FUN_0042dac0
// Address:  0x0042dac0
// Source:   batch_decompile (mass dump)
// Hash:     4d9eb404185b5b17


float10 FUN_0042dac0(undefined4 param_1)

{
  float10 fVar1;
  float fVar2;
  undefined4 extraout_var;
  
  fVar1 = (float10)FUN_0042d9d0(param_1);
  fVar1 = (float10)FUN_0042de80((float)fVar1,extraout_var);
  fVar2 = (float)fVar1;
  fVar1 = (float10)FUN_0042da50(param_1);
  fVar1 = (float10)FUN_00423580((float)fVar1,fVar2);
  return (fVar1 / (float10)3.1415927) * (float10)180.0;
}

