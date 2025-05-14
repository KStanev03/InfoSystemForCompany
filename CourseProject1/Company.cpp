#include "Company.hpp"
#include "Utils.hpp"
#include <stdexcept>

Company::Company(std::string name, std::string type, bool dds_registered, std::vector<Department> departments)
    : name(name), type(type), dds_registered(dds_registered), departments(departments) {
}

Company::Company() : name(""), type(""), dds_registered(false), departments({}) {}

Company::~Company() {}

void Company::setName(std::string name) {
    if (name.length() < 3) {
        throw std::invalid_argument("Company name must be at least 3 characters long.");
    }
    this->name = name;
}

std::string Company::getName() const 
{ 
    return name; 
}

void Company::setType(std::string type) {
    if (type.empty() || (type != "OOD" && type != "AD" && type != "EOOD")) {
        throw std::invalid_argument("Company type must be 'OOD', 'AD', or 'EOOD'.");
    }
    this->type = type;
}
std::string Company::getType() 
{ 
    return type; 
}

void Company::setDdsRegistered(bool dds_registered) {
    this->dds_registered = dds_registered;
}

bool Company::getDdsRegistered() 
{ 
    return dds_registered; 
}

std::vector<Department>& Company::getDepartments() 
{
    return departments;
}

const std::vector<Department>& Company::getDepartments() const 
{
    return departments;
}

void Company::addNewDepartment(Department dep) 
{
    this->departments.push_back(dep);
}

void Company::printInfo() const 
{
    std::cout << "Company Name: " << name << "\nType: " << type
        << "\nDDS Registered: " << (dds_registered ? "Yes" : "No") << std::endl;
    for (const auto& department : departments) {
        department.printInfo();
    }
}

std::ostream& operator<<(std::ostream& os, const Company& company) {
    os << company.name << "\n" << company.type << " " << company.dds_registered << " ";
    os << company.departments.size() << " ";
    for (const auto& department : company.departments) {
        os << department << " ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Company& company) {
    try {
        if (Utils::is_console_input(is)) {
            std::cout << "Enter company name (at least 3 symbols): ";
        }

        std::string name = Utils::readStringFromInput(is);
        company.setName(name);

        if (Utils::is_console_input(is)) {
            std::cout << "Enter company type (OOD, AD, or EOOD): ";
        }
        std::string type;
        is >> type;
        company.setType(type);

        if (Utils::is_console_input(is)) {
            std::cout << "Is DDS registered (1 for yes, 0 for no): ";
        }
        bool dds_registered = Utils::parseBoolFromInput(is);
        company.setDdsRegistered(dds_registered);

        if (Utils::is_console_input(is)) {
            std::cout << "Enter number of departments (at least 1): ";
        }
        size_t departmentCount = Utils::parseSizetFromInput(is);
        company.departments.resize(departmentCount);

        for (auto& department : company.departments) {
            is >> department;
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Input error: " << e.what() << std::endl;
    }

    return is;
}
