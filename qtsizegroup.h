#ifndef QTSIZEGROUP_H
#define QTSIZEGROUP_H

#include <QtCore/QObject>
#include <QtCore/QList>

class QEvent;
class QWidget;

class QtSizeGroup : public QObject
{
    Q_OBJECT
public:
    QtSizeGroup(QObject* parent = 0);

    void addWidget(QWidget* widget);

public Q_SLOTS:
    void updateWidth();

protected:
    bool eventFilter(QObject*, QEvent* event);

private:
    QList<QWidget*> m_widgets;
};

#endif /* QTSIZEGROUP_H */
