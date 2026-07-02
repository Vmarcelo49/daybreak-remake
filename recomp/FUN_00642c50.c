// ============================================
// Address:  0x00642c50
// Original: FUN_00642c50
// Status:   unreviewed
// ============================================


void __thiscall FUN_00642c50(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  *(undefined4 *)(param_1 + 0xb70) = param_2;
  FUN_00645210(*(int *)(param_1 + 0xb70) + 0x7a4,10000,0);
  FUN_00645210(*(int *)(param_1 + 0xb70) + 0x7a4,10000,0);
  FUN_00645210(*(int *)(param_1 + 0xb70) + 0x7a8,10000,0);
  FUN_00645210(*(int *)(param_1 + 0xb70) + 0x834,1000,0);
  iVar2 = *(int *)(param_1 + 0xb70);
  iVar3 = *(int *)(param_1 + 0xb70);
  FUN_00645210(iVar2 + 0x6f4,*(undefined4 *)(iVar2 + 0x6f8),0);
  FUN_00645210(iVar3 + 0x738,*(undefined4 *)(iVar3 + 0x73c),0);
  FUN_00645210(iVar2 + 0x700,*(undefined4 *)(iVar2 + 0x6d0),0);
  FUN_00645210(iVar3 + 0x744,*(undefined4 *)(iVar3 + 0x714),0);
  FUN_00645210(iVar3 + 0x724,0x1e,0);
  FUN_00645210(iVar3 + 0x728,*(undefined4 *)(iVar3 + 0x72c),0);
  cVar1 = *(char *)(*(int *)(param_1 + 0xb70) + 0x318);
  if (cVar1 == '\0') {
    FUN_00655af0(DAT_006c7f40,0,0,0xe6,0x5b);
    FUN_00655af0(DAT_006c7f40,0,0x120,0xe6,0x5b);
    FUN_00655af0(DAT_006c7f40,0,0x180,0xe6,0x5b);
    FUN_00645210(*(int *)(param_1 + 0xb70) + 0x838,
                 *(undefined4 *)(*(int *)(param_1 + 0xb70) + 0x324),2);
    FUN_00645210(*(int *)(param_1 + 0xb70) + 0x838,
                 *(undefined4 *)(*(int *)(param_1 + 0xb70) + 0x328),2);
    FUN_00645210(*(int *)(param_1 + 0xb70) + 0x838,
                 *(undefined4 *)(*(int *)(param_1 + 0xb70) + 0x328),2);
  }
  else if (cVar1 == '\x01') {
    FUN_00655af0(DAT_006c7f40,0x100,0,0xe6,0x5b);
    FUN_00655af0(DAT_006c7f40,0x100,0x120,0xe6,0x5b);
    FUN_00655af0(DAT_006c7f40,0x100,0x180,0xe6,0x5b);
    FUN_00645210(*(int *)(param_1 + 0xb70) + 0x83c,
                 *(undefined4 *)(*(int *)(param_1 + 0xb70) + 0x32c),2);
    FUN_00645210(*(int *)(param_1 + 0xb70) + 0x83c,
                 *(undefined4 *)(*(int *)(param_1 + 0xb70) + 0x330),2);
    FUN_00645210(*(int *)(param_1 + 0xb70) + 0x83c,
                 *(undefined4 *)(*(int *)(param_1 + 0xb70) + 0x330),2);
  }
  else if (cVar1 == '\x02') {
    FUN_00655af0(DAT_006c7f54,0,0,0xe6,0x5b);
    FUN_00655af0(DAT_006c7f40,0,0x120,0xe6,0x5b);
    FUN_00655af0(DAT_006c7f40,0,0x180,0xe6,0x5b);
    FUN_00645210(*(int *)(param_1 + 0xb70) + 0x840,
                 *(undefined4 *)(*(int *)(param_1 + 0xb70) + 0x324),2);
    FUN_00645210(*(int *)(param_1 + 0xb70) + 0x840,
                 *(undefined4 *)(*(int *)(param_1 + 0xb70) + 0x328),2);
    FUN_00645210(*(int *)(param_1 + 0xb70) + 0x840,
                 *(undefined4 *)(*(int *)(param_1 + 0xb70) + 0x328),2);
  }
  return;
}

