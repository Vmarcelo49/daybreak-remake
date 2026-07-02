// ============================================
// Address:  0x00663030
// Original: FUN_00663030
// Status:   unreviewed
// ============================================

BOOL __thiscall FUN_00663030(undefined4 *param_1, LPVOID param_2, uint param_3)

{
    uint uVar1;
    DWORD DVar2;
    BOOL BVar3;
    uint local_18;

    DVar2 = SetFilePointer((HANDLE)*param_1, 0, (PLONG)0x0, 1);
    if ((uint)(param_1[1] + param_1[2]) < DVar2 + param_3)
    {
        param_3 = (param_1[1] + param_1[2]) - DVar2;
    }
    BVar3 = ReadFile((HANDLE)*param_1, param_2, param_3, param_1 + 3, (LPOVERLAPPED)0x0);
    uVar1 = param_1[1];
    for (local_18 = 0; local_18 < param_3; local_18 = local_18 + 1)
    {
        *(byte *)((int)param_2 + local_18) =
            *(byte *)((int)param_2 + local_18) ^ ((byte)(uVar1 >> 1) | 8);
    }
    return BVar3;
}
