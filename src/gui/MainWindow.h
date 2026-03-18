// MainWindow.h
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
private slots:
    void onConnect();
    void armAll();
    void takeoffAll();
    void startFormation();
    void startVision();
    void updateTable();
private:
    QTableWidget *tableDrones;
    QTextEdit *log;
    SwarmManager *swarm;
    QTimer *timer;
};