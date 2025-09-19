#include "roundedprogressbarstyle.h"

#include <QProxyStyle>
#include <QPainter>
#include <QStyleOptionProgressBar>

void RoundedProgressBarStyle::drawControl(ControlElement element, const QStyleOption* option,
                     QPainter* painter, const QWidget* widget) const
{
    if (element == CE_ProgressBarContents)
    {
        const QStyleOptionProgressBar* progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar*>(option);
        if (!progressBarOption)
        {
            return;
        }

        QRect rect = progressBarOption->rect;
        qreal radius = rect.height() / 2.0;

        double percent = (double)(progressBarOption->progress - progressBarOption->minimum) /
                         (progressBarOption->maximum - progressBarOption->minimum);

        QRectF chunkRect = rect.adjusted(0, 0, -(1.0 - percent) * rect.width(), 0);

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(QColor("#000000"));
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(chunkRect, radius, radius);
        painter->restore();
    }
    else if (element == CE_ProgressBarGroove)
    {
        const QStyleOptionProgressBar* progressBarOption = qstyleoption_cast<const QStyleOptionProgressBar*>(option);
        if (!progressBarOption) {
            return;
        }

        QRect rect = progressBarOption->rect;
        qreal radius = rect.height() / 2.0;

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(QColor("#aaaaaa"));
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(rect, radius, radius);
        painter->restore();
    }
    else {
        QProxyStyle::drawControl(element, option, painter, widget);
    }
}
