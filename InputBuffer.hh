#ifndef INPUT_BUFFER_HH
#define INPUT_BUFFER_HH

#include <vector>
#include "Pallet.hh"
#include "PalletContainer.hh"

class InputBuffer : public ApproachablePalletContainer<size_t>{
  public:
    const size_t max_capacity;

    InputBuffer(size_t max_capacity);
    // change argument later to string, adn then it will get data from elsewhere
    auto generateNewPallet(size_t id, Height height) noexcept -> void;
    
  private:
    std::vector<Pallet::Ptr> pallets_;    
  
  public:
    virtual auto isValid (size_t position) const noexcept -> bool override;
    virtual auto getPallet (size_t position) const noexcept -> const Pallet::Ptr& override;     
    virtual auto isApproachable(Height object_height, size_t position) const noexcept(false) -> bool override;
    virtual auto toString(std::string indent="") const noexcept -> std::string override;
};



#endif // INPUT_BUFFER_HH
