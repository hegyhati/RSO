#ifndef PALLET_HH
#define PALLET_HH

#include <ostream>
#include "Length.hh"

class Pallet {
  public:
    Pallet (const uint product_id, const Height height, const float quantity=0)
      : product_id_(product_id), height_(height), quantity_(quantity) {}
    const int getProductID() const { return product_id_; }
    const Height getHeight() const { return height_; }
    const float getQuantity() const { return quantity_; }

  private:
    const uint product_id_;
    const Height height_;
    const float quantity_; // pieces
};

std::ostream& operator << (std::ostream& s, const Pallet& p){
  return s << "[ "
           << "Product: " << p.getProductID()
           << " | "
           << "Height: " << p.getHeight()
           << " | "
           << "Quantity: " << p.getQuantity()
           << " ]";
}


#endif // PALLET_HH
