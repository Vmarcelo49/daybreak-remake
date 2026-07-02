// ============================================
// Address:  0x0065e3a0
// Original: FUN_0065e3a0
// Status:   unreviewed
// ============================================


undefined4 FUN_0065e3a0(uint *param_1,uint *param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = FUN_0065e400((char)*param_1);
  if (cVar1 == '\0') {
    *param_2 = (int)(char)*param_1;
    uVar2 = 1;
  }
  else {
    *param_2 = (*param_1 & 0xff) << 8 | (int)(*param_1 & 0xff00) >> 8;
    uVar2 = 2;
  }
  return uVar2;
}

