// Function: FUN_004235d0
// Address:  0x004235d0
// Source:   batch_decompile (mass dump)
// Hash:     7fda4d46e870663c


void __thiscall FUN_004235d0(int *param_1,int param_2,undefined4 param_3)

{
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  
  if (param_2 == 2) {
    param_1[2] = 0x2d;
  }
  else if (0 < param_1[2]) {
    param_1[2] = param_1[2] + -1;
  }
  if (param_2 < 2) {
    if (param_1[2] != 0) {
      return;
    }
    *param_1 = param_2;
  }
  else {
    *param_1 = param_2;
  }
  fVar1 = (float10)FUN_0065d010(param_3);
  fVar2 = (float10)FUN_0065d050(param_3);
  fVar3 = (float10)FUN_0065d050(0x42340000);
  if ((float10)(float)fVar2 <= fVar3) {
    fVar3 = (float10)FUN_0065d050(0x43070000);
    if (fVar3 <= (float10)(float)fVar2) {
      if ((float)fVar1 <= 0.0) {
        param_1[1] = 3;
      }
      else {
        param_1[1] = 2;
      }
    }
    else {
      param_1[1] = 1;
    }
  }
  else {
    param_1[1] = 0;
  }
  return;
}

