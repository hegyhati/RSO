#include "PalletBlock.hh"

PalletBlock::PalletBlock(std::vector<std::vector<Height>> row_heights, uint column_count)
: lane_count(row_heights.size()), column_count(column_count) {
  pallet_lanes_.reserve(lane_count);
  for (uint lane=0; lane<lane_count; ++lane)
    pallet_lanes_.emplace_back(row_heights[lane],*this);
}
    
bool 
PalletBlock::isApproachable(Height object_height, BlockPosition position) const noexcept(false) {
  if(!isValid(position)) throw WrongPositionException();
  else return pallet_lanes_[position.lane].isApproachable(object_height,position);
}

uint 
PalletBlock::getOrderOf(const PalletLane& lane) const noexcept {
  for(uint l=0; l<lane_count; ++l)
    if (& (pallet_lanes_[l]) == &lane) return l;
  return lane_count;
}

bool 
PalletBlock::isValid (BlockPosition position) const noexcept {
  return position.lane < lane_count && pallet_lanes_[position.lane].isValid(position);
}

const Pallet::Ptr&
PalletBlock::getPallet (BlockPosition position) const noexcept{
  return pallet_lanes_[position.lane].getPallet(position);
}
