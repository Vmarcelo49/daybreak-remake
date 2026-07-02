// ============================================
// Address:  0x00686ca0
// Original: FUN_00686ca0
// Status:   unreviewed
// ============================================

LPVOID __thiscall FUN_00686ca0(int param_1, uint param_2)

{
    LPVOID _Dst;
    undefined4 local_10;

    if (*(uint *)(param_1 + 0x40) == param_2)
    {
        _Dst = *(LPVOID *)(param_1 + 0x44);
    }
    else
    {
        _Dst = CoTaskMemAlloc(param_2);
        if (_Dst == (LPVOID)0x0)
        {
            if (*(uint *)(param_1 + 0x40) < param_2)
            {
                _Dst = (LPVOID)0x0;
            }
            else
            {
                _Dst = *(LPVOID *)(param_1 + 0x44);
            }
        }
        else
        {
            if (*(int *)(param_1 + 0x40) != 0)
            {
                if (param_2 < *(uint *)(param_1 + 0x40))
                {
                    local_10 = param_2;
                }
                else
                {
                    local_10 = *(size_t *)(param_1 + 0x40);
                }
                _memcpy(_Dst, *(void **)(param_1 + 0x44), local_10);
                CoTaskMemFree(*(LPVOID *)(param_1 + 0x44));
            }
            *(uint *)(param_1 + 0x40)   = param_2;
            *(LPVOID *)(param_1 + 0x44) = _Dst;
        }
    }
    return _Dst;
}
