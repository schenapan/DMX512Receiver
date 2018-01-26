/*******************************************************************************
*                                                                              *
*                         File to be included                                  *
*                                                                              *
*******************************************************************************/

// Include micro abstraction layer
#include "Mic/mic_micro.h"

// Include driver
#include "Drv/drv_event.h"
#include "Drv/drv_em260.h"
#include "Drv/drv_led.h"

// Include cluster

// Include service
#include "srv_zb_mfg.h"

// Include application
#include "app_product_hardware.h"

/*******************************************************************************
*                                                                              *
*                         constantes declaration                               *
*                                                                              *
*******************************************************************************/

// version du protocole EZSP compatible avec le module
// in ".h" file cause used in app_man_test.c"
// 0U for
// 1U for stack 3.3.1
// 2U for stack 3.3.3
// 3U for stack 3.5.1
// 4U for stack 4.2.0
#define ZIGBEE_PROTOCOL_VERSION_2                  2U
#define ZIGBEE_PROTOCOL_VERSION_4                  4U

//------------------------------------------------------------------------------
// Frame IDs

enum
{
  // Configuration Frames
  EZSP_VERSION                                  = 0x00U,
  EZSP_GET_CONFIGURATION_VALUE                  = 0x52U,
  EZSP_SET_CONFIGURATION_VALUE                  = 0x53U,
  EZSP_ADD_ENDPOINT                             = 0x02U,
  EZSP_SET_POLICY                               = 0x55U,
  EZSP_GET_POLICY                               = 0x56U,
  EZSP_GET_VALUE                                = 0xAAU,
  EZSP_SET_VALUE                                = 0xABU,

// Utilities Frames
  EZSP_NOP                                      = 0x05U,
  EZSP_ECHO                                     = 0x81U,
  EZSP_INVALID_COMMAND                          = 0x58U,
  EZSP_CALLBACK                                 = 0x06U,
  EZSP_NO_CALLBACKS                             = 0x07U,
  EZSP_SET_TOKEN                                = 0x09U,
  EZSP_GET_TOKEN                                = 0x0AU,
  EZSP_GET_MFG_TOKEN                            = 0x0BU,
  EZSP_SET_RAM                                  = 0x46U,
  EZSP_GET_RAM                                  = 0x47U,
  EZSP_GET_RANDOM_NUMBER                        = 0x49U,
  EZSP_GET_MILLISECOND_TIME                     = 0x0DU,
  EZSP_SET_TIMER                                = 0x0EU,
  EZSP_GET_TIMER                                = 0x4EU,
  EZSP_TIMER_HANDLER                            = 0x0FU,
  EZSP_SERIAL_WRITE                             = 0x10U,
  EZSP_SERIAL_READ                              = 0x11U,
  EZSP_DEBUG_WRITE                              = 0x12U,
  EZSP_DEBUG_HANDLER                            = 0x13U,
  EZSP_READ_AND_CLEAR_COUNTERS                  = 0x65U,
  EZSP_DELAY_TEST                               = 0x9DU,

// Networking Frames
  EZSP_SET_MANUFACTURER_CODE                    = 0x15U,
  EZSP_SET_POWER_DESCRIPTOR                     = 0x16U,
  EZSP_NETWORK_INIT                             = 0x17U,
  EZSP_NETWORK_STATE                            = 0x18U,
  EZSP_STACK_STATUS_HANDLER                     = 0x19U,
  EZSP_START_SCAN                               = 0x1AU,
  EZSP_ENERGY_SCAN_RESULT_HANDLER               = 0x48U,
  EZSP_NETWORK_FOUND_HANDLER                    = 0x1BU,
  EZSP_SCAN_COMPLETE_HANDLER                    = 0x1CU,
  EZSP_STOP_SCAN                                = 0x1DU,
  EZSP_FORM_NETWORK                             = 0x1EU,
  EZSP_JOIN_NETWORK                             = 0x1FU,
  EZSP_SCAN_AND_FORM_NETWORK                    = 0x4FU,
  EZSP_SCAN_AND_JOIN_NETWORK                    = 0x50U,
  EZSP_SCAN_ERROR_HANDLER                       = 0x51U,
  EZSP_SCAN_FOR_JOINABLE_NETWORK                = 0xA8U,
  EZSP_UNUSED_PAN_ID_FOUND_HANDLER              = 0xA9U,
  EZSP_LEAVE_NETWORK                            = 0x20U,
  EZSP_FIND_AND_REJOIN_NETWORK                  = 0x21U,
  EZSP_PERMIT_JOINING                           = 0x22U,
  EZSP_CHILD_JOIN_HANDLER                       = 0x23U,
  EZSP_ENERGY_SCAN_REQUEST                      = 0x9CU,
  EZSP_GET_EUI64                                = 0x26U,
  EZSP_GET_NODE_ID                              = 0x27U,
  EZSP_GET_NETWORK_PARAMETERS                   = 0x28U,
  EZSP_GET_PARENT_CHILD_PARAMETERS              = 0x29U,
  EZSP_GET_CHILD_DATA                           = 0x4AU,
  EZSP_GET_NEIGHBOR                             = 0x79U,
  EZSP_NEIGHBOR_COUNT                           = 0x7AU,
  EZSP_GET_ROUTE_TABLE_ENTRY                    = 0x7BU,
  EZSP_SET_RADIO_POWER                          = 0x99U,
  EZSP_SET_RADIO_CHANNEL                        = 0x9AU,

// Binding Frames
  EZSP_CLEAR_BINDING_TABLE                      = 0x2AU,
  EZSP_SET_BINDING                              = 0x2BU,
  EZSP_GET_BINDING                              = 0x2CU,
  EZSP_DELETE_BINDING                           = 0x2DU,
  EZSP_BINDING_IS_ACTIVE                        = 0x2EU,
  EZSP_GET_BINDING_REMOTE_NODE_ID               = 0x2FU,
  EZSP_SET_BINDING_REMOTE_NODE_ID               = 0x30U,
  EZSP_REMOTE_SET_BINDING_HANDLER               = 0x31U,
  EZSP_REMOTE_DELETE_BINDING_HANDLER            = 0x32U,

// Messaging Frames
  EZSP_MAXIMUM_PAYLOAD_LENGTH                   = 0x33U,
  EZSP_SEND_UNICAST                             = 0x34U,
  EZSP_SEND_BROADCAST                           = 0x36U,
  EZSP_SEND_MULTICAST                           = 0x38U,
  EZSP_SEND_REPLY                               = 0x39U,
  EZSP_MESSAGE_SENT_HANDLER                     = 0x3FU,
  EZSP_SEND_MANY_TO_ONE_ROUTE_REQUEST           = 0x41U,
  EZSP_POLL_FOR_DATA                            = 0x42U,
  EZSP_POLL_COMPLETE_HANDLER                    = 0x43U,
  EZSP_POLL_HANDLER                             = 0x44U,
  EZSP_INCOMING_SENDER_EUI64_HANDLER            = 0x62U,
  EZSP_INCOMING_MESSAGE_HANDLER                 = 0x45U,
  EZSP_INCOMING_ROUTE_RECORD_HANDLER            = 0x59U,
  EZSP_SET_SOURCE_ROUTE                         = 0x5AU,
  EZSP_INCOMING_MANY_TO_ONE_ROUTE_REQUEST_HANDLER = 0x7DU,
  EZSP_INCOMING_ROUTE_ERROR_HANDLER             = 0x80U,
  EZSP_ADDRESS_TABLE_ENTRY_IS_ACTIVE            = 0x5BU,
  EZSP_SET_ADDRESS_TABLE_REMOTE_EUI64           = 0x5CU,
  EZSP_SET_ADDRESS_TABLE_REMOTE_NODE_ID         = 0x5DU,
  EZSP_GET_ADDRESS_TABLE_REMOTE_EUI64           = 0x5EU,
  EZSP_GET_ADDRESS_TABLE_REMOTE_NODE_ID         = 0x5FU,
  EZSP_SET_EXTENDED_TIMEOUT                     = 0x7EU,
  EZSP_GET_EXTENDED_TIMEOUT                     = 0x7FU,
  EZSP_REPLACE_ADDRESS_TABLE_ENTRY              = 0x82U,
  EZSP_LOOKUP_NODE_ID_BY_EUI64                  = 0x60U,
  EZSP_LOOKUP_EUI64_BY_NODE_ID                  = 0x61U,
  EZSP_GET_MULTICAST_TABLE_ENTRY                = 0x63U,
  EZSP_SET_MULTICAST_TABLE_ENTRY                = 0x64U,
  EZSP_ID_CONFLICT_HANDLER                      = 0x7CU,
  EZSP_SEND_RAW_MESSAGE                         = 0x96U,
  EZSP_MAC_PASSTHROUGH_MESSAGE_HANDLER          = 0x97U,
  EZSP_RAW_TRANSMIT_COMPLETE_HANDLER            = 0x98U,

// Security Frames
  EZSP_SET_INITIAL_SECURITY_STATE               = 0x68U,
  EZSP_GET_CURRENT_SECURITY_STATE               = 0x69U,
  EZSP_GET_KEY                                  = 0x6aU,
  EZSP_SWITCH_NETWORK_KEY_HANDLER               = 0x6eU,
  EZSP_GET_KEY_TABLE_ENTRY                      = 0x71U,
  EZSP_SET_KEY_TABLE_ENTRY                      = 0x72U,
  EZSP_FIND_KEY_TABLE_ENTRY                     = 0x75U,
  EZSP_ADD_OR_UPDATE_KEY_TABLE_ENTRY            = 0x66U,
  EZSP_ERASE_KEY_TABLE_ENTRY                    = 0x76U,
  EZSP_REQUEST_LINK_KEY                         = 0x14U,
  EZSP_ZIGBEE_KEY_ESTABLISHMENT_HANDLER         = 0x9BU,

// Trust Center Frames
  EZSP_TRUST_CENTER_JOIN_HANDLER                = 0x24U,
  EZSP_BROADCAST_NEXT_NETWORK_KEY               = 0x73U,
  EZSP_BROADCAST_NETWORK_KEY_SWITCH             = 0x74U,
  EZSP_BECOME_TRUST_CENTER                      = 0x77U,

// Certificate Based Key Exchange (CBKE)
  EZSP_GENERATE_CBKE_KEYS                       = 0xA4U,
  EZSP_GENERATE_CBKE_KEYS_HANDLER               = 0x9EU,
  EZSP_CALCULATE_SMACS                          = 0x9FU,
  EZSP_CALCULATE_SMACS_HANDLER                  = 0xA0U,
  EZSP_CLEAR_TEMPORARY_DATA_MAYBE_STORE_LINK_KEY = 0xA1U,
  EZSP_GET_CERTIFICATE                          = 0xA5U,
  EZSP_DSA_SIGN                                 = 0xA6U,
  EZSP_DSA_SIGN_HANDLER                         = 0xA7U,

// Mfglib
  EZSP_MFGLIB_START                             = 0x83U,
  EZSP_MFGLIB_END                               = 0x84U,
  EZSP_MFGLIB_START_TONE                        = 0x85U,
  EZSP_MFGLIB_STOP_TONE                         = 0x86U,
  EZSP_MFGLIB_START_STREAM                      = 0x87U,
  EZSP_MFGLIB_STOP_STREAM                       = 0x88U,
  EZSP_MFGLIB_SEND_PACKET                       = 0x89U,
  EZSP_MFGLIB_SET_CHANNEL                       = 0x8AU,
  EZSP_MFGLIB_GET_CHANNEL                       = 0x8BU,
  EZSP_MFGLIB_SET_POWER                         = 0x8CU,
  EZSP_MFGLIB_GET_POWER                         = 0x8DU,
  EZSP_MFGLIB_RX_HANDLER                        = 0x8EU,

// Bootloader
  EZSP_LAUNCH_STANDALONE_BOOTLOADER             = 0x8fU,
  EZSP_SEND_BOOTLOAD_MESSAGE                    = 0x90U,
  EZSP_GET_STANDALONE_BOOTLOADER_VERSION_PLAT_MICRO_PHY = 0x91U,
  EZSP_INCOMING_BOOTLOAD_MESSAGE_HANDLER        = 0x92U,
  EZSP_BOOTLOAD_TRANSMIT_COMPLETE_HANDLER       = 0x93U,
  EZSP_AES_ENCRYPT                              = 0x94U,
  EZSP_OVERRIDE_CURRENT_CHANNEL                 = 0x95U,

