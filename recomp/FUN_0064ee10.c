// ============================================
// Address:  0x0064ee10
// Original: FUN_0064ee10
// Status:   unreviewed
// ============================================


void * FUN_0064ee10(int param_1)

{
  byte bVar1;
  undefined4 local_8;
  
  local_8 = operator_new(param_1 + 0x10);
  if (local_8 != (void *)0x0) {
    bVar1 = 0x10 - ((byte)local_8 & 0xf);
    local_8 = (void *)((uint)bVar1 + (int)local_8);
    *(byte *)((int)local_8 + -1) = bVar1;
  }
  return local_8;
}

