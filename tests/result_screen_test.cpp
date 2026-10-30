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
    return 0;
}
