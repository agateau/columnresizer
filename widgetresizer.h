#ifndef WIDGETRESIZER_H
#define WIDGETRESIZER_H

#include <QtCore/QObject>
#include <QtCore/QList>

class QEvent;
class QLayout;
class QWidget;

class WidgetResizer : public QObject
{
    Q_OBJECT
public:
    WidgetResizer(QObject* parent = 0);

    void addWidget(QWidget* widget);
    void addWidgetsFromLayout(QLayout*, int column);

public Q_SLOTS:
    void updateWidth();

protected:
    bool eventFilter(QObject*, QEvent* event);

private:
    QList<QWidget*> m_widgets;
};

#endif /* WIDGETRESIZER_H */
