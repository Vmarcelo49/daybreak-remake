// ============================================
// Address:  0x0064d250
// Original: 
// Name:     WinMain (status: reviewed)
// TODO(decomp): WinMain or wWinMain? Parameter types suggest ANSI (CHAR local_174) but could be wrapper.
// ============================================


/* WinMainWARNINGWinMain: WinMainFunctionWinMain: WinMain__security_check_cookieWinMain WinMainreplacedWinMain WinMainwithWinMain WinMaininjectionWinMain: WinMainsecurity_check_cookieWinMain */
/* WinMainWARNINGWinMain: WinMainGlobalsWinMain WinMainstartingWinMain WinMainwithWinMain 'WinMain_WinMain' WinMainoverlapWinMain WinMainsmallerWinMain WinMainsymbolsWinMain WinMainatWinMain WinMaintheWinMain WinMainsameWinMain WinMainaddressWinMain */

WinMainundefined4WinMain WinMainFUN_0064d250WinMain(WinMainHINSTANCEWinMain WinMainparam_1WinMain,WinMainundefined4WinMain WinMainparam_2WinMain,WinMainundefined4WinMain WinMainparam_3WinMain,WinMainintWinMain WinMainparam_4WinMain)

{
  WinMaincharWinMain WinMaincVar1WinMain;
  WinMainATOMWinMain WinMainAVar2WinMain;
  WinMainintWinMain WinMainiVar3WinMain;
  WinMainintWinMain WinMainiVar4WinMain;
  WinMainintWinMain WinMainiVar5WinMain;
  WinMainundefined4WinMain *WinMainpuVar6WinMain;
  WinMainvoidWinMain *WinMainpvVar7WinMain;
  WinMainundefined4WinMain WinMainlocal_194WinMain;
  WinMainundefined1WinMain WinMainlocal_18cWinMain [WinMain4WinMain];
  WinMainundefined1WinMain WinMainlocal_188WinMain [WinMain4WinMain];
  WinMainundefined1WinMain WinMainlocal_184WinMain [WinMain4WinMain];
  WinMainundefined1WinMain WinMainlocal_180WinMain [WinMain4WinMain];
  WinMainundefined1WinMain WinMainlocal_17cWinMain [WinMain4WinMain];
  WinMainHWNDWinMain WinMainlocal_178WinMain;
  WinMainCHARWinMain WinMainlocal_174WinMain [WinMain268WinMain];
  WinMainundefined4WinMain WinMainlocal_68WinMain;
  WinMaincharWinMain *WinMainlocal_64WinMain;
  WinMainHWNDWinMain WinMainlocal_60WinMain;
  WinMainHINSTANCEWinMain WinMainlocal_5cWinMain;
  WinMainundefined4WinMain WinMainlocal_58WinMain;
  WinMainuintWinMain WinMainlocal_48WinMain;
  WinMainintWinMain WinMainlocal_40WinMain;
  WinMainundefined4WinMain WinMainlocal_3cWinMain;
  WinMainintWinMain WinMainlocal_38WinMain;
  WinMainWNDCLASSEXAWinMain WinMainlocal_34WinMain;
  
  WinMainlocal_68WinMain = WinMainDAT_006b77f4WinMain;
  WinMainGetModuleFileNameAWinMain((WinMainHMODULEWinMain)WinMain0x0WinMain,WinMainlocal_174WinMain,WinMain0x104WinMain);
  WinMainlocal_64WinMain = WinMain_strrchrWinMain(WinMainlocal_174WinMain,WinMain0x5cWinMain);
  WinMainlocal_64WinMain[WinMain1WinMain] = '\WinMain0WinMain';
  WinMainSetCurrentDirectoryAWinMain(WinMainlocal_174WinMain);
  WinMainiVar3WinMain = WinMainGetSystemMetricsWinMain(WinMain0x2dWinMain);
  WinMainiVar4WinMain = WinMainGetSystemMetricsWinMain(WinMain5WinMain);
  WinMainlocal_40WinMain = WinMainGetSystemMetricsWinMain(WinMain7WinMain);
  WinMainlocal_40WinMain = WinMainiVar3WinMain + WinMain800WinMain + WinMainiVar4WinMain + WinMainlocal_40WinMain;
  WinMainiVar3WinMain = WinMainGetSystemMetricsWinMain(WinMain0x2eWinMain);
  WinMainiVar4WinMain = WinMainGetSystemMetricsWinMain(WinMain6WinMain);
  WinMainiVar5WinMain = WinMainGetSystemMetricsWinMain(WinMain8WinMain);
  WinMainlocal_38WinMain = WinMainGetSystemMetricsWinMain(WinMain4WinMain);
  WinMainlocal_38WinMain = WinMainiVar3WinMain + WinMain600WinMain + WinMainiVar4WinMain + WinMainiVar5WinMain + WinMainlocal_38WinMain;
  WinMainlocal_34WinMain.WinMaincbSizeWinMain = WinMain0x30WinMain;
  WinMainlocal_34WinMain.WinMainhInstanceWinMain = WinMainparam_1WinMain;
  WinMainlocal_34WinMain.WinMainlpszClassNameWinMain = "WinMainHigurashiDaybreakWinMain";
  WinMainlocal_34WinMain.WinMainlpfnWndProcWinMain = WinMainFUN_0064d5e0WinMain;
  WinMainlocal_34WinMain.WinMainstyleWinMain = WinMain0WinMain;
  WinMainlocal_34WinMain.WinMainhIconWinMain = WinMainLoadIconAWinMain(WinMainparam_1WinMain,"WinMainICONWinMain");
  WinMainlocal_34WinMain.WinMainhIconSmWinMain = WinMainLoadIconAWinMain(WinMainparam_1WinMain,"WinMainICONWinMain");
  WinMainlocal_34WinMain.WinMainhCursorWinMain = WinMainLoadCursorAWinMain((WinMainHINSTANCEWinMain)WinMain0x0WinMain,(WinMainLPCSTRWinMain)WinMain0x7f00WinMain);
  WinMainlocal_34WinMain.WinMainlpszMenuNameWinMain = (WinMainLPCSTRWinMain)WinMain0x0WinMain;
  WinMainlocal_34WinMain.WinMaincbClsExtraWinMain = WinMain0WinMain;
  WinMainlocal_34WinMain.WinMaincbWndExtraWinMain = WinMain0WinMain;
  WinMainlocal_34WinMain.WinMainhbrBackgroundWinMain = WinMainGetStockObjectWinMain(WinMain4WinMain);
  WinMainAVar2WinMain = WinMainRegisterClassExAWinMain(&WinMainlocal_34WinMain);
  WinMainifWinMain ((WinMainAVar2WinMain != WinMain0WinMain) &&
     (WinMainlocal_178WinMain = WinMainCreateWindowExAWinMain(WinMain0x40000WinMain,"WinMainHigurashiDaybreakWinMain","WinMainHigurashiWinMain WinMainDaybreakWinMain WinMainKaiWinMain",WinMain0xc80000WinMain,
                                  -WinMain0x80000000WinMain,-WinMain0x80000000WinMain,WinMainlocal_40WinMain,WinMainlocal_38WinMain,(WinMainHWNDWinMain)WinMain0x0WinMain,(WinMainHMENUWinMain)WinMain0x0WinMain,
                                  WinMainparam_1WinMain,(WinMainLPVOIDWinMain)WinMain0x0WinMain), WinMainlocal_178WinMain != (WinMainHWNDWinMain)WinMain0x0WinMain)) {
    WinMainShowWindowWinMain(WinMainlocal_178WinMain,WinMainparam_4WinMain);
    WinMainUpdateWindowWinMain(WinMainlocal_178WinMain);
    WinMaindoWinMain {
    } WinMainwhileWinMain (WinMainDAT_006d11a0WinMain == '\WinMain0WinMain');
    WinMainFUN_0064d760WinMain();
    WinMainpuVar6WinMain = (WinMainundefined4WinMain *)WinMainFUN_006532f0WinMain(WinMainlocal_17cWinMain,"WinMaindaybreak00WinMain.WinMaindatWinMain");
    WinMainDAT_006ca824WinMain = *WinMainpuVar6WinMain;
    WinMainpuVar6WinMain = (WinMainundefined4WinMain *)WinMainFUN_006532f0WinMain(WinMainlocal_180WinMain,"WinMaindaybreak04WinMain.WinMaindatWinMain");
    WinMainDAT_006ca828WinMain = *WinMainpuVar6WinMain;
    WinMainFUN_006532f0WinMain(&WinMainlocal_3cWinMain,"WinMaindaybreak07WinMain.WinMaindatWinMain");
    WinMainpuVar6WinMain = (WinMainundefined4WinMain *)WinMainFUN_006532f0WinMain(WinMainlocal_184WinMain,"WinMaindaybreak05WinMain.WinMaindatWinMain");
    WinMain_DAT_006ca82cWinMain = *WinMainpuVar6WinMain;
    WinMainpuVar6WinMain = (WinMainundefined4WinMain *)WinMainFUN_006532f0WinMain(WinMainlocal_188WinMain,"WinMaindaybreak02WinMain.WinMaindatWinMain");
    WinMainDAT_006ca830WinMain = *WinMainpuVar6WinMain;
    WinMainpuVar6WinMain = (WinMainundefined4WinMain *)WinMainFUN_006532f0WinMain(WinMainlocal_18cWinMain,"WinMaindaybreak06WinMain.WinMaindatWinMain");
    WinMainDAT_006ca834WinMain = *WinMainpuVar6WinMain;
    WinMaincVar1WinMain = WinMainFUN_0064d6e0WinMain();
    WinMainifWinMain ((WinMaincVar1WinMain == '\WinMain0WinMain') && (WinMaincVar1WinMain = WinMainFUN_0064d6e0WinMain(), WinMaincVar1WinMain == '\WinMain0WinMain')) {
      WinMainiVar3WinMain = WinMainFUN_0068de10WinMain();
      WinMainifWinMain (WinMainiVar3WinMain != WinMain0WinMain) {
        WinMainFUN_00653480WinMain(WinMainlocal_3cWinMain);
      }
      WinMainFUN_00653480WinMain(WinMainDAT_006ca828WinMain);
      WinMainFUN_00653480WinMain(WinMainDAT_006ca824WinMain);
      WinMainFUN_0064d700WinMain();
      WinMainlocal_60WinMain = WinMainlocal_178WinMain;
      WinMainlocal_5cWinMain = WinMainparam_1WinMain;
      WinMainpvVar7WinMain = WinMainoperator_newWinMain(WinMain4WinMain);
      WinMainifWinMain (WinMainpvVar7WinMain == (WinMainvoidWinMain *)WinMain0x0WinMain) {
        WinMainlocal_194WinMain = WinMain0WinMain;
      }
      WinMainelseWinMain {
        WinMainlocal_194WinMain = WinMainFUN_0064d780WinMain();
      }
      WinMainlocal_58WinMain = WinMainlocal_194WinMain;
      WinMainlocal_48WinMain = WinMainlocal_48WinMain | WinMain1WinMain;
      WinMaincVar1WinMain = WinMainFUN_00657910WinMain(&WinMainlocal_60WinMain);
      WinMainifWinMain (WinMaincVar1WinMain == '\WinMain0WinMain') {
        WinMainMessageBoxAWinMain(WinMainlocal_178WinMain,&WinMainDAT_006a5600WinMain,"WinMainErrorWinMain",WinMain0WinMain);
      }
      WinMainelseWinMain {
        WinMainFUN_006609a0WinMain();
        WinMainFUN_00657ef0WinMain();
        WinMainFUN_00657b00WinMain();
      }
      WinMainFUN_006609d0WinMain();
    }
  }
  WinMainreturnWinMain WinMain0WinMain;
}