 // patch pour la version 1.8, retire les retry lors de l'envoi du broadcast
  EZSP_SEND_BROADCAST_PATCH                     = 0x40U
};

//------------------------------------------------------------------------------
typedef enum {
  // Success.
  EZSP_SUCCESS                                  = 0x00U,
  // Fatal error.
  EZSP_SPI_ERR_FATAL                            = 0x10U,
  // The Response frame of the current transaction indicates the EM260 has
  // reset.
  EZSP_SPI_ERR_EM260_RESET                      = 0x11U,
  // The EM260 is reporting that the Command frame of the current transaction is
  // oversized (the length byte is too large).
  EZSP_SPI_ERR_OVERSIZED_EZSP_FRAME             = 0x12U,
  // The Response frame of the current transaction indicates the previous
  // transaction was aborted (nSSEL deasserted too soon).
  EZSP_SPI_ERR_ABORTED_TRANSACTION              = 0x13U,
  // The Response frame of the current transaction indicates the frame
  // terminator is missing from the Command frame.
  EZSP_SPI_ERR_MISSING_FRAME_TERMINATOR         = 0x14U,
  // The EM260 has not provided a Response within the time limit defined by
  // WAIT_SECTION_TIMEOUT.
  EZSP_SPI_ERR_WAIT_SECTION_TIMEOUT             = 0x15U,
  // The Response frame from the EM260 is missing the frame terminator.
  EZSP_SPI_ERR_NO_FRAME_TERMINATOR              = 0x16U,
  // The Host attempted to send an oversized Command (the length byte is too
  // large) and the AVR's spi-protocol.c blocked the transmission.
  EZSP_SPI_ERR_EZSP_COMMAND_OVERSIZED           = 0x17U,
  // The EM260 attempted to send an oversized Response (the length byte is too
  // large) and the AVR's spi-protocol.c blocked the reception.
  EZSP_SPI_ERR_EZSP_RESPONSE_OVERSIZED          = 0x18U,
  // The Host has sent the Command and is still waiting for the EM260 to send a
  // Response.
  EZSP_SPI_WAITING_FOR_RESPONSE                 = 0x19U,
  // The EM260 has not asserted nHOST_INT within the time limit defined by
  // WAKE_HANDSHAKE_TIMEOUT.
  EZSP_SPI_ERR_HANDSHAKE_TIMEOUT                = 0x1AU,
  // The EM260 has not asserted nHOST_INT after an EM260 reset within the time
  // limit defined by STARTUP_TIMEOUT.
  EZSP_SPI_ERR_STARTUP_TIMEOUT                  = 0x1BU,
  // The Host attempted to verify the SPI Protocol activity and version numberU,
  // and the verification failed.
  EZSP_SPI_ERR_STARTUP_FAIL                     = 0x1CU,
  // The Host has sent a command with a SPI Byte that is unsupported by the
  // current mode the EM260 is operating in.
  EZSP_SPI_ERR_UNSUPPORTED_SPI_COMMAND          = 0x1DU,
  // Operation not yet complete.
  EZSP_ASH_IN_PROGRESS                          = 0x20U,
  // Fatal error detected by host.
  EZSP_ASH_HOST_FATAL_ERROR                     = 0x21U,
  // Fatal error detected by NCP.
  EZSP_ASH_NCP_FATAL_ERROR                      = 0x22U,
  // Tried to send DATA frame too long.
  EZSP_ASH_DATA_FRAME_TOO_LONG                  = 0x23U,
  // Tried to send DATA frame too short.
  EZSP_ASH_DATA_FRAME_TOO_SHORT                 = 0x24U,
  // No space for tx'ed DATA frame.
  EZSP_ASH_NO_TX_SPACE                          = 0x25U,
  // No space for rec'd DATA frame.
  EZSP_ASH_NO_RX_SPACE                          = 0x26U,
  // No receive data available.
  EZSP_ASH_NO_RX_DATA                           = 0x27U,
  // Not in Connected state.
  EZSP_ASH_NOT_CONNECTED                        = 0x28U,
  // The EM260 received a command before the EZSP version had been set.
  EZSP_ERROR_VERSION_NOT_SET                    = 0x30U,
  // The EM260 received a command containing an unsupported frame ID.
  EZSP_ERROR_INVALID_FRAME_ID                   = 0x31U,
  // The direction flag in the frame control field was incorrect.
  EZSP_ERROR_WRONG_DIRECTION                    = 0x32U,
  // The truncated flag in the frame control field was set, indicating there was
  // not enough memory available to complete the response or that the response
  // would have exceeded the maximum EZSP frame length.
  EZSP_ERROR_TRUNCATED                          = 0x33U,
  // The overflow flag in the frame control field was set, indicating one or
  // more callbacks occurred since the previous response and there was not
  // enough memory available to report them to the Host.
  EZSP_ERROR_OVERFLOW                           = 0x34U,
  // Insufficient memory was available.
  EZSP_ERROR_OUT_OF_MEMORY                      = 0x35U,
  // The value was out of bounds.
  EZSP_ERROR_INVALID_VALUE                      = 0x36U,
  // The configuration id was not recognized.
  EZSP_ERROR_INVALID_ID                         = 0x37U,
  // Configuration values can no longer be modified.
  EZSP_ERROR_INVALID_CALL                       = 0x38U,
  // The EM260 failed to respond to a command.
  EZSP_ERROR_NO_RESPONSE                        = 0x39U,
  // The length of the command exceeded the maximum EZSP frame length.
  EZSP_ERROR_COMMAND_TOO_LONG                   = 0x40U,
  // The UART receive queue was full causing a callback response to be dropped.
  EZSP_ERROR_QUEUE_FULL                         = 0x41U,
  // Incompatible ASH version
  EZSP_ASH_ERROR_VERSION                        = 0x50U,
  // Exceeded max ACK timeouts
  EZSP_ASH_ERROR_TIMEOUTS                       = 0x51U,
  // Timed out waiting for RSTACK
  EZSP_ASH_ERROR_RESET_FAIL                     = 0x52U,
  // Unexpected ncp reset
  EZSP_ASH_ERROR_NCP_RESET                      = 0x53U,
  // Serial port initialization failed
  EZSP_ASH_ERROR_SERIAL_INIT                    = 0x54U,
  // Invalid ncp processor type
  EZSP_ASH_ERROR_NCP_TYPE                       = 0x55U,
  // Invalid ncp reset method
  EZSP_ASH_ERROR_RESET_METHOD                   = 0x56U,
  // XON/XOFF not supported by host driver
  EZSP_ASH_ERROR_XON_XOFF                       = 0x57U,
  // ASH protocol started
  EZSP_ASH_STARTED                              = 0x70U,
  // ASH protocol connected
  EZSP_ASH_CONNECTED                            = 0x71U,
  // ASH protocol disconnected
  EZSP_ASH_DISCONNECTED                         = 0x72U,
  // Timer expired waiting for ack
  EZSP_ASH_ACK_TIMEOUT                          = 0x73U,
  // Frame in progress cancelled
  EZSP_ASH_CANCELLED                            = 0x74U,
  // Received frame out of sequence
  EZSP_ASH_OUT_OF_SEQUENCE                      = 0x75U,
  // Received frame with CRC error
  EZSP_ASH_BAD_CRC                              = 0x76U,
  // Received frame with comm error
  EZSP_ASH_COMM_ERROR                           = 0x77U,
  // Received frame with bad ackNum
  EZSP_ASH_BAD_ACKNUM                           = 0x78U,
  // Received frame shorter than minimum
  EZSP_ASH_TOO_SHORT                            = 0x79U,
  // Received frame longer than maximum
  EZSP_ASH_TOO_LONG                             = 0x7AU,
  // Received frame with illegal control byte
  EZSP_ASH_BAD_CONTROL                          = 0x7BU,
  // Received frame with illegal length for its type
  EZSP_ASH_BAD_LENGTH                           = 0x7CU,
  // No reset or error
  EZSP_ASH_NO_ERROR                             = 0xFFU
}EEzspStatus;

