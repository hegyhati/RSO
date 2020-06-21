#ifndef PALLET_CONTAINER_HH
#define PALLET_CONTAINER_HH

#include "Pallet.hh"

class WrongPositionException{};
class OccupiedPositionException{};

template <typename PositionType>
class PalletContainer {
  public:
    using Position = PositionType;
    virtual auto isValid (Position position) const noexcept -> bool =0; 
    virtual auto getPallet (Position position) const noexcept -> const Pallet::Ptr& =0;

    auto put(Pallet::Ptr& pallet, Position position) noexcept(false) -> bool { //could be void later
      if(!isEmpty(position)) throw OccupiedPositionException();
      else {
        // TODO height is not checked
        // How to do without const cast and removing the need for the definition of a const and a non-const getter?
        const_cast<Pallet::Ptr&>(getPallet(position)) = std::move(pallet);
        return true;
      }
    }

    auto operator[] (Position position) const noexcept(false) -> const Pallet& {
      if(isEmpty(position)) throw Pallet::NoPalletException();
      else return *getPallet(position);
    }

    auto isEmpty(Position position) const noexcept(false) -> bool {
      if (!isValid(position)) throw WrongPositionException();
      else return !getPallet(position);  
    }
};




#endif // PALLET_CONTAINER_HH
