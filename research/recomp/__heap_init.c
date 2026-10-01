// ============================================
// Address:  0x00671bbf
// Original: __heap_init
// Status:   unreviewed
// ============================================

/* Library Function - Single Match
    __heap_init

   Library: Visual Studio 2003 Release */

int __cdecl __heap_init(void)

{
    int iVar1;
    int in_stack_00000004;

    DAT_006d8bc0 = HeapCreate((uint)(in_stack_00000004 == 0), 0x1000, 0);
    if (DAT_006d8bc0 == (HANDLE)0x0)
    {
        return 0;
    }
    DAT_006d8bc4 = ___heap_select();
    if ((DAT_006d8bc4 == 3) && (iVar1 = ___sbh_heap_init(0x3f8), iVar1 == 0))
    {
        HeapDestroy(DAT_006d8bc0);
        return 0;
    }
    return 1;
}
