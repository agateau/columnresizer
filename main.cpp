#include <QApplication>
#include <qtsizegroup.h>

#include <QtGui>

#include <main.h>

Window::Window()
{
    QGroupBox* groupBox1 = new QGroupBox("Foo", this);
    QLabel* label1 = new QLabel("Short:");
    QLineEdit* edit1 = new QLineEdit;
    QFormLayout* layout1 = new QFormLayout(groupBox1);
    layout1->addRow(label1, edit1);

    QGroupBox* groupBox2 = new QGroupBox("Bar", this);
    QLabel* label2 = new QLabel("Quite longer:");
    QLineEdit* edit2 = new QLineEdit;
    m_adjustableLabel = new QLabel;
    m_spinBox = new QSpinBox(this);
    QFormLayout* layout2 = new QFormLayout(groupBox2);
    layout2->addRow(label2, edit2);
    layout2->addRow(m_adjustableLabel, m_spinBox);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(groupBox1);
    layout->addWidget(groupBox2);
    layout->addStretch();

    QtSizeGroup* sizeGroup = new QtSizeGroup(this);
    sizeGroup->addWidget(label1);
    sizeGroup->addWidget(label2);
    sizeGroup->addWidget(m_adjustableLabel);

    connect(m_spinBox, SIGNAL(valueChanged(int)), SLOT(updateAdjustableLabel()));
    updateAdjustableLabel();
}

void Window::updateAdjustableLabel()
{
    QString txt;
    txt.fill('#', m_spinBox->value());
    m_adjustableLabel->setText(txt + ':');
}

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Window window;
    window.show();
    return app.exec();
}

#include <main.moc>
