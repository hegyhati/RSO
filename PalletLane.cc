#include "PalletLane.hh"
#include "PalletBlock.hh"


PalletLane::PalletLane(std::vector<Height> row_heights, PalletBlock& block)
: block(block), row_count(row_heights.size()) {
  pallet_rows_.reserve(row_count);
  for(uint row=0; row<row_count; ++row)
    pallet_rows_.emplace_back(row_heights[row], *this);
}

const PalletRow& PalletLane::operator [] (uint row) const noexcept {
  return pallet_rows_[row];
}

bool PalletLane::put(Pallet::Ptr& pallet, uint row, uint column) noexcept {
  return pallet_rows_[row].put(pallet,column);
}

Height PalletLane::getTotalHeight() const {
  Height total("0m");
  for(const auto& row: pallet_rows_)
    total+=row.height;
  return total;
}

std::ostream& operator << (std::ostream& s, const PalletLane& pl){
  s << "  Lane total height: " << pl.getTotalHeight() << std::endl;
  for(uint row=0; row<pl.row_count; ++row) s<<pl[row];
  return s;
}
