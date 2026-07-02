// ============================================
// Address:  0x00640ac0
// Original: FUN_00640ac0
// Status:   unreviewed
// ============================================


int __thiscall FUN_00640ac0(int param_1,undefined1 *param_2)

{
  undefined2 uVar1;
  int local_c;
  undefined2 *local_8;
  
  *param_2 = 0x19;
  *(undefined4 *)(param_2 + 1) = *(undefined4 *)(param_1 + 8);
  local_8 = (undefined2 *)(param_2 + 5);
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    uVar1 = FUN_0066b668();
    *local_8 = uVar1;
    uVar1 = FUN_0066b668();
    local_8[1] = uVar1;
    uVar1 = FUN_0066b668();
    local_8[2] = uVar1;
    uVar1 = FUN_0066b668();
    local_8[3] = uVar1;
    uVar1 = FUN_0066b668();
    local_8[4] = uVar1;
    *(undefined1 *)(local_8 + 5) = *(undefined1 *)(param_1 + 0x5c + local_c * 4);
    *(undefined2 *)((int)local_8 + 0xb) = *(undefined2 *)(param_1 + 0x6c + local_c * 4);
    *(undefined1 *)((int)local_8 + 0xd) = *(undefined1 *)(param_1 + 0x7c + local_c * 4);
    local_8[7] = *(undefined2 *)(param_1 + 0x8c + local_c * 4);
    *(undefined1 *)(local_8 + 8) = *(undefined1 *)(param_1 + 0x9c + local_c * 4);
    *(undefined2 *)((int)local_8 + 0x11) = *(undefined2 *)(param_1 + 0xac + local_c * 4);
    *(undefined1 *)((int)local_8 + 0x13) = *(undefined1 *)(param_1 + 0xbc + local_c * 4);
    local_8[10] = *(undefined2 *)(param_1 + 0xcc + local_c * 4);
    local_8 = local_8 + 0xb;
  }
  return (int)local_8 - (int)param_2;
}

