#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_NAME "/myqueue"

int main()
{
    mqd_t sender_mq;
    sender_mq = mq_open(QUEUE_NAME, O_WRONLY);
    if (sender_mq == -1) {
        perror("mq_open");
        exit(1);
    }

    char msg[128];
    printf("Enter message: ");
    fgets(msg, sizeof(msg), stdin);

    mq_send(sender_mq, msg, strlen(msg), 0);
    printf("Message sent.\n");

    mq_close(sender_mq);

    return 0;
}