//------------------------------------------------------------------------------
// Identifies a configuration value.
enum {
  // The number of packet buffers available to the stack.
  EZSP_CONFIG_PACKET_BUFFER_COUNT               = 0x01U,
  // The maximum number of router neighbors the stack can keep track of. A
  // neighbor is a node within radio range.
  EZSP_CONFIG_NEIGHBOR_TABLE_SIZE               = 0x02U,
  // The maximum number of APS retried messages the stack can be transmitting at
  // any time.
  EZSP_CONFIG_APS_UNICAST_MESSAGE_COUNT         = 0x03U,
  // The maximum number of non-volatile bindings supported by the stack.
  EZSP_CONFIG_BINDING_TABLE_SIZE                = 0x04U,
  // The maximum number of EUI64 to network address associations that the stack
  // can maintain.
  EZSP_CONFIG_ADDRESS_TABLE_SIZE                = 0x05U,
  // The maximum number of multicast groups that the device may be a member of.
  EZSP_CONFIG_MULTICAST_TABLE_SIZE              = 0x06U,
  // The maximum number of destinations to which a node can route messages. This
  // includes both messages originating at this node and those relayed for
  // others.
  EZSP_CONFIG_ROUTE_TABLE_SIZE                  = 0x07U,
  // The number of simultaneous route discoveries that a node will support.
  EZSP_CONFIG_DISCOVERY_TABLE_SIZE              = 0x08U,
  // The size of the alarm broadcast buffer.
  EZSP_CONFIG_BROADCAST_ALARM_DATA_SIZE         = 0x09U,
  // The size of the unicast alarm buffers allocated for end device children.
  EZSP_CONFIG_UNICAST_ALARM_DATA_SIZE           = 0x0AU,
  // Specifies the stack profile.
  EZSP_CONFIG_STACK_PROFILE                     = 0x0CU,
  // The security level used for security at the MAC and network layers. The
  // supported values are 0 (no security) and 5 (payload is encrypted and a
  // four-byte MIC is used for authentication).
  EZSP_CONFIG_SECURITY_LEVEL                    = 0x0DU,
  // The maximum number of hops for a message.
  EZSP_CONFIG_MAX_HOPS                          = 0x10U,
  // The maximum number of end device children that a router will support.
  EZSP_CONFIG_MAX_END_DEVICE_CHILDREN           = 0x11U,
  // The maximum amount of time that the MAC will hold a message for indirect
  // transmission to a child.
  EZSP_CONFIG_INDIRECT_TRANSMISSION_TIMEOUT     = 0x12U,
  // The maximum amount of time that an end device child can wait between polls.
  // If no poll is heard within this timeout, then the parent removes the end
  // device from its tables.
  EZSP_CONFIG_END_DEVICE_POLL_TIMEOUT           = 0x13U,
  // The maximum amount of time that a mobile node can wait between polls. If no
  // poll is heard within this timeout, then the parent removes the mobile node
  // from its tables.
  EZSP_CONFIG_MOBILE_NODE_POLL_TIMEOUT          = 0x14U,
  // The number of child table entries reserved for use only by mobile nodes.
  EZSP_CONFIG_RESERVED_MOBILE_CHILD_ENTRIES     = 0x15U,
  // The amount of RAM available for use by the Host.
  //EZSP_CONFIG_HOST_RAM                          = 0x16U, // remove in stack 4.2.0
  // Enables boost power mode and/or the alternate transmitter output.
  EZSP_CONFIG_TX_POWER_MODE                     = 0x17U,
  // 0: Allow this node to relay messages. 1: Prevent this node from relaying
  // messages.
  EZSP_CONFIG_DISABLE_RELAY                     = 0x18U,
  // The maximum number of EUI64 to network address associations that the Trust
  // Center can maintain.
  EZSP_CONFIG_TRUST_CENTER_ADDRESS_CACHE_SIZE   = 0x19U,
  // The size of the source route table.
  EZSP_CONFIG_SOURCE_ROUTE_TABLE_SIZE           = 0x1AU,
  // The units used for timing out end devices on their parents.
  EZSP_CONFIG_END_DEVICE_POLL_TIMEOUT_SHIFT     = 0x1BU,
  // The number of blocks of a fragmented message that can be sent in a single
  // window.
  EZSP_CONFIG_FRAGMENT_WINDOW_SIZE              = 0x1CU,
  // The time the stack will wait (in milliseconds) between sending blocks of a
  // fragmented message.
  EZSP_CONFIG_FRAGMENT_DELAY_MS                 = 0x1DU,
  // The size of the Key Table used for storing individual link keys (if the
  // device is a Trust Center) or Application Link Keys (if the device is a
  // normal node).
  EZSP_CONFIG_KEY_TABLE_SIZE                    = 0x1EU,
  // The APS ACK timeout value. The stack waits this amount of time between
  // resends of APS retried messages.
  EZSP_CONFIG_APS_ACK_TIMEOUT                   = 0x1FU,
  // The duration of an active scan, in the units used by the 15.4 scan
  // parameter (((1 << duration) + 1) * 15ms). This also controls the jitter
  // used when responding to a beacon request.
  EZSP_CONFIG_ACTIVE_SCAN_DURATION              = 0x20U
};

