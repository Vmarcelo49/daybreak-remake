// ============================================
// Address:  0x00664290
// Original: FUN_00664290
// Status:   unreviewed
// ============================================

undefined4 *__thiscall FUN_00664290(int param_1, undefined4 *param_2, undefined4 param_3)

{
    _Container_proxy *p_Var1;
    undefined4 uVar2;
    char *pcVar3;
    undefined4 *puVar4;
    int *piVar5;
    undefined4 *puVar6;
    undefined1 *puVar7;
    undefined1 *puVar8;
    _Container_proxy *local_70;
    _Container_proxy *local_6c;
    undefined1 local_64[28];
    undefined1 local_48[40];
    _Container_proxy *local_20;
    _Container_proxy *local_1c;
    _Container_proxy *local_18;
    _Container_proxy *local_14;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f2c8;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    uVar2         = FUN_0068de10();
    pcVar3        = (char *)FUN_00663560(uVar2);
    if (*pcVar3 != '\0')
    {
        basic_string<>("invalid map/set<T> iterator");
        local_8 = 0;
        FID_conflict_length_error(local_64);
        /* WARNING: Subroutine does not return */
        __CxxThrowException_8(local_48, &DAT_006b2d40);
    }
    local_14 = (_Container_proxy *)FUN_0068de10();
    FUN_00663c70();
    local_1c = local_14;
    puVar4   = (undefined4 *)FUN_00663590(local_14);
    pcVar3   = (char *)FUN_00663560(*puVar4);
    if (*pcVar3 == '\0')
    {
        puVar4 = (undefined4 *)FUN_00654020(local_1c);
        pcVar3 = (char *)FUN_00663560(*puVar4);
        if (*pcVar3 == '\0')
        {
            local_1c = (_Container_proxy *)FUN_0068de10();
            piVar5   = (int *)FUN_00654020(local_1c);
            local_18 = (_Container_proxy *)*piVar5;
        }
        else
        {
            piVar5   = (int *)FUN_00663590(local_1c);
            local_18 = (_Container_proxy *)*piVar5;
        }
    }
    else
    {
        piVar5   = (int *)FUN_00654020(local_1c);
        local_18 = (_Container_proxy *)*piVar5;
    }
    if (local_1c == local_14)
    {
        piVar5   = (int *)FUN_00653df0(local_14);
        local_20 = (_Container_proxy *)*piVar5;
        pcVar3   = (char *)FUN_00663560(local_18);
        if (*pcVar3 == '\0')
        {
            piVar5  = (int *)FUN_00653df0(local_18);
            *piVar5 = (int)local_20;
        }
        piVar5 = (int *)FUN_00663b30();
        if ((_Container_proxy *)*piVar5 == local_14)
        {
            piVar5  = (int *)FUN_00663b30();
            *piVar5 = (int)local_18;
        }
        else
        {
            piVar5 = (int *)FUN_00663590(local_20);
            if ((_Container_proxy *)*piVar5 == local_14)
            {
                piVar5  = (int *)FUN_00663590(local_20);
                *piVar5 = (int)local_18;
            }
            else
            {
                piVar5  = (int *)FUN_00654020(local_20);
                *piVar5 = (int)local_18;
            }
        }
        piVar5 = (int *)FUN_00663af0();
        if ((_Container_proxy *)*piVar5 == local_14)
        {
            pcVar3 = (char *)FUN_00663560(local_18);
            if (*pcVar3 == '\0')
            {
                local_6c = (_Container_proxy *)FUN_00664e80(local_18);
            }
            else
            {
                local_6c = local_20;
            }
            piVar5  = (int *)FUN_00663af0();
            *piVar5 = (int)local_6c;
        }
        piVar5 = (int *)FUN_00663b10();
        if ((_Container_proxy *)*piVar5 == local_14)
        {
            pcVar3 = (char *)FUN_00663560(local_18);
            if (*pcVar3 == '\0')
            {
                local_70 = (_Container_proxy *)FUN_00664e40(local_18);
            }
            else
            {
                local_70 = local_20;
            }
            piVar5  = (int *)FUN_00663b10();
            *piVar5 = (int)local_70;
        }
    }
    else
    {
        puVar4  = (undefined4 *)FUN_00663590(local_14);
        piVar5  = (int *)FUN_00653df0(*puVar4);
        *piVar5 = (int)local_1c;
        puVar4  = (undefined4 *)FUN_00663590(local_14);
        puVar6  = (undefined4 *)FUN_00663590(local_1c);
        *puVar6 = *puVar4;
        piVar5  = (int *)FUN_00654020(local_14);
        if (local_1c == (_Container_proxy *)*piVar5)
        {
            local_20 = local_1c;
        }
        else
        {
            piVar5   = (int *)FUN_00653df0(local_1c);
            local_20 = (_Container_proxy *)*piVar5;
            pcVar3   = (char *)FUN_00663560(local_18);
            if (*pcVar3 == '\0')
            {
                piVar5  = (int *)FUN_00653df0(local_18);
                *piVar5 = (int)local_20;
            }
            piVar5  = (int *)FUN_00663590(local_20);
            *piVar5 = (int)local_18;
            puVar4  = (undefined4 *)FUN_00654020(local_14);
            puVar6  = (undefined4 *)FUN_00654020(local_1c);
            *puVar6 = *puVar4;
            puVar4  = (undefined4 *)FUN_00654020(local_14);
            piVar5  = (int *)FUN_00653df0(*puVar4);
            *piVar5 = (int)local_1c;
        }
        piVar5 = (int *)FUN_00663b30();
        if ((_Container_proxy *)*piVar5 == local_14)
        {
            piVar5  = (int *)FUN_00663b30();
            *piVar5 = (int)local_1c;
        }
        else
        {
            puVar4 = (undefined4 *)FUN_00653df0(local_14);
            piVar5 = (int *)FUN_00663590(*puVar4);
            if ((_Container_proxy *)*piVar5 == local_14)
            {
                puVar4  = (undefined4 *)FUN_00653df0(local_14);
                piVar5  = (int *)FUN_00663590(*puVar4);
                *piVar5 = (int)local_1c;
            }
            else
            {
                puVar4  = (undefined4 *)FUN_00653df0(local_14);
                piVar5  = (int *)FUN_00654020(*puVar4);
                *piVar5 = (int)local_1c;
            }
        }
        puVar4  = (undefined4 *)FUN_00653df0(local_14);
        puVar6  = (undefined4 *)FUN_00653df0(local_1c);
        *puVar6 = *puVar4;
        uVar2   = FUN_00663ce0(local_14);
        uVar2   = FUN_00663ce0(local_1c, uVar2);
        FUN_00664ef0(uVar2);
    }
    pcVar3 = (char *)FUN_00663ce0(local_14);
    if (*pcVar3 != '\x01')
    {
    LAB_006649e8:
        std::allocator<std::_Container_proxy>::destroy(
            (allocator<std::_Container_proxy> *)(param_1 + 1), local_14);
        deallocate(local_14, 1);
        if (*(int *)(param_1 + 8) != 0)
        {
            *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -1;
        }
        *param_2      = param_3;
        ExceptionList = local_10;
        return param_2;
    }
LAB_0066466c:
    piVar5 = (int *)FUN_00663b30();
    if ((local_18 == (_Container_proxy *)*piVar5) ||
        (pcVar3 = (char *)FUN_00663ce0(local_18), *pcVar3 != '\x01'))
        goto LAB_006649d9;
    piVar5 = (int *)FUN_00663590(local_20);
    if (local_18 == (_Container_proxy *)*piVar5)
    {
        piVar5   = (int *)FUN_00654020(local_20);
        local_1c = (_Container_proxy *)*piVar5;
        pcVar3   = (char *)FUN_00663ce0(local_1c);
        if (*pcVar3 == '\0')
        {
            puVar7  = (undefined1 *)FUN_00663ce0(local_1c);
            *puVar7 = 1;
            puVar7  = (undefined1 *)FUN_00663ce0(local_20);
            *puVar7 = 0;
            FUN_00663ec0(local_20);
            piVar5   = (int *)FUN_00654020(local_20);
            local_1c = (_Container_proxy *)*piVar5;
        }
        pcVar3 = (char *)FUN_00663560(local_1c);
        p_Var1 = local_20;
        if (*pcVar3 == '\0')
        {
            puVar4 = (undefined4 *)FUN_00663590(local_1c);
            pcVar3 = (char *)FUN_00663ce0(*puVar4);
            if (*pcVar3 == '\x01')
            {
                puVar4 = (undefined4 *)FUN_00654020(local_1c);
                pcVar3 = (char *)FUN_00663ce0(*puVar4);
                if (*pcVar3 == '\x01')
                {
                    puVar7  = (undefined1 *)FUN_00663ce0(local_1c);
                    *puVar7 = 0;
                    p_Var1  = local_20;
                    goto LAB_0066465b;
                }
            }
            puVar4 = (undefined4 *)FUN_00654020(local_1c);
            pcVar3 = (char *)FUN_00663ce0(*puVar4);
            if (*pcVar3 == '\x01')
            {
                puVar4  = (undefined4 *)FUN_00663590(local_1c);
                puVar7  = (undefined1 *)FUN_00663ce0(*puVar4);
                *puVar7 = 1;
                puVar7  = (undefined1 *)FUN_00663ce0(local_1c);
                *puVar7 = 0;
                FUN_00663ff0(local_1c);
                piVar5   = (int *)FUN_00654020(local_20);
                local_1c = (_Container_proxy *)*piVar5;
            }
            puVar7  = (undefined1 *)FUN_00663ce0(local_20);
            puVar8  = (undefined1 *)FUN_00663ce0(local_1c);
            *puVar8 = *puVar7;
            puVar7  = (undefined1 *)FUN_00663ce0(local_20);
            *puVar7 = 1;
            puVar4  = (undefined4 *)FUN_00654020(local_1c);
            puVar7  = (undefined1 *)FUN_00663ce0(*puVar4);
            *puVar7 = 1;
            FUN_00663ec0(local_20);
        LAB_006649d9:
            puVar7  = (undefined1 *)FUN_00663ce0(local_18);
            *puVar7 = 1;
            goto LAB_006649e8;
        }
    }
    else
    {
        piVar5   = (int *)FUN_00663590(local_20);
        local_1c = (_Container_proxy *)*piVar5;
        pcVar3   = (char *)FUN_00663ce0(local_1c);
        if (*pcVar3 == '\0')
        {
            puVar7  = (undefined1 *)FUN_00663ce0(local_1c);
            *puVar7 = 1;
            puVar7  = (undefined1 *)FUN_00663ce0(local_20);
            *puVar7 = 0;
            FUN_00663ff0(local_20);
            piVar5   = (int *)FUN_00663590(local_20);
            local_1c = (_Container_proxy *)*piVar5;
        }
        pcVar3 = (char *)FUN_00663560(local_1c);
        if (*pcVar3 == '\0')
        {
            puVar4 = (undefined4 *)FUN_00654020(local_1c);
            pcVar3 = (char *)FUN_00663ce0(*puVar4);
            if (*pcVar3 == '\x01')
            {
                puVar4 = (undefined4 *)FUN_00663590(local_1c);
                pcVar3 = (char *)FUN_00663ce0(*puVar4);
                if (*pcVar3 == '\x01')
                {
                    puVar7   = (undefined1 *)FUN_00663ce0(local_1c);
                    *puVar7  = 0;
                    local_18 = local_20;
                    p_Var1   = local_18;
                    goto LAB_0066465b;
                }
            }
            puVar4 = (undefined4 *)FUN_00663590(local_1c);
            pcVar3 = (char *)FUN_00663ce0(*puVar4);
            if (*pcVar3 == '\x01')
            {
                puVar4  = (undefined4 *)FUN_00654020(local_1c);
                puVar7  = (undefined1 *)FUN_00663ce0(*puVar4);
                *puVar7 = 1;
                puVar7  = (undefined1 *)FUN_00663ce0(local_1c);
                *puVar7 = 0;
                FUN_00663ec0(local_1c);
                piVar5   = (int *)FUN_00663590(local_20);
                local_1c = (_Container_proxy *)*piVar5;
            }
            puVar7  = (undefined1 *)FUN_00663ce0(local_20);
            puVar8  = (undefined1 *)FUN_00663ce0(local_1c);
            *puVar8 = *puVar7;
            puVar7  = (undefined1 *)FUN_00663ce0(local_20);
            *puVar7 = 1;
            puVar4  = (undefined4 *)FUN_00663590(local_1c);
            puVar7  = (undefined1 *)FUN_00663ce0(*puVar4);
            *puVar7 = 1;
            FUN_00663ff0(local_20);
            goto LAB_006649d9;
        }
        p_Var1 = local_20;
    }
LAB_0066465b:
    local_18 = p_Var1;
    local_20 = local_18;
    piVar5   = (int *)FUN_00653df0(local_18);
    local_20 = (_Container_proxy *)*piVar5;
    goto LAB_0066466c;
}
