#ifndef FORKLIFT_HH
#define FORKLIFT_HH

#include <iostream>
#include <string>
#include "Length.hh"
#include "Pallet.hh"
#include "PalletBlock.hh"

// To avoid bool, use empty class / variadic template mabe?
class Forklift : public ActingPalletContainer<bool> {
  public:
    struct OperationErrorException {
      std::string message;
    };

    const Height height;

    Forklift(Height height);

    auto isLoaded() const noexcept -> bool;

  
  private:
    Pallet::Ptr load_;

  public:
    virtual auto toString(std::string indent="") const noexcept -> std::string override;
    virtual auto isValid (bool position=true) const noexcept -> bool override;
    virtual auto getPallet (bool position=true) const noexcept -> const Pallet::Ptr& override;  
};





#endif // FORKLIFT_HH
