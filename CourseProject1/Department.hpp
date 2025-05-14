#ifndef DEPARTMENT_HPP
#define DEPARTMENT_HPP

#include "Employee.hpp"
#include <string>
#include <vector>
#include <iostream>

class Department {
private:
    std::string name;
    std::string start_date;
    std::vector<Employee> employees;

public:
    Department(std::string name, std::string start_date, std::vector<Employee> employees);
    Department();
    ~Department();

    void setName(std::string name);
    std::string getName() const;
    void setStartDate(std::string start_date);
    std::string getStartDate();
    void setEmployees(std::vector<Employee> employees);

    std::vector<Employee>& getEmployees();

    void addNewEmployee(Employee emp);
    void printInfo() const;

    friend std::ostream& operator<<(std::ostream& os, const Department& department);
    friend std::istream& operator>>(std::istream& is, Department& department);
};

#endif // DEPARTMENT_HPP
