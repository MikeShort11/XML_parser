#include "employee.h"
#include <stdexcept>
#include <algorithm>

std::string Employee::to_lower(std::string st){
  std::transform(st.begin(), st.end(), st.begin(), ::tolower);
  return st;
};


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

  Employee *Employee::fromXML(std::istream &is)
  {
    //TODO: some more error checking is needed:
    // same tag twice
    // wrong tag in there
    // data convertion
    // required fields 

    //some storage and tracking vars on the stack
    bool in_employee = false;
    std::string chunk;
    std::string open_tag;
    std::string closing_tag;
    std::string data;

    
    while ((getline(is, chunk, '<'))){ // read to the first tag open
      // read to tag close, if it dosent exist return null
      if (!std::getline(is, open_tag, '>')) return nullptr; 
        if (open_tag == "employee") { // employee open tag found
          // we are inside an eployee object
          in_employee = true;
          break;
        };
    };
    if (!in_employee) return nullptr; // if no employee is found return nullptr
    //Now we have exited a tag and can start getting data
    Employee *emp = new Employee(); // default employee

    while ((getline(is, chunk, '<'))){ // now we are looking for an internal tag
      //read to >, catch unexpected EOF and conver tag to lowercase
      if (!getline(is, open_tag, '>')) throw std::runtime_error("Unexpected EOF");
      open_tag = to_lower(open_tag);

      // return emp when the employee is empty
      if (open_tag == "/employee") {
        return emp;
      }

      // now we are inside a tag inside an emplyee
      //read to the next tag start
      getline(is, data, '<');
      //apparently c++ switch cases cant compare strings
      if (open_tag == "name") emp->name = data;
      if (open_tag == "address") emp->address = data;
      if (open_tag == "city") emp->city = data;
      if (open_tag == "state") emp->state = data;
      if (open_tag == "country") emp->country = data;
      if (open_tag == "phone") emp->phone = data;
      //the two weird ones that need data converstion
      // should throw the right error if the string cant convert?
      if (open_tag == "id") emp->id= std::stoi(data);
      if (open_tag == "salary") emp->salary = stod(data);

      // now we are ready to go to the closing tag and start over
      std::getline(is, closing_tag, '>');
      if (to_lower(closing_tag) != "/" + open_tag) {
          throw std::runtime_error("Missing </" + open_tag + "> tag");
      }
    }    
    return emp; // return the final employee
  };
