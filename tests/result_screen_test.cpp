#include <cstdio>
#define CHECK(condition) do { if (!(condition)) { std::fprintf(stderr,"%s:%d: %s\n",__FILE__,__LINE__,#condition); return 1; } } while (false)
#include "frontend/screen_result.h"
#include "frontend/result_quote.h"
int main() {
    ui::ResultTimeline result;
    CHECK(result.phase()==ui::ResultPhase::Quote);
    CHECK(!result.update(false)); CHECK(result.phase()==ui::ResultPhase::Quote);
    CHECK(!result.update(true)); CHECK(result.phase()==ui::ResultPhase::Report);
    CHECK(!result.update(false)); CHECK(result.phase()==ui::ResultPhase::Report);
    CHECK(result.update(true)); CHECK(result.phase()==ui::ResultPhase::Done);
    ui::ResultTimeline draw(true); CHECK(draw.phase()==ui::ResultPhase::Report);
    CHECK(draw.update(true));
    const auto quote=ui::parseResultQuote("# comment\r\nVOICE W00.wav\r\n\\cFFCCAA日本語\\n次の行\r\nVOICE other.wav\r\nother\r\n");
    CHECK(quote.voice=="W00.wav"); CHECK(quote.text=="\\cFFCCAA日本語\\n次の行");
    CHECK(ui::parseResultQuote("\r\n# comment\r\n").text.empty());
    // The winner art a side must load: one portrait per MEMBER, not the two slots the quote
    // pair always fills — a 1v1 (one-member side) draws one, a 2v2 two (FUN_00635d40:255-273).
    CHECK(ui::winnerPortraitCount(0)==0);
    CHECK(ui::winnerPortraitCount(1)==1);
    CHECK(ui::winnerPortraitCount(2)==2);
    CHECK(ui::winnerPortraitCount(3)==2);   // the original's two slots are the cap

    // The PSP three (16 Satoshi, 17 Miyoko, 18 Okonogi) on a winning side: their portrait comes
    // from psp-data and is optional, and they have no win script — so the screen never refuses
    // for them, and they never borrow Rena's or Rika's persona script ids 16/17.
    {
        const ui::WinnerArt rena=ui::winnerArt(0,false), renaPersona=ui::winnerArt(0,true);
        CHECK(rena.stem=="data/win/00a" && rena.required);
        CHECK(renaPersona.stem=="data/win/00b" && renaPersona.required);
        const ui::WinnerArt satoshi=ui::winnerArt(16,false);
        CHECK(satoshi.stem=="data/win/16a" && !satoshi.required);
        CHECK(!ui::winnerArt(18,false).required);
        CHECK(ui::winnerArt(-1,false).stem.empty());

        const int pc[2]={0,4}, mixed[2]={16,0}, psp[2]={17,-1};
        CHECK(ui::winnerQuoteRequired(pc,2));
        CHECK(!ui::winnerQuoteRequired(mixed,2));
        CHECK(!ui::winnerQuoteRequired(psp,1));
        const int pcSolo[2]={3,-1};
        CHECK(ui::winnerQuoteRequired(pcSolo,1));

        const int weapons[2]={2,0};
        const ui::WinnerQuotePlan solo=ui::planWinnerQuote(psp,weapons,1,0,false);
        CHECK(solo.pairScript.empty() && solo.fallbackScript.empty());
        const ui::WinnerQuotePlan team=ui::planWinnerQuote(mixed,weapons,2,0,false);
        CHECK(team.pairScript.empty() && team.fallbackScript.empty());
        // Rena weapon 2 alone still reads her persona script, unchanged.
        const int rena2[2]={0,-1};
        const ui::WinnerQuotePlan persona=ui::planWinnerQuote(rena2,weapons,1,0,false);
        CHECK(persona.pairA==16 && persona.pairScript=="data/scenario/win/16-16-3.txt");
    }
    return 0;
}
