#include "PalletLane.hh"
#include "PalletBlock.hh"
#include <algorithm>


PalletLane::PalletLane(std::vector<Height> row_heights, PalletBlock& block)
: block(block), row_count(row_heights.size()) {
  pallet_rows_.reserve(row_count);
  for(uint row=0; row<row_count; ++row)
    pallet_rows_.emplace_back(row_heights[row], *this);
}

Height 
PalletLane::getTotalHeight() const noexcept{
  Height total("0m");
  for(const auto& row: pallet_rows_)
    total+=row.height;
  return total;
}

bool
PalletLane::isApproachable(Height object_height, LanePosition position) const noexcept(false){
  if (!isValid(position)) throw WrongPositionException();
  uint object_rows=0;
  for(Height row_height("0m"); row_height < object_height; ++object_rows) 
    row_height+=pallet_rows_[object_rows].height;
  uint clear_rows = std::max(position.row,object_rows-1);
  for(uint r=0; r<=clear_rows; ++r)
    for(uint c=0; c<position.column; ++c)
      if (!isEmpty(position)) return false;
  return true;
}

std::ostream& 
operator << (std::ostream& s, const PalletLane& pl){
  s << "  Lane [" << pl.block.getOrderOf(pl) << "] total height: " << pl.getTotalHeight() << std::endl;
  for(uint row=0; row<pl.row_count; ++row) s<<pl.pallet_rows_[row];
  return s;
}

uint 
PalletLane::getLevelOf(const PalletRow& row) const noexcept {
  for(uint r=0; r<row_count; ++r)
    if (& (pallet_rows_[r]) == &row) return r;
  return row_count;
}

bool 
PalletLane::isValid (LanePosition position) const noexcept {
  return position.row < row_count && pallet_rows_[position.row].isValid(position);
}

const Pallet::Ptr&
PalletLane::getPallet (LanePosition position) const noexcept{
  return pallet_rows_[position.row].getPallet(position);
}
