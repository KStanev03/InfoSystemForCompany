#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include "Company.hpp"
#include "Department.hpp"
#include "Employee.hpp"
#include "Project.hpp"

namespace Utils {

    std::string readStringFromInput(std::istream& is);


    size_t parseSizetFromInput(std::istream& is);

    bool parseBoolFromInput(std::istream& is);


    bool is_console_input(std::istream& is);

    void searchForCompany(std::vector<Company>& companies);

    void searchForDepartment(std::vector<Company>& companies);

    void searchForEmployee(std::vector<Company>& companies);

    void searchForProject(std::vector<Company>& companies);

    void updateCompany(std::vector<Company>& companies);

    void updateDepartmentInCompany(std::vector<Company>& companies);

    void updateEmployeeInDepartment(std::vector<Company>& companies);

    void updateProjectInEmployee(std::vector<Company>& companies);

    void AddCompany(std::vector<Company>& companies);

    void AddDepartment(std::vector<Company>& companies);

    void AddEmployee(std::vector<Company>& companies);

    void AddProject(std::vector<Company>& companies);

    void DeleteCompany(std::vector<Company>& companies);

    void DeleteDepartment(std::vector<Company>& companies);

    void DeleteEmployee(std::vector<Company>& companies);

    void DeleteProject(std::vector<Company>& companies);

    void GetAllCompanies(std::vector<Company>& companies);

    void GetAllDepartments(std::vector<Company>& companies);

    void GetAllEmployees(std::vector<Company>& companies);

    void GetAllProjects(std::vector<Company>& companies);
}

#endif // UTILS_H
