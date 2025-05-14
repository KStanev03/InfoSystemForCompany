#include "Employee.hpp"
#include "Utils.hpp"
#include <stdexcept>

Employee::Employee(std::string name, std::string egn, unsigned short experience, unsigned short contract_type, std::vector<Project> projects)
    : name(name), egn(egn), experience(experience), contract_type(contract_type), projects(projects) {
}

Employee::Employee() : name(""), egn(""), experience(0), contract_type(0), projects({}) {}

Employee::~Employee() {}

void Employee::setName(const std::string& name) {
    if (name.length() < 3) {
        throw std::invalid_argument("Employee name must be at least 3 characters long.");
    }
    this->name = name;
}
const std::string& Employee::getName() const 
{ 
    return name; 
}

void Employee::setEgn(const std::string& egn) 
{
    if (egn.length() != 10) {
        throw std::invalid_argument("EGN must be a 10-digit number.");
    }
    this->egn = egn;
}
const std::string& Employee::getEgn() const 
{ 
    return egn; 
}

void Employee::setExperience(unsigned short experience) 
{
    if (experience > 50) {
        throw std::invalid_argument("Experience must be between 0 and 50 years.");
    }
    this->experience = experience;
}
unsigned short Employee::getExperience() const
{ 
    return experience; 
}

void Employee::setContractType(unsigned short contract_type) 
{
    if (contract_type != 1 && contract_type != 2) {
        throw std::invalid_argument("Contract type must be 1 (full-time) or 2 (part-time).");
    }
    this->contract_type = contract_type;
}

unsigned short Employee::getContractType() const 
{ 
    return contract_type; 
}

void Employee::setProjects(std::vector<Project> projects) 
{
    if (projects.size() == 0) {
        throw std::invalid_argument("There must be at least one project.");
    }
    this->projects = projects;
}
std::vector<Project>& Employee::getProjects() 
{ 
    return projects; 
}

void Employee::addNewProject(Project project) 
{
    this->projects.push_back(project); 
}

void Employee::printInfo() const 
{
    std::cout << "Employee Name: " << name << "\nEGN: " << egn
        << "\nExperience: " << experience << "\nContract Type: " << contract_type << std::endl;
    for (const auto& project : projects) {
        project.printInfo();
    }
}

std::ostream& operator<<(std::ostream& os, const Employee& employee) {
    os << employee.name << "\n" << employee.egn << " " << employee.experience << " " << employee.contract_type << " ";
    os << employee.projects.size() << " ";
    for (const auto& project : employee.projects) {
        os << project << " ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Employee& employee) {
    try {
        if (Utils::is_console_input(is)) {
            std::cout << "Enter employee name (at least 3 symbols): ";
        }
        std::string name = Utils::readStringFromInput(is);
        employee.setName(name);

        if (Utils::is_console_input(is)) {
            std::cout << "Enter employee EGN (10 digits): ";
        }
        std::string egn;
        is >> egn;
        employee.setEgn(egn);

        if (Utils::is_console_input(is)) {
            std::cout << "Enter employee experience (from 0 to 50): ";
        }
        unsigned short experience;
        is >> experience;
        employee.setExperience(experience);

        if (Utils::is_console_input(is)) {
            std::cout << "Enter contract type (1 = full-time, 2 = part-time): ";
        }
        unsigned short contract_type;
        is >> contract_type;
        employee.setContractType(contract_type);

        if (Utils::is_console_input(is)) {
            std::cout << "Enter number of projects (at least one): ";
        }
        size_t projectCount = Utils::parseSizetFromInput(is);
        employee.projects.resize(projectCount);
        for (auto& project : employee.projects) {
            is >> project;
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Input error: " << e.what() << std::endl;
    }
    return is;
}
