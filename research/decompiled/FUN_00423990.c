// Function: FUN_00423990
// Address:  0x00423990
// Source:   batch_decompile (mass dump)
// Hash:     ee358c7fb1e25a4b


undefined4 __thiscall FUN_00423990(int param_1,undefined1 *param_2)

{
  undefined2 uVar1;
  
  *param_2 = 0x36;
  param_2[1] = *(undefined1 *)(param_1 + 8);
  *(undefined2 *)(param_2 + 2) = *(undefined2 *)(param_1 + 10);
  uVar1 = FUN_0066b668();
  *(undefined2 *)(param_2 + 4) = uVar1;
  uVar1 = FUN_0066b668();
  *(undefined2 *)(param_2 + 6) = uVar1;
  uVar1 = FUN_0066b668();
  *(undefined2 *)(param_2 + 8) = uVar1;
  uVar1 = FUN_0066b668();
  *(undefined2 *)(param_2 + 10) = uVar1;
  uVar1 = FUN_0066b668();
  *(undefined2 *)(param_2 + 0xc) = uVar1;
  uVar1 = FUN_0066b668();
  *(undefined2 *)(param_2 + 0xe) = uVar1;
  return 0x10;
}

