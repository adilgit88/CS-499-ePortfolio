#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>

struct Course {
    std::string courseNumber;
    std::string name;
    std::vector<std::string> prerequisites;
};

#endif