// nombre d'élément de la stack a configurer
#define EZSP_NB_CONF_ID 28U // 29U -> remove one in stack 4.2.0

//------------------------------------------------------------------------------
// Manufacturing token IDs used by ezspGetMfgToken().
enum {
  // Custom version (2 bytes).
  EZSP_MFG_CUSTOM_VERSION                       = 0x00U,
  // Manufacturing string (16 bytes).
  EZSP_MFG_STRING                               = 0x01U,
  // Board name (16 bytes).
  EZSP_MFG_BOARD_NAME                           = 0x02U,
  // Manufacturing ID (2 bytes).
  EZSP_MFG_MANUF_ID                             = 0x03U,
  // Radio configuration (2 bytes).
  EZSP_MFG_PHY_CONFIG                           = 0x04U,
  // Bootload AES key (16 bytes).
  EZSP_MFG_BOOTLOAD_AES_KEY                     = 0x05U,
  // ASH configuration (40 bytes).
  EZSP_MFG_ASH_CONFIG                           = 0x06U,
  // EZSP storage (8 bytes).
  EZSP_MFG_EZSP_STORAGE                         = 0x07U,
  // Radio calibration data (64 bytes). 4 bytes (VCO at LNA, mod DAC, filter,
  // LNA) are stored for each of the 16 channels. This token is not stored in
  // the Flash Information Area. It is updated by the stack each time a
  // calibration is performed.
  EZSP_STACK_CAL_DATA                           = 0x08U
};
typedef Int8U EzspMfgTokenId;


