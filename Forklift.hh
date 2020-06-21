#ifndef FORKLIFT_HH
#define FORKLIFT_HH

#include <iostream>
#include <string>
#include "Length.hh"
#include "Pallet.hh"
#include "PalletBlock.hh"


class Forklift {
  public:
    struct OperationErrorException {
      std::string message;
    };

    const Height height;

    Forklift(Height height);

    auto isLoaded() const noexcept -> bool;
    auto load(Pallet::Ptr& pallet) noexcept -> bool; // later will be similar template as unload

    template <typename PositionType>
    auto unload(ApproachablePalletContainer<PositionType>& container, PositionType position) noexcept(false) -> void {
      try {
        if (!container.isApproachable(height,position)) throw OperationErrorException{"Position is not approachable."};
        container.put(load_,position);
      } catch (WrongPositionException) {
        throw OperationErrorException{"Wrong position."};
      } catch (OccupiedPositionException) {
        throw OperationErrorException{"Position already occupied by pallet."};
      } 
    }

  private:
    Pallet::Ptr load_;

  friend std::ostream& operator << (std::ostream& s, const Forklift& fl);
};





#endif // FORKLIFT_HH
