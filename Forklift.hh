#ifndef FORKLIFT_HH
#define FORKLIFT_HH

#include <iostream>
#include "Length.hh"
#include "Pallet.hh"
#include "PalletBlock.hh"

class Forklift {
  public:
    const Height height;

    Forklift(Height height);

    auto isLoaded() const noexcept -> bool;
    auto load(Pallet::Ptr& pallet) noexcept -> bool; // later will load(place,index) as well for unload
    auto unload(PalletBlock& block, PalletBlock::Position position) noexcept -> bool;

  private:
    Pallet::Ptr load_;

  friend std::ostream& operator << (std::ostream& s, const Forklift& fl);
};





#endif // FORKLIFT_HH
