// ============================================
// Address:  0x00661350
// Original: FUN_00661350
// Status:   unreviewed
// ============================================

undefined4 __thiscall
FUN_00661350(int param_1, undefined4 param_2, uint param_3, uint param_4, uint param_5)

{
    char cVar1;
    UINT UVar2;
    int iVar3;

    cVar1 = FUN_00660a10();
    if (cVar1 == '\0')
    {
        if (((*(char *)(param_1 + 0xa0f) != '\0') && (param_3 == 0x100)) && (param_4 == 0xd))
        {
            FUN_006609f0(1);
        }
        return 0;
    }
    if (param_3 < 0x10f)
    {
        if (param_3 == 0x10e)
        {
            FUN_00660b50();
        }
        else if (param_3 == 0x100)
        {
            switch (param_4)
            {
            case 0xd:
                FUN_00661290();
                break;
            default:
                return 0;
            case 0x25:
                FUN_00660fc0(0xffffffff);
                break;
            case 0x27:
                FUN_00660fc0(1);
                break;
            case 0x2e:
                FUN_00661100();
                break;
            case 0xe5:
                UVar2 = MapVirtualKeyA(param_5 >> 0x10, 3);
                if (UVar2 != 0x20)
                {
                    return 0;
                }
                FUN_00660d80();
                return 0;
            }
        }
        else if (param_3 == 0x102)
        {
            if (param_4 != 8)
            {
                return 0;
            }
            iVar3 = FUN_006472b0();
            if (0 < iVar3)
            {
                FUN_00660fc0(0xffffffff);
                FUN_00661100();
            }
        }
        else
        {
            if (param_3 != 0x10d)
            {
                return 0;
            }
            if ((param_5 & 8) != 0)
            {
                FUN_00660ab0();
            }
        }
    }
    else if (param_3 == 0x10f)
    {
        if ((param_5 & 8) != 0)
        {
            FUN_00660ab0();
        }
    }
    else
    {
        if (param_3 != 0x282)
        {
            return 0;
        }
        if ((param_4 == 0) || (5 < param_4))
        {
            return 0;
        }
    }
    return 1;
}
