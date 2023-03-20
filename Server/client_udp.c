//
// Created by eden on 3/16/23.
//
#include "client_udp.h"

static unsigned int test_id = EQUAL_ZERO;

int main(int argc, char *argv[])
{
    while (TRUE)
    {

        /*************************************** Vars ***************************************************/
        struct sockaddr_in dest;                  // Holds Destination socket (IP+PORT)
        int socket_fd;                            // Holds socket file descriptor
        unsigned int ssize;                       // Holds size of dest
        int retVal = EQUAL_ZERO;                  // Holds return Value for recvfrom() / sendto()
        data_packet_t data_packet = {EQUAL_ZERO}; // creating instance of data_packet_t struct
        res_t data_packet_answer = {EQUAL_ZERO};  // // creating instance of res_t struct
        udp_menu(&data_packet.Peripheral, &data_packet.Iterations, &data_packet.length, data_packet.msg,
                 &data_packet.Test_id);
        /************************************* Initialization ******************************************/

        // getting the size of the structs
        int i_size_of_struct = sizeof(data_packet);
        int i_size_of_new_struct = sizeof(data_packet_answer);

        // creating buffers with their size of the struct
        char buffer_to_send[i_size_of_struct];
        char new_buffer[i_size_of_new_struct];

        // setting the buffers to zero
        memset(buffer_to_send, EQUAL_ZERO, i_size_of_struct);
        memset(new_buffer, EQUAL_ZERO, i_size_of_new_struct);

        // transforming the struct to buffer
        memcpy(buffer_to_send, &data_packet, i_size_of_struct);

        /************************************* Initialization ******************************************/

        socket_fd = socket(AF_INET, SOCK_DGRAM, FLAG_ZERO); // Create socket
        if (socket_fd == ERROR)
        {
            perror("Create socket");
            exit(TRUE);
        } // Validate the socket

        bzero((char *)&dest, sizeof(dest));           // Clearing the struct
        dest.sin_family = (short)AF_INET;             // Setting IPv4
        dest.sin_port = htons(PORT);                  // Setting port
        dest.sin_addr.s_addr = inet_addr(IP_ADDRESS); // Setting IP address

        ssize = sizeof(dest); // Get dest size

        /************************************* Code *****************************************************/

        // Send Ping
        retVal = sendto(socket_fd, &buffer_to_send, i_size_of_struct, FLAG_ZERO, (struct sockaddr *)&dest, ssize);
        if (retVal < FALSE)
        {
            break;
        }

        // Get answer
        retVal = recvfrom(socket_fd, &new_buffer, i_size_of_new_struct, FLAG_ZERO, (struct sockaddr *)&dest, &ssize);
        if (retVal < FALSE)
        {
            break;
        }

        printf("------------------------------------\n");
        printf("             massage sent:      \n");
        printf("Test_id : %d\n", data_packet.Test_id);
        printf("Peripheral : %d\n", data_packet.Peripheral);
        printf("length : %d\n", data_packet.length);
        printf("Iterations : %d\n", data_packet.Iterations);
        printf("massage sent : %s\n", data_packet.msg);
        printf("------------------------------------\n");
        printf("\n");

        // getting the data
        data_packet_answer.Test_id = *(uint32_t *)(new_buffer + EQUAL_ZERO);
        data_packet_answer.Test_result = *(uint8_t *)(new_buffer + 4);

        printf("------------------------------------\n");
        printf("            massage received:      \n");
        printf("Test id : %d\n", data_packet_answer.Test_id);
        printf("Test result : %d (1 = passed 0 = failed)  \n", data_packet_answer.Test_result);
        printf("------------------------------------\n");
        printf("\n");

        // Make the process sleep for 3 sec
        sleep(SLEEP_TIME);
    }
}

void udp_menu(uint8_t *per, uint8_t *it, uint8_t *leng, char *ms, uint32_t *test)
{
    char char_holder;
    uint8_t peripheral = EQUAL_ZERO;
    uint8_t iter = EQUAL_ZERO;
    char msg[MSG_BUFFER] = {EQUAL_ZERO};
    char *ptr_c = msg;
    size_t buffer_size = MSG_BUFFER;
    size_t data_holder = EQUAL_ZERO;
    int int_holder;
    uint8_t len = EQUAL_ZERO;

    // call to the menu
    print_menu();
    // loop to get user input
    while (1)
    {
        fflush(stdin);
        fflush(stdout);
        scanf(" %char_holder", &char_holder);
        print_sub_menu();
        switch (char_holder)
        {
        case 'a':
            printf("please enter an Peripheral \n");
            scanf("%hhu", &peripheral);
            *per = peripheral;
            break;
        case 'b':
            printf("please enter number of Iterations \n");
            scanf("%hhu", &iter);
            *it = iter;
            break;
        case 'c':
            printf("please enter a string to send \n");
            while ((int_holder = getchar()) != '\n' && int_holder != EOF)
                ;
            data_holder = getline(&ptr_c, &buffer_size, stdin);

            strcpy(ms, ptr_c);
            len = data_holder + BYTE;
            *leng = len;
            break;
        case 'd':
            printf("sending... \n");
            ++test_id;
            *test = test_id;
            return;
        case 'e':
            exit(EQUAL_ZERO);
        default:
            printf("Try again\n");
        }
    }
}

void print_menu()
{
    printf("***********************************\n");
    printf("************* MENU **************\n");
    printf("        Enter your packet structure  \n");
    printf("***********************************\n");
    printf("\ta- Peripheral to be tested (1 –Timer, 2 – UART, SPI – 4, I2C – 8, ADC – 16)\n");
    printf("\tb- number of Iterations \n");
    printf("\tc- massage to be sent \n");
    printf("\td- send!!! \n");
    printf("\te- Exit program\n");
    printf("***********************************\n\n\n");
}

void print_sub_menu()
{
    printf("\ta- Peripheral to be tested (1 –Timer, 2 – UART, SPI – 4, I2C – 8, ADC – 16)\n");
    printf("\tb- number of Iterations \n");
    printf("\tc- massage to be sent \n");
    printf("\td- send!!! \n");
    printf("\te- Exit program\n");
}
