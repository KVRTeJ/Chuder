#include <QDebug>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPalette>
#include <QColor>

#include "HashTableCellWidget.h"

#include "HashTableWidget.h"

HashTableWidget::HashTableWidget(QWidget *parent)
    : QWidget(parent)
    , m_layout(new QGridLayout(this))
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(m_layout);
    setLayout(mainLayout);

    QMargins margins = m_layout->contentsMargins();
    //TODO: margin recalculating to fit all connections
    margins.setRight(margins.right() + 15);
    m_layout->setContentsMargins(margins);
}

HashTableWidget::~HashTableWidget() {}


int HashTableWidget::findRow(int key, bool isMessage) { //TODO: QPushButton "OK" to reset color
    if(m_highlighted != -1) {
        m_items[m_highlighted].ptr->setPalette(QPalette());
        m_items[m_highlighted].ptr->setAutoFillBackground(false);
    }

    m_highlighted = m_table.m_getIndex(key);

    if(m_highlighted == -1) {
        if(isMessage) {
            QMessageBox msgBox;
            msgBox.setText("Not found. . .");
            msgBox.exec();
        }
        return -1;
    }

    QColor color(119, 136, 153);
    QPalette palet(color);

    m_items[m_highlighted].ptr->setAutoFillBackground(true);
    m_items[m_highlighted].ptr->setPalette(palet);

    return m_highlighted;
}

void HashTableWidget::addRow(int key, const QString &value, bool isMessage) {

    if (!m_items.size()) {
        if(isMessage) {
            QMessageBox msgBox;
            msgBox.setText("Table size is equal 0.");
            msgBox.exec();
        }
        return;
    }

    if(value == "" || key < 1) {
        if(isMessage) {
            QMessageBox msgBox;
            msgBox.setText("Can't add the empty row");
            msgBox.exec();
        }
        return;
    }

    HashTable::Cell newCell(key, value.toStdString());
    int row = m_table.add(newCell);
    if(row == -1) {
        if(isMessage) {
            QMessageBox msgBox;
            msgBox.setText("This element is already added || Table is full");
            msgBox.exec();
        }
        return;
    }

    m_items[row].ptr->setKey(key);
    m_items[row].ptr->setValue(value);
    if(m_table.m_data[row].prev()) {
        int from = m_table.m_getIndex(m_table.m_data[row].prev()->key());
        addConnection(from, row);
        m_items[from].idNext = &m_items[row];
        m_items[row].idPrev = &m_items[from];
    }

    update();

}

bool HashTableWidget::removeRow(int key, const QString &value, bool isMessage) { //TODO: messageBox
    int row = m_table.m_getIndex(key);
    if(row == -1) {
        return false;
    }

    int highlightedKey = -1;
    if(m_highlighted != -1) {
        highlightedKey = m_table.m_data[m_highlighted].key();
    }

    if(!m_table.remove(key)) {
        return false;
    }

    findRow(highlightedKey, false);

    ItemData* current = &m_items[row];
    if(!current->idNext) {
        if(current->idPrev) {
            current->idPrev->next = nullptr;
            current->idPrev->idNext = nullptr;
        }
        current->reset();

        update();
        return true;
    }

    ItemData* it = current->idNext;
    do {
        it->swap(current);
        current = current->idNext;
        it = current->idNext;
    } while(it);
    current->idPrev->next = nullptr;
    current->idPrev->idNext = nullptr;
    current->reset();

    update();

    return true;
}

void HashTableWidget::resize(int size) {
    //TODO: implement
    int oldSize = m_items.size();
    for (int i = oldSize - 1; i >= size; --i) {
        m_items[i].reset();
        delete m_items[i].ptr;
    }

    m_items.resize(size);
    for (int i = oldSize; i < size; ++i) {
        m_items[i].ptr = new HashTableCellWidget(this);
        //TODO: make empty rows uneditable by default
        connect(m_items[i].ptr, &HashTableCellWidget::valueChanged, this, &HashTableWidget::onValueChanged);
        m_layout->addWidget(m_items[i].ptr, i, 0);
    }

    std::vector<HashTable::Cell> oldData(size);
    std::swap(oldData, m_table.m_data);

    for(int i = 0, j = 0; i < oldData.size(); ++i, ++j) {
        if(oldData[i].value() != "") {
            addRow(oldData[i].key(), QString::fromStdString(oldData[i].value()), false);
        }
    }

    oldSize = (oldSize > size
               ? size
               : oldSize);

    for(int i = 0; i < oldSize; ++i) {
        if(m_table.m_data[i].value() == "") {
            m_items[i].reset();
        }
    }

}

