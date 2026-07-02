// ============================================
// Address:  0x00671df4
// Original: ___updatetmbcinfo
// Status:   unreviewed
// ============================================

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    ___updatetmbcinfo

   Library: Visual Studio 2003 Release */

pthreadmbcinfo __cdecl ___updatetmbcinfo(void)

{
    _ptiddata p_Var1;
    pthreadmbcinfo _Memory;

    __lock(0xd);
    p_Var1  = __getptd();
    _Memory = p_Var1->_tpxcptinfoptrs;
    if (_Memory != DAT_006d898c)
    {
        if ((_Memory != (pthreadmbcinfo)0x0) &&
            (_Memory->refcount = _Memory->refcount + -1, _Memory->refcount == 0))
        {
            _free(_Memory);
        }
        p_Var1->_tpxcptinfoptrs = DAT_006d898c;
        _Memory                 = DAT_006d898c;
        DAT_006d898c->refcount  = DAT_006d898c->refcount + 1;
    }
    FUN_00671e5a();
    return _Memory;
}
