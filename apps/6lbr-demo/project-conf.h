/*
 * Copyright (c) 2013, CETIC.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/**
 * \file
 *         6LBR-Demo Project Configuration
 * \author
 *         6LBR Team <6lbr@cetic.be>
 */

#ifndef CETIC_6LBR_DEMO_PROJECT_CONF_H
#define CETIC_6LBR_DEMO_PROJECT_CONF_H

#define UIP_CONF_IPV6 1
#define UIP_CONF_IPV6_RPL 1
#define RPL_CONF_LEAF_ONLY 1 //rpl叶子节点
#define UIP_CONF_UDP 1
#define WITH_COAP 13
#define REST coap_rest_implementation
#define UIP_CONF_TCP 0
#define UIP_CONF_ICMP6 0
#define SICSLOWPAN_CONF_FRAG 1
#define UIP_CONF_IPV6_CHECKS 1
//#define NULLRDC_CONF_ACK_WAIT_TIME (RTIMER_SECOND / 100)
#define KEEP_RADIO_ON 1
//#define RFX2401C_ON 1
#define RPL_CONF_DAO_LATENCY 512 //dao回复时间范围,避免碰撞的机制
#define NBR_STALE_AFTER_NS 0 //当受到NS,把节点状态设置为STALE,这会导致下行数据包引发两次NS-NA
/*
 * csma重发时间1/NETSTACK_CONF_RDC_CHANNEL_CHECK_RATE,
 * rdc层contikimac也用到该值,在csma重发时间段内无限重发
 */
#define NETSTACK_CONF_RDC_CHANNEL_CHECK_RATE 8 

#define DEBUG_FLAG 0 /* debug flag */
#define STARTUP_CONF_VERBOSE 0
#undef CC2530_RF_CONF_CHANNEL
#define CC2530_RF_CONF_CHANNEL 26

#define IEEE802154_CONF_PANID 0xABCD
/*---------------------------------------------------------------------------*/
/* COAP                                                                      */
/*---------------------------------------------------------------------------*/
#define WITH_DTLS_COAP 0
#define COAP_SERVER_PORT 5683

//#define REST_TYPE_TEXT_PLAIN
//#define REST_TYPE_APPLICATION_XML
//#define REST_TYPE_APPLICATION_JSON

/* Chunk size == 128 is troublesome on Z1, maybe related to 6LoWPAN fragmentation */
/* Not sure why, set it to 64 */
#define REST_MAX_CHUNK_SIZE     64

/* Report LQI and RSSI only for parent node */
#define UDP_CLIENT_STORE_RADIO_INFO 1

#if !UIP_CONF_IPV6_RPL
#undef UIP_CONF_ROUTER
#define UIP_CONF_ROUTER            0
#endif

#undef QUEUEBUF_CONF_NUM
#define QUEUEBUF_CONF_NUM          4

#undef UIP_CONF_BUFFER_SIZE
#define UIP_CONF_BUFFER_SIZE    180

#undef UIP_CONF_RECEIVE_WINDOW
#define UIP_CONF_RECEIVE_WINDOW  60

/*---------------------------------------------------------------------------*/
/* WEBSERVER                                                                 */
/*---------------------------------------------------------------------------*/

#undef WEBSERVER_CONF_CFS_CONNS
#define WEBSERVER_CONF_CFS_CONNS 2

/* Reserve space for a file name (default is to not use file name) */
#undef WEBSERVER_CONF_CFS_PATHLEN
#define WEBSERVER_CONF_CFS_PATHLEN 80

/*---------------------------------------------------------------------------*/
/* RADIO                                                                     */
/*---------------------------------------------------------------------------*/

#undef NETSTACK_CONF_MAC
#define NETSTACK_CONF_MAC     		csma_driver

#undef NETSTACK_CONF_RDC
#define NETSTACK_CONF_RDC     		nullrdc_driver
//#define NETSTACK_CONF_RDC     contikimac_driver

#undef SKY_CONF_MAX_TX_POWER
#define SKY_CONF_MAX_TX_POWER 	31

#if CONTIKI_TARGET_ECONOTAG
#undef NULLRDC_CONF_802154_AUTOACK
#define NULLRDC_CONF_802154_AUTOACK_HW     1
#else
#undef NULLRDC_CONF_802154_AUTOACK
#define NULLRDC_CONF_802154_AUTOACK	1
#endif

/*---------------------------------------------------------------------------*/
/* RPL & Network                                                             */
/*---------------------------------------------------------------------------*/

#undef RPL_CONF_INIT_LINK_METRIC
#define RPL_CONF_INIT_LINK_METRIC			3

#define RPL_MAX_DAG_PER_INSTANCE	2
#define RPL_MAX_INSTANCES		1

/* Z1 platform has limited RAM */
#if defined CONTIKI_TARGET_Z1

#define RPL_CONF_MAX_PARENTS_PER_DAG    12
#define NEIGHBOR_CONF_MAX_NEIGHBORS     12

#undef UIP_CONF_DS6_NBR_NBU
#define UIP_CONF_DS6_NBR_NBU     12

//Deprecated, for old DS6 Route API, use UIP_CONF_MAX_ROUTES instead
#undef UIP_CONF_DS6_ROUTE_NBU
#define UIP_CONF_DS6_ROUTE_NBU   12

#undef UIP_CONF_MAX_ROUTES
#define UIP_CONF_MAX_ROUTES   12

#else

#define RPL_CONF_MAX_PARENTS_PER_DAG    24 //代码中没使用
#define NEIGHBOR_CONF_MAX_NEIGHBORS     24 //代码中不再使用,代替它的是NBR_TABLE_CONF_MAX_NEIGHBORS

#undef NBR_TABLE_CONF_MAX_NEIGHBORS
#define NBR_TABLE_CONF_MAX_NEIGHBORS    4 /* 最大邻居个数 */

#undef UIP_CONF_DS6_NBR_NBU
#define UIP_CONF_DS6_NBR_NBU     24 //代码中没有使用

//Deprecated, for old DS6 Route API, use UIP_CONF_MAX_ROUTES instead
#undef UIP_CONF_DS6_ROUTE_NBU
#define UIP_CONF_DS6_ROUTE_NBU   24

#undef UIP_CONF_MAX_ROUTES
#define UIP_CONF_MAX_ROUTES   1 //最大路由个数,叶子节点路由个数可以为0,但是数组大小不能为0

#undef UIP_CONF_ND6_SEND_NA
#define UIP_CONF_ND6_SEND_NA   1

#endif

/*---------------------------------------------------------------------------*/
/* Init                                                                      */
/*---------------------------------------------------------------------------*/
#define UIP_DS6_CONF_NO_STATIC_ADDRESS 1

#endif /* CETIC_6LBR_DEMO_PROJECT_CONF_H */