void HashTableWidget::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    QPainter painter(this);

    for (ItemData &item : m_items) {
        if (item.next) {
            item.connectionRect = item.baseConnectionRect(m_baseConnectionOffset);

            int rightBorderOffset = 0;
            QVector<int> rightBorders;
            for (const ItemData &other : qAsConst(m_items)) {
                if (&other == &item || !other.connectionRect.isValid()) {
                    continue;
                }

                if (other.connectionRect.intersects(item.connectionRect)) {
                    rightBorders.append(other.connectionRect.right());
                    while (rightBorders.contains(item.connectionRect.right() + rightBorderOffset)) {
                        rightBorderOffset += m_connectionOffset;
                    }
                }
            }
            item.connectionRect.setRight(item.connectionRect.right() + rightBorderOffset);

            if (event->rect().intersects(item.connectionRect)) {
                painter.drawLine(item.connectionRect.topLeft(), item.connectionRect.topRight());
                painter.drawLine(item.connectionRect.topRight(), item.connectionRect.bottomRight());
                painter.drawLine(item.connectionRect.bottomRight(), item.connectionRect.bottomLeft());
                //TODO: draw arrow
                painter.drawLine(item.connectionRect.bottomLeft().rx(), item.connectionRect.bottomLeft().ry(),
                                 item.connectionRect.bottomLeft().rx() + 5, item.connectionRect.bottomLeft().ry() - 5);
                painter.drawLine(item.connectionRect.bottomLeft().rx(), item.connectionRect.bottomLeft().ry(),
                                 item.connectionRect.bottomLeft().rx() + 5, item.connectionRect.bottomLeft().ry() + 5);
            }
        }
    }
    //TODO: resize widget / layout
}

void HashTableWidget::addConnection(int from, int to)
{
    m_items[from].next = m_items[to].ptr;
}

void HashTableWidget::removeConnections(int itemIndex)
{
    if (m_items[itemIndex].prev) {
        m_items[itemIndex].prev = m_items[itemIndex].next;
    }
    m_items[itemIndex].prev = nullptr;
    m_items[itemIndex].next = nullptr;
}

void HashTableWidget::onValueChanged(HashTableCellWidget *item)
{
    //TODO: implement
    //m_hashTable[item->key()] = item->value().toStdString();
    qDebug() << item->value(); //FIXME: remove
}

QRect HashTableWidget::ItemData::baseConnectionRect(int connectionOffset) const
{
    return baseConnectionRect(ptr, next, connectionOffset);
}

QRect HashTableWidget::ItemData::baseConnectionRect(HashTableCellWidget *from, HashTableCellWidget *to, int connectionOffset)
{
    if (!from || !to) {
        return QRect();
    }

    QPoint startPos = from->pos();
    startPos.rx() += from->width();
    startPos.ry() += from->height() / 3 * 2;
    QPoint endPos = to->pos();
    endPos.rx() += to->width();
    endPos.ry() += to->height() / 3;

    QRect rect;
    rect.setTopLeft(startPos);
    rect.setBottom(endPos.y());
    rect.setRight(qMax(startPos.x(), endPos.x()) + connectionOffset);
    return rect;
}

void HashTableWidget::ItemData::reset() {
    ptr->setKey(-1);
    ptr->setValue("");

    next = nullptr;
    prev = nullptr;

    idPrev = nullptr;
    idNext = nullptr;
}

void HashTableWidget::ItemData::swap(ItemData* other) {
    if(!other) {
        return;
    }

    auto currentKey = this->ptr->key();
    auto currentValue = this->ptr->value();

    this->ptr->setKey(other->ptr->key());
    this->ptr->setValue(other->ptr->value());

    other->ptr->setKey(currentKey);
    other->ptr->setValue(currentValue);
}

