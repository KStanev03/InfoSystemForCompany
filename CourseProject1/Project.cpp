#include "Project.hpp"
#include "Utils.hpp"
#include <regex> 
#include <stdexcept>

Project::Project(std::string name, unsigned int budget, std::string start_date, std::string deadline_date)
    : name(name), budget(budget), start_date(start_date), deadline_date(deadline_date) {
}

Project::Project() : name(""), budget(0), start_date(""), deadline_date("") {}

Project::~Project() {}

void Project::setName(std::string name) {
    if (name.length() < 3) {
        throw std::invalid_argument("Project name must be at least 3 characters long.");
    }
    this->name = name;
}
std::string Project::getName() const 
{ 
    return name; 
}

void Project::setBudget(unsigned int budget) {
    if (budget <= 0) {
        throw std::invalid_argument("Project budget must be greater than zero.");
    }
    this->budget = budget;
}
unsigned int Project::getBudget() 
{ 
    return budget; 
}

void Project::setStartDate(std::string start_date) {
    if (!isValidDate(start_date)) {
        throw std::invalid_argument("Start date must be in the format YYYY-MM-DD.");
    }
    this->start_date = start_date;
}
std::string Project::getStartDate()
{ 
    return start_date; 
}

void Project::setDeadlineDate(std::string deadline_date) {
    if (!isValidDate(deadline_date)) {
        throw std::invalid_argument("Deadline date must be in the format YYYY-MM-DD.");
    }
    this->deadline_date = deadline_date;
}
std::string Project::getDeadlineDate() 
{
    return deadline_date; 
}

void Project::printInfo() const {
    std::cout << "Project Name: " << name << "\nBudget: " << budget
        << "\nStart Date: " << start_date << "\nDeadline: " << deadline_date << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Project& project) {
    os << project.name << "\n" << project.budget << " " << project.start_date << " " << project.deadline_date;
    return os;
}

std::istream& operator>>(std::istream& is, Project& project) {
    try {
        if (Utils::is_console_input(is)) {
            std::cout << "Enter project name (at least 3 symbols): ";
        }
        std::string name = Utils::readStringFromInput(is);
        project.setName(name);

        if (Utils::is_console_input(is)) {
            std::cout << "Enter project budget (more then 0): ";
        }
        unsigned int budget;
        is >> budget;
        project.setBudget(budget);

        if (Utils::is_console_input(is)) {
            std::cout << "Enter project start date (YYYY-MM-DD): ";
        }
        std::string startDate;
        is >> startDate;
        project.setStartDate(startDate);

        if (Utils::is_console_input(is)) {
            std::cout << "Enter project deadline date (YYYY-MM-DD): ";
        }
        std::string deadlineDate;
        is >> deadlineDate;
        project.setDeadlineDate(deadlineDate);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Input error: " << e.what() << std::endl;
    }
    return is;
}

bool Project::isValidDate(const std::string& date) {
    std::regex date_pattern(R"(\d{4}-\d{2}-\d{2})");
    return std::regex_match(date, date_pattern);
}
