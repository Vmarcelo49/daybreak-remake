// ============================================
// Address:  0x00654340
// Original: FUN_00654340
// Status:   unreviewed
// ============================================


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00654340(undefined2 *param_1,undefined2 param_2)

{
  _DAT_006d1650 = _DAT_006d1650 + 1;
  if (0xffff < _DAT_006d1650) {
    _DAT_006d1650 = 1;
  }
  *param_1 = param_2;
  param_1[1] = DAT_006d1650;
  return;
}

