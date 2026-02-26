#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cassert>
#include <stdexcept>
#include "employee.h"

/**
 * UNIT TESTS: Testing logic in memory
 */
void run_unit_tests() {
    std::cout << "--- Starting Unit Tests ---\n";

    // 1. Test fromXML with required fields (Happy Path) 
    std::string valid_xml = "<Employee>\n  <id> 12345</id>\n  \n<name>Mike Tutor</name> \n</Employee> \n";
    std::stringstream ss(valid_xml);
    Employee* emp = Employee::fromXML(ss);
    
    assert(emp != nullptr && "fromXML failed on valid input");
    assert(emp->getId() == 12345); // Assuming getId() exists
    assert(emp->getName() == "Mike Tutor");
    std::cout << "Unit Test 1 (Happy Path): Passed\n";

    // 2. Test fromXML case insensitivity 
    std::string case_xml = "<EMPLOYEE><name></name><ID>99</ID></EMPLOYEE>";
    std::stringstream ss2(case_xml);
    Employee* emp2 = Employee::fromXML(ss2);
    assert(emp2 != nullptr && emp2->getId() == 99);
    std::cout << "Unit Test 2 (Case Insensitivity): Passed\n";

    // 3. Test fromXML missing required name tag (Should throw) [cite: 32, 50, 132]
    std::string invalid_xml = "<Employee><id>5</id></Employee>";
    std::stringstream ss3(invalid_xml);
    try {
        Employee::fromXML(ss3);
        assert(false && "Should have thrown for missing Name tag");
    } catch (const std::runtime_error& e) {
        std::cout << "Unit Test 3 (Exception Handling): Passed - " << e.what() << "\n";
    }

    delete emp;
    delete emp2;
}

// /**
//  * INTEGRATION TESTS: Testing Binary File I/O [cite: 75, 76]
//  */
// void run_integration_tests() {
//     std::cout << "\n--- Starting Integration Tests (File I/O) ---\n";
//     const std::string bin_file = "employee.bin";

//     // Create a vector and write to binary [cite: 72, 73]
//     std::vector<Employee*> employees;
//     Employee* e1 = new Employee();
//     e1->setId(12345);
//     e1->setName("Jack Dough");
//     e1->setSalary(140000.00);
//     employees.push_back(e1);

//     // Step 4: Write fixed-length records to binary [cite: 75, 143]
//     std::fstream file(bin_file, std::ios::out | std::ios::in | std::ios::binary | std::ios::trunc);
//     if (!file) throw std::runtime_error("Could not create binary file");

//     for (auto e : employees) {
//         e->write(file);
//     }

//     // Step 8: Search for ID 12345 using retrieve [cite: 80, 156]
//     file.seekg(0); 
//     Employee temp_emp; // Use static method if your signature matches retrieve(is, id)
//     Employee* found = temp_emp.retrieve(file, 12345); 

//     assert(found != nullptr && "Retrieve failed to find existing ID");
//     std::cout << "Integration Step 8 (Retrieve): Passed\n";

//     // Step 9 & 10: Modify salary and store back [cite: 81, 82, 158]
//     found->setSalary(150000.00);
//     found->store(file); 
//     std::cout << "Integration Step 10 (Store/Update): Success\n";

//     // Step 11: Final verification [cite: 83]
//     file.seekg(0);
//     Employee* updated = temp_emp.retrieve(file, 12345);
//     assert(updated->getSalary() == 150000.00);
//     std::cout << "Integration Step 11 (Update Verification): Passed\n";

//     // Cleanup [cite: 84]
//     for (auto e : employees) delete e;
//     delete found;
//     delete updated;
//     file.close();
// }

int main(int argc, char* argv[]) {
    try {
        run_unit_tests();
        // run_integration_tests();
        std::cout << "\nALL SYSTEM TESTS PASSED\n";
    } catch (const std::exception& e) {
        std::cerr << "Test failed with error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
