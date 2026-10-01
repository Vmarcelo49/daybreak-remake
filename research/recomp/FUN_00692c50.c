// ============================================
// Address:  0x00692c50
// Original: FUN_00692c50
// Status:   unreviewed
// ============================================

undefined8 FUN_00692c50(uint param_1, uint param_2, uint param_3, uint param_4, uint param_5)

{
    longlong lVar1;
    byte bVar2;
    bool bVar3;
    byte bVar4;
    uint uVar5;
    int iVar6;
    int iVar7;
    bool bVar8;
    bool bVar9;
    bool bVar10;
    ulong local_7c;
    ulong local_78;
    uint local_74;
    uint local_6c;
    uint local_68;
    uint local_64;
    uint local_60;
    uint local_5c;
    uint local_58;
    int local_48;
    undefined4 local_44;
    uint local_40;
    ulong local_30;
    uint local_20;
    undefined8 local_14;
    uint local_c;
    uint local_8;

    if ((int)param_2 < 0)
    {
        local_64 = -param_1;
        local_60 = -(param_2 + (param_1 != 0));
    }
    else
    {
        local_64 = param_1;
        local_60 = param_2;
    }
    if ((int)param_3 < 0)
    {
        local_68 = -param_3;
    }
    else
    {
        local_68 = param_3;
    }
    if ((int)param_4 < 0)
    {
        local_6c = -param_4;
    }
    else
    {
        local_6c = param_4;
    }
    if (((int)param_2 < 1) && ((int)param_2 < 0))
    {
        bVar4 = 1;
        bVar2 = 1;
    }
    else
    {
        bVar4 = 0;
        bVar2 = 0;
    }
    bVar3    = (bool)((int)param_3 < 0 ^ bVar4);
    bVar10   = (bool)((int)param_3 < 0 ^ bVar2);
    local_14 = (ulonglong)local_64 * (ulonglong)local_68;
    if (local_60 == 0)
    {
        local_20 = 0;
    }
    else
    {
        lVar1    = (ulonglong)local_60 * (ulonglong)local_68 + (local_14 >> 0x20);
        local_44 = (undefined4)lVar1;
        local_14 = CONCAT44(local_44, (uint)local_14);
        local_40 = (uint)((ulonglong)lVar1 >> 0x20);
        local_20 = local_40;
    }
    if (param_5 != 0)
    {
        local_58 = (int)param_5 >> 0x1f;
        if (bVar10)
        {
            local_5c = -param_5;
            local_58 = -(local_58 + (param_5 != 0));
            if ((int)param_5 < 1)
            {
                local_48 = 0;
            }
            else
            {
                local_48 = -1;
            }
        }
        else
        {
            local_5c = param_5;
            if ((int)param_5 < 0)
            {
                local_48 = -1;
            }
            else
            {
                local_48 = 0;
            }
        }
        bVar8    = CARRY4(local_5c, (uint)local_14);
        local_5c = local_5c + (uint)local_14;
        bVar9    = CARRY4(local_58, local_14._4_4_);
        local_58 = local_58 + local_14._4_4_;
        uVar5    = local_58 + bVar8;
        local_14 = CONCAT44(uVar5, local_5c);
        local_20 = local_48 + (uint)bVar9 + (uint)CARRY4(local_58, (uint)bVar8) + local_20;
        if ((int)local_20 < 0)
        {
            bVar10   = !bVar3;
            local_5c = ~local_5c;
            iVar6    = local_5c + 1;
            iVar7    = ~uVar5 + (uint)(0xfffffffe < local_5c);
            local_14 = CONCAT44(iVar7, iVar6);
            local_74 = (uint)(iVar6 == 0 && iVar7 == 0);
            local_20 = ~local_20 + local_74;
            bVar3    = bVar10;
        }
    }
    if ((int)param_4 < 0)
    {
        bVar10 = !bVar3;
    }
    if (local_20 < local_6c)
    {
        local_8 = local_20;
        local_c = local_14._4_4_;
        if ((local_20 == 0) && (local_14._4_4_ < local_6c))
        {
            local_30 = 0;
        }
        else
        {
            local_30 =
                EnlargedUnsignedDivide(local_14._4_4_, local_20, local_6c, (int)&local_14 + 4);
        }
        local_7c = EnlargedUnsignedDivide((uint)local_14, local_14._4_4_, local_6c, 0);
        local_78 = local_30;
        if (bVar10)
        {
            bVar10   = local_7c != 0;
            local_7c = -local_7c;
            local_78 = -(local_30 + bVar10);
        }
    }
    else if (bVar10)
    {
        local_7c = 0;
        local_78 = 0x80000000;
    }
    else
    {
        local_7c = 0xffffffff;
        local_78 = 0x7fffffff;
    }
    return CONCAT44(local_78, local_7c);
}
