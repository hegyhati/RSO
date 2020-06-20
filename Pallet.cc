#include "Pallet.hh"

std::ostream& 
operator << (std::ostream& s, const Pallet& p){
  return s << "[ "
           << "Product: " << p.product_id
           << " | "
           << "Height: " << p.height
           << " | "
           << "Quantity: " << p.quantity
           << " ]";
}
