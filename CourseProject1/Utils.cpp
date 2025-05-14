#include "Utils.hpp"
#include <regex>
#include <stdexcept>
#include <sstream>

namespace Utils {

    std::regex date_pattern(R"(\d{4}-\d{2}-\d{2})");  // YYYY-MM-DD

    bool is_console_input(std::istream& is) {
        return &is == &std::cin;
    }

    std::string readStringFromInput(std::istream& is) {
        char curr;
        char name[1024];
        int len = 0;
        is.ignore();
        is.get(curr);
        while (curr != '\n') {
            name[len++] = curr;
            is.get(curr);
        }
        name[len] = '\0';
        return name;
    }


    size_t parseSizetFromInput(std::istream& is) {
        std::string s;
        is >> s;
        try {
            int res = std::stoi(s);
            if (res < 1) {
                throw std::invalid_argument("Value cannot be less than 1");
            }
            return static_cast<size_t>(res);
        }
        catch (std::invalid_argument& e) {
            std::cout << "No conversion could be made" << std::endl;
            throw e;
        }
        catch (const std::out_of_range& e) {
            std::cout << "Input out of range for integer conversion." << std::endl;
            throw;
        }
    }

    bool parseBoolFromInput(std::istream& is) {
        try {
            std::string s;
            is >> s;
            if (s == "true" || s == "1") {
                return true;
            }
            else if (s == "false" || s == "0") {
                return false;
            }
            throw std::invalid_argument("Input value could not be converted to bool");
        }
        catch (std::invalid_argument& e) {
            std::cout << "No conversion could be made" << std::endl;
            throw e;
        }
    }


#pragma region GetMethods

    void Utils::GetAllCompanies(std::vector<Company>& companies) {
        for (auto& company : companies) {
            std::cout << "Company Name: " << company.getName() << std::endl;
            std::cout << "Company Type: " << company.getType() << std::endl;
            std::cout << "DDS Registered: " << (company.getDdsRegistered() ? "Yes" : "No") << std::endl;
            std::cout << "-----------------------------" << std::endl;
        }
    }

    void Utils::GetAllDepartments(std::vector<Company>& companies) {
        for (auto& company : companies) {
            for (auto& department : company.getDepartments()) {
                std::cout << "Department Name: " << department.getName() << std::endl;
                std::cout << "Start Date: " << department.getStartDate() << std::endl;
                std::cout << "-----------------------------" << std::endl;
            }
        }
    }

    void Utils::GetAllEmployees(std::vector<Company>& companies) {
        for (auto& company : companies) {
            for (auto& department : company.getDepartments()) {
                for (auto& employee : department.getEmployees()) {
                    std::cout << "Employee Name: " << employee.getName() << std::endl;
                    std::cout << "EGN: " << employee.getEgn() << std::endl;
                    std::cout << "Experience: " << employee.getExperience() << std::endl;
                    std::cout << "-----------------------------" << std::endl;
                }
            }
        }
    }

    void Utils::GetAllProjects(std::vector<Company>& companies) {
        for (auto& company : companies) {
            for (auto& department : company.getDepartments()) {
                for (auto& employee : department.getEmployees()) {
                    for (auto& project : employee.getProjects()) {
                        std::cout << "Project Name: " << project.getName() << std::endl;
                        std::cout << "Budget: " << project.getBudget() << std::endl;
                        std::cout << "Start Date: " << project.getStartDate() << std::endl;
                        std::cout << "Deadline Date: " << project.getDeadlineDate() << std::endl;
                        std::cout << "-----------------------------" << std::endl;
                    }
                }
            }
        }
    }
#pragma endregion

#pragma region SearchMethods

    void Utils::searchForCompany(std::vector<Company>& companies) {
        std::string companyName;
        std::cout << "Enter company name to search: ";
        std::cin >> companyName;

        for (size_t i = 0; i < companies.size(); ++i) {
            if (companyName == companies[i].getName()) {
                std::cout << "Company found: " << companies[i].getName() << std::endl;
                companies[i].printInfo();
                return;
            }
        }
        std::cout << "Company not found.\n";
    }

