#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "clothing.h"

Clothing::Clothing(const std::string& category, 
  const std::string& name, 
  double price, int qty, 
  const std::string& size, 
  const std::string& brand)
: Product(category, name, price, qty), 
size_(size), brand_(brand){}


/**
* Returns the appropriate keywords that this product should be associated with
*/
std::set<std::string> Clothing::keywords() const{
  std::set<std::string> keys = parseStringToWords(name_); //Name of the product
  std::set<std::string> brands = parseStringToWords(brand_); 
  keys.insert(brands.begin(), brands.end());
  keys.insert(size_);
  return keys;

}

/**
* Returns a string to display the product info for hits of the search
*/
std::string Clothing::displayString() const {
  std::stringstream ss;
  ss << name_ << std::endl;
  ss << "Size: " << size_ << " Brand: " << brand_ << std::endl;
  ss << price_ << " " << qty_ << " left." << std::endl;
  return ss.str();
}

/**
* Outputs the product info in the database format
*/
void Clothing::dump(std::ostream& os) const{
  os << category_ << std::endl;
  os << name_ << std::endl;
  os << price_ << std::endl;
  os << qty_ << std::endl;
  os << size_ << std::endl;
  os << brand_ << std::endl;

 
 
}