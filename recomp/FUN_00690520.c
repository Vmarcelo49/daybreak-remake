// ============================================
// Address:  0x00690520
// Original: FUN_00690520
// Status:   unreviewed
// ============================================


undefined4 FUN_00690520(undefined4 param_1,int *param_2)

{
  undefined4 uVar1;
  LPVOID pvVar2;
  
  if (param_2 == (int *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    pvVar2 = CoTaskMemAlloc(8);
    *param_2 = (int)pvVar2;
    if (*param_2 == 0) {
      uVar1 = 0x8007000e;
    }
    else {
      FUN_00691c80(*param_2,4,&DAT_006ad43c);
      uVar1 = 0;
    }
  }
  return uVar1;
}

