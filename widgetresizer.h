/*
 * Copyright 2011 Aurélien Gâteau <agateau@kde.org>
 * License: LGPL v2.1 or later (see COPYING)
 */
#ifndef WIDGETRESIZER_H
#define WIDGETRESIZER_H

#include <QtGui/QFormLayout>

#include <QtCore/QObject>
#include <QtCore/QList>

class QEvent;
class QGridLayout;
class QLayout;
class QWidget;

struct WidgetResizerPrivate;
class WidgetResizer : public QObject
{
    Q_OBJECT
public:
    WidgetResizer(QObject* parent = 0);
    ~WidgetResizer();

    void addWidget(QWidget* widget);
    void addWidgetsFromLayout(QLayout*, int column);
    void addWidgetsFromGridLayout(QGridLayout*, int column);
    void addWidgetsFromFormLayout(QFormLayout*, QFormLayout::ItemRole role);

public Q_SLOTS:
    void updateWidth();

protected:
    bool eventFilter(QObject*, QEvent* event);

private:
    WidgetResizerPrivate* const d;
};

#endif /* WIDGETRESIZER_H */