/*******************************************************************************
*                                                                              *
*                         private type declaration                             *
*                                                                              *
*******************************************************************************/

typedef struct
{
	Int8U sequence_number;
	Int8U frame_control;
	Int8U frame_id;
} SEzspResponseHeader;

typedef struct
{
  SEzspResponseHeader head;
  Int8U   protocol_version;
  Int8U   stack_type;
  Int16U  stack_version;
} SEzspGetVersionResponse;

typedef struct
{
  SEzspResponseHeader head;
  EEzspStatus   status;
} SEzspStatusResponse;


typedef struct SSEzspConfValue
{
  Int8U   id;
  Int16U  value;
} SEzspConfValue;

typedef struct
{
  SEzspResponseHeader head;
  EEmberStatus   status;
} SEmberStatusResponse;

typedef struct
{
  SEzspResponseHeader header;
  Int8U power;      // The current power
} SEzspGetMfgPowerResponse;

typedef struct
{
  SEzspResponseHeader header;
  Int8U channel;      // The current channel
} SEzspGetMfgChannelResponse;

typedef struct
{
  SEzspResponseHeader header;
  // The length of the tokenData parameter in bytes.
  Int8U token_data_length;
  // The manufacturing token data
  Int8U *token_data;
} SEzspGetMfgTokenResponse;

typedef struct SSEzspGetEUI64Response
{
  SEzspResponseHeader head;
  Int8U eui64[SIZE_OF_MISC_IEEE];
}SEzspGetEUI64Response;

/*******************************************************************************
*                                                                              *
*                             Private  data types                              *
*                                                                              *
*******************************************************************************/

// configuration de la stack
static __CODE_MEMORY const SEzspConfValue ezsp_ini_conf_min_value[EZSP_NB_CONF_ID] =
{
  { EZSP_CONFIG_PACKET_BUFFER_COUNT,              30U   },  // ember : 24U
  { EZSP_CONFIG_NEIGHBOR_TABLE_SIZE,              8U    },
  { EZSP_CONFIG_APS_UNICAST_MESSAGE_COUNT,        20U   },  // ember : 10U
  { EZSP_CONFIG_BINDING_TABLE_SIZE,               0U    },
  { EZSP_CONFIG_ADDRESS_TABLE_SIZE,               0U    },  // ember : 8U
  { EZSP_CONFIG_MULTICAST_TABLE_SIZE,             0U    },  // ember : 8U
  { EZSP_CONFIG_ROUTE_TABLE_SIZE,                 0U    },  // ember : 16U
  { EZSP_CONFIG_DISCOVERY_TABLE_SIZE,             0U    },  // ember : 8U
  { EZSP_CONFIG_BROADCAST_ALARM_DATA_SIZE,        0U    },
  { EZSP_CONFIG_UNICAST_ALARM_DATA_SIZE,          0U    },
  { EZSP_CONFIG_STACK_PROFILE,                    2U    },
  { EZSP_CONFIG_SECURITY_LEVEL,                   5U    },
  { EZSP_CONFIG_MAX_HOPS,                         0U    },  // (B)
  { EZSP_CONFIG_MAX_END_DEVICE_CHILDREN,          0U    },  // ember : 6U
  { EZSP_CONFIG_INDIRECT_TRANSMISSION_TIMEOUT,    0U    },  // ember : 3000U
  { EZSP_CONFIG_END_DEVICE_POLL_TIMEOUT,          0U    },  // ember : 5U
  { EZSP_CONFIG_MOBILE_NODE_POLL_TIMEOUT,         0U    },
  { EZSP_CONFIG_RESERVED_MOBILE_CHILD_ENTRIES,    0U    },
  //{ EZSP_CONFIG_HOST_RAM,                         0U    },
  { EZSP_CONFIG_TX_POWER_MODE,                    0U    },
  { EZSP_CONFIG_DISABLE_RELAY,                    0U    },  // 0 = relay message - 1 = prevent from relaying
  { EZSP_CONFIG_TRUST_CENTER_ADDRESS_CACHE_SIZE,  0U    },
  { EZSP_CONFIG_SOURCE_ROUTE_TABLE_SIZE,          0U    },
  { EZSP_CONFIG_END_DEVICE_POLL_TIMEOUT_SHIFT,    0U    },  // ember : 6U
  { EZSP_CONFIG_FRAGMENT_WINDOW_SIZE,             0U    },
  { EZSP_CONFIG_FRAGMENT_DELAY_MS,                0U    },
  { EZSP_CONFIG_KEY_TABLE_SIZE,                   0U    },
  { EZSP_CONFIG_APS_ACK_TIMEOUT,                  0U    }, // 50*(B)+100
  { EZSP_CONFIG_ACTIVE_SCAN_DURATION,             0U    }
};

