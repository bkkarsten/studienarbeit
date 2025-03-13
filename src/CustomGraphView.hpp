#ifndef CUSTOMGRAPHVIEW_H
#define CUSTOMGRAPHVIEW_H

#include <QuickQanava>
#include <QTimer>
#include <QGuiApplication>

/**
 * @brief A custom graph view that emits signals when clicked or double clicked. 
 * It then provides the location of the click in the graph view instead of the window.
 */
class CustomGraphView : public qan::GraphView {
    Q_OBJECT
    QML_ELEMENT

public:
    CustomGraphView(QQuickItem* parent = nullptr) 
        : qan::GraphView(parent)
        , clickCount(0) 
    {
        clickTimer.setInterval(200); // Time interval in milliseconds
        clickTimer.setSingleShot(true);
        connect(&clickTimer, &QTimer::timeout, this, &CustomGraphView::handleSingleClick);
    }

signals:
    void viewClicked(QPointF pos, bool shift);
    void viewDoubleClicked(QPointF pos, bool shift);

protected:
    virtual void navigableClicked(QPointF pos, QPointF globalPos) override {
        QPointF viewPos(pos.x() - getContainerItem()->x(), pos.y() - getContainerItem()->y());
        clickCount += 1;
        if (clickCount == 1) {
            clickTimer.start();
            lastClickPos = viewPos;
        } else if (clickCount == 2) {
            clickTimer.stop();
            Qt::KeyboardModifiers mods = QGuiApplication::queryKeyboardModifiers();
            emit viewDoubleClicked(viewPos, mods & Qt::ShiftModifier);
            clickCount = 0;
        }
        qan::GraphView::navigableClicked(pos, globalPos);
    }

private slots:
    void handleSingleClick() {
        Qt::KeyboardModifiers mods = QGuiApplication::queryKeyboardModifiers();
        emit viewClicked(lastClickPos, mods & Qt::ShiftModifier);
        clickCount = 0;
    }

private:
    QTimer clickTimer;
    int clickCount;
    QPointF lastClickPos;
};

QML_DECLARE_TYPE(CustomGraphView)

#endif // CUSTOMGRAPHVIEW_H