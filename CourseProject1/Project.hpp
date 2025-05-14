#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <string>
#include <iostream>

class Project {
private:
    std::string name;
    unsigned int budget;
    std::string start_date;
    std::string deadline_date;

public:
    Project(std::string name, unsigned int budget, std::string start_date, std::string deadline_date);
    Project();
    ~Project();

    void setName(std::string name);
    std::string getName() const;
    void setBudget(unsigned int budget);
    unsigned int getBudget();
    void setStartDate(std::string start_date);
    std::string getStartDate();
    void setDeadlineDate(std::string deadline_date);
    std::string getDeadlineDate();

    void printInfo() const;

    friend std::ostream& operator<<(std::ostream& os, const Project& project);
    friend std::istream& operator>>(std::istream& is, Project& project);
    bool isValidDate(const std::string& date);
};

#endif // PROJECT_HPP
