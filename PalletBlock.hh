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

class PalletBlock : public ApproachablePalletContainer<BlockPosition>{
  public:
    const uint lane_count;
    const uint column_count;

    PalletBlock(std::vector<std::vector<Height>> row_heights, uint column_count);
    
    auto getOrderOf(const PalletLane& lane) const noexcept -> uint;
    
  private:
    std::vector<PalletLane> pallet_lanes_;    
  
  public:
    virtual auto isValid (BlockPosition position) const noexcept -> bool override;
    virtual auto getPallet (BlockPosition position) const noexcept -> const Pallet::Ptr& override;     
    virtual auto isApproachable(Height object_height, BlockPosition position) const noexcept(false) -> bool override;
    virtual auto toString(std::string indent="") const noexcept -> std::string override;

};



#endif // PALLET_BLOCK_HH
