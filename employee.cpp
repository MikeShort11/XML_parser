#include "employee.h"
#include <stdexcept>
#include <algorithm>
#include <string>


//default constuctor to make sure id and salary exist
Employee::Employee() : id(0), salary(0.0) {}

// Full constructor for easy testing
Employee::Employee(int id, std::string name, double salary, std::string addr = "", 
         std::string city = "", std::string state = "", 
         std::string country = "", std::string phone = "")
    : id(id), name(name), salary(salary), address(addr), 
      city(city), state(state), country(country), phone(phone) {}


//to lower for consistant cases
std::string Employee::to_lower(std::string st){
  std::transform(st.begin(), st.end(), st.begin(), ::tolower);
  return st;
};

//Defining getters
std::string Employee::getName() const { return name; }
int Employee::getId() const { return id; } 
std::string Employee::getAddress() const { return address; }
std::string Employee::getCity() const { return city; }
std::string Employee::getState() const { return state; }
std::string Employee::getCountry() const { return country; } 
std::string Employee::getPhone() const { return phone; }    
double Employee::getSalary() const { return salary; }

//define setters
void Employee::setName(std::string name){this->name = name;}
void Employee::setId(int id){this->id = id;}
void Employee::setAddress(std::string addr){this->address = addr;}
void Employee::setCity(std::string city){this->city= city;}
void Employee::setState(std::string state){this->state = state;}
void Employee::setCountry(std::string ctry){this->country = ctry;}
void Employee::setPhone(std::string phone){this->phone = phone;}
void Employee::setSalary(double salary){this->salary = salary;}

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
    bool in_employee = false;
    bool name_found = false;
    bool id_found = false;
    bool address_found = false;
    bool state_found = false;
    bool country_found = false;
    bool phone_found = false;
    bool city_found = false;
    bool salary_found = false;

    std::string chunk;
    std::string open_tag;
    std::string closing_tag;
    std::string data;

    
    while ((getline(is, chunk, '<'))){ // read to the first tag open
      // read to tag close, if it dosent exist return null
      if (!std::getline(is, open_tag, '>')) return nullptr; 
      open_tag = Employee::to_lower(open_tag);
      if (open_tag == "employee") { // employee open tag found
        // we are inside an eployee object
        in_employee = true;
        break;
      };
    };
    if (!in_employee) return nullptr; // if no employee is found return nullptr
    //Now we have exited a tag and can start getting data
    Employee *emp = new Employee(); // default employee DELETE THIS IF YOU THROW BELOW THIS LINE ---> _____________

    while ((getline(is, chunk, '<'))){ // now we are looking for an internal tag
      //read to >, catch unexpected EOF and conver tag to lowercase
      if (!getline(is, open_tag, '>')) throw std::runtime_error("Unexpected EOF");
      open_tag = to_lower(open_tag);
       
      // now we are inside a tag inside an emplyee
      //read to the next tag start
      // check that the data is not repeated in the XML and throw if it is
      // also check that the tag is a valid value
      getline(is, data, '<');
      //apparently c++ switch cases cant compare strings
      if (open_tag == "name") {
          if (name_found) { delete emp; throw std::runtime_error("Multiple <name> tags"); }
          emp->name = data;
          name_found = true;
      }
      else if (open_tag == "address") {
          if (address_found) { delete emp; throw std::runtime_error("Multiple <address> tags"); }
          emp->address = data;
          address_found = true;
      }
      else if (open_tag == "city") {
          if (city_found) { delete emp; throw std::runtime_error("Multiple <city> tags"); }
          emp->city = data;
          city_found = true;
      }
      else if (open_tag == "state") {
          if (state_found) { delete emp; throw std::runtime_error("Multiple <state> tags"); }
          emp->state = data;
          state_found = true;
      }
      else if (open_tag == "country") {
          if (country_found) { delete emp; throw std::runtime_error("Multiple <country> tags"); }
          emp->country = data;
          country_found = true;
      }
      else if (open_tag == "phone") {
          if (phone_found) { delete emp; throw std::runtime_error("Multiple <phone> tags"); }
          emp->phone = data;
          phone_found = true;
      }
      else if (open_tag == "id") {
          if (id_found) { delete emp; throw std::runtime_error("Multiple <id> tags"); }
          emp->id = std::stoi(data);
          id_found = true;
      }
      else if (open_tag == "salary") {
          if (salary_found) { delete emp; throw std::runtime_error("Multiple <salary> tags"); }
          emp->salary = std::stod(data);
          salary_found = true;
      }
      else if (open_tag == "/employee") {
        in_employee = false;
        break;
      }
      else {
          delete emp;
          throw std::runtime_error("Invalid tag: <" + open_tag + ">");
      }

      // now we are ready to go to the closing tag and start over
      std::getline(is, closing_tag, '>');
      if (to_lower(closing_tag) != "/" + open_tag) { //check that the closing tag is what we expect
          delete emp;
          throw std::runtime_error("Missing </" + open_tag + "> tag");
      }
    }    
    if (!name_found || !id_found) {delete emp; throw std::runtime_error("Name or ID not provided");}
    return emp; // return the final employee
  };
