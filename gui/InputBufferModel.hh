#ifndef INPUTBUFFERMODEL_HH
#define INPUTBUFFERMODEL_HH

#include "PalletItemModel.hh"

#include "ForkliftModel.hh"
#include "InputBuffer.hh"

class InputBufferModel : public PalletItemModel
{
    Q_OBJECT
public:
    InputBufferModel(InputBuffer& inputbuffer, ForkliftModel& forkliftModel, QObject* parent = nullptr)
        : PalletItemModel(parent), inputbuffer_(&inputbuffer), forkliftModel_(&forkliftModel)
    {
    }

    int rowCount(const QModelIndex &parent) const override {
        Q_UNUSED(parent);
        return inputbuffer_->max_capacity;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (0 > index.row() || index.row() >= (int)inputbuffer_->max_capacity || index.column() != 0 || !inputbuffer_)
            return QVariant();
        const Pallet::Ptr& p = inputbuffer_->getPallet(index.row());
        if (!p)
            return QString();
        if (role == Qt::DisplayRole)
            return QString::fromStdString(p->toString());
        return p->toVariantMap()[roles_[role]];
    }

public slots:
    Q_INVOKABLE
    void interact(int index) override {
        if (index < 0 || !forkliftModel_->forklift_->isLoaded() == inputbuffer_->isEmpty(index)) // both empty or full
            return;
        beginResetModel();
        forkliftModel_->beginResetModel();
        bool ok = true;
        if (forkliftModel_->forklift_->isLoaded()) {
            ok = forkliftModel_->forklift_->unload(true, *inputbuffer_, (size_t)index);
        } else {
            ok = forkliftModel_->forklift_->load(true, *inputbuffer_, (size_t)index);
        }
        forkliftModel_->endResetModel();
        endResetModel();
    }

private:
    InputBuffer* inputbuffer_;
    ForkliftModel* forkliftModel_;
};

#endif // INPUTBUFFERMODEL_HH
