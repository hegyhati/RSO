#ifndef PALLET_HH
#define PALLET_HH

#include <ostream>
#include <memory>
#include "Length.hh"
#include "Serializable.hh"

struct Pallet : public Serializable {
    using Ptr = std::unique_ptr<const Pallet>;
    struct NoPalletException{};

    const uint product_id;
    const Height height;
    const float quantity;

    Pallet (const uint product_id, const Height height, const float quantity=0)
      : product_id(product_id), height(height), quantity(quantity) {}

    Pallet (const Pallet&) = delete;
    Pallet& operator= (const Pallet&) = delete;
    
    virtual auto toString(std::string indent="") const noexcept -> std::string override;
};

#endif // PALLET_HH
