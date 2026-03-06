#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main() {
    int serial_port;
    struct termios tty;
    char buffer[256];

    serial_port = open("/dev/ttyGS0", O_RDWR);

    if (serial_port < 0) {
        printf("Error opening serial port");
        return 1;
    }

    tcgetattr(serial_port, &tty);

    tty.c_cflag = B115200 | CS8 | CREAD;
    tty.c_iflag = IGNPAR;

    tcflush(serial_port, TCIFLUSH);
    tcsetattr(serial_port, TCSANOW, &tty);

    write(serial_port, "Ping\n", 5);
    printf("Sent: Ping\n");

    int n = read(serial_port, buffer, sizeof(buffer) - 1);

    if (n > 0) {
        buffer[n] = '\0';
        printf("Received: %s\n", buffer);
    }

    close(serial_port);
    return 0;
}
