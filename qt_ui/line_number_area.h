#pragma once

#include <QWidget> // Required for inheritance

class PlainTextEdit;

class QLineNumberArea : public QWidget
{
    Q_OBJECT

  public:
    explicit QLineNumberArea(PlainTextEdit *parent = nullptr);

    // Disable copying
    QLineNumberArea(const QLineNumberArea &) = delete;
    QLineNumberArea &operator=(const QLineNumberArea &) = delete;

    QSize sizeHint() const override;

  protected:
    void paintEvent(QPaintEvent *event) override;

  private:

    PlainTextEdit *m_codeEditParent;
};
