#ifndef PALLET_HH
#define PALLET_HH

#include <ostream>

class Pallet {
  public:
    Pallet (const uint productID, const float height, const float quantity=0)
      : productID(productID), height(height), quantity(quantity) {}
    const int getProductID() const { return productID; }
    const float getHeight() const { return height; }
    const float getQuantity() const { return quantity; }

  private:
    const uint productID;
    const float height;
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