struct
{
  void (*rx_callback)( Int8U *packet, Int8U linkQuality, Int8S rssi);
  
  // ieee du noeud, sauvegarde locale
  Int8U eui64[SIZE_OF_MISC_IEEE];  
}srv_zb_mfg;

/*******************************************************************************
*                                                                              *
*                         Private Macros of the module                         *
*                                                                              *
*******************************************************************************/

/*******************************************************************************
*                                                                              *
*                  Private Functions of the Module                             *
*                                                                              *
*******************************************************************************/

/**
*  \brief ZigBee Configuration frame : Get EZSP protocol version
*
*  \param[IN] wanted_version : version de protocol attendu
*
*  \return SEzspGetVersionResponse : pointeur vers la structure de réponse
*/
static SEzspGetVersionResponse *srvZbMfgCfgVersion( Int8U wanted_version );

/**
*  \brief ZigBee Configuration frame Set Stack Configuration Value
*
*  \param[IN] config_id : identifier de configuration a modifier
*  \param[IN] value : valeur a affecter
*
*  \return SEzspStatusResponse : pointeur vers la structure de réponse
*/
static SEzspStatusResponse *srvZbMfgCfgSetConfigurationValue(Int8U config_id,
                                                          Int16U value );

/**
* \brief ZigBee Networking frame lit l'adresse IEEE du noeud
*
* \return pointeur sur l'ieee, NUL en cas d'erreur
*/
static Int8U *srvZbMfgGetInternalEUI64( void );

/*******************************************************************************
*                                                                              *
*                  Public Functions of the Module                              *
*                                                                              *
*******************************************************************************/

/**
* \brief fonction d'initialisation
*
* \return FALSE si le traitement a genere une erreur
*/
Boolean srvZbMfgInit( void )
{
  Boolean out_value;
  
  // initialise variable locale
  srv_zb_mfg.rx_callback = NUL;
  
  // initialisation du driver
  out_value = drvEm260Init();
  if ( out_value == TRUE )
  {
    // test de la version de protocol ezsp utilisé
    SEzspGetVersionResponse *p_version;
  
    p_version = srvZbMfgCfgVersion( 0/*ZIGBEE_PROTOCOL_VERSION_2*/ );
    if ( (p_version != NUL) /*&&
         ( // liste des protocol supporté par l'appli
           (p_version->protocol_version == ZIGBEE_PROTOCOL_VERSION_2) ||
           (p_version->protocol_version == ZIGBEE_PROTOCOL_VERSION_4)
         )*/
       )
    {
      Int8U loop;
      SEzspStatusResponse *prep;
  
      // mise a jour du protocol version utilisé
	  
	  if( 0 != p_version->protocol_version )
	  {
		p_version = srvZbMfgCfgVersion( p_version->protocol_version );
	  }
	  
	  /*
      if( p_version->protocol_version == ZIGBEE_PROTOCOL_VERSION_4 )
      {
        p_version = srvZbMfgCfgVersion( ZIGBEE_PROTOCOL_VERSION_4 );
      }*/
	  
  
      // configuration de la stack
      for ( loop = 0U; loop < EZSP_NB_CONF_ID; loop++ )
      {
        prep = srvZbMfgCfgSetConfigurationValue(
                                      ezsp_ini_conf_min_value[loop].id,
                                      ezsp_ini_conf_min_value[loop].value );

        if ( (prep == NUL)|| (prep->status != EZSP_SUCCESS) )
        {
          loop = EZSP_NB_CONF_ID;
          out_value = FALSE;
        }
      }
    } 
    else
    {
      // mauvaise version du protocole
      out_value = FALSE;
    }
    
  }
  
  if( TRUE == out_value )
  {
    out_value = FALSE;
    
    /** recupere l'ieee */
    memSet( srv_zb_mfg.eui64, 0U, SIZE_OF_MISC_IEEE );
    Int8U *lp_get_eui64_rep;
    lp_get_eui64_rep = srvZbMfgGetInternalEUI64();
    if( NUL != lp_get_eui64_rep )
    {
      memCpy( srv_zb_mfg.eui64, lp_get_eui64_rep, SIZE_OF_MISC_IEEE );
      out_value = TRUE;
    }
  }
  
  return out_value;
}

/**
*
* \brief fonction de traitement des events genere par d'autre module (driver, dervice, ...)
*
* \param[in] i_event : event a prendre en compte ... ou pas
*
* \return i_event, si on ne souhaite pas que l'event continue son chemin mettre
*         le champ type a E_EVENT_NONE
*/
SEvent srvZbMfgDispatcher( SEvent i_event )
{
  if( E_EVENT_EM260 == i_event.type )
  {
    if( E_EM260_DRV_CALLBACK_EVENT == i_event.name )
    {
      // on doit recupere l'event
      SEzspResponseHeader *prep = NUL;
      
      prep = (SEzspResponseHeader *)drvEm260GetCallback();
      if( prep != NUL )
      {
        if( EZSP_MFGLIB_RX_HANDLER == prep->frame_id )
        {
          if( NUL != srv_zb_mfg.rx_callback )
          {
            // maintenant on peut analyser la trame
            // on appel la callback de traitement
            srv_zb_mfg.rx_callback( &((Int8U*)prep)[5], // packet, le premmier octet est la taille
                                     ((Int8U*)prep)[3], // linkquality
                                     ((Int8S*)prep)[4]  // rssi
                                   );
          }
        }
        
        if( EZSP_NO_CALLBACKS != prep->frame_id )
        {
          // on attend d'avoir un NO_CALLBACKS pour s'arreter
          ATOMIC ( drvEventAdd( i_event ); )
        }
      }
    }
  }
  
  return i_event;
}

