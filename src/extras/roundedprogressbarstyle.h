#ifndef ROUNDEDPROGRESSBARSTYLE_H
#define ROUNDEDPROGRESSBARSTYLE_H

#include <QProxyStyle>

class RoundedProgressBarStyle : public QProxyStyle {
    void drawControl(ControlElement element, const QStyleOption* option,
                         QPainter* painter, const QWidget* widget = nullptr) const override;
};

#endif // ROUNDEDPROGRESSBARSTYLE_H
