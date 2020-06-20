#include "PalletLane.hh"
#include "PalletBlock.hh"
#include <algorithm>


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
  if (row >= row_count) return false;
  else return pallet_rows_[row].put(pallet,column);
}

Height PalletLane::getTotalHeight() const noexcept{
  Height total("0m");
  for(const auto& row: pallet_rows_)
    total+=row.height;
  return total;
}


bool PalletLane::isEmpty(uint row, uint column) const noexcept {
  if(row >= row_count) return false;
  return pallet_rows_[row].isEmpty(column);
}

// TODO isAccessible should be moved to Forklift or be private and called from put/take automatically.
bool PalletLane::isAccessible(Height object_height, uint row, uint column) const noexcept {
  if(column >= block.column_count ||  row >= row_count) return false;
  uint object_rows=0;
  for(Height row_height("0m"); row_height < object_height; ++object_rows) 
    row_height+=pallet_rows_[object_rows].height;
  uint clear_rows = std::max(row,object_rows-1);
  for(uint r=0; r<=clear_rows; ++r)
    for(uint c=0; c<column; ++c)
      if (!isEmpty(r,c)) return false;
  return true;
}

std::ostream& operator << (std::ostream& s, const PalletLane& pl){
  s << "  Lane [" << pl.getNumber() << "] total height: " << pl.getTotalHeight() << std::endl;
  for(uint row=0; row<pl.row_count; ++row) s<<pl[row];
  return s;
}

uint PalletLane::getNumber() const noexcept {
  for(uint lane=0; lane<block.lane_count; ++lane)
    if(& (block[lane]) == this) return lane;  
  return block.lane_count;
}
