// Function: FUN_006872a0
// Address:  0x006872a0
// Source:   batch_decompile (mass dump)
// Hash:     e89c463ee68dca37


HRESULT FUN_006872a0(LPUNKNOWN param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  HRESULT HVar1;
  int *local_c;
  int *local_8;
  
  *param_4 = 0;
  HVar1 = CoCreateInstance((IID *)&DAT_006ad1b4,param_1,1,(IID *)&DAT_006ad9a8,&local_c);
  if (-1 < HVar1) {
    HVar1 = (**(code **)*local_c)(local_c,&DAT_006acf74,&local_8);
    if (HVar1 < 0) {
      (**(code **)(*local_c + 8))(local_c);
    }
    else {
      HVar1 = (**(code **)(*local_8 + 0xc))(local_8,param_2,param_3);
      (**(code **)(*local_8 + 8))(local_8);
      if (HVar1 < 0) {
        (**(code **)(*local_c + 8))(local_c);
      }
      else {
        *param_4 = local_c;
        HVar1 = 0;
      }
    }
  }
  return HVar1;
}

