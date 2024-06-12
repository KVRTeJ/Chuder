#ifndef HASHTABLEWIDGET_H
#define HASHTABLEWIDGET_H

#include <QWidget>
#include <QVector>

#include "HashTable.h"
#include "HashFunctionMultiplicationMethod.h"

class QGridLayout;
class HashTableCellWidget;

class HashTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HashTableWidget(QWidget* parent = nullptr);
    ~HashTableWidget();

    int findRow(int key, bool isMessage = true);

public slots:
    void addRow(int key, const QString& value, bool isMessage = true);
    bool removeRow(int key, bool isMessage = true);
    void resize(int size);
    void changeHashFunction(const int key);

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void addConnection(int from, int to);
    void removeConnections(int itemIndex);
    void onValueChanged(HashTableCellWidget* item);

private:
    void clearBackground();
private:
    struct ItemData;

    int m_highlighted = -1;
    QVector<ItemData> m_items;
    QGridLayout *m_layout = nullptr;
    int m_baseConnectionOffset = 10;
    int m_connectionOffset = 5;
    HashTable m_table = {};
};

struct HashTableWidget::ItemData {
    HashTableCellWidget* ptr = nullptr;
    HashTableCellWidget* prev = nullptr;
    HashTableCellWidget* next = nullptr;

    ItemData* idPrev = nullptr;
    ItemData* idNext = nullptr;

    void reset();
    void swap(ItemData* other);
    QRect connectionRect;
    QRect baseConnectionRect(int connectionOffset) const;
    static QRect baseConnectionRect(HashTableCellWidget* from, HashTableCellWidget* to, int connectionOffset);
};

#endif //HASHTABLEWIDGET_H
