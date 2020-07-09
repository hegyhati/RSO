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

    Forklift(Height height);

    auto isLoaded() const noexcept -> bool;

  
  private:
    Pallet::Ptr load_;

  public:
    auto toString(std::string indent="") const noexcept -> std::string override;
    auto toVariantMap() const noexcept -> QVariantMap override;
    auto isValid (bool position=true) const noexcept -> bool override;
    auto getPallet (bool position=true) const noexcept -> const Pallet::Ptr& override;
};





#endif // FORKLIFT_HH
