
#ifndef TTYPROXY_H
#define TTYPROXY_H

#ifdef CROSS_COMPILE

#define tty_proxy_open(file, flag)                  open(file, flag)
#define tty_proxy_tcgetattr(fd, termios_p)          tcgetattr(fd, termios_p)
#define tty_proxy_tcsetattr(fd, actions, termios_p) tcsetattr(fd, actions, termios_p)
#define tty_proxy_tcflush(fd, queue_selector)       tcflush(fd, queue_selector)

#else

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>

static int tty_proxy_open(const char *file, int flag)
{
    flag = flag;

    if (!file)
        return -1;

    uint16_t port = 0;
    if (strcmp("/dev/ttymxc0", file) == 0) {
        port = 20100;
    } else if (strcmp("/dev/ttymxc1", file) == 0) {
        port = 20101;
    } else if (strcmp("/dev/ttymxc2", file) == 0) {
        port = 20102;
    } else if (strcmp("/dev/ttymxc3", file) == 0) {
        port = 20103;
    } else if (strcmp("/dev/ttymxc4", file) == 0) {
        port = 20104;
    } else if (strcmp("/dev/ttymxc5", file) == 0) {
        port = 20105;
    } else if (strcmp("/dev/ttymxc6", file) == 0) {
        port = 20106;
    } else if (strcmp("/dev/ttymxc7", file) == 0) {
        port = 20107;
    } else {
        return -1;
    }

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        return -1;
    }

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("connect");
        return -1;
    }


     if (flag = fcntl(fd, F_GETFL, 0) <0) perror("get flag");
     flag |= O_NONBLOCK;
     if (fcntl(fd, F_SETFL, flag) < 0)
     perror("set flag");



    return fd;
}

static inline int tty_proxy_tcgetattr(int fd, struct termios *termios_p)
{
    fd = fd;
    termios_p = termios_p;
    return 0;
}

static inline int tty_proxy_tcsetattr(int fd, int actions, const struct termios *termios_p)
{
    fd = fd;
    actions = actions;
    termios_p = termios_p;
    return 0;
}

static inline int tty_proxy_tcflush(int fd, int queue_selector)
{
    fd = fd;
    queue_selector = queue_selector;
    return 0;
}

#endif

#endif // TTYPROXY_H
