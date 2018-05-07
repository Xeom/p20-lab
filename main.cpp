#include <QApplication>
#include <iostream>

#include "window.h"
#include "output.h"
#include "serial.h"

#if !defined(NO_UART)
# include <wiringPi.h>
# include <wiringSerial.h>
#endif

using namespace std;

pthread_t listen_thread;
pthread_t output_thread;

Serial *listener;
Output *outputter;

int serialfd;

void *listen_thread_f(void *arg)
{
    while (1)
        listener->wait();
}

void *output_thread_f(void *arg)
{
    while (1)
        outputter->wait();
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Window w;
    Board *b;

    b = w.get_board();

#if !defined(NO_UART)
    if (wiringPiSetup() == -1)
        cout << "Could not set up wiringpi";
    serialfd = serialOpen("/dev/ttyS0", 460800);
    if (serialfd < 0)
        cout << "Could not open serial";
#endif
        
    Serial serial(b);
    Output output(serialfd);

    listener = &serial;
    outputter = &output;

    cout << "Initialized all" << serialfd << endl;

    w.show();

    pthread_create(&listen_thread, NULL, listen_thread_f, NULL);
    pthread_create(&output_thread, NULL, output_thread_f, NULL);

#if !defined(NO_UART)    
    serialPuts(serialfd, "s\r");
#endif

    return app.exec();
}
