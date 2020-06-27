#ifndef PALLET_ROW_HH
#define PALLET_ROW_HH

#include <vector>
#include <memory>
#include <optional>

#include "PalletContainer.hh"
#include "Pallet.hh"
#include "Length.hh"

class PalletLane;

struct RowPosition{
  size_t column;
};

class PalletRow : public PalletContainer<RowPosition>{
  public:
    const PalletLane& lane;
    const size_t& column_count;
    const Height height;

    PalletRow(Height height, const PalletLane& lane);

    auto getTakenSlots() const noexcept -> std::vector<size_t>;    
    
  private:
    std::vector<Pallet::Ptr> pallets_;   
  

  public:
    virtual auto isValid (RowPosition position) const noexcept -> bool override;
    virtual auto getPallet (RowPosition position) const noexcept -> const Pallet::Ptr& override;
    virtual auto toString(std::string indent="") const noexcept -> std::string override;
};

#endif // PALLET_ROW_HH