    void Utils::searchForDepartment(std::vector<Company>& companies) {
        std::string departmentName;
        std::cout << "Enter department name to search: ";
        std::cin >> departmentName;

        for (size_t i = 0; i < companies.size(); ++i) {
            for (size_t j = 0; j < companies[i].getDepartments().size(); ++j) {
                if (departmentName == companies[i].getDepartments()[j].getName()) {
                    std::cout << "Department found in company: " << companies[i].getName() << std::endl;
                    companies[i].getDepartments()[j].printInfo();
                    return;  
                }
            }
        }
        std::cout << "Department not found.\n";
    }

    void Utils::searchForEmployee(std::vector<Company>& companies) {
        std::string egn;
        std::cout << "Enter employee EGN to search: ";
        std::cin >> egn;

        for (size_t i = 0; i < companies.size(); ++i) {
            for (size_t j = 0; j < companies[i].getDepartments().size(); ++j) {
                for (size_t k = 0; k < companies[i].getDepartments()[j].getEmployees().size(); ++k) {
                    if (egn == companies[i].getDepartments()[j].getEmployees()[k].getEgn()) {
                        std::cout << "Employee found in department: " << companies[i].getDepartments()[j].getName() << std::endl;
                        companies[i].getDepartments()[j].getEmployees()[k].printInfo();
                        return; 
                    }
                }
            }
        }
        std::cout << "Employee not found.\n";
    }

    void Utils::searchForProject(std::vector<Company>& companies) {
        std::string projectName;
        std::cout << "Enter project name to search: ";
        std::cin >> projectName;

        for (size_t i = 0; i < companies.size(); ++i) {
            for (size_t j = 0; j < companies[i].getDepartments().size(); ++j) {
                for (size_t k = 0; k < companies[i].getDepartments()[j].getEmployees().size(); ++k) {
                    for (size_t l = 0; l < companies[i].getDepartments()[j].getEmployees()[k].getProjects().size(); ++l) {
                        if (projectName == companies[i].getDepartments()[j].getEmployees()[k].getProjects()[l].getName()) {
                            std::cout << "Project found for employee: " << companies[i].getDepartments()[j].getEmployees()[k].getName() << std::endl;
                            companies[i].getDepartments()[j].getEmployees()[k].getProjects()[l].printInfo();
                            return; 
                        }
                    }
                }
            }
        }
        std::cout << "Project not found.\n";
    }

#pragma endregion

#pragma region UpdateMethods

    void Utils::updateCompany(std::vector<Company>& companies) {
        if (companies.empty()) {
            std::cout << "No companies available.\n";
            return;
        }

        std::string companyName;
        std::cout << "Enter company name to update: ";
        std::cin >> companyName;

        for (auto& company : companies) {
            if (company.getName() == companyName) {
                std::cout << "Company found: " << company.getName() << "\n";
                company.printInfo();  

                std::string newName;
                std::string newType;
                std::string ddsRegisteredS;
                bool newDDSStatus;

                std::cout << "Enter new company name (leave empty to keep the same): ";
                std::cin >> newName;  
                if (!newName.empty()) {
                    company.setName(newName);
                }

                std::cout << "Enter new company type (leave empty to keep the same): ";
                std::cin >> newType;
                if (!newType.empty()) {
                    company.setType(newType);
                }

                std::cout << "Enter new DDS registration status (1 for registered, 0 for not registered): ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, ddsRegisteredS);
                if (ddsRegisteredS == "true" || ddsRegisteredS == "1") {
                    company.setDdsRegistered(true);
                }
                else company.setDdsRegistered(false);;

                std::cout << "Company updated successfully:\n";
                company.printInfo();
                return;
            }
        }

        std::cout << "Company not found.\n";
    }

