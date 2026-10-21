/* HCI UART config override + init.
 * Overrides the weak btble_dma_uart_get_config() to use
 * UART1 on GPIO21(TX)/GPIO22(RX), 115200, no HWFC. */

#include <stdint.h>
#include "btble_lib_api.h"
#include <FreeRTOS.h>
#include "task.h"

struct btble_dma_uart_config {
    const char *uart_name;
    uint32_t    baudrate;
    uint8_t     tx_pin;
    uint8_t     rx_pin;
    uint8_t     cts_pin;
    uint8_t     rts_pin;
    uint8_t     flow_ctrl;
    const char *dma_rx_name;
    const char *dma_tx_name;
};

void btble_dma_uart_get_config(struct btble_dma_uart_config *cfg)
{
    cfg->uart_name   = "uart1";
    cfg->baudrate    = 115200;
    cfg->tx_pin      = 21;
    cfg->rx_pin      = 22;
    cfg->cts_pin     = 0xff;
    cfg->rts_pin     = 0xff;
    cfg->flow_ctrl   = 0;
    cfg->dma_rx_name = "dma0_ch2";
    cfg->dma_tx_name = "dma0_ch3";
}

extern void btble_dma_uart_init(void);

void uarthci_init(void)
{
    btble_dma_uart_init();
    btble_controller_init(configMAX_PRIORITIES - 1);
}
