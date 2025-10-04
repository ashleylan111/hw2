#include "book.h"
#include <iostream>
int main() {

  //CREATING THE BOOK OBJECT
  Book b("book", "The Great Gatsby", 10.99, 3, "0123456789", "F. Scott Fitzgerald");

  //DISPLAY STRING TEST
  std::cout << "Display String Test:" << std::endl;
  std::cout << b.displayString() << std::endl;

  //DUMP TEST
  std::cout << "\nDump Test" << std::endl;
  b.dump(std::cout);

  //KEYWORDS TEST
  std::cout << "\nKeywords Test" << std::endl;
  std::set<std::string> keys = b.keywords();
  for (std::set<std::string>::iterator it = keys.begin(); it!= keys.end(); ++it){
    std::cout << *it << std::endl;
  }

  return 0;

}