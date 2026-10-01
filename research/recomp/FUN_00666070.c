// ============================================
// Address:  0x00666070
// Original: FUN_00666070
// Status:   unreviewed
// ============================================

void __thiscall FUN_00666070(byte *param_1, LPCSTR param_2)

{
    DWORD local_c;
    HANDLE local_8;

    local_8 = CreateFileA(param_2, 0x40000000, 0, (LPSECURITY_ATTRIBUTES)0x0, 4, 0x80, (HANDLE)0x0);
    if (local_8 != (HANDLE)0xffffffff)
    {
        WriteFile(local_8, param_1, 1, &local_c, (LPOVERLAPPED)0x0);
        WriteFile(local_8, param_1 + 4, 4, &local_c, (LPOVERLAPPED)0x0);
        WriteFile(local_8, param_1 + 8, 4, &local_c, (LPOVERLAPPED)0x0);
        WriteFile(local_8, param_1 + 0xc, 4, &local_c, (LPOVERLAPPED)0x0);
        WriteFile(local_8, param_1 + 0x10, 4, &local_c, (LPOVERLAPPED)0x0);
        if (*(int *)(param_1 + 0x10) == 0)
        {
            if (*param_1 < 0x18)
            {
                WriteFile(local_8,
                          *(LPCVOID *)(param_1 + 0x18),
                          *(int *)(param_1 + 0xc) * *(int *)(param_1 + 8) * (uint)*param_1 >> 3,
                          &local_c,
                          (LPOVERLAPPED)0x0);
            }
            else
            {
                WriteFile(local_8,
                          *(LPCVOID *)(param_1 + 0x18),
                          *(int *)(param_1 + 0xc) * *(int *)(param_1 + 8) * 4,
                          &local_c,
                          (LPOVERLAPPED)0x0);
            }
        }
        else
        {
            WriteFile(local_8,
                      *(LPCVOID *)(param_1 + 0x18),
                      *(DWORD *)(param_1 + 0x10),
                      &local_c,
                      (LPOVERLAPPED)0x0);
        }
        CloseHandle(local_8);
    }
    return;
}
