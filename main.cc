#include <iostream>
using namespace std;


#include "PalletLane.hh"

int main(){
  PalletLane lane({"12cm", "1500cm", "19m"});  

  cout << lane;

  auto Pallet1=std::make_unique<Pallet>(1,"6cm",45);
  auto Pallet2=std::make_unique<Pallet>(2,"25cm",9);
  auto Pallet3=std::make_unique<Pallet>(3,"6cm",45);

  lane.put(Pallet1,0,0);
  lane.put(Pallet1,0,1); // already used
  lane.put(Pallet2,0,2); // can't fit 25 cm > 12 cm
  lane.put(Pallet2,1,0);
  lane.put(Pallet3,1,0); // Occupied
  lane.put(Pallet3,1,1); 

  cout << lane;
}
