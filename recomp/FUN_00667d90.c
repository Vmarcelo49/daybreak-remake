// ============================================
// Address:  0x00667d90
// Original: FUN_00667d90
// Status:   unreviewed
// ============================================


int __thiscall FUN_00667d90(int param_1,int param_2)

{
  uint local_18;
  int local_14;
  uint local_10;
  void *local_c;
  undefined4 local_8;
  
  local_c = (void *)0x0;
  local_10 = 0;
  local_8 = (**(code **)(**(int **)(param_1 + 4) + 4))(*(undefined4 *)(param_1 + 4));
  (**(code **)(**(int **)(param_1 + 4) + 0x24))(*(undefined4 *)(param_1 + 4),&local_18);
  if ((local_18 & 1) != 0) {
    (**(code **)(**(int **)(param_1 + 4) + 0x48))(*(undefined4 *)(param_1 + 4));
  }
  (**(code **)(**(int **)(param_1 + 4) + 0x34))(*(undefined4 *)(param_1 + 4),0);
  local_14 = (**(code **)(**(int **)(param_1 + 4) + 0x2c))
                       (*(undefined4 *)(param_1 + 4),0,0,&local_c,&local_10,0,0,2);
  if (-1 < local_14) {
    if (*(uint *)(param_2 + 0x18) < local_10) {
      _memset((void *)((int)local_c + *(int *)(param_2 + 0x18)),0,
              local_10 - *(int *)(param_2 + 0x18));
      _memcpy(local_c,*(void **)(param_2 + 0x14),*(size_t *)(param_2 + 0x18));
    }
    else {
      _memcpy(local_c,*(void **)(param_2 + 0x14),local_10);
    }
    (**(code **)(**(int **)(param_1 + 4) + 0x4c))(*(undefined4 *)(param_1 + 4),local_c,local_10,0,0)
    ;
    (**(code **)(**(int **)(param_1 + 4) + 8))(*(undefined4 *)(param_1 + 4));
  }
  return param_1;
}

