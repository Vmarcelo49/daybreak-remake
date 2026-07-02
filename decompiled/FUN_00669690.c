// Function: FUN_00669690
// Address:  0x00669690
// Source:   batch_decompile (mass dump)
// Hash:     543e143ba4d1691f


undefined4 FUN_00669690(LPSTR param_1,int *param_2,short *param_3,uint *param_4)

{
  HMMIO hmmio;
  undefined4 uVar1;
  MMRESULT MVar2;
  LONG LVar3;
  void *pvVar4;
  uint uVar5;
  _MMCKINFO local_2c;
  _MMCKINFO local_18;
  
  local_2c.ckid = 0;
  local_2c.cksize = 0;
  local_2c.fccType = 0;
  local_2c.dwDataOffset = 0;
  local_2c.dwFlags = 0;
  local_18.ckid = 0;
  local_18.cksize = 0;
  local_18.fccType = 0;
  local_18.dwDataOffset = 0;
  local_18.dwFlags = 0;
  hmmio = mmioOpenA(param_1,(LPMMIOINFO)0x0,0x10000);
  if (hmmio == (HMMIO)0x0) {
    uVar1 = 0;
  }
  else {
    local_2c.fccType = 0x45564157;
    MVar2 = mmioDescend(hmmio,&local_2c,(MMCKINFO *)0x0,0x20);
    if (MVar2 == 0) {
      local_18.ckid = 0x20746d66;
      MVar2 = mmioDescend(hmmio,&local_18,&local_2c,0);
      if (MVar2 == 0) {
        LVar3 = mmioRead(hmmio,(HPSTR)param_3,0x12);
        if (LVar3 == 0x12) {
          if (*param_3 == 1) {
            MVar2 = mmioAscend(hmmio,&local_18,0);
            if (MVar2 == 0) {
              local_18.ckid = 0x61746164;
              MVar2 = mmioDescend(hmmio,&local_18,&local_2c,0x10);
              if (MVar2 == 0) {
                if (*param_2 != 0) {
                  _free((void *)*param_2);
                }
                if (local_18.cksize == 0) {
                  *param_2 = 0;
                  uVar1 = 0;
                }
                else {
                  pvVar4 = operator_new(local_18.cksize);
                  *param_2 = (int)pvVar4;
                  uVar5 = mmioRead(hmmio,(HPSTR)*param_2,local_18.cksize);
                  if (uVar5 == local_18.cksize) {
                    mmioClose(hmmio,0);
                    *param_4 = local_18.cksize;
                    uVar1 = 1;
                  }
                  else {
                    mmioClose(hmmio,0);
                    _free((void *)*param_2);
                    *param_2 = 0;
                    *param_4 = 0;
                    uVar1 = 0;
                  }
                }
              }
              else {
                mmioClose(hmmio,0);
                uVar1 = 0;
              }
            }
            else {
              mmioClose(hmmio,0);
              uVar1 = 0;
            }
          }
          else {
            mmioClose(hmmio,0);
            uVar1 = 0;
          }
        }
        else {
          mmioClose(hmmio,0);
          uVar1 = 0;
        }
      }
      else {
        mmioClose(hmmio,0);
        uVar1 = 0;
      }
    }
    else {
      mmioClose(hmmio,0);
      uVar1 = 0;
    }
  }
  return uVar1;
}

