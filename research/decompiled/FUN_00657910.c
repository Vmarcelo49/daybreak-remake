// Function: FUN_00657910
// Address:  0x00657910
// Source:   batch_decompile (mass dump)
// Hash:     5e60176b67459ec3


undefined4 __thiscall FUN_00657910(undefined4 *param_1,undefined4 *param_2)

{
  char cVar1;
  DWORD DVar2;
  HRESULT HVar3;
  HANDLE pvVar4;
  undefined4 uVar5;
  
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[0xe] = param_2[2];
  timeBeginPeriod(1);
  DVar2 = timeGetTime();
  FUN_0065d0c0(DVar2);
  HVar3 = CoInitialize((LPVOID)0x0);
  if (HVar3 < 0) {
    uVar5 = 0;
  }
  else {
    FUN_00655450(*param_1,param_1[1]);
    cVar1 = FUN_00654b90(*param_1,param_2[3],param_2[4],*(undefined1 *)(param_2 + 5));
    if (cVar1 == '\0') {
      uVar5 = 0;
    }
    else {
      cVar1 = FUN_0064ff30();
      if (cVar1 == '\0') {
        uVar5 = 0;
      }
      else {
        cVar1 = FUN_00658260(*param_1,param_1[1]);
        if (cVar1 == '\0') {
          uVar5 = 0;
        }
        else {
          cVar1 = FUN_00658410();
          if (cVar1 == '\0') {
            uVar5 = 0;
          }
          else {
            cVar1 = FUN_00658550();
            if (cVar1 == '\0') {
              uVar5 = 0;
            }
            else {
              cVar1 = FUN_00661ad0(*param_1,param_2[6]);
              if (cVar1 == '\0') {
                uVar5 = 0;
              }
              else {
                *(undefined1 *)(param_1 + 0x17) = *(undefined1 *)(param_2 + 5);
                if (*(char *)(param_1 + 0x17) == '\0') {
                  *(undefined1 *)(param_1 + 7) = 1;
                  pvVar4 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
                  param_1[0xd] = pvVar4;
                  pvVar4 = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,FUN_006580a0,(LPVOID)0x0,0,
                                        param_1 + 10);
                  param_1[8] = pvVar4;
                  SetThreadPriority((HANDLE)param_1[8],-0xf);
                }
                uVar5 = FUN_00667050();
                param_1[0xc] = uVar5;
                DVar2 = timeGetTime();
                param_1[4] = DVar2;
                (*(code *)**(undefined4 **)param_1[0xe])();
                FUN_00650d50(0xff000000);
                FUN_00657c80(param_2[7]);
                param_1[0x1b] = param_2[7];
                uVar5 = 1;
              }
            }
          }
        }
      }
    }
  }
  return uVar5;
}

