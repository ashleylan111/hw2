#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "movie.h"

Movie::Movie(const std::string& category, 
  const std::string& name, 
  double price, int qty, 
  const std::string& genre, 
  const std::string& rating)
: Product (category, name, price, qty), 
genre_(genre), rating_(rating){}

/**
* Returns the appropriate keywords that this product should be associated with
*/
std::set<std::string> Movie::keywords() const{
  std::set<std::string> keys = parseStringToWords(name_); //Name of the product
  std::set<std::string> genres = parseStringToWords(genre_); 
  keys.insert(genres.begin(), genres.end());
  keys.insert(rating_);
  return keys;

}

/**
* Returns a string to display the product info for hits of the search
*/
std::string Movie::displayString() const {
  std::stringstream ss;
  ss << name_ << std::endl;
  ss << "Genre: " << genre_ << " Rating: " << rating_ << std::endl;
  ss << price_ << " " << qty_ << " left." << std::endl;
  return ss.str();
}

/**
* Outputs the product info in the database format
*/
void Movie::dump(std::ostream& os) const{
  os << category_ << std::endl;
  os << name_ << std::endl;
  os << price_ << std::endl;
  os << qty_ << std::endl;
  os << genre_ << std::endl;
  os << rating_ << std::endl;

}
