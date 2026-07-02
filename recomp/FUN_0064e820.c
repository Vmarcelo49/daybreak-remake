// ============================================
// Address:  0x0064e820
// Original: FUN_0064e820
// Status:   unreviewed
// ============================================


void __thiscall FUN_0064e820(undefined4 param_1,uint param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  
  uVar1 = FUN_0064f010(param_1);
  if (param_2 < uVar1) {
    puVar2 = (undefined4 *)FUN_0064ef20(param_2);
    *puVar2 = param_3;
  }
  return;
}

