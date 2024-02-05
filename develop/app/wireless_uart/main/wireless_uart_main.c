#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/uart.h"

#define PACKET_SYMBOL_START 0x2423
#define PACKET_SYMBOL_END 0x2324
#define PACKET_MIN_SIZE (2+4+2+1) //start + length + min data + checksum

/*
Packet Structure
Start Symbol - uint16 - 0x23 0x24
Data Length - uint32 - 4 bytes - only for data bytes, not include checksum
Data Bytes - bytearray - [Packet Length] bytes
 > Key String - string - dynamic bytes (1~kN) - until '=', if '=' not exist, whole bytes as key string, and value as empty
 > Value Bytes - bytearray - dynamic bytes (0~vN) - until end (allow empty)
XOR Checksum - 1 byte
End Symbol - uint16 - 0x24 0x23 (Optional)
*/
typedef struct {
    char* key_str;
    uint8_t* val_bytes;
    uint8_t* data_bytes;
    uint32_t data_size;
    uint8_t checksum;
} Packet_t;

void setup_uart(int baud_rate, int buf_size){
    // Configure parameters of an UART driver,
    // communication pins and install the driver
    uart_config_t uart_config = {
        .baud_rate = baud_rate,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM_0, &uart_config);
    // esp_err_t uart_driver_install(uart_port_t uart_num, int rx_buffer_size, int tx_buffer_size, int queue_size, QueueHandle_t *uart_queue, int no_use)
    uart_driver_install(UART_NUM_0, buf_size * 2, 0, 0, NULL, 0);
}

void app_main(){
    

    printf("Wireless UART\n");
}