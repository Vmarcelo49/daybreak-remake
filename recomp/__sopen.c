// ============================================
// Address:  0x00675460
// Original: __sopen
// Status:   unreviewed
// ============================================

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __sopen

   Library: Visual Studio 2003 Release */

int __cdecl __sopen(char *_Filename, int _OpenFlag, int _ShareFlag, ...)

{
    int iVar1;
    undefined4 in_stack_00000010;
    undefined1 local_24[4];
    undefined4 local_20[5];
    undefined4 uStack_c;
    undefined4 local_8;

    uStack_c    = 0x67546c;
    local_20[0] = 0;
    local_8     = 0;
    iVar1       = __tsopen_lk(local_20, local_24, _Filename, _OpenFlag, in_stack_00000010);
    local_8     = 0xffffffff;
    FUN_006754a5();
    return iVar1;
}
