// ============================================
// Address:  0x00633930
// Original: FUN_00633930
// Status:   unreviewed
// ============================================


uint __thiscall FUN_00633930(int param_1,uint param_2)

{
  undefined1 local_34 [12];
  float local_28;
  undefined4 *local_24;
  int local_20;
  undefined4 local_1c;
  float local_18;
  undefined4 local_14;
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  local_1c = *(undefined4 *)(param_1 + 0xc);
  local_14 = *(undefined4 *)(param_1 + 0x14);
  local_18 = *(float *)(param_1 + 0x10) + 150.0;
  FUN_0042dfd0(local_34,param_1 + 0x3c);
  D3DXVec3Normalize(local_34,local_34);
  local_20 = 0;
  for (local_24 = *(undefined4 **)(param_2 + 0x44); local_24 != (undefined4 *)0x0;
      local_24 = (undefined4 *)local_24[8]) {
    D3DXIntersect(local_24[2],&local_1c,local_34,&local_20,local_10,local_c,local_8,&local_28,0,0);
    if ((local_20 != 0) && (local_28 < *(float *)(param_1 + 0x78))) {
      FUN_0066b860(param_1 + 0x96,*local_24);
    }
  }
  if (*(int *)(param_2 + 0x48) != 0) {
    FUN_00633930(*(undefined4 *)(param_2 + 0x48));
  }
  if (*(int *)(param_2 + 0x4c) != 0) {
    param_2 = FUN_00633930(*(undefined4 *)(param_2 + 0x4c));
  }
  return param_2 & 0xffffff00;
}

