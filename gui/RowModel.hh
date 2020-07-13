#ifndef ROWMODEL_HH
#define ROWMODEL_HH

#include "PalletItemModel.hh"

#include "ForkliftModel.hh"
#include "PalletBlock.hh"

class RowModel : public PalletItemModel
{
    Q_OBJECT
public:
    RowModel(PalletBlock& block, size_t lane, size_t row, ForkliftModel& forkliftModel, QObject* parent = nullptr)
        : PalletItemModel(parent), block_(&block), lane_(lane), row_(row), forkliftModel_(&forkliftModel), length_(0)
    {
        while (block.isValid(BlockPosition{length_,row,lane}))
            ++length_;
    }

    int rowCount(const QModelIndex &parent) const override {
        Q_UNUSED(parent);
        return length_;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (0 > index.row() || index.row() >= (int)length_ || index.column() != 0 || !block_)
            return QVariant();
        const Pallet::Ptr& p = block_->getPallet(BlockPosition{(size_t)index.row(),row_,lane_});
        if (!p)
            return QString();
        if (role == Qt::DisplayRole)
            return QString::fromStdString(p->toString());
        return p->toVariantMap()[roles_[role]];
    }

public slots:
    Q_INVOKABLE
    void interact(int) override
    {}

private:
    PalletBlock* block_;
    size_t lane_;
    size_t row_;
    ForkliftModel* forkliftModel_;
    size_t length_;
};

#endif // ROWMODEL_HH
