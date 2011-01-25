/*
 * Copyright 2011 Aurélien Gâteau <agateau@kde.org>
 * License: LGPL v2.1 or later (see COPYING)
 */
#include <widgetresizer.h>

#include <QDebug>
#include <QEvent>
#include <QFormLayout>
#include <QGridLayout>
#include <QTimer>
#include <QWidget>

class WRWidgetItem : public QWidgetItem
{
public:
    WRWidgetItem(QWidget* widget, QFormLayout* formLayout)
    : QWidgetItem(widget)
    , m_width(-1)
    , m_formLayout(formLayout)
    {}

    QSize sizeHint() const
    {
        QSize size = QWidgetItem::sizeHint();
        if (m_width != -1) {
            size.setWidth(m_width);
        }
        qDebug() << __FUNCTION__ << size;
        return size;
    }

    QSize minimumSize() const
    {
        QSize size = QWidgetItem::minimumSize();
        if (m_width != -1) {
            size.setWidth(m_width);
        }
        qDebug() << __FUNCTION__ << size;
        return size;
    }

    QSize maximumSize() const
    {
        QSize size = QWidgetItem::maximumSize();
        if (m_width != -1) {
            size.setWidth(m_width);
        }
        qDebug() << __FUNCTION__ << size;
        return size;
    }

    void setFixedWidth(int width)
    {
        qDebug() << width;
        if (width != m_width) {
            m_width = width;
            invalidate();
        }
    }

    void setGeometry(const QRect& _rect)
    {
        QRect rect = _rect;
        int width = widget()->sizeHint().width();
        rect.setLeft(rect.right() - width);
        QWidgetItem::setGeometry(rect);
    }

    QFormLayout* formLayout() const
    {
        return m_formLayout;
    }

private:
    int m_width;
    QFormLayout* m_formLayout;
};

typedef QPair<QGridLayout*, int> GridColumnInfo;

struct WidgetResizerPrivate
{
    QList<QWidget*> m_widgets;
    QList<WRWidgetItem*> m_wrWidgetItemList;
    QList<GridColumnInfo> m_gridColumnInfoList;
};

WidgetResizer::WidgetResizer(QObject* parent)
: QObject(parent)
, d(new WidgetResizerPrivate)
{}

WidgetResizer::~WidgetResizer()
{
    delete d;
}

void WidgetResizer::addWidget(QWidget* widget)
{
    d->m_widgets.append(widget);
    widget->installEventFilter(this);
    QTimer::singleShot(0, this, SLOT(updateWidth()));
}

void WidgetResizer::updateWidth()
{
    int width = 0;
    Q_FOREACH(QWidget* widget, d->m_widgets) {
        width = qMax(widget->sizeHint().width(), width);
    }
    Q_FOREACH(WRWidgetItem* item, d->m_wrWidgetItemList) {
        item->setFixedWidth(width);
        item->formLayout()->update();
    }
    Q_FOREACH(GridColumnInfo info, d->m_gridColumnInfoList) {
        info.first->setColumnMinimumWidth(info.second, width);
    }
}

bool WidgetResizer::eventFilter(QObject*, QEvent* event)
{
    if (event->type() == QEvent::Resize) {
        updateWidth();
    }
    return false;
}

void WidgetResizer::addWidgetsFromLayout(QLayout* layout, int column)
{
    Q_ASSERT(column >= 0);
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(layout);
    QFormLayout* formLayout = qobject_cast<QFormLayout*>(layout);
    if (gridLayout) {
        addWidgetsFromGridLayout(gridLayout, column);
    } else if (formLayout) {
        if (column > QFormLayout::SpanningRole) {
            qCritical() << "column should not be more than" << QFormLayout::SpanningRole << "for QFormLayout";
            return;
        }
        QFormLayout::ItemRole role = static_cast<QFormLayout::ItemRole>(column);
        addWidgetsFromFormLayout(formLayout, role);
    } else {
        qCritical() << "Don't know how to handle layout" << layout;
    }
}

void WidgetResizer::addWidgetsFromGridLayout(QGridLayout* layout, int column)
{
    for (int row = 0; row < layout->rowCount(); ++row) {
        QLayoutItem* item = layout->itemAtPosition(row, column);
        if (!item) {
            qDebug() << "No item at row" << row << "column" << column;
            continue;
        }
        QWidget* widget = item->widget();
        if (!widget) {
            continue;
        }
        addWidget(widget);
    }
    d->m_gridColumnInfoList << GridColumnInfo(layout, column);
}

void WidgetResizer::addWidgetsFromFormLayout(QFormLayout* layout, QFormLayout::ItemRole role)
{
    for (int row = 0; row < layout->rowCount(); ++row) {
        QLayoutItem* item = layout->itemAt(row, role);
        if (!item) {
            qDebug() << "No item at row" << row << "role" << role;
            continue;
        }
        QWidget* widget = item->widget();
        if (!widget) {
            continue;
        }
        layout->removeItem(item);
        delete item;
        WRWidgetItem* wrWidgetItem = new WRWidgetItem(widget, layout);
        layout->setItem(row, role, wrWidgetItem);
        addWidget(widget);
        d->m_wrWidgetItemList << wrWidgetItem;
    }
}

#include <widgetresizer.moc>
// vi: ts=4 sw=4 et
