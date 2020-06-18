#ifndef LENGTH_HH
#define LENGTH_HH

#include <string>
#include <iostream>
#include <map>


class BasicLength {
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
    bool operator < (const BasicLength& other) const;
    bool operator <= (const BasicLength& other) const;
    BasicLength operator + (const BasicLength& other) const;
    BasicLength operator - (const BasicLength& other) const;

  private:
    void parseFromStream(std::istream& s);
    float length_in_meter_;
};

std::ostream& operator << (std::ostream& s, const BasicLength& l);

enum class LengthType { height, width, depth };

template <LengthType E> 
class Length : public BasicLength {
  public:
    Length(std::istream& s) : BasicLength(s) {}
    Length(const std::string& s) : BasicLength(s) {}
    Length(const char* s) : BasicLength(s) {}

    bool operator < (const Length<E>& other) const { return *this < other; } 
    bool operator <= (const Length<E>& other) const { return *this <= other; }
    Length<E> operator + (const Length<E>& other) const { return *this + other; }
    Length<E> operator - (const Length<E>& other) const { return *this - other; }
};

using Height = Length<LengthType::height>;
using Width  = Length<LengthType::width>;
using Depth  = Length<LengthType::depth>;



#endif // LENGTH_HH
