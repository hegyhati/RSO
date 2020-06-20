#include "PalletRow.hh"

PalletRow::PalletRow(const Height& height)
  : height(height), pallets_(column_count_) {}

bool PalletRow::put(std::unique_ptr<Pallet>& pallet, uint column) noexcept {
  if (column >= column_count_ || pallets_[column] || !pallet) return false;
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
  s << "Row height: " << pr.height << std::endl;
  for(auto slot: pr.getTakenSlots())
    s << "\t Slot "<< slot <<": " << pr[slot] << std::endl;
  return s;
}
