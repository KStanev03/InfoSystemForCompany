#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include "Project.hpp"
#include <string>
#include <vector>
#include <iostream>

class Employee {
private:
    std::string name;
    std::string egn;
    unsigned short experience;
    unsigned short contract_type; 
    std::vector<Project> projects;

public:
    Employee(std::string name, std::string egn, unsigned short experience, unsigned short contract_type, std::vector<Project> projects);
    Employee();
    ~Employee();

    void setName(const std::string& name);
    const std::string& getName() const;

    void setEgn(const std::string& egn);
    const std::string& getEgn() const;

    void setExperience(unsigned short experience);
    unsigned short getExperience() const;

    void setContractType(unsigned short contract_type);
    unsigned short getContractType() const;

    void setProjects(const std::vector<Project> projects);
    std::vector<Project>& getProjects(); 

    void addNewProject(Project proj);
    void printInfo() const;

    friend std::ostream& operator<<(std::ostream& os, const Employee& employee);
    friend std::istream& operator>>(std::istream& is, Employee& employee);
};

#endif // EMPLOYEE_HPP
