#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <sstream>

class Firma {
private:
    std::string type;
    bool registered_by_vat;
    std::vector<Department> departments;

public:
    Firma();
    Firma(const std::string& type, bool registered_by_vat);

    void setType(const std::string& type);
    std::string getType() const;

    void setRegisteredByVat(bool registered_by_vat);
    bool isRegisteredByVat() const;

    void addDepartment(const Department& department);
    void removeDepartment(const std::string& name);
    std::vector<Department>& getDepartments();

    friend std::ostream& operator<<(std::ostream& os, const Firma& firma);
};


class Department {
private:
    std::string name;
    int num_employees;
    std::tm creation_date;
    std::vector<Employee> employees;

public:
    Department();
    Department(const std::string& name, int num_employees, const std::tm& creation_date);

    void setName(const std::string& name);
    std::string getName() const;

    void setNumEmployees(int num_employees);
    int getNumEmployees() const;

    void setCreationDate(const std::tm& creation_date);
    std::tm getCreationDate() const;

    void addEmployee(const Employee& employee);
    void removeEmployee(const std::string& name);
    std::vector<Employee>& getEmployees();

    friend std::ostream& operator<<(std::ostream& os, const Department& department);
};

class Employee {
private:
    std::string name;
    std::string egn;
    double work_experience;
    int working_hours;
    std::vector<std::string> projects;

public:
    Employee();
    Employee(const std::string& name, const std::string& egn, double work_experience, int working_hours, const std::vector<std::string>& projects);

    void setName(const std::string& name);
    std::string getName() const;

    void setEgn(const std::string& egn);
    std::string getEgn() const;

    void setWorkExperience(double work_experience);
    double getWorkExperience() const;

    void setWorkingHours(int working_hours);
    int getWorkingHours() const;

    void addProject(const std::string& project);
    std::vector<std::string>& getProjects();

    friend std::ostream& operator<<(std::ostream& os, const Employee& employee);
};


void showMenu() {
    std::cout << "\n--- Menu ---\n";
    std::cout << "1. Add company\n";
    std::cout << "2. Remove company\n";
    std::cout << "3. Add department to a company\n";
    std::cout << "4. Remove department from a company\n";
    std::cout << "5. Add employee to a department\n";
    std::cout << "6. Remove employee from a department\n";
    std::cout << "7. Show all companies and their details\n";
    std::cout << "8. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    std::vector<Firma> firms;

    while (true) {
        showMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: { // Add company
            std::string type;
            bool registered_by_vat;
            std::cout << "Enter company type: ";
            std::cin >> type;
            std::cout << "Is the company registered by VAT? (1 for yes, 0 for no): ";
            std::cin >> registered_by_vat;
            firms.push_back(Firma(type, registered_by_vat));
            break;
        }
        case 2: { // Remove company
            std::string name;
            std::cout << "Enter company name to remove: ";
            std::cin >> name;
            auto it = std::find_if(firms.begin(), firms.end(), [&name](const Firma& f) { return f.getType() == name; });
            if (it != firms.end()) {
                firms.erase(it);
                std::cout << "Company removed successfully.\n";
            }
            else {
                std::cout << "Company not found.\n";
            }
            break;
        }
        case 3: { // Add department to a company
            std::string firm_name, department_name;
            int num_employees;
            std::tm creation_date;
            std::cout << "Enter company name: ";
            std::cin >> firm_name;
            std::cout << "Enter department name: ";
            std::cin >> department_name;
            std::cout << "Enter number of employees: ";
            std::cin >> num_employees;
            std::cout << "Enter creation date (YYYY MM DD): ";
            std::cin >> creation_date.tm_year >> creation_date.tm_mon >> creation_date.tm_mday;
            creation_date.tm_year -= 1900;
            creation_date.tm_mon--;
            auto it = std::find_if(firms.begin(), firms.end(), [&firm_name](const Firma& f) { return f.getType() == firm_name; });
            if (it != firms.end()) {
                it->addDepartment(Department(department_name, num_employees, creation_date));
                std::cout << "Department added successfully.\n";
            }
            else {
                std::cout << "Company not found.\n";
            }
            break;
        }
        case 4: { // Remove department from a company
            std::string firm_name, department_name;
            std::cout << "Enter company name: ";
            std::cin >> firm_name;
            std::cout << "Enter department name to remove: ";
            std::cin >> department_name;
            auto it = std::find_if(firms.begin(), firms.end(), [&firm_name](const Firma& f) { return f.getType() == firm_name; });
            if (it != firms.end()) {
                it->removeDepartment(department_name);
                std::cout << "Department removed successfully.\n";
            }
            else {
                std::cout << "Company not found.\n";
            }
            break;
        }
        case 5: { // Add employee to a department
            std::string firm_name, department_name, employee_name;
            std::string egn;
            double work_experience;
            int working_hours;
            std::vector<std::string> projects;
            std::cout << "Enter company name: ";
            std::cin >> firm_name;
            std::cout << "Enter department name: ";
            std::cin >> department_name;
            std::cout << "Enter employee name: ";
            std::cin >> employee_name;
            std::cout << "Enter EGN: ";
            std::cin >> egn;
            std::cout << "Enter work experience: ";
            std::cin >> work_experience;
            std::cout << "Enter working hours: ";
            std::cin >> working_hours;
            std::cout << "Enter number of projects: ";
            int num_projects;
            std::cin >> num_projects;
            for (int i = 0; i < num_projects; ++i) {
                std::string project;
                std::cout << "Enter project " << i + 1 << ": ";
                std::cin >> project;
                projects.push_back(project);
            }
            auto it = std::find_if(firms.begin(), firms.end(), [&firm_name](const Firma& f) { return f.getType() == firm_name; });
            {
                if (it != firms.end()) {
                    auto dept_it = std::find_if(it->getDepartments().begin(), it->getDepartments().end(), [&department_name](const Department& d) { return d.getName() == department_name; });
                    if (dept_it != it->getDepartments().end()) {
                        dept_it->addEmployee(Employee(employee_name, egn, work_experience, working_hours, projects));
                        std::cout << "Employee added successfully.\n";
                    }
                    else {
                        std::cout << "Department not found.\n";
                    }
                }
                else {
                    std::cout << "Company not found.\n";
                }
                break;
            }
        }
        case 6: { // Remove employee from a department
            std::string firm_name, department_name, employee_name;
            std::cout << "Enter company name: ";
            std::cin >> firm_name;
            std::cout << "Enter department name: ";
            std::cin >> department_name;
            std::cout << "Enter employee name to remove: ";
            std::cin >> employee_name;
            auto it = std::find_if(firms.begin(), firms.end(), [&firm_name](const Firma& f) { return f.getType() == firm_name; });
            if (it != firms.end()) {
                auto dept_it = std::find_if(it->getDepartments().begin(), it->getDepartments().end(), [&department_name](const Department& d) { return d.getName() == department_name; });
                if (dept_it != it->getDepartments().end()) {
                    dept_it->removeEmployee(employee_name);
                    std::cout << "Employee removed successfully.\n";
                }
                else {
                    std::cout << "Department not found.\n";
                }
            }
            else {
                std::cout << "Company not found.\n";
            }
            break;
        }
        case 7: { // Show all companies and their details
            for (const auto& firma : firms) {
                std::cout << firma;
            }
            break;
        }
        case 8: { // Exit
            return 0;
        }
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
       }
   }
