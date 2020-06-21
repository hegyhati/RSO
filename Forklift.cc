#include "Forklift.hh"


Forklift::Forklift(Height height) : ActingPalletContainer<bool>(height) {}

bool 
Forklift::isLoaded() const noexcept {
  return  load_.get() != nullptr;
}


bool
Forklift::isValid (bool position) const noexcept {
  return position;
}

const Pallet::Ptr&
Forklift::getPallet (bool position) const noexcept{
  return load_;
}
