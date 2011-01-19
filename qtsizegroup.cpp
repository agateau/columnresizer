#include <qtsizegroup.h>

#include <QDebug>
#include <QEvent>
#include <QFormLayout>
#include <QGridLayout>
#include <QTimer>
#include <QWidget>

QtSizeGroup::QtSizeGroup(QObject* parent)
: QObject(parent)
{}

void QtSizeGroup::addWidget(QWidget* widget)
{
    m_widgets.append(widget);
    widget->installEventFilter(this);
    QTimer::singleShot(0, this, SLOT(updateWidth()));
}

void QtSizeGroup::updateWidth()
{
    int width = 0;
    Q_FOREACH(QWidget* widget, m_widgets) {
        width = qMax(widget->sizeHint().width(), width);
    }
    Q_FOREACH(QWidget* widget, m_widgets) {
        widget->setMinimumWidth(width);
    }
}

bool QtSizeGroup::eventFilter(QObject*, QEvent* event)
{
    if (event->type() == QEvent::Resize) {
        updateWidth();
    }
    return false;
}

void QtSizeGroup::addWidgetsFromLayout(QLayout* layout, int column)
{
    Q_ASSERT(column >= 0);
    QGridLayout* grid = qobject_cast<QGridLayout*>(layout);
    QFormLayout* form = qobject_cast<QFormLayout*>(layout);
    if (grid) {
    } else if (form) {
        if (column > QFormLayout::SpanningRole) {
            qCritical() << "column should not be more than" << QFormLayout::SpanningRole << "for QFormLayout";
            return;
        }
        QFormLayout::ItemRole role = static_cast<QFormLayout::ItemRole>(column);
        for (int row = 0; row < form->rowCount(); ++row) {
            QLayoutItem* item = form->itemAt(row, role);
            QWidget* widget = item->widget();
            if (widget) {
                addWidget(widget);
            } else {
                qWarning() << "Not handling content of row" << row + 1 << ": layout item is not a widget";
            }
        }
    } else {
        qCritical() << "Don't know how to handle layout" << layout;
    }
}

#include <qtsizegroup.moc>
// vi: ts=4 sw=4 et
