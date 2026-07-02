// ============================================
// Address:  0x0067e570
// Original: FUN_0067e570
// Status:   unreviewed
// ============================================


uint FUN_0067e570(uint param_1)

{
  uint uVar1;
  
  uVar1 = CONCAT22((short)param_1,(ushort)(byte)(param_1 >> 0x10)) << 8 |
          (param_1 >> 0x10 | param_1 << 0x10) >> 8 & 0xff00ff;
  uVar1 = (uVar1 & 0xff0f0f0f) << 4 | uVar1 >> 4 & 0xf0f0f0f;
  uVar1 = (uVar1 & 0xf3333333) << 2 | uVar1 >> 2 & 0x33333333;
  return uVar1 >> 1 & 0x55555555 | (uVar1 & 0xd5555555) << 1;
}

