#ifndef BLOCKMODEL_HH
#define BLOCKMODEL_HH

#include "PalletItemModel.hh"

#include <QVector>

#include "ForkliftModel.hh"
#include "PalletBlock.hh"
#include "LaneModel.hh"

class BlockModel : public PalletItemModel
{
    Q_OBJECT
public:
    BlockModel(PalletBlock& block, ForkliftModel& forkliftModel, QObject* parent = nullptr)
        : PalletItemModel(parent), block_(&block), forkliftModel_(&forkliftModel), submodels_(block.lane_count)
    {
        for (size_t i = 0; i < block.lane_count; ++i) {
            submodels_[i] = new LaneModel(block, i, forkliftModel, this);
            connect(submodels_[i], &LaneModel::modelReset, this, &BlockModel::endResetModel);
        }
    }

    int rowCount(const QModelIndex &parent) const override {
        Q_UNUSED(parent);
        return block_->lane_count;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (0 > index.row() || index.row() >= submodels_.size() || index.column() != 0 || !block_)
            return QVariant();
        if (role == SubModelRole)
            return QVariant::fromValue(submodels_[index.row()]);
        return QVariant();
    }

public slots:
    Q_INVOKABLE
    void interact(int) override
    {}

private:
    PalletBlock* block_;
    ForkliftModel* forkliftModel_;
    QVector<LaneModel*> submodels_;
};

#endif // BLOCKMODEL_HH
