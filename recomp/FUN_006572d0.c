// ============================================
// Address:  0x006572d0
// Original: FUN_006572d0
// Status:   unreviewed
// ============================================


void * __fastcall FUN_006572d0(void *param_1)

{
  _memset((void *)((int)param_1 + 0x38),0,0x28);
  _memset(param_1,0,0x34);
  *(undefined1 *)((int)param_1 + 0x60) = 0;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  return param_1;
}

