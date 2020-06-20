#include <iostream>
using namespace std;


#include "PalletRow.hh"

int main(){
  PalletRow test=PalletRow("13cm");
  auto Pallet1=std::make_unique<Pallet>(13,"6cm",45);
  test.put(Pallet1,3);
  test.put(Pallet1,4);

  cout << test;
}
