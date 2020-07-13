#ifndef LANEMODEL_HH
#define LANEMODEL_HH

#include "PalletItemModel.hh"

#include <QVector>

#include "ForkliftModel.hh"
#include "PalletBlock.hh"
#include "RowModel.hh"

class LaneModel : public PalletItemModel
{
    Q_OBJECT
public:
    LaneModel(PalletBlock& block, size_t lane, ForkliftModel& forkliftModel, QObject* parent = nullptr)
        : PalletItemModel(parent), block_(&block), lane_(lane), forkliftModel_(&forkliftModel), submodels_(block.getRowCountOf(lane))
    {
        for (size_t i = 0; (int)i < submodels_.size(); ++i) {
            submodels_[i] = new RowModel(block, lane, i, forkliftModel, this);
        }
    }

    int rowCount(const QModelIndex &parent) const override {
        Q_UNUSED(parent);
        return submodels_.size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (0 > index.row() || index.row() >= submodels_.size() || index.column() != 0 || !block_)
            return QVariant();
        if (role == SubModelRole)
            return QVariant::fromValue(submodels_[index.row()]);
        const size_t row = index.row();
        // find the first pallet in the requested row
        for (size_t col = 0; block_->isValid(BlockPosition{col,row,lane_}); ++col) {
            const Pallet::Ptr& p = block_->getPallet(BlockPosition{col,row,lane_});
            if (p) {
                if (role == Qt::DisplayRole)
                    return QString::fromStdString(p->toString());
                return p->toVariantMap()[roles_[role]];
            }
        }
        return QString();
    }

public slots:
    Q_INVOKABLE
    void interact(int) override
    {}

private:
    PalletBlock* block_;
    size_t lane_;
    ForkliftModel* forkliftModel_;
    QVector<RowModel*> submodels_;
};

#endif // LANEMODEL_HH
