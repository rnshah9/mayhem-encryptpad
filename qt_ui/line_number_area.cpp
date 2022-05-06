#include "line_number_area.h"

// Qt
#include <QAbstractTextDocumentLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QScrollBar>
#include <QTextBlock>
#include "plain_text_edit.h"

QLineNumberArea::QLineNumberArea(PlainTextEdit *parent)
    : QWidget(parent), m_codeEditParent(parent)
{
}

QSize QLineNumberArea::sizeHint() const
{
    if (m_codeEditParent == nullptr)
    {
        return QWidget::sizeHint();
    }

    const int digits = QString::number(m_codeEditParent->document()->blockCount()).length();
    int space;

#if QT_VERSION >= 0x050B00
    space = 15 + m_codeEditParent->fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
#else
    space = 15 + m_codeEditParent->fontMetrics().width(QLatin1Char('9')) * digits;
#endif

    return {space, 0};
}

void QLineNumberArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Clearing rect to update
    auto backgroundColor = m_codeEditParent->palette().background().color();
    auto foregroundColor = m_codeEditParent->palette().foreground().color();
    painter.fillRect(event->rect(), backgroundColor);

    auto blockNumber = m_codeEditParent->getFirstVisibleBlock();
    auto block = m_codeEditParent->document()->findBlockByNumber(blockNumber);

    // auto top = (int)m_codeEditParent->document()
    //                ->documentLayout()
    //                ->blockBoundingRect(block)
    //                .top();

    auto top = m_codeEditParent->getContentOffsetY();
    auto bottom = top + (int)m_codeEditParent->document()->documentLayout()->blockBoundingRect(block).height();

    auto currentLine = m_codeEditParent->palette().highlight().color();
    auto otherLines = foregroundColor;

    painter.setFont(m_codeEditParent->font());

    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);

            auto isCurrentLine = m_codeEditParent->textCursor().blockNumber() == blockNumber;
            painter.setPen(isCurrentLine ? currentLine : otherLines);

            painter.drawText(-5, top, sizeHint().width(), m_codeEditParent->fontMetrics().height(), Qt::AlignRight,
                             number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int)m_codeEditParent->document()->documentLayout()->blockBoundingRect(block).height();
        ++blockNumber;
    }
}
