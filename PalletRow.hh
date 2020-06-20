#ifndef PALLET_ROW_HH
#define PALLET_ROW_HH

#include <vector>
#include <memory>
#include <optional>

#include "Pallet.hh"
#include "Length.hh"

//class PalletLane;
//class PalletBlock;
//class PalletRackingSystem;

class NoPalletException {};

class PalletRow {
  public:
    const Height height;

    PalletRow(const Height& height);
    
    auto operator [] (uint column) const noexcept(false) -> const Pallet& ;
    auto put(std::unique_ptr<Pallet>& pallet, uint column) noexcept -> bool;
    auto getTakenSlots() const noexcept -> std::vector<uint>;
    
  private:
    const uint column_count_ = 5; // will be replaced by const ref to lane/block, that has this
    std::vector<std::unique_ptr<const Pallet>> pallets_;    
};

std::ostream& operator << (std::ostream& s, const PalletRow& pr);



#endif // PALLET_ROW_HH
