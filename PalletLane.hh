#ifndef PALLET_LANE_HH
#define PALLET_LANE_HH

#include "Length.hh"
#include "PalletRow.hh"
#include "PalletContainer.hh"

#include <iostream>
#include <vector>

class PalletBlock;

struct LanePosition : public RowPosition {
  size_t row;
};

class PalletLane : public ApproachablePalletContainer<LanePosition>{
  public:
    const PalletBlock& block;
    const size_t row_count;

    PalletLane(std::vector<Height> row_heights, PalletBlock& block);
 
    auto getTotalHeight() const noexcept-> Height;
    auto getLevelOf(const PalletRow& row) const noexcept -> size_t;
    
  private:
    std::vector<PalletRow> pallet_rows_;   
  
  public:
    virtual auto isValid (LanePosition position) const noexcept -> bool override;
    virtual auto getPallet (LanePosition position) const noexcept -> const Pallet::Ptr& override; 
    virtual auto isApproachable(Height object_height, LanePosition position) const noexcept(false) -> bool override;
    virtual auto toString(std::string indent="") const noexcept -> std::string override;
};





#endif // PALLET_LANE_HH
