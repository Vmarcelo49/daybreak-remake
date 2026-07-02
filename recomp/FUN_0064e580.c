// ============================================
// Address:  0x0064e580
// Original: FUN_0064e580
// Status:   unreviewed
// ============================================


void __fastcall FUN_0064e580(int param_1)

{
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < 2; local_8 = local_8 + 1) {
    if (*(int *)(param_1 + 0xc + local_8 * 4) != 0) {
      (**(code **)(**(int **)(param_1 + 0xc + local_8 * 4) + 0x34))
                (*(undefined4 *)(param_1 + 0xc + local_8 * 4),0,0);
    }
  }
  FUN_0064e360();
  return;
}

