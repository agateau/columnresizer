/*
 * Copyright 2011 Aurélien Gâteau <agateau@kde.org>
 * License: BSD-3-Clause
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
