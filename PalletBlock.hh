#ifndef PALLET_BLOCK_HH
#define PALLET_BLOCK_HH

#include "Length.hh"
#include "PalletLane.hh"
#include "PalletContainer.hh"

#include <iostream>
#include <vector>


struct BlockPosition : LanePosition {
  size_t lane;
};

class PalletBlock : public ApproachablePalletContainer<BlockPosition>{
  public:
    const size_t lane_count;
    const size_t column_count;

    PalletBlock(std::vector<std::vector<Height>> row_heights, size_t column_count);
    
    auto getOrderOf(const PalletLane& lane) const noexcept -> size_t;

    auto getRowCountOf(size_t lane) const noexcept -> size_t;
    
  private:
    std::vector<PalletLane> pallet_lanes_;    
  
  public:
    virtual auto isValid (BlockPosition position) const noexcept -> bool override;
    virtual auto getPallet (BlockPosition position) const noexcept -> const Pallet::Ptr& override;     
    virtual auto isApproachable(Height object_height, BlockPosition position) const noexcept(false) -> bool override;
    virtual auto toString(std::string indent="") const noexcept -> std::string override;

};



#endif // PALLET_BLOCK_HH
