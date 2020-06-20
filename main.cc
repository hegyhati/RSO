#include <iostream>
using namespace std;


#include "PalletBlock.hh"

int main(){
  PalletBlock block({
    {"12cm", "1500cm","19m"},
    {"4cm","8km","6in","4ft"}
  }, 19);  

  cout << block;
  auto Pallet1=std::make_unique<const Pallet>(1,"6cm",45);
  auto Pallet2=std::make_unique<const Pallet>(2,"25cm",9);
  auto Pallet3=std::make_unique<const Pallet>(3,"6cm",45);

  block.put(Pallet1,0,0,0);
  block.put(Pallet1,0,0,1); // already used
  block.put(Pallet2,0,0,2); // can't fit 25 cm > 12 cm
  block.put(Pallet2,0,1,0);
  block.put(Pallet3,0,1,0); // Occupied
  block.put(Pallet3,0,1,51); // column index out of range 
  block.put(Pallet3,0,1,15); 

  cout << block;
}


