#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_NAME "/myqueue"

int main()
{
    mqd_t receive_mq;
    struct mq_attr attr;

    attr.mq_flags = 0;        // blocking
    attr.mq_maxmsg = 10;      // max messages in queue
    attr.mq_msgsize = 128;    // max size of each message
    attr.mq_curmsgs = 0;

    // Create or open queue
    receive_mq = mq_open(QUEUE_NAME, O_RDONLY | O_CREAT, 0644, &attr);
    if (receive_mq == -1) {
        perror("receiver mq_open not open");
        exit(1);
    }

    char buffer[128];
    printf("Receiver started. Waiting for messages...\n");

    while (1) {
        ssize_t bytes = mq_receive(receive_mq, buffer, sizeof(buffer), NULL);
        if (bytes >= 0) {
            buffer[bytes] = '\0';
            printf("Received: %s\n", buffer);
        } else {
            perror("mq_receive");
        }
    }

    mq_close(receive_mq);
    mq_unlink(QUEUE_NAME);
    return 0;
}
