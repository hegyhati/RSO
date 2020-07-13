#ifndef PALLETITEMMODEL_HH
#define PALLETITEMMODEL_HH

#include <QAbstractListModel>

class PalletItemModel : public QAbstractListModel {
    Q_OBJECT
public:
    PalletItemModel(QObject* parent = nullptr) : QAbstractListModel(parent) {
        roles_[ProductRole] = "product";
        roles_[SizeRole] = "size";
        roles_[QuantityRole] = "quantity";
        roles_[SubModelRole] = "submodel";
    }

    enum PalletRoles {
        ProductRole = Qt::UserRole + 1,
        SizeRole,
        QuantityRole,
        SubModelRole
    };

    QHash<int, QByteArray> roleNames() const override { return roles_; }

public slots:
    Q_INVOKABLE
    virtual void interact(int index) = 0;

protected:
    QHash<int, QByteArray> roles_;
};

#endif // PALLETITEMMODEL_HH
