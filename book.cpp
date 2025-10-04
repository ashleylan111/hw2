#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "book.h"

Book::Book(const std::string& category, 
const std::string& name, 
double price, 
int qty,
const std::string& isbn, 
const std::string& author) 
: Product(category, name, price, qty), 
isbn_(isbn), author_(author){}


/**
* Returns the appropriate keywords that this product should be associated with
*/
std::set<std::string> Book::keywords() const{
  std::set<std::string> keys = parseStringToWords(name_); //Name of the product
  std::set<std::string> authors = parseStringToWords(author_); //Author of the book 
  keys.insert(authors.begin(), authors.end());
  keys.insert(isbn_);
  return keys;

}

/**
* Returns a string to display the product info for hits of the search
*/
std::string Book::displayString() const {
  std::ostringstream oss;
  std::stringstream ss;
  ss << name_ << std::endl;
  ss << "Author: " << author_ << " ISBN: " << isbn_ << std::endl;
  ss << price_ << " " << qty_ << " left." << std::endl;
  return ss.str();
}

/**
* Outputs the product info in the database format
*/
void Book::dump(std::ostream& os) const{
  os << category_ << std::endl;
  os << name_ << std::endl;
  os << price_ << std::endl;
  os << qty_ << std::endl;
  os << isbn_ << std::endl;
  os << author_ << std::endl;

}



