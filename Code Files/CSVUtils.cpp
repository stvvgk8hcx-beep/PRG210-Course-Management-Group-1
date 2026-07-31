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

        // added .c_str(). deptName is a std::string but my Department constructor
        // wants a const char*, .c_str() makes string a char
        StoreDepartments[i] = Department(deptName.c_str());

        for (int j = 0; j < totalCourses; ++j)
        {
            if (!std::getline(file, line))
                break;
            std::stringstream courseStream(line);
            std::string courseNumber, courseSection, courseName, schedule; // ADDED courseSection - Calvin
            double price;

            std::getline(courseStream, courseNumber, ',');
            std::getline(courseStream, courseSection, ',');  // added read my section, right after the number
            std::getline(courseStream, courseName, ',');
            std::getline(courseStream, schedule, ',');
            courseStream >> price;

            // added courseSection so my Course gets all 5 pieces, and put .c_str()
            // on every string so they fit my const char* constructor (this was the red error on this line)
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
        file << dept.getName() << ", " << dept.getCourseCount() << "\n";
        for (size_t j = 0; j < dept.getCourseCount(); ++j)
        {
            Course *c = dept.getCourse(j);
           // added getCourseSection() so the section I read on load gets written
            // back out too, in the same spot (right after the number) so load and save stay a matching pair
            file << c->getCourseNumber() << ", " << c->getCourseSection() << ", "
                 << c->getCourseName() << ", " << c->getSchedule() << ", " << c->getPrice() << "\n";
        }
    }

    file.close();
    std::cout << "Changes saved to CSV successfully.\n";
    return true;
}
