// ============================================
// Address:  0x006585f0
// Original: FUN_006585f0
// Suggested: UpdateInputState (confidence: low)
// Status:   suggested — name kept as comment until reviewed
// ============================================


void __fastcall FUN_006585f0(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 local_c;
  
  if (*(int *)(param_1 + 8) != 0) {
    for (local_c = 0; local_c < (int)(uint)*(byte *)(param_1 + 0x120); local_c = local_c + 1) {
      piVar1 = (int *)FUN_00658a10(local_c);
      if (*piVar1 != 0) {
        puVar2 = (undefined4 *)FUN_00658a10(local_c);
        iVar3 = (**(code **)(*(int *)*puVar2 + 100))((int *)*puVar2);
        if (iVar3 < 0) {
          puVar2 = (undefined4 *)FUN_00658a10(local_c);
          (**(code **)(*(int *)*puVar2 + 0x1c))((int *)*puVar2);
        }
        puVar2 = (undefined4 *)FUN_00658a10(local_c);
        piVar1 = (int *)*puVar2;
        uVar4 = FUN_00404e20(local_c);
        (**(code **)(*piVar1 + 0x24))(piVar1,0x50,uVar4);
      }
    }
  }
  return;
}

