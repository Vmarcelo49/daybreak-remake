// Function: FUN_0065d9a0
// Address:  0x0065d9a0
// Source:   batch_decompile (mass dump)
// Hash:     449d64c6a454b86d


void __thiscall FUN_0065d9a0(int param_1,UINT param_2)

{
  void *pvVar1;
  _GLYPHMETRICS local_3c;
  DWORD local_28;
  MAT2 local_24;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if ((*(int *)(param_1 + 4) != 0) && (*(int *)(param_1 + 8) != 0)) {
    _memset(&local_3c,0,0x14);
    local_c = 0x10000;
    local_14 = 0;
    local_8 = 0;
    local_10 = 0x10000;
    local_24.eM11.fract = 0;
    local_24.eM11.value = 1;
    local_24.eM12.fract = 0;
    local_24.eM12.value = 0;
    local_24.eM21.fract = 0;
    local_24.eM21.value = 0;
    local_24.eM22.fract = 0;
    local_24.eM22.value = 1;
    local_28 = GetGlyphOutlineA(*(HDC *)(param_1 + 4),param_2,5,&local_3c,0,(LPVOID)0x0,&local_24);
    if (*(int *)(param_1 + 0x10) != 0) {
      _free(*(void **)(param_1 + 0x10));
      *(undefined4 *)(param_1 + 0x10) = 0;
    }
    pvVar1 = operator_new(local_28);
    *(void **)(param_1 + 0x10) = pvVar1;
    GetGlyphOutlineA(*(HDC *)(param_1 + 4),param_2,5,&local_3c,local_28,*(LPVOID *)(param_1 + 0x10),
                     &local_24);
    *(UINT *)(param_1 + 0x18) = local_3c.gmBlackBoxX;
    *(UINT *)(param_1 + 0x14) = local_3c.gmBlackBoxY;
    *(uint *)(param_1 + 0x1c) = local_28 / local_3c.gmBlackBoxY & 0xfffffffc;
    *(LONG *)(param_1 + 0x28) = local_3c.gmptGlyphOrigin.x;
    *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x24) - local_3c.gmptGlyphOrigin.y;
  }
  return;
}

