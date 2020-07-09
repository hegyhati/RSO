#ifndef SERIALIZABLE_HH
#define SERIALIZABLE_HH

#include <string>
#include <iostream>
#include <QVariantMap>

class Serializable {
  protected:
    static const std::string endl;
    static const std::string indentincrement;
  public:
    auto virtual toString(std::string indent="") const noexcept -> std::string = 0;
    auto virtual toVariantMap() const noexcept -> QVariantMap /*= 0; TODO */ { return QVariantMap(); }
};

inline std::ostream& operator << (std::ostream& s, const Serializable& serializable){
  return s << serializable.toString() << std::endl;
}

#endif // SERIALIZABLE_HH
