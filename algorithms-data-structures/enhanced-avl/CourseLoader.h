#ifndef COURSE_LOADER_H
#define COURSE_LOADER_H

#include "AVLTree.h"

#include <cstddef>
#include <string>
#include <vector>

struct LoadResult {
    bool success = false;
    std::size_t loadedCount = 0;
    std::size_t skippedCount = 0;
    std::vector<std::string> messages;
};

class CourseLoader {
public:
    static LoadResult loadCsv(const std::string& filename, AVLTree& tree);

private:
    static std::string trim(const std::string& value);
    static std::string toUpper(std::string value);
    static std::vector<std::string> splitCsvLine(const std::string& line);
};

#endif
