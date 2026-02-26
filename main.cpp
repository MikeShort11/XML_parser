#include "employee.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>

int main(int argc, char *argv[]){
  //i forgot that the program itself is an argument
  if (argc < 2){
    printf("Usage: ./main filename.xml filename.xml ...");
  }
  std::vector<std::unique_ptr<Employee>> employees;
  for (int i=1; i < argc; i++){
    std::ifstream xml_file(argv[i]);
    if (xml_file.is_open()) {
      //looping through the file to read all employees
      try {
      while(Employee* emp = Employee::fromXML(xml_file)){
        if (emp) {
          employees.push_back(std::unique_ptr<Employee>(emp));
        }
      }
      }
      catch (std::runtime_error &e){
        std::cout << "File: " << argv[i] << " contained error: " << e.what() << ". File may have only been partially read" << "\n";
      }

    }
  }
  for (int i=0; i < employees.size(); i++){
    employees[i]->display(std::cout);
  }
  std::fstream bin_file("employee.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
  for (const auto& emp: employees){
    emp->write(bin_file);
  }

employees.clear();
  bin_file.seekg(0, std::ios::beg); // Reset to start
  while (Employee* emp_ptr = Employee::read(bin_file)) {
    employees.push_back(std::unique_ptr<Employee>(emp_ptr));
}

// 7. Display the new vector
std::cout << "\n--- Data from Binary File ---\n";
for (const auto& emp : employees) {
    emp->display(std::cout);
}

bin_file.clear();
Employee* to_change = Employee::retrieve(bin_file, 12345);

if (to_change != nullptr) {
    to_change->setSalary(150000.00);
    to_change->store(bin_file);
    delete to_change;
} else {
    std::cout << "DEBUG: First retrieve failed! ID 12345 not found in file." << std::endl;
}

bin_file.clear();
// Reset stream state before the second search
bin_file.clear(); 
bin_file.seekg(0, std::ios::beg);

Employee* now_changed = Employee::retrieve(bin_file, 12345);
if (now_changed != nullptr) {
    now_changed->display(std::cout);
    delete now_changed;
} else {
    std::cout << "DEBUG: Second retrieve failed!" << std::endl;
}
  return 0;
}
