#include "CustomGraphView.hpp"

CustomGraphView::CustomGraphView(QQuickItem* parent)
    : qan::GraphView(parent)
    , clickCount(0) 
{
    clickTimer.setInterval(200); // Time interval in milliseconds
    clickTimer.setSingleShot(true);
    connect(&clickTimer, &QTimer::timeout, this, &CustomGraphView::handleSingleClick);
}

void CustomGraphView::navigableClicked(QPointF pos, QPointF globalPos) {
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

void CustomGraphView::keyPressEvent(QKeyEvent* event) {
    int key = event->key();
    if(key == Qt::Key_Delete || key == Qt::Key_Backspace) {
        int numSelected = getGraph()->getSelectedNodes().size() + getGraph()->getSelectedEdges().size() + getGraph()->getSelectedGroups().size();
        
        getGraph()->removeSelection();

        if(numSelected >= 1) {
            emit graphChanged();
        }
    }
    qan::GraphView::keyPressEvent(event);
}

void CustomGraphView::handleSingleClick() {
    Qt::KeyboardModifiers mods = QGuiApplication::queryKeyboardModifiers();
    emit viewClicked(lastClickPos, mods & Qt::ShiftModifier);
    clickCount = 0;
}