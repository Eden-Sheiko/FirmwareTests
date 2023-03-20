//
// Created by eden on 3/16/23.
//

#ifndef UDP_SERVER_CLIENT_UDP_H
#define UDP_SERVER_CLIENT_UDP_H
#ifndef UDPSOCKET_CLIENT_UDP_H
#define UDPSOCKET_CLIENT_UDP_H

#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define IP_ADDRESS "192.168.220.34"
#define FLAG_ZERO 0
#define EQUAL_ZERO 0
#define TRUE 1
#define BYTE 1
#define FALSE 0
#define PORT 7
#define SLEEP_TIME 3
#define ERROR (-1)
#define MSG_BUFFER 256

/**
 * data_packet - is the packet  that being send to the
 * udp server
 * @brief data_packet contains 5 types:
 * Test_id type:[uint32_t]
 * Peripheral type:[uint8_t]
 * Iterations type:[uint8_t]
 * length type:[uint8_t]
 * msg type:[char]
 */
typedef struct data_packet
{
    uint32_t Test_id;
    uint8_t Peripheral;
    uint8_t Iterations;
    uint8_t length;
    char msg[MSG_BUFFER];
} data_packet_t;

/*
 *  4B       1B               			1B				1B		8B - 64 bit / 4B 32bit (word size)
 *   +------+----------+---+--------+---~~--+---------+--------+---~~---+
 *   | TEST ID | Peripheral to be tested |  Iterations  |length | *string |
 *   +------+----------+---+--------+---~~--+---------+--------+---~~---+
 */

/**
 * res is the result that being send back by the server
 * @brief res contains 2 types
 * Test_id type:[uint32_t]
 * Test_result type:[uint8_t]
 */
typedef struct res
{
    uint32_t Test_id;
    uint8_t Test_result;
} res_t;

/*
 *  4B       1B
 *   +------+----------+---+--~~---+
 *   | TEST ID | Test_result       |
 *   +------+----------+---+--~~---+
 */

// functions

/**
 * @brief udp_menu is a void function that  builds the packet structure according to the
 * user in input
 * @param per Peripheral to be tested (1 –Timer, 2 – UART, SPI – 4, I2C – 8, ADC – 16)
 * @param it number of Iterations
 * @param leng length of the stream
 * @param ms massage to be send
 * @param test test id
 */
void udp_menu(uint8_t *, uint8_t *, uint8_t *, char *, uint32_t *);

/**
 * print_menu
 * prints main menu
 */

void print_menu();

/**
 * print_sub_menu
 * prints sub menu
 */
void print_sub_menu();

#endif // UDPSOCKET_CLIENT_UDP_H

#endif // UDP_SERVER_CLIENT_UDP_H
