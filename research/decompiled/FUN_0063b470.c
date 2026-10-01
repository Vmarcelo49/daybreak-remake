// Function: FUN_0063b470
// Address:  0x0063b470
// Source:   batch_decompile (mass dump)
// Hash:     a827e2ec1ede4ed8


undefined4 FUN_0063b470(undefined4 param_1,float param_2,undefined4 param_3,float param_4)

{
  undefined4 uVar1;
  undefined2 extraout_var;
  float10 fVar2;
  float10 fVar3;
  bool local_18;
  undefined1 local_10 [12];
  
  uVar1 = FUN_0042dfd0(local_10,param_3);
  fVar2 = (float10)FUN_0063bec0(uVar1);
  fVar3 = ((float10)param_2 + (float10)param_4) * ((float10)param_2 + (float10)param_4);
  local_18 = fVar3 < fVar2 == 0 && (fVar3 == fVar2) == 0;
  return CONCAT31((int3)(CONCAT22(extraout_var,
                                  (ushort)(fVar3 < fVar2) << 8 |
                                  (ushort)(NAN(fVar3) || NAN(fVar2)) << 10 |
                                  (ushort)(fVar3 == fVar2) << 0xe) >> 8),local_18);
}

