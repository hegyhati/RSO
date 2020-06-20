#ifndef PALLET_LANE_HH
#define PALLET_LANE_HH

#include "Length.hh"
#include "PalletRow.hh"

#include <iostream>
#include <vector>

class PalletBlock;

class PalletLane {
  public:
    const PalletBlock& block;
    const uint row_count;

    PalletLane(std::vector<Height> row_heights, PalletBlock& block);
    
    auto operator [] (uint row) const noexcept -> const PalletRow& ;
    auto put(Pallet::Ptr& pallet, uint row, uint column) noexcept -> bool;
    auto getTotalHeight() const -> Height;
    
  private:
    std::vector<PalletRow> pallet_rows_;    
};

std::ostream& operator << (std::ostream& s, const PalletLane& pl);



#endif // PALLET_LANE_HH
