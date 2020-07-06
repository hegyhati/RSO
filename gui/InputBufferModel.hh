#ifndef INPUTBUFFERMODEL_HH
#define INPUTBUFFERMODEL_HH

#include "PalletItemModel.hh"

#include "InputBuffer.hh"

class InputBufferModel : public PalletItemModel
{
    Q_OBJECT
public:
    InputBufferModel(InputBuffer& inputbuffer, QObject* parent = nullptr)
        : PalletItemModel(parent), inputbuffer_(&inputbuffer)
    {
    }

    int rowCount(const QModelIndex &parent) const override {
        Q_UNUSED(parent);
        return inputbuffer_->max_capacity;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        Q_UNUSED(role);
        if (0 > index.row() || index.row() >= (int)inputbuffer_->max_capacity || index.column() != 0 || !inputbuffer_)
            return QVariant();
        const Pallet::Ptr& p = inputbuffer_->getPallet(index.row());
        if (!p)
            return QString();
        if (role == Qt::DisplayRole)
            return QString::fromStdString(p->toString());
        return p->toVariantMap()[roles_[role]];
    }
private:
    InputBuffer* inputbuffer_;
};

#endif // INPUTBUFFERMODEL_HH
