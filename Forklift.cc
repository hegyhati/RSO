#include "Forklift.hh"


Forklift::Forklift(Height height) : height(height) {}

bool 
Forklift::isLoaded() const noexcept {
  return  load_.get() != nullptr;
}

bool 
Forklift::load(Pallet::Ptr& pallet) noexcept {
  if( !pallet || isLoaded() ) return false;
  else {
    load_ = std::move(pallet);
    return true;
  }
}
