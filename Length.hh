#ifndef LENGTH_HH
#define LENGTH_HH

#include <string>
#include <iostream>
#include <map>

#include "Serializable.hh"


class BasicLength : public Serializable{
  public:
    static const std::map < const std::string, const float > unit_multipliers; 

    //TODO could be std::optional
    static float convert (float quantity, std::string fromUnit, std::string toUnit);

    BasicLength(std::istream& s);    
    BasicLength(const std::string& s);
    BasicLength(const char* s);

    float to(std::string unit) const;
    std::string getSuggestedUnit() const;
  
  protected:
    BasicLength(float length_in_meter);
    auto operator <  (const BasicLength& other) const -> bool;
    auto operator <= (const BasicLength& other) const -> bool;
    auto operator +  (const BasicLength& other) const -> BasicLength;
    auto operator -  (const BasicLength& other) const -> BasicLength;
    auto operator += (const BasicLength& other) -> BasicLength&;

  private:
    void parseFromStream(std::istream& s);
    float length_in_meter_;
  
  public:
    virtual auto toString(std::string indent="") const noexcept -> std::string override;
};

enum class LengthType { height, width, depth };

template <LengthType E> 
class Length : public BasicLength {
  public:
    Length(std::istream& s) : BasicLength(s) {}
    Length(const std::string& s) : BasicLength(s) {}
    Length(const char* s) : BasicLength(s) {}

    
    auto operator <  (const Length<E>& other) const -> bool       { return BasicLength::operator< (other); } 
    auto operator <= (const Length<E>& other) const -> bool       { return BasicLength::operator<=(other); }
    auto operator +  (const Length<E>& other) const -> Length<E>  { return static_cast<Length<E> >(BasicLength::operator+ (other)); }
    auto operator -  (const Length<E>& other) const -> Length<E>  { return static_cast<Length<E> >(BasicLength::operator- (other)); }
    auto operator += (const Length<E>& other) -> Length<E>&       { return static_cast<Length<E>&>(BasicLength::operator+=(other)); }
};

using Height = Length<LengthType::height>;
using Width  = Length<LengthType::width>;
using Depth  = Length<LengthType::depth>;



#endif // LENGTH_HH
