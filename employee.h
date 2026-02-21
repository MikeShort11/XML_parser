#pragma once
#include <string>
#include <iostream>

class Employee
{
private:
  struct employeeRecord {
    int id;
    char name[30];
    char address[20];
    char city[20];
    char state[20];
    char country[20];
    char phone[12];
    double salary;
  };

  std::string name;
  int id;
  std::string address;
  std::string city;
  std::string state;
  std::string country;
  std::string phone;
  double salary;

public:
  void display(std::ostream &os) const;
  void write(std::ostream &os) const;
  void store(std::iostream &is) const;
  Employee *read(std::istream &is);
  Employee *retrieve(std::istream &is, int id);
  Employee *fromXML(std::istream &is);
};
