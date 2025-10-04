#include "util.h"
#include <iostream>

int main(){

std::set<std::string> words = parseStringToWords("Hello, this is a test. Testing.");

std::cout << "Parsed words: " << std::endl;
for (std::set<std::string>::iterator it = words.begin(); it != words.end(); ++it){
  std::cout << *it << std::endl;
}


//Testing intersection and union with numerical sets 
std::set<int> s1; s1.insert(1); s1.insert(2); s1.insert(3);
std::set<int> s2; s2.insert(2); s2.insert(3); s2.insert(4);

//Intersection testing
std::set<int> intersection = setIntersection(s1, s2);
std::cout << "Intersection: " << std::endl;
for (std::set<int>::iterator it = intersection.begin(); it != intersection.end(); ++it){
  std::cout << *it << " ";
}
std::cout << std::endl;

//Union testing 
std::set<int> union = setUnion(s1, s2);
std::cout << "Union: ";
for (std::set<int>::iterator it = union.begin(); it != union.end(); ++it){
  std::cout << *it << " ";
}
std::cout << std::endl;

return 0;



}