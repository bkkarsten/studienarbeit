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
    CustomGraphView(QQuickItem* parent = nullptr);

signals:
    void viewClicked(QPointF pos, bool shift);
    void viewDoubleClicked(QPointF pos, bool shift);

protected:
    virtual void navigableClicked(QPointF pos, QPointF globalPos) override;

    virtual void keyPressEvent(QKeyEvent* event) override;

private slots:
    void handleSingleClick();

private:
    QTimer clickTimer;
    int clickCount;
    QPointF lastClickPos;
};

QML_DECLARE_TYPE(CustomGraphView)

#endif // CUSTOMGRAPHVIEW_H