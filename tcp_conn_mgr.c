/**
 ******************************************************************************
 * @file           : 
 * @brief          : 
 ******************************************************************************
 */

/* Private includes ----------------------------------------------------------*/
#include "tcp_conn_mgr.h"
#include "stdint.h"
#include "osapi.h"
#include "mem.h"
#include "debug.h"

#define MAX_CONN_NO 5 /*Maximum supported concurrent connection by esp*/

/* Private variables ---------------------------------------------------------*/
static uint8_t active_conn_count = 0;

/**
    *@brief 
    *@param void
    *@retval void
*/
struct espconn *TcpMgr_OpenConn(void)
{
    struct espconn *pConn = 0;

    if(active_conn_count < MAX_CONN_NO)
    {
        pConn = os_zalloc(sizeof(struct espconn));

        if(pConn != 0)
        {
            esp_tcp *pTcpInfo = os_zalloc(sizeof(esp_tcp));

            if(pTcpInfo != 0)
            {
                pConn->proto.tcp = pTcpInfo;
                pConn->type = ESPCONN_TCP;
                pConn->state = ESPCONN_NONE;

                active_conn_count++;
            }
            else
            {
                os_free(pConn);
                pConn = 0;
            }
            
        }
    }

    return pConn;
}

/**
    *@brief 
    *@param void
    *@retval void
*/
void TcpMgr_CloseConn(struct espconn * pConn)
{
    if(pConn)
    {
        os_free(pConn->proto.tcp);
    }
    os_free(pConn);

    if(active_conn_count > 0)
    {
        active_conn_count--;
    }
}