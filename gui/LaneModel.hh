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
    void interact(int index) override {
        const size_t row = index;
        // find the first pallet in the requested row
        size_t col;
        for (col = 0; block_->isValid(BlockPosition{col,row,lane_}); ++col) {
            if (!block_->isEmpty(BlockPosition{col,row,lane_})) {
                break;
            }
        }
        try {
            if (forkliftModel_->forklift_->isEmpty(true)) { // forklift is empty, try to load it
                if (!block_->isValid(BlockPosition{col,row,lane_})) // row is empty too
                    return;
                forkliftModel_->forklift_->load(true, *block_, BlockPosition{col,row,lane_});
                forkliftModel_->endResetModel();
                endResetModel();
            } else { // forklift is loaded, try to unload it
                if (col == 0) // row is full
                    return;
                forkliftModel_->forklift_->unload(true, *block_, BlockPosition{col-1,row,lane_});
                forkliftModel_->endResetModel();
                endResetModel();
            }
        } catch (const NotApproachableException&) {}
    }

private:
    PalletBlock* block_;
    size_t lane_;
    ForkliftModel* forkliftModel_;
    QVector<RowModel*> submodels_;
};

#endif // LANEMODEL_HH
