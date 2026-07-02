// Function: FUN_00402010
// Address:  0x00402010
// Source:   batch_decompile (mass dump)
// Hash:     7398ceb375d555a5


CPropertySection * __thiscall FUN_00402010(CPropertySection *param_1,uint param_2)

{
  CPropertySection::~CPropertySection(param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

