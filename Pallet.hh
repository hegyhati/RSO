#ifndef PALLET_HH
#define PALLET_HH

#include <ostream>
#include "Length.hh"

class Pallet {
  public:
    Pallet (const uint productID, const Height height, const float quantity=0)
      : productID(productID), height(height), quantity(quantity) {}
    const int getProductID() const { return productID; }
    const Height getHeight() const { return height; }
    const float getQuantity() const { return quantity; }

  private:
    const uint productID;
    const Height height;
    const float quantity; // pieces
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
