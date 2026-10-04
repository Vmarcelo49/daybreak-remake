#include <cstdio>
#define CHECK(condition) do { if (!(condition)) { std::fprintf(stderr,"%s:%d: %s\n",__FILE__,__LINE__,#condition); return 1; } } while (false)
#include "ui/screen_result.h"
int main() {
    ui::ResultTimeline result;
    for (int i=0;i<179;++i) { CHECK(!result.update(true)); CHECK(result.phase()==ui::ResultPhase::Victory); }
    CHECK(!result.update(false)); CHECK(result.phase()==ui::ResultPhase::Quote);
    CHECK(!result.update(false)); CHECK(result.phase()==ui::ResultPhase::Quote);
    CHECK(!result.update(true)); CHECK(result.phase()==ui::ResultPhase::Report);
    CHECK(!result.update(false)); CHECK(result.phase()==ui::ResultPhase::Report);
    CHECK(result.update(true)); CHECK(result.phase()==ui::ResultPhase::Done);
    ui::ResultTimeline draw(true); CHECK(draw.phase()==ui::ResultPhase::Report);
    CHECK(draw.update(true));
    const auto quote=ui::parseResultQuote("# comment\r\nVOICE W00.wav\r\n\\cFFCCAA日本語\\n次の行\r\nVOICE other.wav\r\nother\r\n");
    CHECK(quote.voice=="W00.wav"); CHECK(quote.text=="\\cFFCCAA日本語\\n次の行");
    CHECK(ui::parseResultQuote("\r\n# comment\r\n").text.empty());
}
