// ============================================
// Address:  0x00662f70
// Original: FUN_00662f70
// Status:   unreviewed
// ============================================


bool __thiscall FUN_00662f70(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  PLONG lpDistanceToMoveHigh;
  DWORD dwMoveMethod;
  undefined1 local_118 [272];
  undefined1 local_8 [4];
  
  uVar2 = FUN_006631b0(param_2,0,0);
  FUN_00663480(local_8,uVar2);
  uVar2 = FUN_00654620(local_118);
  cVar1 = const_iterator__operator__(uVar2);
  if (cVar1 == '\0') {
    iVar3 = FUN_00663510();
    param_1[1] = *(undefined4 *)(iVar3 + 0x108);
    iVar3 = FUN_00663510();
    param_1[2] = *(undefined4 *)(iVar3 + 0x104);
    dwMoveMethod = 0;
    lpDistanceToMoveHigh = (PLONG)0x0;
    iVar3 = FUN_00663510();
    SetFilePointer((HANDLE)*param_1,*(LONG *)(iVar3 + 0x108),lpDistanceToMoveHigh,dwMoveMethod);
  }
  return cVar1 == '\0';
}

