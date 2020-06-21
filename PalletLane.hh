#ifndef PALLET_LANE_HH
#define PALLET_LANE_HH

#include "Length.hh"
#include "PalletRow.hh"
#include "PalletContainer.hh"

#include <iostream>
#include <vector>

class PalletBlock;

struct LanePosition : public RowPosition {
  uint row;
};

class PalletLane : public PalletContainer<LanePosition>{
  public:
    const PalletBlock& block;
    const uint row_count;

    PalletLane(std::vector<Height> row_heights, PalletBlock& block);
 
    auto isAccessible(Height object_height, LanePosition position) const noexcept -> bool;
    auto getTotalHeight() const noexcept-> Height;
    auto getLevelOf(const PalletRow& row) const noexcept -> uint;
    
    friend std::ostream& operator << (std::ostream& s, const PalletLane& pl);

  private:
    std::vector<PalletRow> pallet_rows_;   
  
  public:
    virtual auto isValid (LanePosition position) const noexcept -> bool override;
    virtual auto getPallet (LanePosition position) const noexcept -> const Pallet::Ptr& override; 
};





#endif // PALLET_LANE_HH