    void Utils::updateDepartmentInCompany(std::vector<Company>& companies) {
        if (companies.empty()) {
            std::cout << "No companies available.\n";
            return;
        }

        std::string companyName, departmentName;
        std::cout << "Enter company name: ";
        std::cin >> companyName;

        for (auto& company : companies) {
            if (companyName == company.getName()) {
                std::cout << "Enter department name: ";
                std::cin >> departmentName;

                for (auto& department : company.getDepartments()) { 
                    if (departmentName == department.getName()) {
                        std::cout << "Updating Department:\n";
                        department.printInfo();

                        std::string newName, newStartDate;
                        std::cout << "Enter new department name: ";
                        std::cin >> newName;
                        std::cout << "Enter new start date: ";
                        std::cin >> newStartDate;

                        department.setName(newName);
                        department.setStartDate(newStartDate);
                        department.printInfo();
                        std::cout << "Department updated successfully.\n";
                        return;
                    }
                }

                std::cout << "Department not found in this company.\n";
                return;
            }
        }

        std::cout << "Company not found.\n";
    }
    void Utils::updateEmployeeInDepartment(std::vector<Company>& companies) {
        if (companies.empty()) {
            std::cout << "No companies available.\n";
            return;
        }

        std::string companyName, departmentName, egn;
        std::cout << "Enter company name: ";
        std::cin >> companyName;

        for (auto& company : companies) {
            if (companyName == company.getName()) {
                std::cout << "Enter department name: ";
                std::cin >> departmentName;

                for (auto& department : company.getDepartments()) {
                    if (departmentName == department.getName()) {
                        std::cout << "Enter employee EGN to update: ";
                        std::cin >> egn;

                        for (auto& employee : department.getEmployees()) {
                            if (egn == employee.getEgn()) {
                                std::cout << "Updating Employee:\n";
                                employee.printInfo();

                                std::string newName, newEgn;
                                int newWorkExperience, newContractHours;
                                std::cout << "Enter new name: ";
                                std::cin >> newName;
                                std::cout << "Enter new EGN: ";
                                std::cin >> newEgn;
                                std::cout << "Enter new work experience: ";
                                std::cin >> newWorkExperience;
                                std::cout << "Enter new contract hours: ";
                                std::cin >> newContractHours;

                                employee.setName(newName);
                                employee.setEgn(newEgn);
                                employee.setExperience(newWorkExperience);
                                employee.setContractType(newContractHours);
                                employee.printInfo();
                                std::cout << "Employee updated successfully.\n";
                                return;
                            }
                        }

                        std::cout << "Employee with given EGN not found in this department.\n";
                        return;
                    }
                }

                std::cout << "Department not found in this company.\n";
                return;
            }
        }

        std::cout << "Company not found.\n";
    }

    void Utils::updateProjectInEmployee(std::vector<Company>& companies) {
        if (companies.empty()) {
            std::cout << "No companies available.\n";
            return;
        }

        std::string companyName, egn, projectName;
        std::cout << "Enter company name: ";
        std::cin >> companyName;

        for (auto& company : companies) {
            if (company.getName() == companyName) {
                std::cout << "Enter employee EGN: ";
                std::cin >> egn;

                for (auto& department : company.getDepartments()) {
                    for (auto& employee : department.getEmployees()) {
                        if (employee.getEgn() == egn) {
                            std::cout << "Enter project name to update: ";
                            std::cin >> projectName;
                            for (auto& project : employee.getProjects()) {
                                if (project.getName() == projectName) {
                                    std::cout << "Updating Project:\n";
                                    project.printInfo();

                                    std::string newName, newStartDate, newDeadlineDate;
                                    unsigned int newBudget;

                                    std::cout << "Enter new project name: ";
                                    std::cin >> newName;
                                    std::cout << "Enter new start date: ";
                                    std::cin >> newStartDate;
                                    std::cout << "Enter new deadline date: ";
                                    std::cin >> newDeadlineDate;
                                    std::cout << "Enter new budget: ";
                                    std::cin >> newBudget;

                                    project.setName(newName);
                                    project.setStartDate(newStartDate);
                                    project.setDeadlineDate(newDeadlineDate);
                                    project.setBudget(newBudget);

                                    std::cout << "Project updated successfully.\n";
                                    return;
                                }
                            }
                            std::cout << "Project not found for this employee.\n";
                            return;
                        }
                    }
                }

                std::cout << "Employee not found in this company.\n";
                return;
            }
        }

        std::cout << "Company not found.\n";
    }
#pragma endregion

#pragma region AddMethods

