/*
 *  AtCmd.h - GS2200 AT Command Operation
 *  Copyright 2019 Norikazu Goto
 *
 *  This work is free software; you can redistribute it and/or modify it under the terms 
 *  of the GNU Lesser General Public License as published by the Free Software Foundation; 
 *  either version 2.1 of the License, or (at your option) any later version.
 *
 *  This work is distributed in the hope that it will be useful, but without any warranty; 
 *  without even the implied warranty of merchantability or fitness for a particular 
 *  purpose. See the GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License along with 
 *  this work; if not, write to the Free Software Foundation, 
 *  Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#ifndef _GS_ATCM_H_
#define _GS_ATCM_H_


#define  ATCMD_VERSION                "1.0.0"

#define  ATCMD_INVALID_CID            0xFF  /* invalid CID */

#define ATCMD_BSSID_MAX_LENGTH        20
#define ATCMD_SSID_MAX_LENGTH         32
#define ATCMD_MAC_MAX_LENGTH          18
#define ATCMD_PASSWORD_MAX_LENGTH     32

#define  ATCMD_CR          0x0D     /* Carriage Return */
#define  ATCMD_LF          0x0A     /* Line Feed       */
#define  ATCMD_ESC         0x1B     /* ESC charcter    */



typedef enum {
    ATCMD_FSM_START = 0,
    ATCMD_FSM_RESPONSE,
    ATCMD_FSM_ESC_START,
    ATCMD_FSM_BULK_DATA,
    ATCMD_FSM_UDP_BULK_DATA
} ATCMD_FSM_E;

typedef enum {
    ATCMD_RESP_UNMATCH = 0,
    ATCMD_RESP_OK = 1,
    ATCMD_RESP_INVALID_INPUT,
    ATCMD_RESP_ERROR,
    ATCMD_RESP_ERROR_SOCKET_FAILURE,
    ATCMD_RESP_DISCONNECT,
    ATCMD_RESP_DISASSOCIATION_EVENT,
    ATCMD_RESP_OUT_OF_STBY_ALARM,
    ATCMD_RESP_OUT_OF_STBY_TIMER,
    ATCMD_RESP_OUT_OF_DEEP_SLEEP,
    ATCMD_RESP_ERROR_IP_CONFIG_FAIL,
    ATCMD_RESP_NORMAL_BOOT_MSG,
    ATCMD_RESP_RESET_WLAN_WD,
    ATCMD_RESP_RESET_APP_WD,
    ATCMD_RESP_RESET_WLAN_SW,
    ATCMD_RESP_RESET_APP_SW,
    ATCMD_RESP_RESET_WLAN_EXCEPT,
    ATCMD_RESP_EXTERNAL_RESET,
    ATCMD_RESP_RESPONSE_TIMEOUT,
    ATCMD_RESP_BULK_DATA_RX,
    ATCMD_RESP_UDP_BULK_DATA_RX,
    ATCMD_RESP_ESC_OK,
    ATCMD_RESP_ESC_FAIL,
    ATCMD_RESP_TCP_SERVER_CONNECT,
    ATCMD_RESP_TIMEOUT,
    ATCMD_RESP_NO_MORE_MEMORY,
    ATCMD_RESP_SPI_ERROR
} ATCMD_RESP_E;

typedef enum {
    ATCMD_REGDOMAIN_FCC = 0,
    ATCMD_REGDOMAIN_ETSI = 1,
    ATCMD_REGDOMAIN_TELEC = 2,
    ATCMD_REGDOMAIN_UNKNOWN = -1
} ATCMD_REGDOMAIN_E;

typedef enum {
    ATCMD_SEC_MAUTO = 0,
    ATCMD_SEC_OPEN = 1,
    ATCMD_SEC_WEP = 2,
    ATCMD_SEC_WPAPSK = 4,
    ATCMD_SEC_WPA2PSK = 8,
    ATCMD_SEC_WPA_E = 16,
    ATCMD_SEC_WPA2_E = 32,
    ATCMD_SEC_WPA2_AEC_TKIP = 64,
    ATCMD_SEC_UNKNOWN = -1
} ATCMD_SECURITYMODE_E;


typedef enum {
    ATCMD_SOCKOPT_TYPE_SOCKET = 1,
    ATCMD_SOCKOPT_TYPE_IP = 2,
    ATCMD_SOCKOPT_TYPE_TCP = 3,
    ATCMD_SOCKOPT_TYPE_UNKNOWN = -1
} ATCMD_SOCKET_OPTION_TYPE_E;

typedef enum {
    ATCMD_SOCKOPT_PARAM_TCP_MAXRT = 29,
    ATCMD_SOCKOPT_PARAM_TCP_KEEPALIVE = 9,
    ATCMD_SOCKOPT_PARAM_TCP_MAX_REXMIT = 0x2A,
    ATCMD_SOCKOPT_PARAM_TCP_REX_TIMER_RATE = 0x2B,
    ATCMD_SOCKOPT_PARAM_SO_RCVBUF = 8, /* Max 64KB */
    ATCMD_SOCKOPT_PARAM_TCP_MAX_TX_Q_DEPTH = 0x2E,
    ATCMD_SOCKOPT_PARAM_TCP_REX_TIMER_RATE_TICK = 0x2F,
    ATCMD_SOCKOPT_PARAM_IP_DSCP = 0x25,
    ATCMD_SOCKOPT_PARAM_UNKNOWN = -1
} ATCMD_SOCKET_OPTION_PARAM_E;

