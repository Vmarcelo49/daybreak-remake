#include "frontend/story_script.h"

#include <cstdlib>
#include <sstream>

namespace ui {
namespace {

bool startsWithNoCase(const std::string& line, const char* keyword) {
    size_t i = 0;
    for (; keyword[i]; ++i) {
        if (i >= line.size()) return false;
        char c = line[i];
        if (c >= 'A' && c <= 'Z') c = static_cast<char>(c - 'A' + 'a');
        if (c != keyword[i]) return false;
    }
    return true;
}

// The whole line after a keyword and its padding, as the field reader sees it.
std::string afterKeyword(const std::string& line, size_t keywordLength) {
    const size_t start = line.find_first_not_of(' ', keywordLength);
    return start == std::string::npos ? std::string() : line.substr(start);
}

std::string firstField(const std::string& text) { return text.substr(0, text.find(',')); }

// The fields after the first, read with atol as the original does: absent ones stay 0.
std::vector<int> numbersAfterFirst(const std::string& text) {
    std::vector<int> numbers;
    for (size_t comma = text.find(','); comma != std::string::npos; comma = text.find(',', comma + 1))
        numbers.push_back(std::atoi(text.c_str() + comma + 1));
    return numbers;
}

}  // namespace

std::vector<StoryCommand> parseStoryScript(const std::string& utf8) {
    std::vector<StoryCommand> commands;
    std::string characterDir, voiceDir;
    std::istringstream lines(utf8);
    std::string line;
    while (std::getline(lines, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty() || line[0] == '#') continue;

        StoryCommand command;
        if (startsWithNoCase(line, "character ")) {
            const std::string fields = afterKeyword(line, 10);
            const std::vector<int> numbers = numbersAfterFirst(fields);
            command.type = StoryCommand::Type::Character;
            command.text = characterDir + firstField(fields);
            if (numbers.size() > 0) command.slot = numbers[0];
            if (numbers.size() > 1) command.hasX = numbers[1] != 0;
            if (command.hasX && numbers.size() > 2) command.x = numbers[2];
        } else if (startsWithNoCase(line, "bg ")) {
            command.type = StoryCommand::Type::Background;
            command.text = firstField(afterKeyword(line, 3));
        } else if (startsWithNoCase(line, "bgm ")) {
            command.type = StoryCommand::Type::Bgm;
            command.text = firstField(afterKeyword(line, 4));
        } else if (startsWithNoCase(line, "voice ")) {
            command.type = StoryCommand::Type::Voice;
            command.text = voiceDir + firstField(afterKeyword(line, 6));
        } else if (startsWithNoCase(line, "sleep ")) {
            command.type = StoryCommand::Type::Sleep;
            command.milliseconds = std::atoi(line.c_str() + 6);
        } else if (startsWithNoCase(line, "move ")) {
            const std::string fields = line.substr(5);
            const std::vector<int> numbers = numbersAfterFirst(fields);
            command.type = StoryCommand::Type::Move;
            command.slot = std::atoi(fields.c_str());
            if (numbers.size() > 0) command.delta = numbers[0];
            if (numbers.size() > 1) command.frames = numbers[1];
        } else if (startsWithNoCase(line, "front ")) {
            command.type = StoryCommand::Type::Front;
            command.slot = std::atoi(line.c_str() + 6);
        } else if (startsWithNoCase(line, "characterdir ")) {
            characterDir = firstField(afterKeyword(line, 13));
            continue;
        } else if (startsWithNoCase(line, "voicedir ")) {
            voiceDir = firstField(afterKeyword(line, 9));
            continue;
        } else {
            command.text = firstField(line);
        }
        commands.push_back(std::move(command));
    }
    return commands;
}

}  // namespace ui
