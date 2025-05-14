#ifndef COMPANY_HPP
#define COMPANY_HPP

#include "Department.hpp"
#include <string>
#include <vector>
#include <iostream>

class Company {
private:
    std::string name;
    std::string type;
    bool dds_registered;
    std::vector<Department> departments;

public:
    Company(std::string name, std::string type, bool dds_registered, std::vector<Department> departments);
    Company();
    ~Company();

    void setName(std::string name);
    std::string getName() const;
    void setType(std::string type);
    std::string getType();
    void setDdsRegistered(bool dds_registered);
    bool getDdsRegistered();

    std::vector<Department>& getDepartments();

    const std::vector<Department>& getDepartments() const;

    void addNewDepartment(Department dep);
    void printInfo() const;

    friend std::ostream& operator<<(std::ostream& os, const Company& company);
    friend std::istream& operator>>(std::istream& is, Company& company);
};

#endif // COMPANY_HPP
