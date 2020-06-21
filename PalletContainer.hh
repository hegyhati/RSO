#ifndef PALLET_CONTAINER_HH
#define PALLET_CONTAINER_HH

#include "Length.hh"
#include "Pallet.hh"
#include "Serializable.hh"

class WrongPositionException{};
class OccupiedPositionException{};

template <typename PositionType>
class PalletContainer : public Serializable {
  public:
    using Position = PositionType;
    virtual auto isValid (Position position) const noexcept -> bool =0; 
    virtual auto getPallet (Position position) const noexcept -> const Pallet::Ptr& =0;

    auto operator[] (Position position) const noexcept(false) -> const Pallet& {
      if(isEmpty(position)) throw Pallet::NoPalletException();
      else return *getPallet(position);
    }

    auto isEmpty(Position position) const noexcept(false) -> bool {
      if (!isValid(position)) throw WrongPositionException();
      else return !getPallet(position);  
    }
};

template<typename PositionType>
class ApproachablePalletContainer : public PalletContainer<PositionType>{
  public:
    virtual auto isApproachable(Height object_height, PositionType position) const noexcept(false) -> bool =0;
};

template<typename PositionType>
class ActingPalletContainer : public PalletContainer<PositionType> {
  private:
    template<typename PTypeFrom, typename PTypeTo>
    static auto move(PalletContainer<PTypeFrom>& from_container, PTypeFrom from_position, PalletContainer<PTypeTo>& to_container, PTypeTo to_position) -> bool {
      if (!from_container.getPallet(from_position)) return false;
      else if (!to_container.isEmpty(to_position)) throw OccupiedPositionException();
      else {
        const_cast<Pallet::Ptr&>(to_container.getPallet(to_position)) = std::move(const_cast<Pallet::Ptr&>(from_container.getPallet(from_position)));
        return true;
      }    
    }
  public:
    template<typename PositionTypeOther>
    auto unload(PositionType position, ApproachablePalletContainer<PositionTypeOther>& other_container, PositionTypeOther other_position) -> bool{
      return move(*this,position,other_container,other_position);      
    }
    template<typename PositionTypeOther>
    auto load(PositionType position, ApproachablePalletContainer<PositionTypeOther>& other_container, PositionTypeOther other_position) -> bool{
      return move(other_container,other_position,*this,position);            
    }
};


#endif // PALLET_CONTAINER_HH
