#include "Serializable.hh"

const std::string Serializable::endl="\n";
const std::string Serializable::indentincrement="  ";

#include "Length.hh"
std::string
BasicLength::toString (std::string indent) const noexcept{ 
  return  std::to_string(to(getSuggestedUnit())) + " " + getSuggestedUnit();
}


#include "Pallet.hh"
std::string
Pallet::toString(std::string indent) const noexcept{
  return indent
    + "[ "
    + "Product: " + std::to_string(product_id)
    + " | "
    + "Height: " + height.toString()
    + " | "
    + "Quantity: " + std::to_string(quantity)
    + " ]";
}

#include "PalletRow.hh"
#include "PalletLane.hh"
std::string 
PalletRow::toString(std::string indent) const noexcept{
  std::string toReturn = indent +"Row [" + std::to_string(lane.getLevelOf(*this)) + "] height: " + height.toString() + endl;
  for(auto slot: getTakenSlots())
    toReturn += indent + indentincrement + "Slot " + std::to_string(slot) + ": " + getPallet({slot})->toString() + endl;
  return toReturn;
}

#include "PalletLane.hh"
#include "PalletBlock.hh"
std::string 
PalletLane::toString(std::string indent) const noexcept{
  std::string toReturn = indent + "Lane [" + std::to_string(block.getOrderOf(*this)) + "] total height: " + getTotalHeight().toString() + endl;
  for(uint row=0; row<row_count; ++row) 
    toReturn += pallet_rows_[row].toString(indent+indentincrement);
  return toReturn;
}

#include "PalletBlock.hh"
std::string 
PalletBlock::toString(std::string indent) const noexcept{
  std::string toReturn = "Block, number of columns: " + std::to_string(column_count) + endl;
  for(uint lane=0; lane<lane_count; ++lane)
    toReturn += pallet_lanes_[lane].toString(indent+indentincrement);
  return toReturn;
}


#include "Forklift.hh"
std::string 
Forklift::toString(std::string indent) const noexcept{
  return indent + "Forklift, height: " + height.toString() + ", load: " +( isLoaded() ? load_->toString() : "---");
}

#include "InputBuffer.hh"
std::string
InputBuffer::toString(std::string indent) const noexcept {
  std::string toReturn = indent +"Input Buffer, max capacity:" + std::to_string(max_capacity) + endl;
  for(uint slot=0;slot<max_capacity;++slot)
    toReturn += indent + indentincrement + "Slot " + std::to_string(slot) + ": " 
    + (getPallet(slot) ? getPallet(slot)->toString() : " empty ") + endl;
  return toReturn;
}