void srvZbMfgCheckMessage( void )
{
	SEzspResponseHeader *prep = NUL;
			
	prep = (SEzspResponseHeader *)drvEm260GetCallback();
	if( prep != NUL )
	{
		if( EZSP_MFGLIB_RX_HANDLER == prep->frame_id )
		{
			if( NUL != srv_zb_mfg.rx_callback )
			{
				// maintenant on peut analyser la trame
				// on appel la callback de traitement
				srv_zb_mfg.rx_callback( &((Int8U*)prep)[5], // packet, le premmier octet est la taille
				((Int8U*)prep)[3], // linkquality
				((Int8S*)prep)[4]  // rssi
				);
			}
		}
	}
}

/*******************************************************************************
*                                                                              *
*                  Private Functions of the Module                             *
*                                                                              *
*******************************************************************************/


/**
*  \brief ZigBee Configuration frame : Get EZSP protocol version
*
*  \param[IN] wanted_version : version de protocol attendu
*
*  \return SEzspGetVersionResponse : pointeur vers la structure de réponse
*/
static SEzspGetVersionResponse *srvZbMfgCfgVersion( Int8U wanted_version )
{
  SEzspGetVersionResponse *prep;

  prep = (SEzspGetVersionResponse *)drvEm260DataTranfert(EZSP_VERSION,
                                                         &wanted_version,
                                                         1U, NUL,
                                                         0U, NUL,
                                                         0U );

  return prep;
}

/**
*  \brief ZigBee Configuration frame Set Stack Configuration Value
*
*  \param[IN] config_id : identifier de configuration a modifier
*  \param[IN] value : valeur a affecter
*
*  \return SEzspStatusResponse : pointeur vers la structure de réponse
*/
static SEzspStatusResponse *srvZbMfgCfgSetConfigurationValue(Int8U config_id,
                                                          Int16U value )
{
  SEzspStatusResponse *prep = NUL;

  prep = (SEzspStatusResponse *)drvEm260DataTranfert(
                                                 EZSP_SET_CONFIGURATION_VALUE,
                                                 &config_id, sizeof(Int8U),
                                                 (Int8U*)&value,
                                                 sizeof(Int16U),
                                                 NUL, 0U );

  return prep;
}

//------------------------------------------------------------------------------
/**
*
* \brief demarre la mfglib
*
* \param[in] i_rx_callback : poiteur vers la fonction de reception,
*                            NUL si non utilisée
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgStart( void (*i_rx_callback)( Int8U *packet, 
                                                         Int8U linkQuality, 
                                                         Int8S rssi) )
{
  SEmberStatusResponse *prep;
  Boolean l_use_rx = (NUL!=i_rx_callback);

  prep = (SEmberStatusResponse *)drvEm260DataTranfert( EZSP_MFGLIB_START,
                                                       &l_use_rx, sizeof(l_use_rx),
                                                       NUL, 0U,
                                                       NUL, 0U );
  if( TRUE == l_use_rx )
  {
    srv_zb_mfg.rx_callback = i_rx_callback;
  }
  else
  {
    srv_zb_mfg.rx_callback = NUL;
  }
  
  return prep->status;
}


/**
*
* \brief arrete la mfglib
*
* \param[in] None
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgStop( void )
{
  SEmberStatusResponse *prep;

  prep = (SEmberStatusResponse *)drvEm260DataTranfert( EZSP_MFGLIB_END,
                                                       NUL, 0U,
                                                       NUL, 0U,
                                                       NUL, 0U );
  
  srv_zb_mfg.rx_callback = NUL;
  
  return prep->status;
}

//------------------------------------------------------------------------------

/**
*
* \brief transmit an unmodulated tone on the currently set channel and power level
*
* \param[in] None
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgStartTone( void )
{
  SEmberStatusResponse *prep;

  prep = (SEmberStatusResponse *)drvEm260DataTranfert( EZSP_MFGLIB_START_TONE,
                                                      NUL, 0U,
                                                      NUL, 0U,
                                                      NUL, 0U );
  return prep->status;
}

/**
*
* \brief Stops transmitting a tone
*
* \param[in] None
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgStopTone( void )
{
  SEmberStatusResponse *prep;

  prep = (SEmberStatusResponse *)drvEm260DataTranfert( EZSP_MFGLIB_STOP_TONE,
                                                      NUL, 0U,
                                                      NUL, 0U,
                                                      NUL, 0U );
  return prep->status;
}
//------------------------------------------------------------------------------

/**
*
* \brief Starts transmitting a random stream of characters
*
* \param[in] None
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgStartStream( void )
{
  SEmberStatusResponse *prep;

  prep = (SEmberStatusResponse *)drvEm260DataTranfert( EZSP_MFGLIB_START_STREAM,
                                                      NUL, 0U,
                                                      NUL, 0U,
                                                      NUL, 0U );
  return prep->status;
}

/**
*
* \brief Stops transmitting a random stream of characters
*
* \param[in] None
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgStopStream( void )
{
  SEmberStatusResponse *prep;

  prep = (SEmberStatusResponse *)drvEm260DataTranfert( EZSP_MFGLIB_STOP_STREAM,
                                                      NUL, 0U,
                                                      NUL, 0U,
                                                      NUL, 0U );

  return prep->status;
}

//------------------------------------------------------------------------------

/**
*
* \brief Sends a single packet
*
* \param[in] i_packet_size : taille du packet en octets
* \param[in] i_packet : donnée a envoyer sans l'octet de taille. 
*                       La taille doit etre comprise entre 3 et 123 bytes
* \param[in] i_repeat : nombre de repetition a effectuer, 
*                       0 correspond a un envoi simple
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgSendPacket( Int8U i_packet_size, Int8U *i_packet, 
                                Int16U i_repeat )
{
  SEmberStatusResponse *prep;

  prep = (SEmberStatusResponse *)drvEm260DataTranfert( EZSP_MFGLIB_SEND_PACKET,
                                                       &i_packet_size, sizeof(i_packet_size),
                                                       i_packet, i_packet_size,
                                                       NUL, 0U );

  return prep->status;
}

//------------------------------------------------------------------------------
/**
*
* \brief adjust the transmit power
*
* \param[in] i_power_mode : mode a utiliser : 
*                           EMBER_TX_POWER_MODE_DEFAULT
*                           EMBER_TX_POWER_MODE_BOOST
*                           EMBER_TX_POWER_MODE_ALTERNATE
*                           EMBER_TX_POWER_MODE_BOOST_AND_ALTERNATE
* \param[in] i_power_dbm : discrete valeur definie dans la datasheet du composant
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgSetPower( Int16U i_power_mode, Int8S i_power_dbm )
{
  EmberStatus o_success = EMBER_BAD_ARGUMENT;
  
  if( EMBER_TX_POWER_MODE_BOOST_AND_ALTERNATE >= i_power_mode )
  {
    SEmberStatusResponse *prep;
    Int8U data[3];
    data[0] = LOW_BYTE(i_power_mode);
    data[1] = HIGH_BYTE(i_power_mode);
    data[2] = (Int8U)i_power_dbm;
  
    prep = (SEmberStatusResponse *)drvEm260DataTranfert( EZSP_MFGLIB_SET_POWER,
                                                        data,
                                                        sizeof(Int16U)+sizeof(Int8U),
                                                        NUL, 0U,
                                                        NUL, 0U );
    o_success = prep->status;
  }
  
  return o_success;
}

/**
*
* \brief returns the current radio power
*
* \param[in] None
*
* \return puissance actuellement utilisee
*/
Int8S srvZbMfgGetPower( void )
{
  SEzspGetMfgPowerResponse *prep;
  prep = (SEzspGetMfgPowerResponse *)drvEm260DataTranfert( EZSP_MFGLIB_GET_POWER,
                                                           NUL, 0U,
                                                           NUL, 0U,
                                                           NUL, 0U );

  return prep->power;
}

