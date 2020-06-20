#include "PalletLane.hh"


PalletLane::PalletLane(std::vector<Height> row_heights)
: row_count(row_heights.size()) {
  for(uint row=0; row<row_count; ++row)
    pallet_rows_.push_back(PalletRow(row_heights[row]));
}

const PalletRow& PalletLane::operator [] (uint row) const noexcept {
  return pallet_rows_[row];
}

bool PalletLane::put(std::unique_ptr<Pallet>& pallet, uint row, uint column) noexcept {
  return pallet_rows_[row].put(pallet,column);
}

Height PalletLane::getTotalHeight() const {
  Height total("0m");
  for(const auto& row: pallet_rows_)
    total+=row.height;
  return total;
}

std::ostream& operator << (std::ostream& s, const PalletLane& pl){
  s << "Lane total height: " << pl.getTotalHeight() << std::endl;
  for(uint row=0; row<pl.row_count; ++row) s<<pl[row];
  return s;
}
