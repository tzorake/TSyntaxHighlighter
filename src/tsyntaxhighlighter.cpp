#include "tsyntaxhighlighter.h"
#include "helper.h"

#include <QTextBlock>
#include <QRegularExpression>

TSyntaxHighlighter::TSyntaxHighlighter(QTextEdit *parent)
    : QObject(parent)
{
    Helper::readFile(":/resources/styles/googlecode.css", m_styles);

    QTextEdit *textEdit = static_cast<QTextEdit *>(parent);
    QTextDocument *document = textEdit->document();

    document->setDefaultStyleSheet(m_styles);

    connect(textEdit, &QTextEdit::textChanged, this, &TSyntaxHighlighter::onTextChanged);
    connect(&m_lexerWorker, &LexerWorker::processingFinished, this, &TSyntaxHighlighter::handleProcessingFinished);
}

QPair<int, int> TSyntaxHighlighter::linesWithinViewport()
{
    QTextEdit *textEdit = static_cast<QTextEdit *>(parent());

    QRect rect = textEdit->viewport()->rect();
    QTextCursor topCursor = textEdit->cursorForPosition(rect.topLeft());
    QTextCursor bottomCursor = textEdit->cursorForPosition(rect.bottomLeft());

    return QPair<int, int>(topCursor.blockNumber(), bottomCursor.blockNumber());
}

void TSyntaxHighlighter::onTextChanged()
{
    QTextEdit *textEdit = static_cast<QTextEdit *>(parent());
    QString text = textEdit->toPlainText();
    m_lexerWorker.processText(text);
}

void TSyntaxHighlighter::handleProcessingFinished(const QString &text)
{
    QTextEdit *textEdit = static_cast<QTextEdit *>(parent());
    QTextDocument *document = textEdit->document();
    QTextCursor cursor = textEdit->textCursor();

    {
        const QSignalBlocker blocker(textEdit);

        QRegularExpression codeRegex("<pre><code class='javascript'>(.*?)</code></pre>", QRegularExpression::DotMatchesEverythingOption);
        QRegularExpressionMatch match = codeRegex.match(text);
        if (match.hasMatch()) {
            QString text = match.captured(1);
            QStringList lines = text.split("\n");

            QPair<int, int> bounds = linesWithinViewport();

            for (int i = bounds.first; i <= bounds.second; ++i) {
                QTextBlock block = document->findBlockByLineNumber(i);
                cursor.setPosition(block.position());
                cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
                cursor.insertHtml(lines[i]);
            }
        }
    }

    textEdit->setTextCursor(cursor);

//    {
//        const QSignalBlocker blocker(textEdit);

//        QTextDocument *document = textEdit->document();
//        QTextCursor cursor = textEdit->textCursor();
//        int cursorPosition = cursor.position();

//        QRegularExpression codeRegex("<pre><code class='javascript'>(.*?)</code></pre>", QRegularExpression::DotMatchesEverythingOption);
//        QRegularExpressionMatch match = codeRegex.match(text);

////        QRegularExpression commentRegex("<span class=\"hljs-comment\">(.*?)</span>");

//        if (match.hasMatch()) {
//            QString text = match.captured(1);

////            QRegularExpressionMatchIterator it;

////            for (const QRegularExpressionMatch &match : commentRegex.globalMatch(text)) {
////                QString m = match.captured(1);
////                int start = match.capturedStart(1);
////                int end = match.capturedEnd(1);
////            }

//            QStringList lines = text.split("\n");

//            QTextCursor cursor = textEdit->textCursor();
//            QPair<int, int> bounds = linesWithinViewport();

//            for (int i = bounds.first; i <= bounds.second; ++i) {
//                QTextBlock block = document->findBlockByLineNumber(i);
//                cursor.setPosition(block.position());
//                cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
//                cursor.insertHtml(lines[i]);
//            }
//        }

//        cursor.setPosition(cursorPosition);
//        textEdit->setTextCursor(cursor);
//    }
}
