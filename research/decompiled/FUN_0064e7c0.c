// Function: FUN_0064e7c0
// Address:  0x0064e7c0
// Source:   batch_decompile (mass dump)
// Hash:     9f42c51b48b47bfc


uint __thiscall FUN_0064e7c0(undefined4 param_1,char *param_2)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  char *_Str2;
  uint local_8;
  
  local_8 = 0;
  while( true ) {
    uVar1 = FUN_0064f010(param_1);
    if (uVar1 <= local_8) {
      return 0xffffffff;
    }
    _Str2 = param_2;
    puVar2 = (undefined4 *)FUN_00658a10(local_8);
    iVar3 = _strcmp((char *)*puVar2,_Str2);
    if (iVar3 == 0) break;
    local_8 = local_8 + 1;
  }
  return local_8;
}

