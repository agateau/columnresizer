/*
 * Copyright 2011 Aurélien Gâteau <agateau@kde.org>
 * License: LGPL v2.1 or later (see COPYING)
 */
#ifndef MAIN_H
#define MAIN_H

class Ui_DemoWidget;

class Window : public QWidget
{
    Q_OBJECT
public:
    Window();

public Q_SLOTS:
    void updateAdjustableLabel();

private:
    Ui_DemoWidget* m_ui;
};

#endif /* MAIN_H */
