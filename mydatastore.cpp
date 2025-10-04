#include "datastore.h"
#include "mydatastore.h"
#include "util.h"
#include "user.h"
#include "product.h"
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <string>
#include <iostream>

MyDataStore::MyDataStore(){


}

MyDataStore::~MyDataStore(){


  carts_.clear();

  for (auto p : products_){
    delete p;
  }
  products_.clear();

  for (auto u : users_) {
    delete u;
  }

  users_.clear();



}

void MyDataStore::addProduct(Product* p){
  products_.push_back(p);
  std::set<std::string> keys = p->keywords();
  
  for (std::set<std::string>::iterator it = keys.begin(); it != keys.end(); ++it){
    keywMap_[*it].insert(p);
  }
}

void MyDataStore::addUser(User* u){
  if (u == nullptr){
    return;
  }
  users_.push_back(u);
  userMap_[convToLower(u->getName())] = u;

}

/**
* Performs a search of products whose keywords match the given "terms"
*  type 0 = AND search (intersection of results for each term) while
*  type 1 = OR search (union of results for each term)
*/
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  std::set<Product*> results;
  
  if(terms.size() == 0){
    return std::vector<Product*>();
  }

  //First term
  std::map<std::string, std::set<Product*>>::iterator it = keywMap_.find(terms[0]);
  if(it!= keywMap_.end()){
    results = it->second;
  }

  //Process the rest 
  for (size_t i = 1; i < terms.size(); i++){
    std::map<std::string, std::set<Product*>>::iterator next = keywMap_.find(terms[i]);
    std::set<Product*> setOfTerms;
    if (next != keywMap_.end()){
      setOfTerms = next->second;
    }

    if (type == 0){
      results = setIntersection(results, setOfTerms);
    }
    else {
      results = setUnion(results, setOfTerms);
    }

  }

  return std::vector<Product*>(results.begin(), results.end());

}

void MyDataStore::dump(std::ostream& ofile){
  ofile << "<products>" << std::endl;
  for (std::vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
    (*it)->dump(ofile);
  }
  ofile << "</products>" << std::endl;

  ofile << "<users>" << std::endl;
  for (std::vector<User*>::iterator it = users_.begin(); it != users_.end(); ++it){
    (*it)->dump(ofile);
  }
  ofile << "</users>" << std::endl;

}

void MyDataStore::addToCart(const std::string& username, Product* p){
  if (p == nullptr){
    std::cout << "Invalid request" << std::endl;
    return;
  }

  std::map<std::string, User*>::iterator it = userMap_.find(convToLower(username));
  if (it == userMap_.end()){
    std::cout << "Invalid request" << std::endl;
    return;
  }

  User* user = it->second;
  carts_[convToLower(username)].push_back(p);

}

void MyDataStore::viewCart(const std::string& username){
  
  std::string lowUsername = convToLower(username);

  //Check is the user exists on the map
  std::map<std::string, User*>::iterator userIt = userMap_.find(lowUsername);
  if(userIt == userMap_.end()){
    std::cout << "Invalid username" << std::endl;
    return;
  }

  //Check if the user has a cart
  std::map<std::string, std::deque<Product*>>::iterator cartIt = carts_.find(lowUsername); 
  if (carts_.find(lowUsername) == carts_.end() || carts_[lowUsername].empty()){
    std::cout << "Cart is empty" << std::endl;
    return;
  }

  //Print items
  int idx = 1;
  std::deque<Product*>::iterator prodIt;
  for (prodIt = cartIt->second.begin(); prodIt != cartIt->second.end(); ++prodIt){
    std::cout << "Item " << idx++ << std::endl;
    std::cout << (*prodIt)->displayString() << std::endl;
    std::cout << std::endl;
  }

}

void MyDataStore::buyCart(const std::string& username){

  std::string lowUsername = convToLower(username);

  //Finding the user First
  std::map<std::string, User*>::iterator userIt = userMap_.find(convToLower(username));
  if(userIt == userMap_.end()){
    std::cout << "Invalid username" << std::endl;
    return;
  }
  User* user = userIt->second;

  //Finding the user's cart
  std::map<std::string, std::deque<Product*>>::iterator cartIt = carts_.find(lowUsername);
  if (cartIt == carts_.end()){
    //Cart does not exist, however there is a user
    return;
  }

  std::deque<Product*> remains;

  for(std::deque<Product*>::iterator prodIt = cartIt->second.begin(); 
  prodIt != cartIt->second.end(); ++prodIt){
    Product* p = *prodIt;
    if(p!= nullptr && p->getQty() > 0 && user->getBalance() >= p->getPrice()){
      user->deductAmount(p->getPrice());
      p->subtractQty(1);
    } else {
      remains.push_back(p);
    }

  }
  
  cartIt->second = remains;



}



