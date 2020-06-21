#include <iostream>
#include <string>
using namespace std;

#include "InputBuffer.hh"
#include "Forklift.hh"
#include "PalletBlock.hh"

struct TestSystem : public Serializable{
  InputBuffer input_buffer=InputBuffer(5);
  Forklift forklift = Forklift("4m");
  PalletBlock block = PalletBlock({
    {"2m","3m","4m"},
    {"12cm", "1500cm","19m"},
    {"4cm","8km","6in","4ft"}
  }, 19);  

  string toString(string indent) const noexcept override { 
    return input_buffer.toString("|")+forklift.toString("|")+block.toString("|")+endl; 
  }

  void interact(){
    string response = "";
    bool toPrint=true;
    while(response != "q") {
      if (toPrint) cout << *this << R"(
        Commands:
          q -> quit
          g ID HEIGHT -> generate new pallet on input buffer (if possible)
          l POS -> load pallet to forklift from POS position on input buffer (if possible)
          u LANE ROW COL -> unload pallet from forklift to position (LANE,ROW,COL) in the block (if possible)
          
          )";
      toPrint=true;
      cin >> response;
      if (response == "q");
      else if (response == "g"){
        uint id;
        cin >> id;
        Height height(cin);
        input_buffer.generateNewPallet(id,height);
      } else if (response == "l") {
        uint pos;
        cin >> pos;
        try { forklift.load(true,input_buffer,pos); } 
        catch (OccupiedPositionException) { cout << "Forklift already has a load\n"; toPrint=false;}
        catch (WrongPositionException) {cout << "No such position at the input buffer\n"; toPrint=false;}
        catch (Pallet::NoPalletException) {cout << "No pallet at that position in the input buffer\n"; toPrint=false;}
      } else if (response == "u") {
        uint lane,row,column;
        cin >> lane >> row >> column;
        try { forklift.unload(true,block,BlockPosition{column,row,lane});}
        catch (OccupiedPositionException) { cout << "Position already occupied in the block\n"; toPrint=false;}
        catch (WrongPositionException) {cout << "No such position at the block\n"; toPrint=false;}
        catch (Pallet::NoPalletException) {cout << "No pallet on the forklift\n"; toPrint=false;}
      } else {
        cout << "Wrong command";
        cin.ignore(500,'\n');
      }
    }
  }  
};

int main(){
  TestSystem t;
  t.interact();
}


