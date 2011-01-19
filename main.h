#ifndef MAIN_H
#define MAIN_H

class Window : public QWidget
{
    Q_OBJECT
public:
    Window();

public Q_SLOTS:
    void updateAdjustableLabel();

private:
    QSpinBox* m_spinBox;
    QLabel* m_adjustableLabel;
};

#endif /* MAIN_H */
