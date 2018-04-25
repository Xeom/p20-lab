#include <QApplication>
#include <iostream>
#include "window.h"
#include "serial.h"

using namespace std;

pthread_t listen_thread;

Serial *listener;

void *listen_thread_f(void *arg)
{
    while (1)
        listener->wait();
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Window w;
    Board *b;

    b = w.get_board();

    Serial serial(b, &cin);

    listener = &serial;

    w.show();

    pthread_create(&listen_thread, NULL, listen_thread_f, NULL);
    
    return app.exec();
}
