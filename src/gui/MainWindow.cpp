#pragma once

#include <QMainWindow>
#include <QTimer>
class SwarmManager;
class QTableWidget;
class QTextEdit;
class QQuickWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateUI();

private:
    SwarmManager* swarm = nullptr;
    QTableWidget* table = nullptr;
    QTextEdit* log = nullptr;
    QQuickWidget* mapWidget = nullptr;
    QTimer* timer = nullptr;
};