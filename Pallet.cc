#include "Pallet.hh"

std::ostream& 
operator << (std::ostream& s, const Pallet& p){
  return s << "[ "
           << "Product: " << p.getProductID()
           << " | "
           << "Height: " << p.getHeight()
           << " | "
           << "Quantity: " << p.getQuantity()
           << " ]";
}
