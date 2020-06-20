#include "PalletRow.hh"
#include "PalletLane.hh"

PalletRow::PalletRow(const Height& height, const PalletLane& lane)
  : height(height), lane(lane), pallets_(column_count_) {}

bool PalletRow::put(std::unique_ptr<Pallet>& pallet, uint column) noexcept {
  if (column >= column_count_ || pallets_[column] || !pallet || height < pallet->getHeight()) return false;
  else {
    pallets_[column] = std::move(pallet);
    return true;
  }
}

std::vector<uint> PalletRow::getTakenSlots() const noexcept {
  std::vector<uint> toReturn;
  for(uint i=0; i<column_count_; ++i)
    if(pallets_[i]) toReturn.push_back(i);
  return toReturn;
}

const Pallet& PalletRow::operator [] (uint column) const noexcept(false) {
  if (column >= column_count_ || ! pallets_[column]) throw NoPalletException();
  else return *pallets_[column];
}


std::ostream& operator << (std::ostream& s, const PalletRow& pr) {
  s << "\t Row ["<< pr.getLevel() << "] height: " << pr.height << std::endl;
  for(auto slot: pr.getTakenSlots())
    s << "\t\t Slot "<< slot <<": " << pr[slot] << std::endl;
  return s;
}

uint PalletRow::getLevel() const noexcept {
  for(uint row=0; row<lane.row_count; ++row)
    if(& lane[row] == this) return row;
  return lane.row_count;
}
