#ifndef __SX1278_DEFS_H
#define __SX1278_DEFS_H

/*
FIFO write/read register
not accessible in SLEEP mode
*/
#define REG_FIFO 0x00

// << Common Register Settings >>
/*
Operation mode register
2-0 Device modes (default: 0x01 STDBY)
    0x0 -> SLEEP 
    0x1 -> STDBY (default)
    0x2 -> Frequency synthesis TX (FSTX)
    0x3 -> Transmit (TX)
    0x4 -> Frequency synthesis RX (FSRX)
    0x5 -> Receive continuous (RXCONTINUOUS)
    0x6 -> receive single (RXSINGLE)
    0x7 -> Channel activity detection (CAD)
3   Low Freq Mode On bit (default: 0x01 LF)
5-4 reserved
6   [Only Lora Mode] 
    0=access Lora reg page 0x0D-0x3F (default)
    1=access FSK reg page  0x0D-0x3F
7   [Only in SLEEP mode]
    0 = FSK/OOK mode (default)
    1 = LoRa mode
*/
#define REG_OP_MODE 0x01

typedef enum
{
    SX_MODE_SLEEP = 0u,
    SX_MODE_STDBY,
    SX_MODE_FSTX,
    SX_MODE_TX,
    SX_MODE_FSRX,
    SX_MODE_RXCONTINUOUS,
    SX_MODE_RXSINGLE,
    SX_MODE_CAD
} sx1278_mode;

/*
MSB of RF carrier freqency Frf(23:16)
*/
#define REG_FR_MSB 0x06

/*
MidSB of RF carrier frequency Frf(15:8)
*/
#define REG_FR_MID 0x07

/*
LSB of RF carrier frequency Frf(7:0)
*/
#define REG_FR_LSB 0x08

// << Registers for RF blocks >>

/*
elects PA output pin
0 -> RFO pin        | power <= +14 dBm
1 -> PA_BOOST pin   | power <= +20 dBm
*/
#define REG_PA_CONFIG 0x09

/*
Rise/Fall time of ramp up/down in FSK
*/
#define REG_PA_RAMP 0x0A

/*
overload current protection register
*/
#define REG_OCP 0x0B

/*
1-0 High Frequency (RFI_HF) LNA current adjustment
2   reserved
4-3 Low Frequency (RFI_LF) LNA current adjustment
7-5 LNA gain settings
*/
#define REG_LNA 0x0C

// << Lora page registers >>

/*
SPI interface address pointer in FIFO data buffer
*/
#define REG_FIFO_ADDR_PTR 0x0D

/*
write base address in FIFO data buffer for TX modulator
*/
#define REG_FIFO_TX_BASE_ADDR 0x0E

/*
read base address in FIFO data buffer for RX demodulator
*/
#define REG_FIFO_RX_BASE_ADDR 0x0F

/*
Start address (in data buffer) of last packet received
*/
#define REG_FIFO_RX_CURRENT_ADDR 0x10

/*
*/
#define REG_IRQ_FLAGS_MASK 0x11

/*
*/
#define REG_IRQ_FLAGS 0x12

/*
Number of payload bytes of latest packet received
*/
#define REG_RX_NB_BYTES 0x13

/*
*/
#define REG_RX_HEADER_CNT_VALUE_MSB 0x14

/*
*/
#define REG_RX_HEADER_CNT_VALUE_LSB 0x15

/*
*/
#define REG_RX_PACKET_CNT_VALUE_MSB 0x16

/*
*/
#define REG_RX_PACKET_CNT_VALUE_LSB 0x17

/*
0-4 Modem Status
7-5 Coding Rate
*/
#define REG_MODEM_STAT 0x18

/*
Estimation of SNR on last packet received. 
*/
#define REG_PKT_SNR_VALUE 0x19

/*
RSSI of the latest packet received
*/
#define REG_PKT_RSSI_VALUE 0x1A

/*
current RSSI value
*/
#define REG_RSSI_VALUE 0x1B

/*
*/
#define REG_HOP_CHANNEL 0x1C

/*
0   Implicit header mode on
3-1 Coding rate
7-4 signal bandwidth
*/
#define REG_MODEM_CONFIG_1 0x1D

/*
1-0 Rx Time-out Msb
2   Enable CRC generation and chenck on payload
3   continuous mode on (default to 0 - single packet mode)
7-4 Spreading Factor
*/
#define REG_MODEM_CONFIG_2 0x1E

/*
RX timeout LSB
*/
#define REG_SYMB_TIMEOUT_LSB 0x1F

/*
Preamble length MSB
*/
#define REG_PREAMBLE_MSB 0x20

/*
Preamble length LSB
*/
#define REG_PREAMBLE_LSB 0x21

/*
payload length in bytes
needs to be set in implicit mode 
for the expected packet length (0 is prohibited)
*/
#define REG_PAYLOAD_LENGTH 0x22

/*
Maximum payload length
*/
#define REG_MAX_PAYLOAD_LENGTH 0x23

/*
*/
#define REG_HOP_PERIOD 0x24

/*
Current value of RX databuffer pointer
(address of last byte writen by Loar receiver)
*/
#define REG_FIFO_RX_BYTE_ADDR_PTR 0x25

/*
1-0 reserved
2   AgcAutoOn bit
3   LowDataRateOptimize bit
7-4 unused
*/
#define REG_MODEM_CONFIG_3 0x26

/*
Estimated frequency error MSB
*/
#define REG_FEI_MSB 0x28

/*
*/
#define REG_FEI_MID 0x29

/*
*/
#define REG_FEI_LSB 0x2A

/*
Wideband RSSI measurement used to locally generate a random value
*/
#define REG_RSSI_WIDEBAND 0x2C

/*
*/
#define REG_DETECT_OPTIMIZE 0x31

/*
6   Invert the LoRA I and Q signals
*/
#define REG_INVERT_IQ 0x33

/*
LoRa detection threshold
*/
#define REG_DETECTION_THRESHOLD 0x37

/*
LoRa sync Word
0x34 reserved for lorawan networks
*/
#define REG_SYNC_WORD 0x39

// << Low Frequency additional registers >>

/*
Sets the floor reference for all AGC thresholds
*/
#define REG_AGC_REF_LF 0x61

/*
defines the 1st GC Threshold
*/
#define REG_AGC_THRESH1_LF 0x62

/*
*/
#define REG_AGC_THRESH2_LF 0x63

/*
*/
#define REG_AGC_THRESH3_LF 0x64

/*
5-0 reserved
7-6 PLL bandwidth
*/
#define REG_PLL_LF 0x70

#endif