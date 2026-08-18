#include "CourseLoader.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <unordered_set>

LoadResult CourseLoader::loadCsv(
    const std::string& filename,
    BinarySearchTree& tree) {

    LoadResult result;
    std::ifstream file(filename);

    if (!file.is_open()) {
        result.messages.push_back(
            "Error: Could not open file '" + filename + "'.");
        return result;
    }

    std::vector<std::vector<std::string>> rows;
    std::unordered_set<std::string> validCourseNumbers;

    std::string line;
    std::size_t lineNumber = 0;

    while (std::getline(file, line)) {
        ++lineNumber;
        line = trim(line);

        if (line.empty()) {
            continue;
        }

        std::vector<std::string> tokens = splitCsvLine(line);
        if (tokens.size() < 2 || tokens[0].empty() || tokens[1].empty()) {
            ++result.skippedCount;
            result.messages.push_back(
                "Warning: Line " + std::to_string(lineNumber) +
                " is malformed and was skipped.");
            continue;
        }

        tokens[0] = toUpper(tokens[0]);
        validCourseNumbers.insert(tokens[0]);
        rows.push_back(std::move(tokens));
    }

    if (rows.empty()) {
        result.messages.push_back(
            "Error: No valid course data was found in '" + filename + "'.");
        return result;
    }

    tree.clear();

    for (const auto& tokens : rows) {
        Course course;
        course.courseNumber = tokens[0];
        course.name = tokens[1];

        for (std::size_t index = 2; index < tokens.size(); ++index) {
            const std::string prerequisite = toUpper(tokens[index]);
            if (prerequisite.empty()) {
                continue;
            }

            if (validCourseNumbers.find(prerequisite) != validCourseNumbers.end()) {
                course.prerequisites.push_back(prerequisite);
            } else {
                result.messages.push_back(
                    "Warning: Prerequisite '" + prerequisite +
                    "' for course '" + course.courseNumber +
                    "' was not found and was skipped.");
            }
        }

        const auto insertResult = tree.insert(course);
        if (insertResult == BinarySearchTree::InsertResult::Inserted) {
            ++result.loadedCount;
        } else {
            ++result.skippedCount;
            result.messages.push_back(
                "Warning: Duplicate course number '" +
                course.courseNumber + "' was skipped.");
        }
    }

    result.success = result.loadedCount > 0;
    return result;
}

std::string CourseLoader::trim(const std::string& value) {
    const std::size_t start = value.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }

    const std::size_t end = value.find_last_not_of(" \t\r\n");
    return value.substr(start, end - start + 1);
}

std::string CourseLoader::toUpper(std::string value) {
    std::transform(
        value.begin(),
        value.end(),
        value.begin(),
        [](unsigned char character) {
            return static_cast<char>(std::toupper(character));
        });
    return value;
}

std::vector<std::string> CourseLoader::splitCsvLine(const std::string& line) {
    std::istringstream stream(line);
    std::vector<std::string> tokens;
    std::string token;

    while (std::getline(stream, token, ',')) {
        tokens.push_back(trim(token));
    }

    return tokens;
}
