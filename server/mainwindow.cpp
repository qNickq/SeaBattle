#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->game_started = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_bt_clicked()
{
    listener = new QTcpServer(this);

    if (!listener->listen(QHostAddress::Any, 2019) && server_status == false)
    {
        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(listener->errorString());
        ui->textEdit->append(listener->errorString());
    }
    else
    {
        server_status = 1;
        ui->textEdit->append(QString::fromUtf8("Server is running!"));
        this->pls.resize(2);
    }
     connect(listener, SIGNAL(newConnection()), this, SLOT(newuser()));

}

void MainWindow::on_stop_bt_clicked()
{
    if(server_status == 1)
    {
        foreach(int i, SClients.keys())
        {
            QTextStream os(SClients[i]);
            os.setAutoDetectUnicode(true);
            os << QDateTime::currentDateTime().toString() << "\n";

            SClients[i]->close();
            SClients.remove(i);
        }
        for (int i = 0; i < pls.size(); ++i)
        {
            pls[i]->socket()->write("Server stoped");
            pls[i]->socket()->close();
        }
        pls.clear();
        listener->close();
        game_started = false;
        ui->textEdit->append(QString::fromUtf8("Server stoped!"));
        server_status = 0;
    }
}

void MainWindow::newuser()
{
    if(server_status == 1 && SClients.size() < 2)
    {
        ui->textEdit->append(QString::fromUtf8("New connection!"));

        QTcpSocket* clientSocket = listener->nextPendingConnection();
        int idusersocs = clientSocket->socketDescriptor();

        SClients[idusersocs] = clientSocket;
        connect(SClients[idusersocs], SIGNAL(readyRead()), this, SLOT(slotReadClient()));

        switch (this->SClients.size())
        {
        case 1 :
        {
            pls[0] = new Player(clientSocket);
            pls[0]->set_first_step(1);
            pls[0]->socket()->write("1");
            break;
        }
        case 2  :
        {
            pls[1] = new Player(clientSocket);
            pls[1]->set_first_step(0);
            pls[1]->socket()->write("2");
            pls[1]->socket()->waitForReadyRead(100);
            break;
        }
        }
    }
}

void MainWindow::show_map(QString msg,int descr)
{
    QStringList list = msg.split(' ');
    QString mes;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            mes += list[j*10 + i] + " ";
        }
        mes += "\n";
    }
    ui->textEdit->append("Player-" + QString::number(descr) + ": " + "\n" + mes);

}

void MainWindow::slotReadClient()
{
    QTcpSocket* clientSocket = reinterpret_cast<QTcpSocket*>(sender());

    int idusersocs = clientSocket->socketDescriptor();
    int size = clientSocket->bytesAvailable();

    QString msg = clientSocket->read(size);
    parse_msg(msg, idusersocs);

}

void MainWindow::send_status(const char* msg)
{
    QList<int> descs = SClients.keys();

    for (int i = 0; i < descs.size(); i++)
    {
        SClients[descs[i]]->flush();
        SClients[descs[i]]->write(msg, QString(msg).size());
    }
    ui->textEdit->append(msg);
}

void MainWindow::parse_msg(QString msg,int descr)
{
    /*
    1) Поле после расстановки кораблей
    2) Координаты обстрела
    */
    size_t id = identify_player(descr);

    if (!game_started)
    { // Поле после расстановки кораблей

        show_map(msg,descr);

        pls[id]->set_map(convert_str_to_matrix(msg));
        pls[id]->set_ready(1);

        if(pls[!id] && pls[!id]->isReady())
        {
            game_started = true;
            send_status("all_ready");
        }
    }
    else
    { // Координаты обстрела

        QStringList list = msg.split(',');
        QPoint point(list[0].toInt(), list[1].toInt());

        bool res = pls[!id]->check_point(point); // Проверяем на попадание на карте соперника и меняем значение
        bool first_map_is_empty = pls[id]->isEmpty();
        bool second_map_is_empty = pls[!id]->isEmpty();

        if (!first_map_is_empty && !second_map_is_empty) // У обоих есть живые корабли
        {
            pls[id]->socket()->write(QString::number(res).toUtf8());
            pls[!id]->socket()->write((QString::number(point.x()) + "," + QString::number(point.y())).toUtf8());

            QString mes = "Client-" + QString::number(descr) + ": Shoot in " + msg + " and res is "+ QString::number(res);
            ui->textEdit->append(mes);
        }
        else if (first_map_is_empty) // У первого закончились. Победа второго.
        {
            pls[id]->socket()->write((QString::number(point.x()) + "," + QString::number(point.y())).toUtf8());
            pls[id]->socket()->waitForReadyRead(100);
            pls[!id]->socket()->write("WINNER");
            pls[id]->socket()->write("LOSE");

            ui->textEdit->append("Player-" + QString::number(pls[!id]->descriptor()) + " - winner");
        }
        else if (second_map_is_empty) // У второго закончились. Победа первого.
        {

            pls[!id]->socket()->write((QString::number(point.x()) + "," + QString::number(point.y())).toUtf8());
            pls[!id]->socket()->waitForReadyRead(100);
            pls[id]->socket()->write("WINNER");
            pls[!id]->socket()->write("LOSE");

            ui->textEdit->append("Player-" + QString::number(pls[id]->descriptor()) + " - winner");
        }
    }
}

size_t MainWindow::identify_player(int id)
{
    if (id == pls[0]->descriptor())
        return 0;
    else return 1;
}

QVector<QVector<int> > MainWindow::convert_str_to_matrix(QString msg)
{
    QStringList list = msg.split(' ');
    qDebug()<<msg;
    QVector<QVector<int> > matr(10,QVector<int>(10,0));

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            matr[i][j]=(list[i*10 + j].toInt());
        }
    }
    qDebug()<<matr;
    return matr;
}
