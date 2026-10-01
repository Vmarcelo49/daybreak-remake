// Function: FUN_00431b50
// Address:  0x00431b50
// Source:   batch_decompile (mass dump)
// Hash:     954be79b564d23db


void __thiscall
FUN_00431b50(float *param_1,int param_2,float param_3,undefined4 param_4,float param_5,int param_6,
            char param_7)

{
  float local_10;
  char local_9;
  int local_8;
  
  if (param_2 < 0) {
    param_2 = -param_2;
    local_9 = '\x02';
  }
  else if (param_7 == '\0') {
    local_9 = '\0';
  }
  else {
    local_9 = '\x01';
  }
  local_8 = param_2;
  local_10 = param_3 - param_5 * *param_1;
  if (param_6 < 1) {
    while (-1 < local_8) {
      FUN_00408250(param_5);
      FUN_00655d60(local_10,param_4);
      if (local_8 < 10) {
        local_8 = -1;
      }
      else {
        local_8 = local_8 / 10;
      }
      local_10 = local_10 - (*param_1 + param_1[1]) * param_5;
    }
  }
  else {
    for (; 0 < param_6; param_6 = param_6 + -1) {
      FUN_00408250(param_5);
      FUN_00655d60(local_10,param_4);
      local_10 = local_10 - (*param_1 + param_1[1]) * param_5;
    }
  }
  if (local_9 != '\0') {
    FUN_00408250(param_5);
    FUN_00655d60(local_10,param_4);
  }
  return;
}

