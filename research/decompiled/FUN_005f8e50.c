// Function: FUN_005f8e50
// Address:  0x005f8e50
// Source:   batch_decompile (mass dump)
// Hash:     9cb6819af6436c68


CPropertySection * __thiscall FUN_005f8e50(CPropertySection *param_1,uint param_2)

{
  if ((param_2 & 2) == 0) {
    CPropertySection::~CPropertySection(param_1);
    if ((param_2 & 1) != 0) {
      _free(param_1);
    }
  }
  else {
    _eh_vector_destructor_iterator_
              (param_1,0x9c,*(int *)(param_1 + -4),CPropertySection::~CPropertySection);
    if ((param_2 & 1) != 0) {
      _free(param_1 + -4);
    }
    param_1 = param_1 + -4;
  }
  return param_1;
}

