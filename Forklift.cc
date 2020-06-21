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

std::ostream& 
operator << (std::ostream& s, const Forklift& fl) {
  s << "Forklift, height: " << fl.height << ", load: ";
  if( fl.isLoaded() ) s << *(fl.load_);
  else s << "---";
  return s << std::endl;
}
