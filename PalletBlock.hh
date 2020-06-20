#ifndef PALLET_BLOCK_HH
#define PALLET_BLOCK_HH

#include "Length.hh"
#include "PalletLane.hh"

#include <iostream>
#include <vector>

class PalletBlock {
  public:
    const uint lane_count;
    const uint column_count;

    PalletBlock(std::vector<std::vector<Height>> row_heights, uint column_count);
    
    auto operator [] (uint lane) const noexcept -> const PalletLane& ;
    auto put(Pallet::Ptr& pallet, uint lane, uint row, uint column) noexcept -> bool;
    
  private:
    std::vector<PalletLane> pallet_lanes_;    
};

std::ostream& operator << (std::ostream& s, const PalletBlock& pb);



#endif // PALLET_BLOCK_HH
