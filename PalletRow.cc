#include "PalletRow.hh"
#include "PalletLane.hh"
#include "PalletBlock.hh"

PalletRow::PalletRow(Height height, const PalletLane& lane)
  : lane(lane), column_count(lane.block.column_count), height(height), pallets_(column_count) {}

std::vector<uint> 
PalletRow::getTakenSlots() const noexcept {
  std::vector<uint> toReturn;
  for(uint i=0; i<lane.block.column_count; ++i)
    if(pallets_[i]) toReturn.push_back(i);
  return toReturn;
}

std::ostream& 
operator << (std::ostream& s, const PalletRow& pr) {
  s << "    Row ["<< pr.lane.getLevelOf(pr) << "] height: " << pr.height << std::endl;
  for(auto slot: pr.getTakenSlots())
    s << "      Slot "<< slot <<": " << pr[RowPosition{slot}] << std::endl;
  return s;
}

bool 
PalletRow::isValid (RowPosition position) const noexcept {
  return position.column < column_count;
}

const Pallet::Ptr&
PalletRow::getPallet (RowPosition position) const noexcept{
  return pallets_[position.column];
}


