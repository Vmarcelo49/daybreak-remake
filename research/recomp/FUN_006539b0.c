// ============================================
// Address:  0x006539b0
// Original: FUN_006539b0
// Status:   unreviewed
// ============================================

void __thiscall FUN_006539b0(undefined4 *param_1, undefined4 param_2, LONG param_3, DWORD param_4)

{
    char cVar1;
    int iVar2;
    undefined4 *puVar3;
    PLONG lpDistanceToMoveHigh;

    cVar1 = FUN_0064d6e0();
    if (cVar1 == '\0')
    {
        iVar2 = FUN_006543d0(param_2);
        if (iVar2 == 0)
        {
            lpDistanceToMoveHigh = (PLONG)0x0;
            puVar3               = (undefined4 *)FUN_006543d0(param_2);
            SetFilePointer((HANDLE)*puVar3, param_3, lpDistanceToMoveHigh, param_4);
        }
        else
        {
            FUN_006630f0(param_3, param_4);
        }
    }
    else
    {
        SetFilePointer((HANDLE)*param_1, param_3, (PLONG)0x0, param_4);
    }
    return;
}
