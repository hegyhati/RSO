#include "PalletBlock.hh"


PalletBlock::PalletBlock(std::vector<std::vector<Height>> row_heights, uint column_count)
: lane_count(row_heights.size()), column_count(column_count) {
  pallet_lanes_.reserve(lane_count);
  for (uint lane=0; lane<lane_count; ++lane)
    pallet_lanes_.emplace_back(row_heights[lane],*this);
}
    
const PalletLane& 
PalletBlock::operator [] (uint lane) const noexcept {
  return pallet_lanes_[lane];
}

bool 
PalletBlock::put(Pallet::Ptr& pallet, uint lane, uint row, uint column) noexcept {
  if (lane >= lane_count) return false;
  else return pallet_lanes_[lane].put(pallet,row,column);
}

// TODO out of bounds should be exception, preferably chacked at one place
bool 
PalletBlock::isEmpty(uint lane, uint row, uint column) const noexcept {
  if(lane >= lane_count) return false;
  else return pallet_lanes_[lane].isEmpty(row,column);
}

bool 
PalletBlock::isAccessible(Height object_height, uint lane, uint row, uint column) const noexcept {
  if (lane >= lane_count) return false;
  else return pallet_lanes_[lane].isAccessible(object_height,row,column);
}

std::ostream& 
operator << (std::ostream& s, const PalletBlock& pb){
  s << "Block, number of columns: " << pb.column_count << std::endl;
  for(uint lane=0; lane<pb.lane_count; ++lane) s<<pb[lane];
  return s;
}

