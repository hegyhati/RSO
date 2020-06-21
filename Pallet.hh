#ifndef PALLET_HH
#define PALLET_HH

#include <ostream>
#include <memory>
#include "Length.hh"

struct Pallet {
    using Ptr = std::unique_ptr<const Pallet>;
    struct NoPalletException{};

    const uint product_id;
    const Height height;
    const float quantity;

    Pallet (const uint product_id, const Height height, const float quantity=0)
      : product_id(product_id), height(height), quantity(quantity) {}

    Pallet (const Pallet&) = delete;
    Pallet& operator= (const Pallet&) = delete;
};

std::ostream& operator << (std::ostream& s, const Pallet& p);

#endif // PALLET_HH
