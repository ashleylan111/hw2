#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"
#include <vector>
#include <string>
#include <deque>
#include <set>
#include <map>

class MyDataStore : public DataStore{
public:
  MyDataStore();
  ~MyDataStore();

  void addProduct(Product* p) override;
  void addUser(User* u) override;
  virtual std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
  virtual void dump(std::ostream& ofile) override;

  void addToCart(const std::string& username, Product* p);
  void viewCart(const std::string& username);
  void buyCart(const std::string& username);

private:
  std::vector<Product*> products_;
  std::vector<User*> users_;
  std::map<std::string, std::set<Product*>> keywMap_;
  std::map<std::string, std::deque<Product*>> carts_;
  std::map<std::string, User*> userMap_;

};

#endif

