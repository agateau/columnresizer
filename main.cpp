/*
 * Copyright 2011 Aurélien Gâteau <agateau@kde.org>
 * License: LGPL v2.1 or later (see COPYING)
 */
#include <QApplication>
#include <widgetresizer.h>

#include <QtGui>

#include <main.h>

#include <ui_demowidget.h>

Window::Window()
{
    m_ui = new Ui_DemoWidget;
    m_ui->setupUi(this);

    WidgetResizer* sizeGroup = new WidgetResizer(this);
    sizeGroup->addWidgetsFromLayout(m_ui->gridGroupBox->layout(), 0);
    sizeGroup->addWidgetsFromLayout(m_ui->formGroupBox1->layout(), 0);
    sizeGroup->addWidgetsFromLayout(m_ui->formGroupBox2->layout(), 0);

    sizeGroup = new WidgetResizer(this);
    sizeGroup->addWidgetsFromLayout(m_ui->gridGroupBox->layout(), 1);
    sizeGroup->addWidgetsFromLayout(m_ui->formGroupBox1->layout(), 1);
    sizeGroup->addWidgetsFromLayout(m_ui->formGroupBox2->layout(), 1);

    /*
    WidgetResizer* sizeGroup = new WidgetResizer(this);
    sizeGroup->addWidgetsFromLayout(layout1, 0);
    sizeGroup->addWidgetsFromLayout(layout2, 0);

    connect(m_spinBox, SIGNAL(valueChanged(int)), SLOT(updateAdjustableLabel()));
    updateAdjustableLabel();
    */
}

void Window::updateAdjustableLabel()
{
    /*
    QString txt;
    txt.fill('#', m_spinBox->value());
    m_adjustableLabel->setText(txt + ':');
    */
}

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Window window;
    window.show();
    return app.exec();
}

#include <main.moc>
