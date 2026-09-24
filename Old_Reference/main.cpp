#include <linux/can.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>
#include <bridge.h>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <zmq.hpp>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Bridge bridge;
    engine.rootContext()->setContextProperty("bridge", &bridge);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("plswork", "Main");

    // Worker thread — never touches Qt UI objects directly
    QThread *worker = QThread::create([&bridge]() {
        zmq::context_t ctx;
        zmq::socket_t socket(ctx, zmq::socket_type::sub);
        socket.connect("ipc:///tmp/zmq_pubsub.sock");

        // Subscribe to all messages (empty filter = receive everything)
        socket.set(zmq::sockopt::subscribe, "");

        std::cout << "Subscriber connected, waiting for messages...\n";

        while (true) {
            zmq::message_t msg;
            socket.recv(msg, zmq::recv_flags::none);
            std::cout << "Received: " << msg.to_string() << "\n";
            can_frame f = *msg.data<can_frame>();

            switch(f.can_id){
            case 0x02:
                emit bridge.setSpeed(f.data[0]);
                emit bridge.setRpm(f.data[1]);
                emit bridge.setTemp1(f.data[2]);
                emit bridge.setTemp2(f.data[3]);
                emit bridge.setTemp3(f.data[4]);
                emit bridge.setTemp4(f.data[5]);
                break;
            }
        }

        // return 0;

        // int i = 0;
        // while (true) {
        //     sleep(1);
        //     i++;
        //     std::cout << i << std::endl;
        //     // Qt::QueuedConnection (default across threads) marshals
        //     // this safely onto the main/UI thread
        //     emit bridge.apps1(QString::number(i));
        // }
    });
    worker->start();

    int ret = QCoreApplication::exec();
    worker->quit();
    worker->wait();
    return ret;
}