#include "employee.h"

void Employee::display(std::ostream &os) const
{
  os << "ID: " << id << std::endl;
  os << "Name: " << name << std::endl;
  os << "Address: " << address << std::endl;
  os << "City: " << city << std::endl;
  os << "State: " << state << std::endl;
  os << "Country: " << country << std::endl;
  os << "Phone: " << phone << std::endl;
  os << "Salary: " << salary << std::endl;
}

void Employee::write(std::ostream &os) const
{
  //needs to be decared and {} so that there isnt garbage data
  employeeRecord record = {};
  //easy writes
  record.id = this->id;
  record.salary = this->salary;
  //copy strings into char arrays, use larges size allowed with null terminator
  this->name.copy(record.name, sizeof(record.name) - 1);
  this->address.copy(record.address, sizeof(record.address) - 1);
  this->city.copy(record.city, sizeof(record.city) - 1);
  this->state.copy(record.state, sizeof(record.state) - 1);
  this->country.copy(record.country, sizeof(record.country) - 1);
  this->phone.copy(record.phone, sizeof(record.phone) - 1);
  //reinterpret record as binary data and write it to the stream
  os.write(reinterpret_cast<char*>(&record), sizeof(record));
  }

