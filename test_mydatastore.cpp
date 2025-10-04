#include "mydatastore.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include <iostream>

int main() {
  MyDataStore ds;

  //Adding users
  ds.addUser(new User("amanda", 100.0, 1));
  ds.addUser(new User("bob", 50.0, 1));

  //Adding example products
  ds.addProduct(new Book("book", "Harry Potter", 15.0, 2, "1110000111", "J.K. Rowling"));
  ds.addProduct(new Clothing("clothing", "Jeans", 45.0, 2, "American Eagle", "M"))
  ds.addProduct(new Movie("movie", "JUMANJI", 13.0, 1, "Adventure", "PG-13"));

  //SEARCH TEST
  std::vector<std::string> terms;
  terms.push_back("inception");
  std::vector<Product*> hits = ds.search(terms, 1);
  std::cout << "Search results for 'inception': " << std::endl;
  for (std::vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it){
    std::cout << (*it)->displayString() << std::endl;
  }

  //ADD TO CART AND VIEW TEST
  if(!hits.empty()){
    ds.addToCart("amanda", hits[0]);
    std::cout << "\nAmanda's cart: " << std::endl;
    ds.viewCart("amanda");
  }

  //BUYING
  std::cout << "\nAmanda buys her cart" << std::endl;
  ds.buyCart("amanda");
  ds.viewCart("amanda");


  return 0;
  
}