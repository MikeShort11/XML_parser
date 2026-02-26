#pragma once
#include <istream>
#include <string>
#include <iostream>

class Employee
{
private:
  // struct for constant size recording
  struct employeeRecord {
    int id;
    char name[31];
    char address[26];
    char city[21];
    char state[21];
    char country[21];
    char phone[21];
    double salary;
  };
  // attributes of class
   std::string name;
   int id;
   std::string address;
   std::string city;
   std::string state;
   std::string country;
   std::string phone;
   double salary;

  //private methods
  static std::streampos seek(std::istream &ios, const int &id);
  static std::string to_lower(std::string st);//helper to consisly convert strings to lower
  
public:
  //declae
  Employee();
  
  Employee(int id, std::string name, double salary, std::string address, std::string city,
           std::string state, std::string country, std::string phone);

  // Getters
  std::string getName() const;
  int getId() const;
  std::string getAddress() const;
  std::string getCity() const;
  std::string getState() const;
  std::string getCountry() const; 
  std::string getPhone() const;
  double getSalary() const;

  //setters 
  void setName(std::string name);
  void setId(int id);
  void setAddress(std::string addr);
  void setCity(std::string city);
  void setState(std::string state);
  void setCountry(std::string ctry); 
  void setPhone(std::string phone);
  void setSalary(double salary);

  //public methods
  void display(std::ostream &os) const;
  void write(std::ostream &os) const;
  void store(std::iostream &is) const;
  // ask about these being static
  static Employee *read(std::istream &is);
  static Employee *retrieve(std::istream &is, int id);
  static Employee *fromXML(std::istream &is);
};
