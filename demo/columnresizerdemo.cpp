/*
 * Copyright 2011 Aurélien Gâteau <agateau@kde.org>
 * License: BSD-3-Clause
 */
#include <QApplication>
#include <columnresizer.h>

#include <QtGui>

#include <columnresizerdemo.h>

#include <ui_demowidget.h>

Window::Window()
{
    m_ui = new Ui_DemoWidget;
    m_ui->setupUi(this);

    ColumnResizer* resizer = new ColumnResizer(this);
    resizer->addWidgetsFromLayout(m_ui->gridGroupBox1->layout(), 0);
    resizer->addWidgetsFromLayout(m_ui->formGroupBox1->layout(), 0);
    resizer->addWidgetsFromLayout(m_ui->formGroupBox2->layout(), 0);
    resizer->addWidgetsFromLayout(m_ui->gridGroupBox2->layout(), 0);

    connect(m_ui->spinBox, SIGNAL(valueChanged(int)), SLOT(updateAdjustableLabel()));
    updateAdjustableLabel();
}

void Window::updateAdjustableLabel()
{
    QString txt;
    txt.fill('#', m_ui->spinBox->value());
    m_ui->adjustableLabel->setText("Spin me" + txt + ':');
}

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Window window;
    window.show();
    return app.exec();
}

#include <columnresizerdemo.moc>
