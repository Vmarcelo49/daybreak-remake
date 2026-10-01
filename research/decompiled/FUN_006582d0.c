// Function: FUN_006582d0
// Address:  0x006582d0
// Source:   batch_decompile (mass dump)
// Hash:     6af13e7bd97ba63d


void __fastcall FUN_006582d0(int param_1)

{
  uint uVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined4 local_8;
  
  local_8 = 0;
  while( true ) {
    uVar1 = FUN_0064f010();
    if (uVar1 <= local_8) break;
    piVar2 = (int *)FUN_00658a10(local_8);
    if (*piVar2 != 0) {
      puVar3 = (undefined4 *)FUN_00658a10(local_8);
      (**(code **)(*(int *)*puVar3 + 0x20))((int *)*puVar3);
      puVar3 = (undefined4 *)FUN_00658a10(local_8);
      (**(code **)(*(int *)*puVar3 + 8))((int *)*puVar3);
      puVar3 = (undefined4 *)FUN_00658a10(local_8);
      *puVar3 = 0;
    }
    local_8 = local_8 + 1;
  }
  FUN_0065a5e0();
  FUN_006589c0();
  if (*(int *)(param_1 + 0xc) != 0) {
    (**(code **)(**(int **)(param_1 + 0xc) + 0x20))(*(undefined4 *)(param_1 + 0xc));
    (**(code **)(**(int **)(param_1 + 0xc) + 8))(*(undefined4 *)(param_1 + 0xc));
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  if (*(int *)(param_1 + 8) != 0) {
    (**(code **)(**(int **)(param_1 + 8) + 8))(*(undefined4 *)(param_1 + 8));
    *(undefined4 *)(param_1 + 8) = 0;
  }
  return;
}

