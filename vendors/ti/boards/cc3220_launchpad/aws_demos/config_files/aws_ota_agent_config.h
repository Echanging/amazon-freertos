/*
 * Amazon FreeRTOS V1.4.8
 * Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/**
 * @file aws_ota_agent_config.h
 * @brief OTA user configurable settings.
 */

#ifndef _AWS_OTA_AGENT_CONFIG_H_
#define _AWS_OTA_AGENT_CONFIG_H_

/**
 * @brief The number of words allocated to the stack for the OTA agent.
 */
#define otaconfigSTACK_SIZE                     630U

/**
 * @brief Log base 2 of the size of the file data block message (excluding the header).
 *
 * 10 bits yields a data block size of 1KB.
 */
#define otaconfigLOG2_FILE_BLOCK_SIZE           10UL

/**
 * @brief Milliseconds to wait for the self test phase to succeed before we force reset.
 */
#define otaconfigSELF_TEST_RESPONSE_WAIT_MS     16000U

/**
 * @brief Milliseconds to wait before requesting data blocks from the OTA service if nothing is happening.
 *
 * The wait timer is reset whenever a data block is received from the OTA service so we will only send
 * the request message after being idle for this amount of time.
 */
#define otaconfigFILE_REQUEST_WAIT_MS           10000U

/**
 * @brief The OTA agent task priority. Normally it runs at a low priority.
 */
#define otaconfigAGENT_PRIORITY                 tskIDLE_PRIORITY

/**
 * @brief The maximum allowed length of the thing name used by the OTA agent.
 *
 * AWS IoT requires Thing names to be unique for each device that connects to the broker.
 * Likewise, the OTA agent requires the developer to construct and pass in the Thing name when
 * initializing the OTA agent. The agent uses this size to allocate static storage for the
 * Thing name used in all OTA base topics. Namely $aws/things/<thingName>
 */
#define otaconfigMAX_THINGNAME_LEN              64U

/**
 * @brief The maximum number of data blocks requested from OTA streaming service.
 *
 *  This configuration parameter is sent with data requests and represents the maximum number of
 *  data blocks the service will send in response. The maximum limit for this must be calculated
 *  from the maximum data response limit (128 KB from service) divided by the block size.
 *  For example if block size is set as 1 KB then the maximum number of data blocks that we can
 *  request is 128/1 = 128 blocks. Configure this parameter to this maximum limit or lower based on
 *  how many data blocks response is expected for each data requests.
 *  Please note that this must be set larger than zero.
 *
 */
#define otaconfigMAX_NUM_BLOCKS_REQUEST        8U

/**
 * @brief The maximum number of requests allowed to send without a response before we abort.
 *
 * This configuration parameter sets the maximum number of times the requests are made over
 * the selected communication channel before aborting and returning error.
 *
 */
#define otaconfigMAX_NUM_REQUEST_MOMENTUM       32U

/**
 * @brief The number of data buffers reserved by the OTA agent.
 *
 * This configurations parameter sets the maximum number of static data buffers used by
 * the OTA agent for job and file data blocks received.
 */
#define otaconfigMAX_NUM_OTA_DATA_BUFFERS       2U

/**
 * @brief The protocol selected for OTA control operations.

 * This configurations parameter sets the default protocol for all the OTA control
 * operations like requesting OTA job, updating the job status etc.
 *
 * Note - Only MQTT is supported at this time for control operations.
 */
#define configENABLED_CONTROL_PROTOCOL       ( OTA_CONTROL_OVER_MQTT )

/**
 * @brief The protocol selected for OTA data operations.

 * This configurations parameter sets the protocols selected for the data operations
 * like requesting file blocks from the service.
 *
 * Note - Both MQTT and HTTP is supported for data transfer. This configuration parameter
 * can be set to following -
 * Enable data over MQTT - ( OTA_DATA_OVER_MQTT )
 * Enable data over HTTP - ( OTA_DATA_OVER_HTTP)
 * Enable data over both MQTT & HTTP ( OTA_DATA_OVER_MQTT | OTA_DATA_OVER_HTTP )
 */
#define configENABLED_DATA_PROTOCOLS         ( OTA_DATA_OVER_MQTT )

 /**
  * @brief The preferred protocol selected for OTA data operations.
  *
  * Primary data protocol will be the protocol used for downloading file if more than
  * one protocol is selected while creating OTA job. Default primary data protocol is MQTT
  * and following update here to switch to HTTP as primary.
  *
  * Note - use OTA_DATA_OVER_HTTP for HTTP as primary data protocol.
  */

#define configOTA_PRIMARY_DATA_PROTOCOL     ( OTA_DATA_OVER_MQTT )

#endif /* _AWS_OTA_AGENT_CONFIG_H_ */
