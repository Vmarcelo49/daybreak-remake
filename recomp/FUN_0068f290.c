// ============================================
// Address:  0x0068f290
// Original: FUN_0068f290
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_0068f290(int *param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  HANDLE hEvent;
  undefined8 uVar3;
  undefined4 local_14;
  undefined4 local_10;
  undefined1 local_c [8];
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    iVar2 = (**(code **)(*param_1 + 0x58))(param_2,&local_14,local_c);
    if (iVar2 < 0) {
      uVar1 = 0;
    }
    else if (iVar2 == 0) {
      hEvent = (HANDLE)FUN_0068de10();
      SetEvent(hEvent);
      uVar1 = 1;
    }
    else {
      uVar1 = FUN_0068de10(param_1 + 0x1a);
      uVar3 = FUN_00697fc0(local_14,local_10,uVar1);
      iVar2 = (**(code **)(*(int *)param_1[6] + 0x10))(param_1[6],uVar3);
      if (iVar2 < 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = 1;
      }
    }
  }
  return uVar1;
}

