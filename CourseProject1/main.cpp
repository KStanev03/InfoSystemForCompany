#include <iostream>
#include "Company.hpp"
#include "Department.hpp" 
#include "Employee.hpp"
#include "Project.hpp"
#include "Utils.hpp" 
#include <vector>
#include <fstream>

#pragma region Load,Save and Display

void saveCompaniesToFile(const std::vector<Company>& companies) {
    std::ofstream file("companies_data.txt");
    if (file.is_open()) {
        file << companies.size() << "\n"; 
        for (const auto& company : companies) {
            file << company << "\n";
        }
        file.close();
        std::cout << "All company data saved successfully.\n";
    }
    else {
        std::cerr << "Failed to open file for writing.\n";
    }
}

void loadCompaniesFromFile(std::vector<Company>& companies) {
    std::ifstream file("companies_data.txt");

    if (file.is_open()) {
        size_t companyCount;
        file >> companyCount; 
        companies.resize(companyCount);
        for (auto& company : companies) {
            file >> company; 
        }
        file.close();
        std::cout << "All company data loaded successfully.\n";
    }
    else {
        std::cerr << "Failed to open file for reading.\n";
    }
}

void displayAllCompanies(const std::vector<Company>& companies) {
    if (companies.empty()) {
        std::cout << "No companies available.\n";
        return;
    }

    for (const auto& company : companies) {
        std::cout << company << std::endl;
    }

    for (const auto& company : companies) {
        company.printInfo();
    }
}
#pragma endregion

int main() {
    std::vector<Company> companies;
    char choice;
    char choiceDisplayAll;
    char choiceSearchFor;
    std::cout << "Please load the files first, and then save.Saving without loading will result in an empty file";
    while (true) {
        std::cout << "\n=== Menu ===\n";
        std::cout << "0. Delete (Companies/Departments/Employees/Projects)\n";
        std::cout << "1. Add a new company\n";
        std::cout << "2. Display all companies\n";
        std::cout << "3. Save companies to file\n";
        std::cout << "4. Load companies from file\n";
        std::cout << "5. Display All (Companies/Departments/Employees/Projects)\n";
        std::cout << "6. Search for (Company/Department/Employee/Project)\n";
        std::cout << "7. Update (Company/Department/Employee/Project) \n";
        std::cout << "8. Add (Company/Department/Employee/Project)\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case '1': {
            Company company;
            std::cin >> company;
            companies.push_back(company);
            break;
        }
        case '2':
            displayAllCompanies(companies);
            break;
        case '3':
            saveCompaniesToFile(companies);
            break;
        case '4':
            loadCompaniesFromFile(companies);
            break;
        case '5':
            std::cout << "\nDisplay All Menu:\n";
            std::cout << "1. Display Companies\n";
            std::cout << "2. Display Departments\n";
            std::cout << "3. Display Employees\n";
            std::cout << "4. Display Projects\n";
            std::cout << "5. Back\n";
            std::cout << "Enter your choice: ";
            std::cin >> choiceDisplayAll;
            switch (choiceDisplayAll)
            {
            case '1':
                Utils::GetAllCompanies(companies);
                break;
            case '2':
                Utils::GetAllDepartments(companies);
                break;
            case '3':
                Utils::GetAllEmployees(companies);
                break;
            case '4':
                Utils::GetAllProjects(companies);
                break;
            default:
                break;
            }
            break;
        case '6':
            std::cout << "\nSearch Menu:\n";
            std::cout << "1. Search Company\n";
            std::cout << "2. Search Department\n";
            std::cout << "3. Search Employee\n";
            std::cout << "4. Search Project\n";
            std::cout << "5. Back\n";
            std::cout << "Enter your choice: ";
            std::cin >> choiceSearchFor;
            switch (choiceSearchFor)
            {
            case '1':
                Utils::searchForCompany(companies);
                break;
            case '2':
                Utils::searchForDepartment(companies);
                break;
            case '3':
                Utils::searchForEmployee(companies);
                break;
            case '4':
                Utils::searchForProject(companies);
                break;
            default:
                break;
            }
            break;
        case '7':
            std::cout << "\nUpdate Menu:\n";
            std::cout << "1. Update Company\n";
            std::cout << "2. Update Department\n";
            std::cout << "3. Update Employee\n";
            std::cout << "4. Update Project\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
            case '1':
                Utils::updateCompany(companies);
                break;
            case '2':
                Utils::updateDepartmentInCompany(companies);
                break;
            case '3':
                Utils::updateEmployeeInDepartment(companies);
                break;
            case '4':
                Utils::updateProjectInEmployee(companies);
                break;
            default:
                std::cout << "Invalid choice.\n";
            }
            break;
        case '8':
            std::cout << "\nAdd Menu:\n";
            std::cout << "1. Add Company\n";
            std::cout << "2. Add Department\n";
            std::cout << "3. Add Employee\n";
            std::cout << "4. Add Project\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
            case '1':
                Utils::AddCompany(companies);
                break;
            case '2':
                Utils::AddDepartment(companies);
                break;
            case '3':
                Utils::AddEmployee(companies);
                break;
            case '4':
                Utils::AddProject(companies);
                break;
            default:
                std::cout << "Invalid choice.\n";
            }
            break;
        case '9':
            std::cout << "Exiting the program.\n";
            return 0;
        case '0':
            std::cout << "\nDelete Menu:\n";
            std::cout << "1. Delete Company\n";
            std::cout << "2. Delete Department\n";
            std::cout << "3. Delete Employee\n";
            std::cout << "4. Delete Project\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
            case '1':
                Utils::DeleteCompany(companies);
                break;
            case '2':
                Utils::DeleteDepartment(companies);
                break;
            case '3':
                Utils::DeleteEmployee(companies);
                break;
            case '4':
                Utils::DeleteProject(companies);
                break;
            default:
                std::cout << "Invalid choice.\n";
            }
            break;
        default:
            std::cerr << "Invalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}