    void Utils::AddCompany(std::vector<Company>& companies) {
        std::string name, type;
        std::string ddsRegisteredS;
        bool ddsRegistered;

        std::cout << "Enter company name (at least 3 symbols): ";
        std::cin.ignore(); 
        std::getline(std::cin, name);

        if (name.length() < 3) {
            std::cout << "Company name must be at least 3 characters long.\n";
            return;
        }

        std::cout << "Enter company type (OOD, AD, or EOOD): ";
        std::getline(std::cin, type);

        if (type != "OOD" && type != "AD" && type != "EOOD") {
            std::cout << "Invalid company type. Please enter 'OOD', 'AD', or 'EOOD'.\n";
            return;
        }

        std::cout << "Is DDS registered (1 for Yes, if not 1 -> No): ";
        std::getline(std::cin, ddsRegisteredS);
        if (ddsRegisteredS == "true" || ddsRegisteredS == "1") {
            ddsRegistered = true;
        }
        else ddsRegistered = false;

        Company newCompany(name, type, ddsRegistered, {});

        companies.push_back(newCompany);

        std::cout << "New company added successfully!\n";
    }



    void Utils::AddDepartment(std::vector<Company>& companies) {
        if (companies.empty()) {
            std::cout << "No companies available.\n";
            return;
        }

        std::string companyName;
        std::string departmentName;
        std::string startDate;

        std::cout << "Enter company name to add a department: ";
        std::cin.ignore();  
        std::getline(std::cin, companyName);

        for (auto& company : companies) {
            if (company.getName() == companyName) {
                std::cout << "Company found: " << company.getName() << "\n";
                company.printInfo(); 

                std::cout << "Enter new department name (at least 3 symbols): ";
                std::getline(std::cin, departmentName);

                if (departmentName.length() < 3) {
                    std::cout << "Department name must be at least 3 characters long.\n";
                    return;
                }

                std::cout << "Enter department start date (YYYY-MM-DD): ";
                std::getline(std::cin, startDate);
                
                if (!std::regex_match(startDate, date_pattern)) {
                    throw std::invalid_argument("Start date must be in the format YYYY-MM-DD.");
                }

                Department newDepartment(departmentName, startDate, {});

                company.addNewDepartment(newDepartment);

                std::cout << "New department added to the company.\n";
                return;
            }
        }

        std::cout << "Company not found.\n";
    }


    void Utils::AddEmployee(std::vector<Company>& companies) {
        if (companies.empty()) {
            std::cout << "No companies available.\n";
            return;
        }

        std::string companyName;
        std::string departmentName;

        std::cout << "Enter company name to add an employee: ";
        std::cin.ignore(); 
        std::getline(std::cin, companyName);

        for (auto& company : companies) {
            if (company.getName() == companyName) {
                std::cout << "Company found: " << company.getName() << "\n";
                company.printInfo();  

                std::cout << "Enter department name to add an employee: ";
                std::getline(std::cin, departmentName);

                bool departmentFound = false;
                for (auto& department : company.getDepartments()) {
                    if (department.getName() == departmentName) {
                        departmentFound = true;

                        std::string employeeName;
                        std::string egn;
                        unsigned short experience;
                        unsigned short contractType;

                        std::cout << "Enter employee name (at least 3 symbols): ";
                        std::getline(std::cin, employeeName);

                        if (employeeName.length() < 3) {
                            std::cout << "Employee name must be at least 3 characters long.\n";
                            return;
                        }

                        std::cout << "Enter employee EGN (10 digits): ";
                        std::getline(std::cin, egn);

                        if (egn.length() != 10) {
                            std::cout << "Invalid EGN. It should be exactly 10 digits.\n";
                            return;
                        }

                        std::cout << "Enter employee experience (from 0 to 50): ";
                        std::cin >> experience;

                        if (experience >= 50) {
                            std::cout << "Experience must be a positive number.\n";
                            return;
                        }

                        std::cout << "Enter contract type (1 = full-time, 2 = part-time): ";
                        std::cin >> contractType;

                        if (contractType != 1 && contractType != 2) {
                            std::cout << "Contract type must be 1 (full-time) or 2 (part-time).\n";
                            return;
                        }

                        Employee newEmployee(employeeName, egn, experience, contractType, {});

                        department.addNewEmployee(newEmployee);

                        std::cout << "Employee " << newEmployee.getName() << " added to department " << department.getName() << " successfully.\n";
                        return;
                    }
                }

                if (!departmentFound) {
                    std::cout << "Department not found in company.\n";
                }
                return;
            }
        }

        std::cout << "Company not found.\n";
    }


