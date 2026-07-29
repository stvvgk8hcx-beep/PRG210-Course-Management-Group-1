#define _CRT_SECURE_NO_WARNINGS

#include "CSVUtils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

extern Department *StoreDepartments;
extern int TotalDepartments;

bool loadFromCSV(const char *filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "CSV file not found. Starting with empty data.\n";
        return false;
    }

    file >> TotalDepartments;
    file.ignore(); // ignore newline

    delete[] StoreDepartments;
    StoreDepartments = new Department[TotalDepartments];

    std::string line;
    for (int i = 0; i < TotalDepartments; ++i)
    {
        if (!std::getline(file, line))
            break;
        std::stringstream deptStream(line);
        std::string deptName;
        int totalCourses = 0;

        std::getline(deptStream, deptName, ',');
        deptStream >> totalCourses;

        StoreDepartments[i] = Department(deptName.c_str());

        for (int j = 0; j < totalCourses; ++j)
        {
            if (!std::getline(file, line))
                break;
            std::stringstream courseStream(line);
            std::string courseNumber, courseSection, courseName, schedule;
            double price;

            std::getline(courseStream, courseNumber, ',');
            std::getline(courseStream, courseSection, ',');
            std::getline(courseStream, courseName, ',');
            std::getline(courseStream, schedule, ',');
            courseStream >> price;

            StoreDepartments[i].addCourse(Course(courseNumber.c_str(), courseSection.c_str(),
                                                 courseName.c_str(), schedule.c_str(), price));
        }
    }

    file.close();
    std::cout << "Data loaded from CSV successfully.\n";
    return true;
}

bool saveToCSV(const char *filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Failed to open CSV file for writing.\n";
        return false;
    }

    file << TotalDepartments << "\n";
    for (int i = 0; i < TotalDepartments; ++i)
    {
        Department &dept = StoreDepartments[i];
        file << dept.getName() << "," << dept.getCourseCount() << "\n";
        for (size_t j = 0; j < dept.getCourseCount(); ++j)
        {
            Course *c = dept.getCourse(j);
            file << c->getCourseNumber() << "," << c->getCourseSection() << ","
                 << c->getCourseName() << "," << c->getSchedule() << "," << c->getPrice() << "\n";
        }
    }

    file.close();
    std::cout << "Changes saved to CSV successfully.\n";
    return true;
}


/* ok so now .c_str() on the constructor calls storedepartments because
inside the exisitng cvs it was std::string but my coourse and department constructors take
constr char* because i am using char arrays not std::string for memeory
was getting no matching constructor

course section I also added into this so that it reads say NBB for a course section
removed the spaces after commands it was causing file load issues where they load in wit hspaces infront of the names

also added define crit warning*/
