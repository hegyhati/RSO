#ifndef INPUT_BUFFER_HH
#define INPUT_BUFFER_HH

#include <vector>
#include "Pallet.hh"
#include "PalletContainer.hh"

class InputBuffer : public ApproachablePalletContainer<uint>{
  public:
    const uint max_capacity;

    InputBuffer(uint max_capacity);
    // change argument later to string, adn then it will get data from elsewhere
    auto generateNewPallet(uint id, Height height) noexcept -> void;
    
  private:
    std::vector<Pallet::Ptr> pallets_;    
  
  public:
    virtual auto isValid (uint position) const noexcept -> bool override;
    virtual auto getPallet (uint position) const noexcept -> const Pallet::Ptr& override;     
    virtual auto isApproachable(Height object_height, uint position) const noexcept(false) -> bool override;
    virtual auto toString(std::string indent="") const noexcept -> std::string override;
};



#endif // INPUT_BUFFER_HH
