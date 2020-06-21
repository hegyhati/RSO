#include <iostream>
using namespace std;


#include "Forklift.hh"
#include "PalletBlock.hh"

int main(){
  PalletBlock block({
    {"2m","3m","4m"},
    {"12cm", "1500cm","19m"},
    {"4cm","8km","6in","4ft"}
  }, 19);  

  Forklift fl("4m"); // 2 rows need to be cleared in the first lane

  Pallet::Ptr input_buffer;
  

  cerr << block;
  cerr << fl;

  
  cerr << "\n\n Make Palett and load to Forklift \n\n";
  input_buffer=std::make_unique<const Pallet>(1,"1m",45);
  fl.load(input_buffer);
  cerr << block;
  cerr << fl;

  cerr << "\n\n Unload content to position 0,0,0 \n\n";
  try{fl.unload(block,{0,0,0});} catch (Forklift::OperationErrorException e) {cerr<<e.message;}
  cerr << block;
  cerr << fl;

  cerr << "\n\n Make Palett and load to Forklift \n\n";
  input_buffer=std::make_unique<const Pallet>(2,"3.5m",45);
  fl.load(input_buffer);
  cerr << block;
  cerr << fl;

  cerr << "\n\n Try to unload to the same position and fail \n\n";
  try{fl.unload(block,{0,0,0});} catch (Forklift::OperationErrorException e) {cerr<<e.message;}
  cerr << block;
  cerr << fl;

  cerr << "\n\n Try to unload to the position behind and fail \n\n";
  try{fl.unload(block,{0,0,1});} catch (Forklift::OperationErrorException e) {cerr<<e.message;}
  cerr << block;
  cerr << fl;

  cerr << "\n\n Try to unload to the position above and fail due to size \n\n";
  try{fl.unload(block,{0,1,0});} catch (Forklift::OperationErrorException e) {cerr<<e.message;}
  cerr << block;
  cerr << fl;

  cerr << "\n\n Try to unload to the position above that and succeed \n\n";
  try{fl.unload(block,{0,2,0});} catch (Forklift::OperationErrorException e) {cerr<<e.message;}
  cerr << block;
  cerr << fl;
  
}


