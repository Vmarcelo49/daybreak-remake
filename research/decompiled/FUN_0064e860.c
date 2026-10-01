// Function: FUN_0064e860
// Address:  0x0064e860
// Source:   batch_decompile (mass dump)
// Hash:     7daf38bbfcd8db17


void __fastcall FUN_0064e860(undefined4 param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 local_8;
  
  local_8 = 0;
  while( true ) {
    uVar1 = FUN_0064f010(param_1);
    if (uVar1 <= local_8) break;
    puVar2 = (undefined4 *)FUN_0064ef20(local_8);
    *puVar2 = 0xffffffff;
    local_8 = local_8 + 1;
  }
  return;
}

