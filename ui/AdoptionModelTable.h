// AdoptionTableModel.h
#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "Dog.h"

class AdoptionTableModel : public QAbstractTableModel {
    Q_OBJECT
public:
    AdoptionTableModel(const std::vector<Dog>& dogs, QObject* parent = nullptr)
        : QAbstractTableModel(parent), dogs(dogs) {}

    int rowCount(const QModelIndex& = {}) const override {
        return (int)dogs.size();
    }
    int columnCount(const QModelIndex& = {}) const override {
        return 4;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || role != Qt::DisplayRole) return {};
        const Dog& d = dogs[index.row()];
        switch (index.column()) {
            case 0: return QString::fromStdString(d.getBreed());
            case 1: return QString::fromStdString(d.getName());
            case 2: return d.getAge();
            case 3: return QString::fromStdString(d.getPhotoLink());
        }
        return {};
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return {};
        switch (section) {
            case 0: return "Breed";
            case 1: return "Name";
            case 2: return "Age";
            case 3: return "Photo";
        }
        return {};
    }

private:
    std::vector<Dog> dogs;
};