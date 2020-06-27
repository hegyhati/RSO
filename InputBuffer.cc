#include "InputBuffer.hh"


InputBuffer::InputBuffer(size_t max_capacity) : max_capacity(max_capacity), pallets_(max_capacity) {}

void
InputBuffer::generateNewPallet(size_t id, Height height) noexcept {
  for(size_t idx=0; idx<max_capacity; ++idx)
    if(!pallets_[idx]) {
      pallets_[idx]=std::make_unique<Pallet>(id,height);
      return;
    }
}

bool
InputBuffer::isValid (size_t position) const noexcept {
  return position < max_capacity;
}

const Pallet::Ptr&
InputBuffer::getPallet (size_t position) const noexcept{
  return pallets_[position];
}    

bool
InputBuffer::isApproachable(Height object_height, size_t position) const noexcept(false){
  if (!isValid(position)) throw WrongPositionException();
  else return true;
}


