#include "PalletBlock.hh"


PalletBlock::PalletBlock(std::vector<std::vector<Height>> row_heights, uint column_count)
: lane_count(row_heights.size()), column_count(column_count) {
  pallet_lanes_.reserve(lane_count);
  for (uint lane=0; lane<lane_count; ++lane)
    pallet_lanes_.emplace_back(row_heights[lane],*this);
}
    
const PalletLane& PalletBlock::operator [] (uint lane) const noexcept {
  return pallet_lanes_[lane];
}

bool PalletBlock::put(Pallet::Ptr& pallet, uint lane, uint row, uint column) noexcept {
  return pallet_lanes_[lane].put(pallet,row,column);
}

std::ostream& operator << (std::ostream& s, const PalletBlock& pb){
  s << "Block, number of columns: " << pb.column_count << std::endl;
  for(uint lane=0; lane<pb.lane_count; ++lane) s<<pb[lane];
  return s;
}
