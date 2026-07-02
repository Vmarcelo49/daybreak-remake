// ============================================
// Address:  0x00656c80
// Original: FUN_00656c80
// Status:   unreviewed
// ============================================

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __thiscall FUN_00656c80(int *param_1, char *param_2, undefined4 *param_3)

{
    char cVar1;
    size_t sVar2;
    int iVar3;
    undefined1 local_2b0[4];
    undefined4 local_2ac;
    int local_2a8;
    int local_2a4;
    int local_2a0;
    int local_29c;
    int local_298;
    int local_294;
    char local_290[4];
    uint local_28c[20];
    undefined1 auStack_23c[4];
    undefined1 local_238[268];
    uint local_12c;
    uint local_128;
    char local_121;
    CHAR local_120[264];
    undefined4 local_18;
    int local_14;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069ee06;
    local_10      = ExceptionList;
    local_18      = DAT_006b77f4;
    local_298     = -0x7789f794;
    ExceptionList = &local_10;
    _eh_vector_constructor_iterator_(
        local_290, 0x1c, 3, FUN_00664f40, Concurrency::details::TaskStack::~TaskStack);
    local_8 = 0;
    FUN_0066b860(local_238, param_2);
    sVar2              = _strlen(param_2);
    auStack_23c[sVar2] = 0;
    local_29c          = 1;
    for (local_2a0 = *param_1; -1 < local_2a0; local_2a0 = local_2a0 + -1)
    {
        if (local_2a0 == 0)
        {
            FUN_0066b860(local_120, param_2);
        }
        else
        {
            wsprintfA(local_120, "%s_%d.bmp", local_238, local_2a0);
        }
        cVar1 = FUN_00661d10(local_120, local_290);
        iVar3 = local_298;
        if (cVar1 != '\0')
            break;
        if (local_2a0 == 0)
        {
            local_8 = 0xffffffff;
            _eh_vector_destructor_iterator_(
                local_290, 0x1c, 3, Concurrency::details::TaskStack::~TaskStack);
            ExceptionList = local_10;
            return iVar3;
        }
    }
    local_121 = '\x01' - (local_2a0 != *param_1);
    local_12c = local_28c[0];
    local_128 = local_28c[1];
    local_14  = 0;
    local_294 = 0;
    if (1 < local_28c[0])
    {
        for (local_12c = local_28c[0] - 1; local_12c != 1; local_12c = local_12c >> 1)
        {
            local_14 = local_14 + 1;
        }
        local_12c = 2 << ((byte)local_14 & 0x1f);
    }
    if (1 < local_28c[1])
    {
        for (local_128 = local_28c[1] - 1; local_128 != 1; local_128 = local_128 >> 1)
        {
            local_294 = local_294 + 1;
        }
        local_128 = 2 << ((byte)local_294 & 0x1f);
    }
    if (local_121 != '\0')
    {
        for (local_2a4 = 1; local_2a4 < 3; local_2a4 = local_2a4 + 1)
        {
            wsprintfA(local_120, "%s_%d.bmp", local_238, local_2a4 + *param_1);
            cVar1 = FUN_00661d10(local_120, local_290 + local_2a4 * 0x1c);
            if (cVar1 == '\0')
                break;
            local_29c = local_29c + 1;
        }
    }
    FUN_0065d670();
    if ((local_290[0] == ' ') || (local_290[0] == '\x18'))
    {
        local_298 =
            D3DXCreateTexture(DAT_006d16f8, local_12c, local_128, local_29c, 0, 0x15, 1, param_3);
    }
    else if ((local_290[0] == '\b') || (local_290[0] == '\x10'))
    {
        local_298 =
            D3DXCreateTexture(DAT_006d16f8, local_12c, local_128, local_29c, 0, 0x19, 1, param_3);
    }
    FUN_0065d6a0();
    iVar3 = local_298;
    if (local_298 < 0)
    {
        local_8 = 0xffffffff;
        _eh_vector_destructor_iterator_(
            local_290, 0x1c, 3, Concurrency::details::TaskStack::~TaskStack);
    }
    else
    {
        for (local_2a8 = 0;
             (iVar3 = local_298,
             local_2a8 < local_29c && ((local_28c[local_2a8 * 7] == local_12c || (local_2a8 < 1))));
             local_2a8 = local_2a8 + 1)
        {
            FUN_0065d670();
            local_298 =
                (**(code **)(*(int *)*param_3 + 0x4c))(*param_3, local_2a8, local_2b0, 0, 0);
            if (local_298 == 0)
            {
                FUN_00666750(local_2ac, local_290[local_2a8 * 0x1c], local_12c);
                (**(code **)(*(int *)*param_3 + 0x50))(*param_3, 0);
            }
            FUN_0065d6a0();
            local_12c = local_12c >> 1;
        }
        local_8 = 0xffffffff;
        _eh_vector_destructor_iterator_(
            local_290, 0x1c, 3, Concurrency::details::TaskStack::~TaskStack);
    }
    ExceptionList = local_10;
    return iVar3;
}
