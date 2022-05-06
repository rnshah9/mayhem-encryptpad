#ifndef PLAIN_TEXT_EDIT_H
#define PLAIN_TEXT_EDIT_H

#include <QPlainTextEdit>

class QLineNumberArea;
class PlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    typedef QPlainTextEdit super;
    explicit PlainTextEdit(QWidget *parent = 0);
    int getFirstVisibleBlock() const;
    int getContentOffsetY() const;

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
signals:
    void urlDropped(QUrl url);
    void leaveControl();
    void enterControl();

public slots:
    void updateLineNumberAreaWidth(int);
private:
    QLineNumberArea *lineNumberArea;

};

#endif // PLAIN_TEXT_EDIT_H
