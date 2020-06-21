#ifndef PALLET_BLOCK_HH
#define PALLET_BLOCK_HH

#include "Length.hh"
#include "PalletLane.hh"
#include "PalletContainer.hh"

#include <iostream>
#include <vector>


struct BlockPosition : LanePosition {
  uint lane;
};

class PalletBlock : public PalletContainer<BlockPosition>{
  public:
    const uint lane_count;
    const uint column_count;

    PalletBlock(std::vector<std::vector<Height>> row_heights, uint column_count);
    
    auto isAccessible(Height object_height, BlockPosition position) const noexcept -> bool;
    auto getOrderOf(const PalletLane& lane) const noexcept -> uint;

    friend std::ostream& operator << (std::ostream& s, const PalletBlock& pb);
    
  private:
    std::vector<PalletLane> pallet_lanes_;    
  
  public:
    virtual auto isValid (BlockPosition position) const noexcept -> bool override;
    virtual auto getPallet (BlockPosition position) const noexcept -> const Pallet::Ptr& override; 
};



#endif // PALLET_BLOCK_HH