    void Utils::AddProject(std::vector<Company>& companies) {
        if (companies.empty()) {
            std::cout << "No companies available.\n";
            return;
        }

        std::string companyName;
        std::string employeeEgn;

        std::cout << "Enter company name to add a project: ";
        std::cin.ignore();  
        std::getline(std::cin, companyName);

        bool companyFound = false;
        for (auto& company : companies) {
            if (company.getName() == companyName) {
                companyFound = true;
                std::cout << "Company found: " << company.getName() << "\n";
                company.printInfo(); 

                std::string departmentName;
                std::cout << "Enter department name to add a project: ";
                std::getline(std::cin, departmentName);

                bool departmentFound = false;
                for (auto& department : company.getDepartments()) {
                    if (department.getName() == departmentName) {
                        departmentFound = true;

                        std::cout << "Enter employee EGN to add a project: ";
                        std::cin >> employeeEgn;

                        bool employeeFound = false;
                        for (auto& employee : department.getEmployees()) {
                            if (employee.getEgn() == employeeEgn) {
                                employeeFound = true;
                                std::cout << "Employee found: " << employee.getName() << "\n";
                                employee.printInfo();  

                                std::string projectName;
                                std::string projectStartDate;
                                std::string projectDeadlineDate;
                                unsigned int projectBudget;

                                std::cout << "Enter project name (at least 3 symbols): ";
                                std::cin.ignore();  
                                std::getline(std::cin, projectName);

                                std::cout << "Enter project start date (YYYY-MM-DD): ";
                                std::getline(std::cin, projectStartDate);

                                if (!std::regex_match(projectStartDate, date_pattern)) {
                                    throw std::invalid_argument("Start date must be in the format YYYY-MM-DD.");
                                }

                                std::cout << "Enter project deadline date (YYYY-MM-DD): ";
                                std::getline(std::cin, projectDeadlineDate);
                                if (!std::regex_match(projectDeadlineDate, date_pattern)) {
                                    throw std::invalid_argument("Start date must be in the format YYYY-MM-DD.");
                                }

                                std::cout << "Enter project budget (more then 0): ";
                                std::cin >> projectBudget;
                                if (projectBudget <= 0) {
                                    std::cout << "Project budget must be a positive number.\n";
                                    return;
                                }

                                Project newProject(projectName, projectBudget, projectStartDate, projectDeadlineDate);
                                employee.addNewProject(newProject);

                                std::cout << "Project added to employee " << employee.getName() << " successfully.\n";
                                return;
                            }
                        }

                        if (!employeeFound) {
                            std::cout << "Employee with EGN " << employeeEgn << " not found.\n";
                        }
                        return;
                    }
                }

                if (!departmentFound) {
                    std::cout << "Department " << departmentName << " not found in company " << company.getName() << ".\n";
                }
                return;
            }
        }

        if (!companyFound) {
            std::cout << "Company " << companyName << " not found.\n";
        }
    }

#pragma endregion

#pragma region DeleteMethods

