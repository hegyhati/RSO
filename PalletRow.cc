#include "PalletRow.hh"
#include "PalletLane.hh"
#include "PalletBlock.hh"

PalletRow::PalletRow(const Height& height, const PalletLane& lane)
  : lane(lane), height(height), pallets_(lane.block.column_count) {}

bool 
PalletRow::put(Pallet::Ptr& pallet, uint column) noexcept {
  if (column >= lane.block.column_count || pallets_[column] || !pallet || height < pallet->getHeight()) return false;
  else {
    pallets_[column] = std::move(pallet);
    return true;
  }
}

std::vector<uint> 
PalletRow::getTakenSlots() const noexcept {
  std::vector<uint> toReturn;
  for(uint i=0; i<lane.block.column_count; ++i)
    if(pallets_[i]) toReturn.push_back(i);
  return toReturn;
}

const Pallet& 
PalletRow::operator [] (uint column) const noexcept(false) {
  if (column >= lane.block.column_count || ! pallets_[column]) throw NoPalletException();
  else return *pallets_[column];
}


std::ostream& 
operator << (std::ostream& s, const PalletRow& pr) {
  s << "    Row ["<< pr.getLevel() << "] height: " << pr.height << std::endl;
  for(auto slot: pr.getTakenSlots())
    s << "      Slot "<< slot <<": " << pr[slot] << std::endl;
  return s;
}

bool 
PalletRow::isEmpty(uint column) const noexcept {
  if(column >= lane.block.column_count ) return false;
  else return ! pallets_[column];
}

uint 
PalletRow::getLevel() const noexcept {
  for(uint row=0; row<lane.row_count; ++row)
    if(& (lane[row]) == this) return row;  
  return lane.row_count;
}
