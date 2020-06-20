#ifndef PALLET_ROW_HH
#define PALLET_ROW_HH

#include <vector>
#include <memory>
#include <optional>

#include "Pallet.hh"
#include "Length.hh"

class PalletLane;

class NoPalletException {};

class PalletRow {
  public:
    const PalletLane& lane;
    const Height height;

    PalletRow(const Height& height, const PalletLane& lane);
    
    auto operator [] (uint column) const noexcept(false) -> const Pallet& ;
    auto put(Pallet::Ptr& pallet, uint column) noexcept -> bool;
    auto getTakenSlots() const noexcept -> std::vector<uint>;
    auto getLevel() const noexcept -> uint;
    
  private:
    std::vector<Pallet::Ptr> pallets_;    
};

std::ostream& operator << (std::ostream& s, const PalletRow& pr);



#endif // PALLET_ROW_HH