typedef enum {
    ATCMD_MODE_STATION = 0,
    ATCMD_MODE_AD_HOC = 1, 	/* Ad Hoc is not supported. This is for AT+WS command */
    ATCMD_MODE_LIMITED_AP = 2,
    ATCMD_MODE_UNKNOWN = -1
} ATCMD_MODE_E;


typedef uint8_t ATCMD_IPv4[4];


typedef union {
    ATCMD_IPv4 ipv4;
} ATCMD_IP;

typedef struct {
	char bssid[ATCMD_BSSID_MAX_LENGTH + 1];
	char ssid[ATCMD_SSID_MAX_LENGTH + 1];
	uint8_t channel;
	ATCMD_MODE_E station;
	int8_t signal;
	ATCMD_SECURITYMODE_E security;
} ATCMD_NetworkScanEntry;

typedef struct {
	char mac[ATCMD_MAC_MAX_LENGTH + 1];
	uint8_t connected;
	ATCMD_MODE_E mode;
	char bssid[ATCMD_BSSID_MAX_LENGTH + 1];
	char ssid[ATCMD_SSID_MAX_LENGTH + 1];
	uint8_t channel;
	ATCMD_SECURITYMODE_E security;
	char signal;
	ATCMD_IP addr;
	ATCMD_IP subnet;
	ATCMD_IP gateway;
	ATCMD_IP dns1;
	ATCMD_IP dns2;
	uint32_t rxCount;
	uint32_t txCount;
} ATCMD_NetworkStatus;

typedef struct {
    char ssid[ATCMD_SSID_MAX_LENGTH + 1];
    char password[ATCMD_PASSWORD_MAX_LENGTH + 1];
    uint16_t channel;
} AtCmd_WPSResult;

/*************<Function prototye forward delarations >***************/
void AtCmd_Init(void);
ATCMD_RESP_E AtCmd_AT(void);
ATCMD_RESP_E AtCmd_VER(void);
ATCMD_RESP_E AtCmd_ATE(uint8_t n);
ATCMD_RESP_E AtCmd_RESET(void);
ATCMD_RESP_E AtCmd_NMAC_Q(char *mac);
ATCMD_RESP_E AtCmd_WRXACTIVE(uint8_t n);
ATCMD_RESP_E AtCmd_WRXPS(uint8_t n);
ATCMD_RESP_E AtCmd_BDATA(uint8_t n);
ATCMD_RESP_E AtCmd_WREGDOMAIN_Q(ATCMD_REGDOMAIN_E *regDomain);
ATCMD_RESP_E AtCmd_WREGDOMAIN(ATCMD_REGDOMAIN_E regDomain);
ATCMD_RESP_E AtCmd_WM(ATCMD_MODE_E mode);
ATCMD_RESP_E AtCmd_WSEC(ATCMD_SECURITYMODE_E security);
ATCMD_RESP_E AtCmd_WPAPSK(char *pSsid, char *pPsk);
ATCMD_RESP_E AtCmd_WA(char *pSsid, char *pBssid, uint8_t channel);
ATCMD_RESP_E AtCmd_WWPS(uint8_t method, char *pin, AtCmd_WPSResult *result);
ATCMD_RESP_E AtCmd_WSTATUS(void);
ATCMD_RESP_E AtCmd_WD(void);
ATCMD_RESP_E AtCmd_NDHCP(uint8_t n);
ATCMD_RESP_E AtCmd_DHCPSRVR(uint8_t start);
ATCMD_RESP_E AtCmd_NSET(char *device, char *subnet, char *gateway);
ATCMD_RESP_E AtCmd_NSTAT(ATCMD_NetworkStatus *pStatus);
ATCMD_RESP_E AtCmd_NCTCP( char *destAddress, char *port, char *cid);
ATCMD_RESP_E AtCmd_NCUDP(char *destAddress, char *port, char *srcPort, uint8_t *cid );
ATCMD_RESP_E AtCmd_NSTCP(char *port, uint8_t *cid);
ATCMD_RESP_E AtCmd_NSUDP(char *port, uint8_t *cid);
ATCMD_RESP_E AtCmd_NCLOSE(uint8_t cid);
ATCMD_RESP_E AtCmd_NCLOSEALL(void);
ATCMD_RESP_E AtCmd_PSDPSLEEP(uint32_t timeout);
ATCMD_RESP_E AtCmd_PSSTBY(uint32_t x, uint32_t delay, uint8_t alarm1_pol, uint8_t alarm2_pol);
ATCMD_RESP_E AtCmd_STORENWCONN(void);
ATCMD_RESP_E AtCmd_RESTORENWCONN(void);
ATCMD_RESP_E AtCmd_SendCommand(char *command);
ATCMD_RESP_E AtCmd_checkResponse(const char *pBuffer);
ATCMD_RESP_E AtCmd_ParseRcvData(uint8_t *ptr);
ATCMD_RESP_E AtCmd_RecvResponse(void);
ATCMD_RESP_E AtCmd_SendBulkData(uint8_t cid, const void *txBuf, uint16_t dataLen);
ATCMD_RESP_E AtCmd_UDP_SendBulkData(uint8_t cid, const void *txBuf, uint16_t dataLen, const char *pUdpClientIP, uint16_t udpClientPort);
ATCMD_RESP_E AtCmd_APCLIENTINFO(void);

#endif /* _GS_ATCMD_H_ */


/*-------------------------------------------------------------------------*
 * End of File:  AtCmd.h
 *-------------------------------------------------------------------------*/
