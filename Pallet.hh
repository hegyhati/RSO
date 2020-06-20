#ifndef PALLET_HH
#define PALLET_HH

#include <ostream>
#include <memory>
#include "Length.hh"

class Pallet {
  public:
    typedef std::unique_ptr<const Pallet> Ptr;

    Pallet (const uint product_id, const Height height, const float quantity=0)
      : product_id_(product_id), height_(height), quantity_(quantity) {}

    Pallet (const Pallet&) = delete;
    Pallet& operator= (const Pallet&) = delete;

    auto getProductID() const noexcept -> const int { return product_id_; }
    auto getHeight() const noexcept -> const Height{ return height_; }
    auto getQuantity() const noexcept -> double { return quantity_; }

  private:
    const uint product_id_;
    const Height height_;
    const float quantity_; // pieces
};

std::ostream& operator << (std::ostream& s, const Pallet& p);

#endif // PALLET_HH
