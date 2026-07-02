// ============================================
// Address:  0x0067dbc0
// Original: FUN_0067dbc0
// Status:   unreviewed
// ============================================


float10 FUN_0067dbc0(uint param_1)

{
  double dVar1;
  undefined8 local_8;
  
  local_8 = (double)(param_1 & 0x1fffff);
  if ((param_1 & 0x80000000) != 0) {
    local_8 = -local_8;
  }
  dVar1 = _ldexp(local_8,((int)param_1 >> 0x15 & 0x3ffU) - 0x314);
  return (float10)dVar1;
}

