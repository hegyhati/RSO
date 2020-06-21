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

bool 
Forklift::unload(PalletBlock& block, PalletBlock::Position position) noexcept {
  if( ! block.isAccessible(height,position) || ! block.isEmpty(position) ) return false;
  else return block.put(load_,position);
}


std::ostream& 
operator << (std::ostream& s, const Forklift& fl) {
  s << "Forklift, height: " << fl.height << ", load: ";
  if( fl.isLoaded() ) s << *(fl.load_);
  else s << "---";
  return s << std::endl;
}
