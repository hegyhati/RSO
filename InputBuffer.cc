#include "InputBuffer.hh"


InputBuffer::InputBuffer(uint max_capacity) : max_capacity(max_capacity), pallets_(max_capacity) {}

void
InputBuffer::generateNewPallet(uint id, Height height) noexcept {
  for(uint idx=0; idx<max_capacity; ++idx)
    if(!pallets_[idx]) {
      pallets_[idx]=std::make_unique<Pallet>(id,height);
      return;
    }
}

bool
InputBuffer::isValid (uint position) const noexcept {
  return position < max_capacity;
}

const Pallet::Ptr&
InputBuffer::getPallet (uint position) const noexcept{
  return pallets_[position];
}    

bool
InputBuffer::isApproachable(Height object_height, uint position) const noexcept(false){
  if (!isValid(position)) throw WrongPositionException();
  else return true;
}


