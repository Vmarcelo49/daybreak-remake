// Function: FUN_00674d58
// Address:  0x00674d58
// Source:   batch_decompile (mass dump)
// Hash:     42b6fb6c0048c837


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */

DWORD FUN_00674d58(uint param_1)

{
  HANDLE hFile;
  BOOL BVar1;
  DWORD *pDVar2;
  undefined4 *puVar3;
  int iVar4;
  DWORD local_20;
  
  if (DAT_006d8bc8 <= param_1) {
LAB_00674e00:
    puVar3 = (undefined4 *)FUN_0066ef57();
    *puVar3 = 9;
    return 0xffffffff;
  }
  iVar4 = (param_1 & 0x1f) * 0x24;
  if ((*(byte *)((&DAT_006d8be0)[(int)param_1 >> 5] + 4 + iVar4) & 1) == 0) goto LAB_00674e00;
  __lock_fhandle(param_1);
  if ((*(byte *)((&DAT_006d8be0)[(int)param_1 >> 5] + 4 + iVar4) & 1) != 0) {
    hFile = (HANDLE)__get_osfhandle(param_1);
    BVar1 = FlushFileBuffers(hFile);
    if (BVar1 == 0) {
      local_20 = GetLastError();
    }
    else {
      local_20 = 0;
    }
    if (local_20 == 0) goto LAB_00674de7;
    pDVar2 = (DWORD *)FUN_0066ef60();
    *pDVar2 = local_20;
  }
  puVar3 = (undefined4 *)FUN_0066ef57();
  *puVar3 = 9;
  local_20 = 0xffffffff;
LAB_00674de7:
  FUN_00674df8();
  return local_20;
}