/**
*
* \brief Selects the radio channel
*
* \param[in] i_channel : numero du canal a utiliser entre 11 et 26
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgSetChannel( Int8U i_channel )
{
  EmberStatus o_success = EMBER_BAD_ARGUMENT;
  
  if( (11U <= i_channel) && (i_channel <= 26U ) )
  {
    SEmberStatusResponse *prep;

    prep = (SEmberStatusResponse *)drvEm260DataTranfert( EZSP_MFGLIB_SET_CHANNEL,
                                                         &i_channel, sizeof(Int8U),
                                                         NUL, 0U,
                                                         NUL, 0U );
    
    o_success = prep->status;
  }
  
  return o_success;
}


/**
*
* \brief Returns the current radio channel
*
* \param[in] None
*
* \return numero du canal radio entre 11 et 26
*/
Int8U srvZbMfgGetChannel( void )
{
  SEzspGetMfgChannelResponse *prep;
  prep = (SEzspGetMfgChannelResponse *)drvEm260DataTranfert( EZSP_MFGLIB_GET_CHANNEL,
                                                             NUL, 0U,
                                                             NUL, 0U,
                                                             NUL, 0U );

  return prep->channel;
}

//------------------------------------------------------------------------------


/**
*
* \brief lit un token de type mfg 
*
* \param[in] i_mfg_token_id : token id :
* \param[in] i_data : buffer dans lequel sera copiee les valeurs 
* \param[in|out] io_data_size : en entree la taille de i_data, 
*                               en sortie la taille du token lu en octet
*
* \return EMBER_SUCCESS si aucune erreur
*/
EmberStatus srvZbMfgGetToken( TokenMfgId i_mfg_token_id, Int8U *i_data, 
                                                         Int8U *io_data_size )
{
  Int8U i;
  SEzspGetMfgTokenResponse *prep;

  prep = (SEzspGetMfgTokenResponse *)drvEm260DataTranfert( EZSP_GET_MFG_TOKEN,
                                                           &i_mfg_token_id, sizeof(EzspMfgTokenId),
                                                           NUL, 0U,
                                                           NUL, 0U );

  *io_data_size = prep->token_data_length;
  for( i = 0U ; i < *io_data_size ; i++ )
  {
    i_data[i] = prep->token_data[i];
  }
 
  return EMBER_SUCCESS;

}

/**
* \brief ZigBee Networking frame lit l'adresse IEEE du noeud
*
* \return pointeur sur l'ieee, NUL en cas d'erreur
*/
static Int8U *srvZbMfgGetInternalEUI64( void )
{
  SEzspGetEUI64Response *prep = NUL;
  Int8U *lpo_ieee = NUL;

  prep = (SEzspGetEUI64Response *)drvEm260DataTranfert( EZSP_GET_EUI64,
                                                        NUL, 0U,
                                                        NUL, 0U,
                                                        NUL, 0U);
  if( prep != NUL )
  {
    lpo_ieee = prep->eui64;
  }

  return lpo_ieee;
}

/**
* \brief test si l'ieee entrante correspond a notre noeud 
* 
* \param[IN] ip_ieee : ieee a tester
*
* \return TRUE si l'ieee correspond
*/
Boolean srvZbMfgCheckIeee( Int8U *ip_ieee )
{
  Boolean lo_success = TRUE;
  Int8U loop;
  
  for( loop=0U; loop<SIZE_OF_MISC_IEEE; loop++ )
  {
    if( ip_ieee[loop] != srv_zb_mfg.eui64[loop] )
    {
      if( 0xFF != ip_ieee[loop] )
      {
        lo_success = FALSE;
      }
    }

    if( FALSE == lo_success )
    {
      loop = SIZE_OF_MISC_IEEE;
    }
  }
  
  return lo_success;
}

/**
* \brief retourne l'addresse ieee du noeud lue lors de l'init
*
* \return pointeur sur l'ieee
*/
Int8U *srvZbMfgGetEUI64( void )
{
  return srv_zb_mfg.eui64;
}

/*******************************************************************************
*                                                                              *
*                  ISR Function of the Module                                  *
*                                                                              *
*******************************************************************************/

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
