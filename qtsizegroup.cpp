#include <qtsizegroup.h>

#include <QTimer>
#include <QtGui>

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

#include <qtsizegroup.moc>
// vi: ts=4 sw=4 et
