#ifndef HASHTABLEWIDGET_H
#define HASHTABLEWIDGET_H

#include <QWidget>
#include <QVector>

#include "HashTable.h"

class QGridLayout;
class HashTableCellWidget;

class HashTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HashTableWidget(QWidget *parent = nullptr);
    ~HashTableWidget();

    int findRow(int key) const;

public slots:
    void addRow(int key, const QString &value);
    bool removeRow(int key, const QString &value);
    void resize(int size);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void addConnection(int from, int to);
    void removeConnections(int itemIndex);
    void onValueChanged(HashTableCellWidget *item);

private:
    struct ItemData //TODO: to class
    {
        HashTableCellWidget *ptr = nullptr;
        HashTableCellWidget *prev = nullptr;
        HashTableCellWidget *next = nullptr;

        ///pass prev elements
        void recalculateLinks(ItemData* prev, ItemData* next, HashTable::Cell const* current); //TODO: to private //TODO: unused
        void reset();
        QRect connectionRect;
        QRect baseConnectionRect(int connectionOffset) const;
        static QRect baseConnectionRect(HashTableCellWidget *from, HashTableCellWidget *to, int connectionOffset);
    };

    QVector<ItemData> m_items;
    QGridLayout *m_layout = nullptr;
    int m_baseConnectionOffset = 10;
    int m_connectionOffset = 5;
    HashTable m_table = {};
};

#endif //HASHTABLEWIDGET_H
