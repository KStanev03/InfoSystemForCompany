#include "Department.hpp"
#include "Utils.hpp"
#include <regex> 
#include <stdexcept>

Department::Department(std::string name, std::string start_date, std::vector<Employee> employees)
    : name(name), start_date(start_date), employees(employees) {
}

Department::Department() : name(""), start_date(""), employees({}) {}

Department::~Department() {}

void Department::setName(std::string name) {
    if (name.length() < 3) {
        throw std::invalid_argument("Department name must be at least 3 characters long.");
    }
    this->name = name;
}

std::string Department::getName() const 
{
    return name; 
}

void Department::setStartDate(std::string start_date) {
    std::regex date_pattern(R"(\d{4}-\d{2}-\d{2})");  
    if (!std::regex_match(start_date, date_pattern)) {
        throw std::invalid_argument("Start date must be in the format YYYY-MM-DD.");
    }
    this->start_date = start_date;
}
std::string Department::getStartDate() 
{ 
    return start_date; 
}

void Department::setEmployees(std::vector<Employee> employees) {
    if (employees.size() == 0) {
        throw std::invalid_argument("There must be at least one employee.");
    }
    this->employees = employees;
}

std::vector<Employee>& Department::getEmployees() 
{ 
    return employees; 
}

void Department::addNewEmployee(Employee emp) 
{ 
    this->employees.push_back(emp); 
}

void Department::printInfo() const 
{
    std::cout << "Department Name: " << name << "\nStart Date: " << start_date << "\nEmployee Count: " << employees.size() << std::endl;
    for (const auto& employee : employees) {
        employee.printInfo();
    }
}

std::ostream& operator<<(std::ostream& os, const Department& department) {
    os << department.name << "\n" << department.start_date << " ";
    os << department.employees.size() << " ";
    for (const auto& employee : department.employees) {
        os << employee << " ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Department& department) {
    try {
        if (Utils::is_console_input(is)) {
            std::cout << "Enter department name (at least 3 symbols): ";
        }
        std::string name = Utils::readStringFromInput(is);
        department.setName(name); 
        
        if (Utils::is_console_input(is)) {
            std::cout << "Enter department start date (YYYY-MM-DD): ";
        }
        std::string startDate;
        is >> startDate;
        department.setStartDate(startDate);  
        
        if (Utils::is_console_input(is)) {
            std::cout << "Enter number of employees (at least 1): ";
        }

        size_t employeeCount = Utils::parseSizetFromInput(is);
        department.employees.resize(employeeCount);

        for (auto& employee : department.employees) {
            is >> employee;
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Input error: " << e.what() << std::endl;
        throw e;
    }

    return is;
}