    void DeleteCompany(std::vector<Company>& companies) {
        std::string companyName;
        std::cout << "Enter the company name to delete: ";
        std::cin.ignore(); 
        std::getline(std::cin, companyName); 

        auto it = std::find_if(companies.begin(), companies.end(), [&companyName](const Company& company) {
            return company.getName() == companyName;  
            });

        if (it != companies.end()) {
            companies.erase(it);
            std::cout << "Company '" << companyName << "' has been deleted successfully.\n";
        }
        else {
            std::cout << "Company '" << companyName << "' not found.\n";
        }
    }

    void Utils::DeleteDepartment(std::vector<Company>& companies) {
        std::string companyName, departmentName;

        std::cout << "Enter the company name: ";
        std::cin.ignore();
        std::getline(std::cin, companyName);

        std::cout << "Enter the department name to delete: ";
        std::getline(std::cin, departmentName);

        bool found = false;

        for (auto& company : companies) {
            if (company.getName() == companyName) {
                auto& departments = company.getDepartments();
                auto it = std::remove_if(departments.begin(), departments.end(),
                    [&departmentName](const Department& dept) { return dept.getName() == departmentName; });

                if (it != departments.end()) {
                    departments.erase(it, departments.end());
                    std::cout << "Department '" << departmentName << "' deleted from company '" << company.getName() << "'." << std::endl;
                    found = true;
                }
                else {
                    std::cout << "Department '" << departmentName << "' not found in company '" << company.getName() << "'." << std::endl;
                }
                break;
            }
        }

        if (!found) {
            std::cout << "No matching company or department found." << std::endl;
        }
    }

    void Utils::DeleteEmployee(std::vector<Company>& companies) {
        std::string employeeEgn;
        std::cout << "Enter the EGN (or name) of the employee to delete: ";
        std::cin.ignore(); 
        std::getline(std::cin, employeeEgn);

        bool found = false;

        for (auto& company : companies) {
            for (auto& department : company.getDepartments()) {
                auto& employees = department.getEmployees();

                auto it = std::remove_if(employees.begin(), employees.end(),
                    [&employeeEgn](const Employee& e) { return e.getEgn() == employeeEgn; });

                if (it != employees.end()) {
                    employees.erase(it, employees.end());
                    std::cout << "Employee with EGN '" << employeeEgn << "' deleted successfully from department: " << department.getName() << std::endl;
                    found = true;
                }
            }
        }

        if (!found) {
            std::cout << "Employee with EGN '" << employeeEgn << "' not found." << std::endl;
        }
    }


    void Utils::DeleteProject(std::vector<Company>& companies) {
        std::string companyName, departmentName, employeeNameOrEgn, projectName;

        std::cout << "Enter the company name: ";
        std::cin.ignore(); 
        std::getline(std::cin, companyName);

        std::cout << "Enter the department name: ";
        std::getline(std::cin, departmentName);

        std::cout << "Enter the employee name or EGN: ";
        std::getline(std::cin, employeeNameOrEgn);

        std::cout << "Enter the project name to delete: ";
        std::getline(std::cin, projectName);

        bool found = false;

        for (auto& company : companies) {
            if (company.getName() == companyName) {
                for (auto& department : company.getDepartments()) {
                    if (department.getName() == departmentName) {
                        for (auto& employee : department.getEmployees()) {
                            if (employee.getName() == employeeNameOrEgn || employee.getEgn() == employeeNameOrEgn) {

                                auto& projects = employee.getProjects();

                                auto it = std::remove_if(projects.begin(), projects.end(),
                                    [&projectName](const Project& p) { return p.getName() == projectName; });

                                if (it != projects.end()) {
                                    projects.erase(it, projects.end());
                                    std::cout << "Project '" << projectName << "' deleted from employee '" << employee.getName() << "' in department '" << department.getName() << "'." << std::endl;
                                    found = true;
                                }
                                else {
                                    std::cout << "Project '" << projectName << "' not found for employee '" << employee.getName() << "'." << std::endl;
                                }
                                break; 
                            }
                        }
                        break; 
                    }
                }
                break; 
            }
        }

        if (!found) {
            std::cout << "No matching employee, department, or project found." << std::endl;
        }
    }

#pragma endregion

}