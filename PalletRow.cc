#include "PalletRow.hh"
#include "PalletLane.hh"
#include "PalletBlock.hh"

PalletRow::PalletRow(Height height, const PalletLane& lane)
  : lane(lane), column_count(lane.block.column_count), height(height), pallets_(column_count) {}

std::vector<size_t> 
PalletRow::getTakenSlots() const noexcept {
  std::vector<size_t> toReturn;
  for(size_t i=0; i<lane.block.column_count; ++i)
    if(pallets_[i]) toReturn.push_back(i);
  return toReturn;
}

bool 
PalletRow::isValid (RowPosition position) const noexcept {
  return position.column < column_count;
}

const Pallet::Ptr&
PalletRow::getPallet (RowPosition position) const noexcept{
  return pallets_[position.column];
}


