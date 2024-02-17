#include "CommandWidget.h"
#include <QDebug>

CommandWidget::CommandWidget(QWidget *parent): QTextEdit(parent) {
    setStyleSheet("background-color:rgb(0,0,0); color:rgb(255,255,255); border:0px;");
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWindowTitle("命令行提示符");

    prefix="Command";

    font.setFamily("Times New Roman");
    font.setPixelSize(16);
    setFont(font);

    QTextCursor editCursor = textCursor();
    QTextBlockFormat textBlockFormat;
    textBlockFormat.setLineHeight(20, QTextBlockFormat::FixedHeight);
    editCursor.setBlockFormat(textBlockFormat);
    setTextCursor(editCursor);
}

void CommandWidget::keyPressEvent(QKeyEvent *e) {
    QTextCursor editCursor = textCursor();
    if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {
        e->ignore();
        editCursor.setPosition(lastPosition, QTextCursor::MoveAnchor);
        editCursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
        QString string = editCursor.selectedText();
        editCursor.clearSelection();
#ifdef Q_OS_WIN
        lastInput = string.toLocal8Bit() + '\r' + '\n';
#elif Q_OS_LINUX
        lastInput =  string.toLocal8Bit() + '\n';
#endif
        emit message(lastInput);
        readMessage("",BACommand::STANDARDMSG);
        return;
    } else if ((e->key() == Qt::Key_Delete && editCursor.position() <= lastPosition) ||
               (e->key() == Qt::Key_Backspace && editCursor.position() <= lastPosition))
        return;
    else
        return QTextEdit::keyPressEvent(e);
}

void CommandWidget::readMessage(const QString& str, BACommand::Types type) {
    Qt::GlobalColor c;
    switch (type) {
        case BACommand::STANDARDMSG:
            c = Qt::white;
            break;
        case BACommand::ERRORMSG:
            c = Qt::red;
            break;
        default:;
    }
    if (str != QString::fromLocal8Bit(lastInput)) {
        if(!str.isEmpty())
            writeToTextEdit(str,c);
        writeToTextEdit(prefix+">",Qt::white);
    }
}

void CommandWidget::setPrefix(const QString &pre) {
    prefix = pre;
}

void CommandWidget::writeToTextEdit(const QString &str, Qt::GlobalColor c) {
    setTextColor(c);
    append(str.trimmed());
    moveCursor(QTextCursor::End);
    lastPosition = textCursor().position();
}

void CommandWidget::mousePressEvent(QMouseEvent *event) {
    //QTextEdit::mousePressEvent(event);
}

void CommandWidget::mouseReleaseEvent(QMouseEvent *event) {
    //QTextEdit::mouseReleaseEvent(event);
}

void CommandWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    //QTextEdit::mouseDoubleClickEvent(event);
}

void CommandWidget::initView() {
    writeToTextEdit(prefix+">",Qt::white);
}
