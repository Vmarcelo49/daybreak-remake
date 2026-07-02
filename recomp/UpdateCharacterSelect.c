// ============================================
// Address:  0x00406850
// Original:
// Name:     UpdateCharacterSelect (status: reviewed)
// ============================================

UpdateCharacterSelectvoidUpdateCharacterSelect UpdateCharacterSelect__thiscallUpdateCharacterSelect
UpdateCharacterSelectFUN_00406850UpdateCharacterSelect(
    UpdateCharacterSelectintUpdateCharacterSelect UpdateCharacterSelectparam_1UpdateCharacterSelect,
    UpdateCharacterSelectintUpdateCharacterSelect UpdateCharacterSelectparam_2UpdateCharacterSelect)

{
    UpdateCharacterSelectintUpdateCharacterSelect UpdateCharacterSelectiVar1UpdateCharacterSelect;
    UpdateCharacterSelectundefined4UpdateCharacterSelect
        UpdateCharacterSelectuVar2UpdateCharacterSelect;
    UpdateCharacterSelectundefined4UpdateCharacterSelect
        *UpdateCharacterSelectpuVar3UpdateCharacterSelect;
    UpdateCharacterSelectuintUpdateCharacterSelect UpdateCharacterSelectuVar4UpdateCharacterSelect;
    UpdateCharacterSelectundefined1UpdateCharacterSelect
        UpdateCharacterSelectlocal_14UpdateCharacterSelect
            [UpdateCharacterSelect4UpdateCharacterSelect];
    UpdateCharacterSelectintUpdateCharacterSelect
        UpdateCharacterSelectlocal_10UpdateCharacterSelect;
    UpdateCharacterSelectintUpdateCharacterSelect
        *UpdateCharacterSelectlocal_cUpdateCharacterSelect;
    UpdateCharacterSelectcharUpdateCharacterSelect
        UpdateCharacterSelectlocal_5UpdateCharacterSelect;

    UpdateCharacterSelectFUN_00657390UpdateCharacterSelect();
    UpdateCharacterSelectlocal_cUpdateCharacterSelect =
        &UpdateCharacterSelectDAT_006cae94UpdateCharacterSelect +
        UpdateCharacterSelectparam_2UpdateCharacterSelect *
            UpdateCharacterSelect0x19UpdateCharacterSelect;
    UpdateCharacterSelectifUpdateCharacterSelect(
        (*(UpdateCharacterSelectintUpdateCharacterSelect
               *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                  UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                  UpdateCharacterSelectparam_2UpdateCharacterSelect *
                      UpdateCharacterSelect4UpdateCharacterSelect) <
         UpdateCharacterSelect0UpdateCharacterSelect) &&
        (((*UpdateCharacterSelectlocal_cUpdateCharacterSelect !=
               UpdateCharacterSelect0UpdateCharacterSelect ||
           ((&UpdateCharacterSelectDAT_006cae98UpdateCharacterSelect)
                [UpdateCharacterSelectparam_2UpdateCharacterSelect *
                 UpdateCharacterSelect0x19UpdateCharacterSelect] !=
            UpdateCharacterSelect0UpdateCharacterSelect)) ||
          ((&UpdateCharacterSelectDAT_006cae9cUpdateCharacterSelect)
               [UpdateCharacterSelectparam_2UpdateCharacterSelect *
                UpdateCharacterSelect0x19UpdateCharacterSelect] !=
           UpdateCharacterSelect0UpdateCharacterSelect))))
    {
        *(UpdateCharacterSelectintUpdateCharacterSelect
              *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                 UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                 UpdateCharacterSelectparam_2UpdateCharacterSelect *
                     UpdateCharacterSelect4UpdateCharacterSelect) =
            UpdateCharacterSelectparam_2UpdateCharacterSelect;
    }
    UpdateCharacterSelectlocal_5UpdateCharacterSelect =
        *(UpdateCharacterSelectcharUpdateCharacterSelect
              *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                 UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                 UpdateCharacterSelectparam_2UpdateCharacterSelect *
                     UpdateCharacterSelect4UpdateCharacterSelect);
    UpdateCharacterSelectlocal_10UpdateCharacterSelect =
        *(UpdateCharacterSelectintUpdateCharacterSelect
              *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                 UpdateCharacterSelect0x2e98UpdateCharacterSelect +
                 UpdateCharacterSelectparam_2UpdateCharacterSelect *
                     UpdateCharacterSelect4UpdateCharacterSelect);
    UpdateCharacterSelectswitchUpdateCharacterSelect(
        *(UpdateCharacterSelectundefined4UpdateCharacterSelect
              *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                 UpdateCharacterSelect0x2e98UpdateCharacterSelect +
                 UpdateCharacterSelectparam_2UpdateCharacterSelect *
                     UpdateCharacterSelect4UpdateCharacterSelect))
    {
        UpdateCharacterSelectcaseUpdateCharacterSelect UpdateCharacterSelect0UpdateCharacterSelect
            : UpdateCharacterSelectifUpdateCharacterSelect(
                  (((&UpdateCharacterSelectDAT_006caea0UpdateCharacterSelect)
                        [UpdateCharacterSelectparam_2UpdateCharacterSelect *
                         UpdateCharacterSelect0x19UpdateCharacterSelect] ==
                    UpdateCharacterSelect1UpdateCharacterSelect) &&
                   (*(UpdateCharacterSelectintUpdateCharacterSelect
                          *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                             UpdateCharacterSelect0x2e98UpdateCharacterSelect) ==
                    UpdateCharacterSelect0UpdateCharacterSelect)) &&
                  (*(UpdateCharacterSelectintUpdateCharacterSelect
                         *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                            UpdateCharacterSelect0x2e9cUpdateCharacterSelect) ==
                   UpdateCharacterSelect0UpdateCharacterSelect))
        {
            UpdateCharacterSelectFUN_0064aed0UpdateCharacterSelect(
                UpdateCharacterSelect1UpdateCharacterSelect);
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e18UpdateCharacterSelect) =
                UpdateCharacterSelect0UpdateCharacterSelect;
            UpdateCharacterSelectreturnUpdateCharacterSelect;
        }
        UpdateCharacterSelectiVar1UpdateCharacterSelect =
            UpdateCharacterSelectFUN_00403aa0UpdateCharacterSelect(
                (&UpdateCharacterSelectDAT_006cae98UpdateCharacterSelect)
                    [UpdateCharacterSelectparam_2UpdateCharacterSelect *
                     UpdateCharacterSelect0x19UpdateCharacterSelect]);
        UpdateCharacterSelectifUpdateCharacterSelect(
            UpdateCharacterSelectiVar1UpdateCharacterSelect ==
            UpdateCharacterSelect1UpdateCharacterSelect)
        {
            UpdateCharacterSelectifUpdateCharacterSelect(
                UpdateCharacterSelectlocal_cUpdateCharacterSelect
                    [UpdateCharacterSelect1UpdateCharacterSelect] <
                UpdateCharacterSelect1UpdateCharacterSelect)
            {
                UpdateCharacterSelectifUpdateCharacterSelect(
                    *(UpdateCharacterSelectintUpdateCharacterSelect
                          *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                             UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                             UpdateCharacterSelectparam_2UpdateCharacterSelect *
                                 UpdateCharacterSelect4UpdateCharacterSelect) ==
                    UpdateCharacterSelect0UpdateCharacterSelect)
                {
                    *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                          *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                             UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                             UpdateCharacterSelectparam_2UpdateCharacterSelect *
                                 UpdateCharacterSelect4UpdateCharacterSelect) =
                        UpdateCharacterSelect2UpdateCharacterSelect;
                }
                UpdateCharacterSelectelseUpdateCharacterSelect
                    UpdateCharacterSelectifUpdateCharacterSelect(
                        *(UpdateCharacterSelectintUpdateCharacterSelect
                              *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                                 UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                                 UpdateCharacterSelectparam_2UpdateCharacterSelect *
                                     UpdateCharacterSelect4UpdateCharacterSelect) <
                        UpdateCharacterSelect2UpdateCharacterSelect)
                {
                    *(UpdateCharacterSelectintUpdateCharacterSelect
                          *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                             UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                             UpdateCharacterSelectparam_2UpdateCharacterSelect *
                                 UpdateCharacterSelect4UpdateCharacterSelect) =
                        *(UpdateCharacterSelectintUpdateCharacterSelect
                              *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                                 UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                                 UpdateCharacterSelectparam_2UpdateCharacterSelect *
                                     UpdateCharacterSelect4UpdateCharacterSelect) +
                        -UpdateCharacterSelect1UpdateCharacterSelect;
                }
                UpdateCharacterSelectelseUpdateCharacterSelect
                {
                    *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                          *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                             UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                             UpdateCharacterSelectparam_2UpdateCharacterSelect *
                                 UpdateCharacterSelect4UpdateCharacterSelect) =
                        UpdateCharacterSelect1UpdateCharacterSelect;
                }
            }
            UpdateCharacterSelectelseUpdateCharacterSelect
                UpdateCharacterSelectifUpdateCharacterSelect(
                    *(UpdateCharacterSelectintUpdateCharacterSelect
                          *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                             UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                             UpdateCharacterSelectparam_2UpdateCharacterSelect *
                                 UpdateCharacterSelect4UpdateCharacterSelect) <
                    UpdateCharacterSelect2UpdateCharacterSelect)
            {
                *(UpdateCharacterSelectintUpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                         UpdateCharacterSelectparam_2UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) =
                    *(UpdateCharacterSelectintUpdateCharacterSelect
                          *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                             UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                             UpdateCharacterSelectparam_2UpdateCharacterSelect *
                                 UpdateCharacterSelect4UpdateCharacterSelect) +
                    UpdateCharacterSelect1UpdateCharacterSelect;
            }
            UpdateCharacterSelectelseUpdateCharacterSelect
            {
                *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                         UpdateCharacterSelectparam_2UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) =
                    UpdateCharacterSelect0UpdateCharacterSelect;
            }
            UpdateCharacterSelectFUN_0064aed0UpdateCharacterSelect(
                UpdateCharacterSelect2UpdateCharacterSelect);
        }
        UpdateCharacterSelectelseUpdateCharacterSelect
        {
            UpdateCharacterSelectiVar1UpdateCharacterSelect =
                UpdateCharacterSelectFUN_00403aa0UpdateCharacterSelect(
                    *UpdateCharacterSelectlocal_cUpdateCharacterSelect);
            UpdateCharacterSelectifUpdateCharacterSelect(
                UpdateCharacterSelectiVar1UpdateCharacterSelect ==
                UpdateCharacterSelect1UpdateCharacterSelect)
            {
                UpdateCharacterSelectifUpdateCharacterSelect(
                    *(UpdateCharacterSelectintUpdateCharacterSelect
                          *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                             UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                             UpdateCharacterSelectparam_2UpdateCharacterSelect *
                                 UpdateCharacterSelect4UpdateCharacterSelect) ==
                    UpdateCharacterSelect2UpdateCharacterSelect)
                {
                    *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                          *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                             UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                             UpdateCharacterSelectparam_2UpdateCharacterSelect *
                                 UpdateCharacterSelect4UpdateCharacterSelect) =
                        UpdateCharacterSelect3UpdateCharacterSelect;
                }
                UpdateCharacterSelectelseUpdateCharacterSelect
                    UpdateCharacterSelectifUpdateCharacterSelect(
                        *(UpdateCharacterSelectintUpdateCharacterSelect
                              *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                                 UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                                 UpdateCharacterSelectparam_2UpdateCharacterSelect *
                                     UpdateCharacterSelect4UpdateCharacterSelect) ==
                        UpdateCharacterSelect3UpdateCharacterSelect)
                {
                    *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                          *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                             UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                             UpdateCharacterSelectparam_2UpdateCharacterSelect *
                                 UpdateCharacterSelect4UpdateCharacterSelect) =
                        UpdateCharacterSelect2UpdateCharacterSelect;
                }
                UpdateCharacterSelectFUN_0064aed0UpdateCharacterSelect(
                    UpdateCharacterSelect2UpdateCharacterSelect);
            }
        }
        UpdateCharacterSelectifUpdateCharacterSelect(
            *(UpdateCharacterSelectintUpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                     UpdateCharacterSelectparam_2UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) <
            UpdateCharacterSelect2UpdateCharacterSelect)
        {
            UpdateCharacterSelectifUpdateCharacterSelect(
                ((UpdateCharacterSelectlocal_cUpdateCharacterSelect
                      [UpdateCharacterSelect3UpdateCharacterSelect] ==
                  UpdateCharacterSelect1UpdateCharacterSelect) &&
                 (*(UpdateCharacterSelectintUpdateCharacterSelect
                        *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                           UpdateCharacterSelect0x2e90UpdateCharacterSelect +
                           UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                               UpdateCharacterSelect4UpdateCharacterSelect) <
                  UpdateCharacterSelect0UpdateCharacterSelect)) &&
                ((*(UpdateCharacterSelectintUpdateCharacterSelect
                        *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                           UpdateCharacterSelect0x2e40UpdateCharacterSelect +
                           UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                               UpdateCharacterSelect4UpdateCharacterSelect) ==
                      UpdateCharacterSelectparam_2UpdateCharacterSelect ||
                  (*(UpdateCharacterSelectintUpdateCharacterSelect
                         *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                            UpdateCharacterSelect0x2e40UpdateCharacterSelect +
                            UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                                UpdateCharacterSelect4UpdateCharacterSelect) ==
                   UpdateCharacterSelect4UpdateCharacterSelect))))
            {
                UpdateCharacterSelectifUpdateCharacterSelect(
                    *(UpdateCharacterSelectintUpdateCharacterSelect
                          *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                             UpdateCharacterSelect0x2e40UpdateCharacterSelect +
                             UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                                 UpdateCharacterSelect4UpdateCharacterSelect) ==
                    UpdateCharacterSelectparam_2UpdateCharacterSelect)
                {
                    *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                          *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                             UpdateCharacterSelect0x2ea0UpdateCharacterSelect +
                             UpdateCharacterSelectparam_2UpdateCharacterSelect *
                                 UpdateCharacterSelect4UpdateCharacterSelect) =
                        UpdateCharacterSelect0xffffffffUpdateCharacterSelect;
                }
                *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2e40UpdateCharacterSelect +
                         UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) =
                    UpdateCharacterSelect0xffffffffUpdateCharacterSelect;
                (&UpdateCharacterSelectDAT_006cfb4cUpdateCharacterSelect)
                    [UpdateCharacterSelectlocal_5UpdateCharacterSelect] =
                        UpdateCharacterSelect0UpdateCharacterSelect;
                *(UpdateCharacterSelectundefined1UpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2ea8UpdateCharacterSelect +
                         (UpdateCharacterSelectintUpdateCharacterSelect)
                             UpdateCharacterSelectlocal_5UpdateCharacterSelect) =
                    UpdateCharacterSelect0UpdateCharacterSelect;
            }
            UpdateCharacterSelectelseUpdateCharacterSelect
                UpdateCharacterSelectifUpdateCharacterSelect(
                    ((UpdateCharacterSelectlocal_cUpdateCharacterSelect
                          [UpdateCharacterSelect2UpdateCharacterSelect] ==
                      UpdateCharacterSelect1UpdateCharacterSelect) &&
                     (*(UpdateCharacterSelectintUpdateCharacterSelect
                            *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                               UpdateCharacterSelect0x2e90UpdateCharacterSelect +
                               UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                                   UpdateCharacterSelect4UpdateCharacterSelect) <
                      UpdateCharacterSelect0UpdateCharacterSelect)) &&
                    (*(UpdateCharacterSelectintUpdateCharacterSelect
                           *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                              UpdateCharacterSelect0x2e40UpdateCharacterSelect +
                              UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                                  UpdateCharacterSelect4UpdateCharacterSelect) <
                     UpdateCharacterSelect0UpdateCharacterSelect))
            {
                UpdateCharacterSelectifUpdateCharacterSelect(
                    (UpdateCharacterSelectlocal_cUpdateCharacterSelect
                         [UpdateCharacterSelect5UpdateCharacterSelect] ==
                     UpdateCharacterSelect0UpdateCharacterSelect) ||
                    ('\UpdateCharacterSelectx05UpdateCharacterSelect' <
                     (UpdateCharacterSelectcharUpdateCharacterSelect)(&UpdateCharacterSelectDAT_006b710cUpdateCharacterSelect)
                         [*(UpdateCharacterSelectintUpdateCharacterSelect
                                *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                                   UpdateCharacterSelect0x2e20UpdateCharacterSelect) *
                              UpdateCharacterSelect2UpdateCharacterSelect +
                          UpdateCharacterSelectparam_2UpdateCharacterSelect]))
                {
                    (&UpdateCharacterSelectDAT_006cfb4cUpdateCharacterSelect)
                        [UpdateCharacterSelectlocal_5UpdateCharacterSelect] =
                            UpdateCharacterSelect0UpdateCharacterSelect;
                }
                UpdateCharacterSelectelseUpdateCharacterSelect
                {
                    (&UpdateCharacterSelectDAT_006cfb4cUpdateCharacterSelect)
                        [UpdateCharacterSelectlocal_5UpdateCharacterSelect] =
                            UpdateCharacterSelect1UpdateCharacterSelect;
                }
                UpdateCharacterSelectFUN_0064aed0UpdateCharacterSelect(
                    UpdateCharacterSelect0UpdateCharacterSelect);
                *(UpdateCharacterSelectundefined1UpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2ea8UpdateCharacterSelect +
                         (UpdateCharacterSelectintUpdateCharacterSelect)
                             UpdateCharacterSelectlocal_5UpdateCharacterSelect) =
                    UpdateCharacterSelect0UpdateCharacterSelect;
                *(UpdateCharacterSelectintUpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2e90UpdateCharacterSelect +
                         UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) =
                    UpdateCharacterSelectparam_2UpdateCharacterSelect;
                *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2e98UpdateCharacterSelect +
                         UpdateCharacterSelectparam_2UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) =
                    UpdateCharacterSelect3UpdateCharacterSelect;
                *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2e30UpdateCharacterSelect +
                         UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) =
                    UpdateCharacterSelect0UpdateCharacterSelect;
            }
        }
        UpdateCharacterSelectelseUpdateCharacterSelect UpdateCharacterSelectifUpdateCharacterSelect(
            UpdateCharacterSelectlocal_cUpdateCharacterSelect
                [UpdateCharacterSelect2UpdateCharacterSelect] ==
            UpdateCharacterSelect1UpdateCharacterSelect)
        {
            UpdateCharacterSelectifUpdateCharacterSelect(
                ((*(UpdateCharacterSelectintUpdateCharacterSelect
                        *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                           UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                           UpdateCharacterSelectparam_2UpdateCharacterSelect *
                               UpdateCharacterSelect4UpdateCharacterSelect) ==
                  UpdateCharacterSelect3UpdateCharacterSelect) &&
                 (*(UpdateCharacterSelectintUpdateCharacterSelect
                        *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                           UpdateCharacterSelect0x2e98UpdateCharacterSelect) ==
                  UpdateCharacterSelect0UpdateCharacterSelect)) &&
                (*(UpdateCharacterSelectintUpdateCharacterSelect
                       *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                          UpdateCharacterSelect0x2e9cUpdateCharacterSelect) ==
                 UpdateCharacterSelect0UpdateCharacterSelect))
            {
                UpdateCharacterSelectFUN_0064aed0UpdateCharacterSelect(
                    UpdateCharacterSelect1UpdateCharacterSelect);
                *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2e18UpdateCharacterSelect) =
                    UpdateCharacterSelect0UpdateCharacterSelect;
                UpdateCharacterSelectreturnUpdateCharacterSelect;
            }
            UpdateCharacterSelectifUpdateCharacterSelect(
                ((*(UpdateCharacterSelectintUpdateCharacterSelect
                        *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                           UpdateCharacterSelect0x2e28UpdateCharacterSelect +
                           UpdateCharacterSelectparam_2UpdateCharacterSelect *
                               UpdateCharacterSelect4UpdateCharacterSelect) ==
                  UpdateCharacterSelect2UpdateCharacterSelect) &&
                 (*(UpdateCharacterSelectintUpdateCharacterSelect
                        *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                           UpdateCharacterSelect0x2e98UpdateCharacterSelect) ==
                  UpdateCharacterSelect0UpdateCharacterSelect)) &&
                (*(UpdateCharacterSelectintUpdateCharacterSelect
                       *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                          UpdateCharacterSelect0x2e9cUpdateCharacterSelect) ==
                 UpdateCharacterSelect0UpdateCharacterSelect))
            {
                UpdateCharacterSelectFUN_0064aed0UpdateCharacterSelect(
                    UpdateCharacterSelect0UpdateCharacterSelect);
                *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2e18UpdateCharacterSelect) =
                    UpdateCharacterSelect2UpdateCharacterSelect;
                UpdateCharacterSelectreturnUpdateCharacterSelect;
            }
        }
        UpdateCharacterSelectbreakUpdateCharacterSelect;
        UpdateCharacterSelectcaseUpdateCharacterSelect UpdateCharacterSelect1UpdateCharacterSelect
            : UpdateCharacterSelectiVar1UpdateCharacterSelect =
                  UpdateCharacterSelectFUN_00403aa0UpdateCharacterSelect(
                      (&UpdateCharacterSelectDAT_006cae98UpdateCharacterSelect)
                          [UpdateCharacterSelectparam_2UpdateCharacterSelect *
                           UpdateCharacterSelect0x19UpdateCharacterSelect]);
        UpdateCharacterSelectifUpdateCharacterSelect(
            (UpdateCharacterSelectiVar1UpdateCharacterSelect ==
             UpdateCharacterSelect1UpdateCharacterSelect) &&
            (*(UpdateCharacterSelectintUpdateCharacterSelect
                   *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                      UpdateCharacterSelect0x2ea0UpdateCharacterSelect +
                      UpdateCharacterSelectparam_2UpdateCharacterSelect *
                          UpdateCharacterSelect4UpdateCharacterSelect) <
             UpdateCharacterSelect0UpdateCharacterSelect))
        {
            UpdateCharacterSelectFUN_0064aed0UpdateCharacterSelect(
                UpdateCharacterSelect2UpdateCharacterSelect);
            UpdateCharacterSelectuVar4UpdateCharacterSelect =
                *(UpdateCharacterSelectintUpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2e30UpdateCharacterSelect +
                         UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) +
                    UpdateCharacterSelect2UpdateCharacterSelect +
                    UpdateCharacterSelectlocal_cUpdateCharacterSelect
                        [UpdateCharacterSelect1UpdateCharacterSelect] &
                UpdateCharacterSelect0x80000001UpdateCharacterSelect;
            UpdateCharacterSelectifUpdateCharacterSelect(
                (UpdateCharacterSelectintUpdateCharacterSelect)
                    UpdateCharacterSelectuVar4UpdateCharacterSelect <
                UpdateCharacterSelect0UpdateCharacterSelect)
            {
                UpdateCharacterSelectuVar4UpdateCharacterSelect =
                    (UpdateCharacterSelectuVar4UpdateCharacterSelect -
                         UpdateCharacterSelect1UpdateCharacterSelect |
                     UpdateCharacterSelect0xfffffffeUpdateCharacterSelect) +
                    UpdateCharacterSelect1UpdateCharacterSelect;
            }
            *(UpdateCharacterSelectuintUpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e30UpdateCharacterSelect +
                     UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                UpdateCharacterSelectuVar4UpdateCharacterSelect;
        }
        UpdateCharacterSelectifUpdateCharacterSelect(
            UpdateCharacterSelectlocal_cUpdateCharacterSelect
                [UpdateCharacterSelect2UpdateCharacterSelect] ==
            UpdateCharacterSelect1UpdateCharacterSelect)
        {
            UpdateCharacterSelectFUN_0064aed0UpdateCharacterSelect(
                UpdateCharacterSelect0UpdateCharacterSelect);
            UpdateCharacterSelectifUpdateCharacterSelect(
                *(UpdateCharacterSelectintUpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2e30UpdateCharacterSelect +
                         UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) ==
                UpdateCharacterSelect0UpdateCharacterSelect)
            {
                *(UpdateCharacterSelectintUpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2ea0UpdateCharacterSelect +
                         UpdateCharacterSelectparam_2UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) =
                    (UpdateCharacterSelectintUpdateCharacterSelect)
                        UpdateCharacterSelectlocal_5UpdateCharacterSelect;
                *(UpdateCharacterSelectintUpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2e40UpdateCharacterSelect +
                         UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) =
                    UpdateCharacterSelectparam_2UpdateCharacterSelect;
            }
            UpdateCharacterSelectelseUpdateCharacterSelect
            {
                *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2e40UpdateCharacterSelect +
                         UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) =
                    UpdateCharacterSelect4UpdateCharacterSelect;
            }
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e98UpdateCharacterSelect +
                     UpdateCharacterSelectparam_2UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                UpdateCharacterSelect8UpdateCharacterSelect;
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2eacUpdateCharacterSelect +
                     UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                UpdateCharacterSelect0x40800000UpdateCharacterSelect;
            *(UpdateCharacterSelectundefined1UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2ea8UpdateCharacterSelect +
                     (UpdateCharacterSelectintUpdateCharacterSelect)
                         UpdateCharacterSelectlocal_5UpdateCharacterSelect) =
                UpdateCharacterSelect1UpdateCharacterSelect;
            UpdateCharacterSelectFUN_0065b1d0UpdateCharacterSelect(
                *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x1a4UpdateCharacterSelect));
            UpdateCharacterSelectuVar2UpdateCharacterSelect =
                UpdateCharacterSelectFUN_00649770UpdateCharacterSelect(
                    (UpdateCharacterSelectintUpdateCharacterSelect)(UpdateCharacterSelectcharUpdateCharacterSelect)(&UpdateCharacterSelectDAT_006b710cUpdateCharacterSelect)
                        [*(UpdateCharacterSelectintUpdateCharacterSelect
                               *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                                  UpdateCharacterSelect0x2e20UpdateCharacterSelect) *
                             UpdateCharacterSelect2UpdateCharacterSelect +
                         (UpdateCharacterSelectintUpdateCharacterSelect)
                             UpdateCharacterSelectlocal_5UpdateCharacterSelect]);
            UpdateCharacterSelectwsprintfAUpdateCharacterSelect(
                (UpdateCharacterSelectLPSTRUpdateCharacterSelect)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                                                                  UpdateCharacterSelect4UpdateCharacterSelect),
                "UpdateCharacterSelectdataUpdateCharacterSelect/"
                "UpdateCharacterSelectvoiceUpdateCharacterSelect/"
                "UpdateCharacterSelectentryUpdateCharacterSelect/"
                "%UpdateCharacterSelectsUpdateCharacterSelect."
                "UpdateCharacterSelectwavUpdateCharacterSelect",
                UpdateCharacterSelectuVar2UpdateCharacterSelect);
            UpdateCharacterSelectpuVar3UpdateCharacterSelect =
                (UpdateCharacterSelectundefined4UpdateCharacterSelect *)
                    UpdateCharacterSelectFUN_0065b0d0UpdateCharacterSelect(
                        UpdateCharacterSelectlocal_14UpdateCharacterSelect,
                        UpdateCharacterSelectparam_1UpdateCharacterSelect +
                            UpdateCharacterSelect4UpdateCharacterSelect);
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x1a4UpdateCharacterSelect) =
                *UpdateCharacterSelectpuVar3UpdateCharacterSelect;
            UpdateCharacterSelectFUN_0065b330UpdateCharacterSelect(
                *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x1a4UpdateCharacterSelect),
                UpdateCharacterSelect0UpdateCharacterSelect);
        }
        UpdateCharacterSelectelseUpdateCharacterSelect UpdateCharacterSelectifUpdateCharacterSelect(
            UpdateCharacterSelectlocal_cUpdateCharacterSelect
                [UpdateCharacterSelect3UpdateCharacterSelect] ==
            UpdateCharacterSelect1UpdateCharacterSelect)
        {
            UpdateCharacterSelectFUN_0064aed0UpdateCharacterSelect(
                UpdateCharacterSelect1UpdateCharacterSelect);
            UpdateCharacterSelectifUpdateCharacterSelect(
                *(UpdateCharacterSelectintUpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2ea0UpdateCharacterSelect +
                         UpdateCharacterSelectparam_2UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) ==
                (UpdateCharacterSelectintUpdateCharacterSelect)
                    UpdateCharacterSelectlocal_5UpdateCharacterSelect)
            {
                *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2ea0UpdateCharacterSelect +
                         UpdateCharacterSelectparam_2UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) =
                    UpdateCharacterSelect0xffffffffUpdateCharacterSelect;
            }
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e98UpdateCharacterSelect +
                     UpdateCharacterSelectparam_2UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                UpdateCharacterSelect4UpdateCharacterSelect;
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e30UpdateCharacterSelect +
                     UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2e70UpdateCharacterSelect +
                         UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect);
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e40UpdateCharacterSelect +
                     UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                UpdateCharacterSelect0xffffffffUpdateCharacterSelect;
        }
        UpdateCharacterSelectbreakUpdateCharacterSelect;
        UpdateCharacterSelectcaseUpdateCharacterSelect UpdateCharacterSelect3UpdateCharacterSelect
            : UpdateCharacterSelectiVar1UpdateCharacterSelect =
                  UpdateCharacterSelectFUN_00403aa0UpdateCharacterSelect(
                      (&UpdateCharacterSelectDAT_006cae98UpdateCharacterSelect)
                          [UpdateCharacterSelectparam_2UpdateCharacterSelect *
                           UpdateCharacterSelect0x19UpdateCharacterSelect]);
        UpdateCharacterSelectifUpdateCharacterSelect(
            UpdateCharacterSelectiVar1UpdateCharacterSelect ==
            UpdateCharacterSelect1UpdateCharacterSelect)
        {
            UpdateCharacterSelectFUN_0064aed0UpdateCharacterSelect(
                UpdateCharacterSelect2UpdateCharacterSelect);
            *(UpdateCharacterSelectintUpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e30UpdateCharacterSelect +
                     UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                (*(UpdateCharacterSelectintUpdateCharacterSelect
                       *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                          UpdateCharacterSelect0x2e30UpdateCharacterSelect +
                          UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                              UpdateCharacterSelect4UpdateCharacterSelect) +
                 UpdateCharacterSelect3UpdateCharacterSelect +
                 UpdateCharacterSelectlocal_cUpdateCharacterSelect
                     [UpdateCharacterSelect1UpdateCharacterSelect]) %
                UpdateCharacterSelect3UpdateCharacterSelect;
        }
        *(UpdateCharacterSelectundefined4UpdateCharacterSelect
              *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                 UpdateCharacterSelect0x2e60UpdateCharacterSelect +
                 UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                     UpdateCharacterSelect4UpdateCharacterSelect) =
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e30UpdateCharacterSelect +
                     UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect);
        UpdateCharacterSelectifUpdateCharacterSelect(
            UpdateCharacterSelectlocal_cUpdateCharacterSelect
                [UpdateCharacterSelect2UpdateCharacterSelect] ==
            UpdateCharacterSelect1UpdateCharacterSelect)
        {
            UpdateCharacterSelectFUN_0064aed0UpdateCharacterSelect(
                UpdateCharacterSelect0UpdateCharacterSelect);
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e98UpdateCharacterSelect +
                     UpdateCharacterSelectparam_2UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                UpdateCharacterSelect4UpdateCharacterSelect;
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e30UpdateCharacterSelect +
                     UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                UpdateCharacterSelect0UpdateCharacterSelect;
        }
        UpdateCharacterSelectelseUpdateCharacterSelect UpdateCharacterSelectifUpdateCharacterSelect(
            UpdateCharacterSelectlocal_cUpdateCharacterSelect
                [UpdateCharacterSelect3UpdateCharacterSelect] ==
            UpdateCharacterSelect1UpdateCharacterSelect)
        {
            UpdateCharacterSelectFUN_0064aed0UpdateCharacterSelect(
                UpdateCharacterSelect1UpdateCharacterSelect);
            UpdateCharacterSelectifUpdateCharacterSelect(
                *(UpdateCharacterSelectintUpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2ea0UpdateCharacterSelect +
                         UpdateCharacterSelectparam_2UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) ==
                (UpdateCharacterSelectintUpdateCharacterSelect)
                    UpdateCharacterSelectlocal_5UpdateCharacterSelect)
            {
                *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2ea0UpdateCharacterSelect +
                         UpdateCharacterSelectparam_2UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) =
                    UpdateCharacterSelect0xffffffffUpdateCharacterSelect;
            }
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e98UpdateCharacterSelect +
                     UpdateCharacterSelectparam_2UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                UpdateCharacterSelect0UpdateCharacterSelect;
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e40UpdateCharacterSelect +
                     UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                UpdateCharacterSelect0xffffffffUpdateCharacterSelect;
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e60UpdateCharacterSelect +
                     UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                UpdateCharacterSelect0xffffffffUpdateCharacterSelect;
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e90UpdateCharacterSelect +
                     UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                UpdateCharacterSelect0xffffffffUpdateCharacterSelect;
            (&UpdateCharacterSelectDAT_006cfb4cUpdateCharacterSelect)
                [UpdateCharacterSelectlocal_5UpdateCharacterSelect] =
                    UpdateCharacterSelect0UpdateCharacterSelect;
        }
        UpdateCharacterSelectbreakUpdateCharacterSelect;
        UpdateCharacterSelectcaseUpdateCharacterSelect UpdateCharacterSelect4UpdateCharacterSelect
            : UpdateCharacterSelectiVar1UpdateCharacterSelect =
                  UpdateCharacterSelectFUN_00403aa0UpdateCharacterSelect(
                      (&UpdateCharacterSelectDAT_006cae98UpdateCharacterSelect)
                          [UpdateCharacterSelectparam_2UpdateCharacterSelect *
                           UpdateCharacterSelect0x19UpdateCharacterSelect]);
        UpdateCharacterSelectifUpdateCharacterSelect(
            UpdateCharacterSelectiVar1UpdateCharacterSelect ==
            UpdateCharacterSelect1UpdateCharacterSelect)
        {
            UpdateCharacterSelectFUN_0064aed0UpdateCharacterSelect(
                UpdateCharacterSelect2UpdateCharacterSelect);
            *(UpdateCharacterSelectintUpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e30UpdateCharacterSelect +
                     UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                (*(UpdateCharacterSelectintUpdateCharacterSelect
                       *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                          UpdateCharacterSelect0x2e30UpdateCharacterSelect +
                          UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                              UpdateCharacterSelect4UpdateCharacterSelect) +
                 UpdateCharacterSelect3UpdateCharacterSelect +
                 UpdateCharacterSelectlocal_cUpdateCharacterSelect
                     [UpdateCharacterSelect1UpdateCharacterSelect]) %
                UpdateCharacterSelect3UpdateCharacterSelect;
        }
        *(UpdateCharacterSelectundefined4UpdateCharacterSelect
              *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                 UpdateCharacterSelect0x2e70UpdateCharacterSelect +
                 UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                     UpdateCharacterSelect4UpdateCharacterSelect) =
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e30UpdateCharacterSelect +
                     UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect);
        UpdateCharacterSelectifUpdateCharacterSelect(
            UpdateCharacterSelectlocal_cUpdateCharacterSelect
                [UpdateCharacterSelect2UpdateCharacterSelect] ==
            UpdateCharacterSelect1UpdateCharacterSelect)
        {
            UpdateCharacterSelectFUN_0064aed0UpdateCharacterSelect(
                UpdateCharacterSelect0UpdateCharacterSelect);
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e98UpdateCharacterSelect +
                     UpdateCharacterSelectparam_2UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                UpdateCharacterSelect1UpdateCharacterSelect;
            UpdateCharacterSelectifUpdateCharacterSelect(
                *(UpdateCharacterSelectintUpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2ea0UpdateCharacterSelect +
                         UpdateCharacterSelectparam_2UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) ==
                (UpdateCharacterSelectintUpdateCharacterSelect)
                    UpdateCharacterSelectlocal_5UpdateCharacterSelect)
            {
                *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2ea0UpdateCharacterSelect +
                         UpdateCharacterSelectparam_2UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) =
                    UpdateCharacterSelect0xffffffffUpdateCharacterSelect;
                *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2e30UpdateCharacterSelect +
                         UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) =
                    UpdateCharacterSelect0UpdateCharacterSelect;
            }
            UpdateCharacterSelectelseUpdateCharacterSelect
            {
                *(UpdateCharacterSelectuintUpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2e30UpdateCharacterSelect +
                         UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) =
                    (UpdateCharacterSelectuintUpdateCharacterSelect)(-UpdateCharacterSelect1UpdateCharacterSelect <
                                                                     *(UpdateCharacterSelectintUpdateCharacterSelect
                                                                           *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                                                                              UpdateCharacterSelect0x2ea0UpdateCharacterSelect +
                                                                              UpdateCharacterSelectparam_2UpdateCharacterSelect *
                                                                                  UpdateCharacterSelect4UpdateCharacterSelect));
            }
        }
        UpdateCharacterSelectelseUpdateCharacterSelect UpdateCharacterSelectifUpdateCharacterSelect(
            UpdateCharacterSelectlocal_cUpdateCharacterSelect
                [UpdateCharacterSelect3UpdateCharacterSelect] ==
            UpdateCharacterSelect1UpdateCharacterSelect)
        {
            UpdateCharacterSelectFUN_0064aed0UpdateCharacterSelect(
                UpdateCharacterSelect1UpdateCharacterSelect);
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e98UpdateCharacterSelect +
                     UpdateCharacterSelectparam_2UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                UpdateCharacterSelect3UpdateCharacterSelect;
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e30UpdateCharacterSelect +
                     UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2e60UpdateCharacterSelect +
                         UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect);
        }
        UpdateCharacterSelectbreakUpdateCharacterSelect;
        UpdateCharacterSelectcaseUpdateCharacterSelect UpdateCharacterSelect8UpdateCharacterSelect
            : UpdateCharacterSelectifUpdateCharacterSelect(
                  *(UpdateCharacterSelectfloatUpdateCharacterSelect
                        *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                           UpdateCharacterSelect0x2eacUpdateCharacterSelect +
                           UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                               UpdateCharacterSelect4UpdateCharacterSelect) <=
                  UpdateCharacterSelect1UpdateCharacterSelect
                      .UpdateCharacterSelect0UpdateCharacterSelect)
        {
            UpdateCharacterSelectFUN_0064aed0UpdateCharacterSelect(
                UpdateCharacterSelect3UpdateCharacterSelect);
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e98UpdateCharacterSelect +
                     UpdateCharacterSelectparam_2UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                UpdateCharacterSelect0UpdateCharacterSelect;
            *(UpdateCharacterSelectundefined4UpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e90UpdateCharacterSelect +
                     UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                UpdateCharacterSelect0xffffffffUpdateCharacterSelect;
        }
        UpdateCharacterSelectelseUpdateCharacterSelect
        {
            *(UpdateCharacterSelectfloatUpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2eacUpdateCharacterSelect +
                     UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                *(UpdateCharacterSelectfloatUpdateCharacterSelect
                      *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                         UpdateCharacterSelect0x2eacUpdateCharacterSelect +
                         UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                             UpdateCharacterSelect4UpdateCharacterSelect) -
                UpdateCharacterSelect0UpdateCharacterSelect
                    .UpdateCharacterSelect2UpdateCharacterSelect;
        }
    }
    UpdateCharacterSelectifUpdateCharacterSelect(
        ((*(UpdateCharacterSelectintUpdateCharacterSelect
                *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                   UpdateCharacterSelect0x2e98UpdateCharacterSelect +
                   UpdateCharacterSelectparam_2UpdateCharacterSelect *
                       UpdateCharacterSelect4UpdateCharacterSelect) ==
          UpdateCharacterSelect4UpdateCharacterSelect) ||
         (*(UpdateCharacterSelectintUpdateCharacterSelect
                *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                   UpdateCharacterSelect0x2e98UpdateCharacterSelect +
                   UpdateCharacterSelectparam_2UpdateCharacterSelect *
                       UpdateCharacterSelect4UpdateCharacterSelect) ==
          UpdateCharacterSelect3UpdateCharacterSelect)) ||
        (*(UpdateCharacterSelectintUpdateCharacterSelect
               *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                  UpdateCharacterSelect0x2e98UpdateCharacterSelect +
                  UpdateCharacterSelectparam_2UpdateCharacterSelect *
                      UpdateCharacterSelect4UpdateCharacterSelect) ==
         UpdateCharacterSelect1UpdateCharacterSelect))
    {
        UpdateCharacterSelectifUpdateCharacterSelect(
            *UpdateCharacterSelectlocal_cUpdateCharacterSelect ==
            UpdateCharacterSelect1UpdateCharacterSelect)
        {
            *(UpdateCharacterSelectintUpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e80UpdateCharacterSelect +
                     UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                (*(UpdateCharacterSelectintUpdateCharacterSelect
                       *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                          UpdateCharacterSelect0x2e80UpdateCharacterSelect +
                          UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                              UpdateCharacterSelect4UpdateCharacterSelect) +
                 UpdateCharacterSelect1UpdateCharacterSelect) %
                (UpdateCharacterSelectintUpdateCharacterSelect)(UpdateCharacterSelectcharUpdateCharacterSelect)(&UpdateCharacterSelectDAT_006b71c0UpdateCharacterSelect)
                    [(UpdateCharacterSelectcharUpdateCharacterSelect)(&UpdateCharacterSelectDAT_006b710cUpdateCharacterSelect)
                         [*(UpdateCharacterSelectintUpdateCharacterSelect
                                *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                                   UpdateCharacterSelect0x2e20UpdateCharacterSelect) *
                              UpdateCharacterSelect2UpdateCharacterSelect +
                          (UpdateCharacterSelectintUpdateCharacterSelect)
                              UpdateCharacterSelectlocal_5UpdateCharacterSelect]];
        }
        UpdateCharacterSelectelseUpdateCharacterSelect UpdateCharacterSelectifUpdateCharacterSelect(
            *UpdateCharacterSelectlocal_cUpdateCharacterSelect ==
            -UpdateCharacterSelect1UpdateCharacterSelect)
        {
            *(UpdateCharacterSelectintUpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2e80UpdateCharacterSelect +
                     UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) =
                (*(UpdateCharacterSelectintUpdateCharacterSelect
                       *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                          UpdateCharacterSelect0x2e80UpdateCharacterSelect +
                          UpdateCharacterSelectlocal_5UpdateCharacterSelect *
                              UpdateCharacterSelect4UpdateCharacterSelect) +
                 -UpdateCharacterSelect1UpdateCharacterSelect +
                 (UpdateCharacterSelectintUpdateCharacterSelect)(UpdateCharacterSelectcharUpdateCharacterSelect)(&UpdateCharacterSelectDAT_006b71c0UpdateCharacterSelect)
                     [(UpdateCharacterSelectcharUpdateCharacterSelect)(&UpdateCharacterSelectDAT_006b710cUpdateCharacterSelect)
                          [*(UpdateCharacterSelectintUpdateCharacterSelect
                                 *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                                    UpdateCharacterSelect0x2e20UpdateCharacterSelect) *
                               UpdateCharacterSelect2UpdateCharacterSelect +
                           (UpdateCharacterSelectintUpdateCharacterSelect)
                               UpdateCharacterSelectlocal_5UpdateCharacterSelect]]) %
                (UpdateCharacterSelectintUpdateCharacterSelect)(UpdateCharacterSelectcharUpdateCharacterSelect)(&UpdateCharacterSelectDAT_006b71c0UpdateCharacterSelect)
                    [(UpdateCharacterSelectcharUpdateCharacterSelect)(&UpdateCharacterSelectDAT_006b710cUpdateCharacterSelect)
                         [*(UpdateCharacterSelectintUpdateCharacterSelect
                                *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                                   UpdateCharacterSelect0x2e20UpdateCharacterSelect) *
                              UpdateCharacterSelect2UpdateCharacterSelect +
                          (UpdateCharacterSelectintUpdateCharacterSelect)
                              UpdateCharacterSelectlocal_5UpdateCharacterSelect]];
        }
    }
    UpdateCharacterSelectifUpdateCharacterSelect(
        *(UpdateCharacterSelectintUpdateCharacterSelect
              *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                 UpdateCharacterSelect0x2e98UpdateCharacterSelect +
                 UpdateCharacterSelectparam_2UpdateCharacterSelect *
                     UpdateCharacterSelect4UpdateCharacterSelect) !=
        UpdateCharacterSelectlocal_10UpdateCharacterSelect)
    {
        *(UpdateCharacterSelectundefined4UpdateCharacterSelect
              *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                 UpdateCharacterSelect0x2eb4UpdateCharacterSelect +
                 UpdateCharacterSelectparam_2UpdateCharacterSelect *
                     UpdateCharacterSelect4UpdateCharacterSelect) =
            UpdateCharacterSelect0x43960000UpdateCharacterSelect;
    }
    UpdateCharacterSelectifUpdateCharacterSelect(
        UpdateCharacterSelect0UpdateCharacterSelect.UpdateCharacterSelect0UpdateCharacterSelect <
        *(UpdateCharacterSelectfloatUpdateCharacterSelect
              *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                 UpdateCharacterSelect0x2eb4UpdateCharacterSelect +
                 UpdateCharacterSelectparam_2UpdateCharacterSelect *
                     UpdateCharacterSelect4UpdateCharacterSelect))
    {
        *(UpdateCharacterSelectfloatUpdateCharacterSelect
              *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                 UpdateCharacterSelect0x2eb4UpdateCharacterSelect +
                 UpdateCharacterSelectparam_2UpdateCharacterSelect *
                     UpdateCharacterSelect4UpdateCharacterSelect) =
            *(UpdateCharacterSelectfloatUpdateCharacterSelect
                  *)(UpdateCharacterSelectparam_1UpdateCharacterSelect +
                     UpdateCharacterSelect0x2eb4UpdateCharacterSelect +
                     UpdateCharacterSelectparam_2UpdateCharacterSelect *
                         UpdateCharacterSelect4UpdateCharacterSelect) -
            UpdateCharacterSelect20UpdateCharacterSelect
                .UpdateCharacterSelect0UpdateCharacterSelect;
    }
    UpdateCharacterSelectreturnUpdateCharacterSelect;
}
