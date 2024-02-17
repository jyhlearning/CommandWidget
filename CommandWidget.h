#ifndef OSMA_BACOMMANDWIDGET_H
#define OSMA_BACOMMANDWIDGET_H

#include <QTextEdit>
#include <QKeyEvent>
#include <QFont>
#include <QProcess>
#include <QByteArray>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextLayout>
#include <QTextCursor>
#include <QTextBlock>

namespace BACommand {
    enum Types {
        STANDARDMSG,
        ERRORMSG,
    };
}

class CommandWidget : public QTextEdit {
Q_OBJECT

public:
    explicit CommandWidget(QWidget *parent = nullptr);

    void setPrefix(const QString &pre);

    void initView();

protected:
    void keyPressEvent(QKeyEvent *e) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    // 字体
    QFont font;
    // 光标位置
    qint64 lastPosition = 0;
    // 上一次的输入内容
    QByteArray lastInput;
    //输出前缀
    QString prefix;

    void writeToTextEdit(const QString &str, Qt::GlobalColor c);

public slots:

    void readMessage(const QString& str, BACommand::Types type);

signals:

    void message(QString msg);
};

#endif//OSMA_BACOMMANDWIDGET_H