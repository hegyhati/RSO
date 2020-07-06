#ifndef FORKLIFTMODEL_HH
#define FORKLIFTMODEL_HH

#include "PalletItemModel.hh"

#include "Forklift.hh"

class ForkliftModel : public PalletItemModel
{
    Q_OBJECT
public:
    ForkliftModel(Forklift& forklift, QObject* parent = nullptr)
        : PalletItemModel(parent), forklift_(&forklift)
    {
    }

    int rowCount(const QModelIndex &parent) const override {
        Q_UNUSED(parent);
        return 1;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        Q_UNUSED(role);
        if (index.row() != 0 || index.column() != 0 || !forklift_)
            return QVariant();
        if (!forklift_->isLoaded())
            return QString();
        if (role == Qt::DisplayRole)
            return QString::fromStdString(forklift_->getPallet(true)->toString());
        return forklift_->toVariantMap()[roles_[role]];
    }
private:
    Forklift* forklift_;
};

#endif // FORKLIFTMODEL_HH
