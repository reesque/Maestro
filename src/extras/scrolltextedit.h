#ifndef SCROLLTEXTEDIT_H
#define SCROLLTEXTEDIT_H

#define WAIT_TIME 1000

#include <QTextEdit>
#include <QTimer>

class ScrollTextEdit : public QTextEdit {
    Q_OBJECT

public:
    explicit ScrollTextEdit(QWidget *parent = nullptr);
    ~ScrollTextEdit() override;

    void startScrolling();
    void stopScrolling();

private slots:
    void scrollStep();
    void waitAtTheStart();
    void waitAtTheEnd();

private:
    QTimer* scrollTimer;
    QTimer* startTimer;
    QTimer* endTimer;
};


#endif // SCROLLTEXTEDIT_H
