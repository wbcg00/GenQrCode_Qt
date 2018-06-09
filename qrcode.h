#ifndef CODE_H
#define CODE_H

#include <QDebug>
#include <QIcon>
#include <QWidget>
#include <QPainter>
#include <QSpacerItem>
#include <QByteArray>
#include <QPaintEvent>
#include "qrencode/qrencode.h"

class QRCode:public QWidget {
    Q_OBJECT
public:
    enum QR_MODE {
        MODE_NUL = QR_MODE_NUL,
        MODE_NUM = QR_MODE_NUM,
        MODE_AN = QR_MODE_AN,
        MODE_8 = QR_MODE_8,
        MODE_KANJI = QR_MODE_KANJI,
        MODE_STRUCTURE = QR_MODE_STRUCTURE,
        MODE_ECI = QR_MODE_ECI,
        MODE_FNC1FIRST = QR_MODE_FNC1FIRST,
        MODE_FNC1SECOND = QR_MODE_FNC1SECOND
    };
    
    enum QR_LEVEL {
        LEVEL_L = QR_ECLEVEL_L,
        LEVEL_M = QR_ECLEVEL_M,
        LEVEL_Q = QR_ECLEVEL_Q,
        LEVEL_H = QR_ECLEVEL_H
    };

    QRCode(QWidget *parent=NULL):QWidget(parent) {
        this->iconPixmap=QPixmap(":/logo.png");
        this->margin = 10;
        this->foreground = QColor("black");
        this->background = QColor("white");
        this->casesen = true;
        this->mode = MODE_8;
        this->level = LEVEL_Q;
        this->percent = 0.23;
    }
    
    //----------------------------------------------------------------------------
    // 函数原型： setQrCodeMargin
    // 函数功能： 设置二维码和四周的距离
    // 传入参数： int &margine  true:影响；false：不影响
    // 传出参数： 无
    // 函数返回： 无
    //
    // 注意事项： 默认为10，看情况设置
    //----------------------------------------------------------------------------
    void setQrCodeMargin(const int &margin) {
        this->margin = margin;
        //update();
    }
    //----------------------------------------------------------------------------
    // 函数原型： setQrCodeIcon
    // 函数功能： 设置二维码中心的图标
    // 传入参数： QPixmap &icon  要显示的图片
    // 传入参数： qreal percent  影响图片大小
    // 传出参数： 无
    // 函数返回： 无
    //
    // 注意事项： 图标格式建议：png 大小：512*512
    //----------------------------------------------------------------------------
    void setQrCodeIcon(const QPixmap &icon, qreal percent=0.23) {
        this->percent = percent < 0.5 ? percent : 0.3;
        this->iconPixmap = icon;
       // update();
    }
    //----------------------------------------------------------------------------
    // 函数原型： setQrCodeCaseSensitive
    // 函数功能： 设置二维码内容是否受大小写影响
    // 传入参数： bool flag=false  true:影响；false：不影响
    // 传出参数： 无
    // 函数返回： 无
    //
    // 注意事项： 类的构造函数默认是对大小写敏感的
    //----------------------------------------------------------------------------
    void setQrCodeCaseSensitive(bool flag=false) {
        this->casesen = flag;
        //update();
    }
    //----------------------------------------------------------------------------
    // 函数原型： setQrCodeContent
    // 函数功能： 设置二维码内容和尺寸大小
    // 传入参数： QByteArray &text  要显示的内容
    // 传入参数： QSize &size       二维码尺寸大小
    // 传出参数： 无
    // 函数返回： 无
    //
    // 注意事项： 设置完其它属性后最后调用，因为它才触发了重绘事件
    //----------------------------------------------------------------------------
    void setQrCodeContent(const QByteArray &text,const QSize &size)
    {
        if (text.length () == 0) {
            this->text = QByteArray("http://github.com/chinat");
        }
        else {
            this->text = text;
        }
        setFixedSize (size);

        update();
    }
protected:
    void paintEvent (QPaintEvent *event) {
        QWidget::paintEvent (event);
        QPainter painter(this);
        QRcode *qrcode = QRcode_encodeString(text.data (), 7, (QRecLevel)level, (QRencodeMode)mode, casesen ? 1 : 0);
        if(0 != qrcode) {
            unsigned char *point = qrcode->data;
            painter.setPen(Qt::NoPen);
            painter.setBrush(this->background);
            painter.drawRect(0, 0, this->width(), this->height());
            double scale = (this->width () - 2.0 * margin) / qrcode->width;
            painter.setBrush(this->foreground);
            for (int y = 0; y < qrcode->width; y ++) {
                for (int x = 0; x < qrcode->width; x ++) {
                    if (*point & 1) {
                        QRectF r(margin + x * scale, margin + y * scale, scale, scale);
                        painter.drawRects(&r, 1);
                    }
                    point ++;
                }
            }
            point = NULL;
            QRcode_free(qrcode);
            // draw icon
            // if (icon.isNull ()) {
            painter.setBrush(this->background);
            double icon_width = (this->width () - 2.0 * margin) * percent;
            double icon_height = icon_width;
            double wrap_x = (this->width () - icon_width) / 2.0;
            double wrap_y = (this->width () - icon_height) / 2.0;
            QRectF wrap(wrap_x - 5, wrap_y - 5, icon_width + 10, icon_height + 10);
            painter.drawRoundRect(wrap, 50, 50);

            QRectF target(wrap_x, wrap_y, icon_width, icon_height);
            QRectF source(0, 0, iconPixmap.width (), iconPixmap.height ());
            painter.drawPixmap (target, iconPixmap, source);
        }
        qrcode = NULL;
        event->accept ();
    }
    
private:
    bool casesen;
    int margin;
    QPixmap iconPixmap;
    qreal percent;
    QByteArray text;
    QColor foreground;
    QColor background;
    QR_MODE mode;
    QR_LEVEL level;
};
#endif // CODE_H
