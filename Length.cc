#include "Length.hh"

#include <sstream>

const std::map < const std::string, const float > 
BasicLength::unit_multipliers = {
      { "km"  , 1000    },
      { "m"   , 1       },
      { "dm"  , 0.1     },
      { "cm"  , 0.01    },
      { "mm"  , 0.001   },
      { "mi"  , 1609.34 },
      { "yd"  , 0.9144  },
      { "ft"  , 0.3048  },
      { "\'"  , 0.3048  },
      { "in"  , 0.0254  },
      { "\""  , 0.0254  }
    };

float 
BasicLength::convert (float quantity, std::string fromUnit, std::string toUnit){
  if ( unit_multipliers.count(fromUnit) && unit_multipliers.count(toUnit)) 
    return quantity * unit_multipliers.at(fromUnit) / unit_multipliers.at(toUnit);
  else return 0;
}

void 
BasicLength::parseFromStream(std::istream& s){
  float length;
  s >> length;
  std::string unit;
  s >> unit;
  length_in_meter_= convert(length,unit,"m");
}

BasicLength::BasicLength(std::istream& s){ parseFromStream(s); }

BasicLength::BasicLength(const std::string& s){
  std::istringstream iss(s);
  parseFromStream(iss); 
}

BasicLength::BasicLength(const char* s){
  std::string ss(s);
  std::istringstream iss(ss);
  parseFromStream(iss);
}

float 
BasicLength::to(std::string unit) const { return convert(length_in_meter_,"m",unit); }

std::string 
BasicLength::getSuggestedUnit() const {
  if (length_in_meter_>=1000) return "km";
  else if (length_in_meter_ < 1 && length_in_meter_ >= 0.01 ) return "cm";
  else if (length_in_meter_ < 0.01 && length_in_meter_ > 0 ) return "mm";
  else return "m";
}

BasicLength::BasicLength(float length_in_meter)
  : length_in_meter_(length_in_meter) {}

bool 
BasicLength::operator < (const BasicLength& other) const {
  return length_in_meter_ < other.length_in_meter_;
}

bool 
BasicLength::operator <= (const BasicLength& other) const {
  return length_in_meter_ <= other.length_in_meter_;
}

BasicLength 
BasicLength::operator + (const BasicLength& other) const {
  return BasicLength(length_in_meter_+other.length_in_meter_);
}

BasicLength 
BasicLength::operator - (const BasicLength& other) const {
  return BasicLength(length_in_meter_+other.length_in_meter_);
}

BasicLength& 
BasicLength::operator += (const BasicLength& other) {
  length_in_meter_ += other.length_in_meter_;
  return *this;
}
