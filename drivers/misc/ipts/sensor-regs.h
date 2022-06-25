/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 *
 * Intel Precise Touch & Stylus
 * Copyright (c) 2013-2016 Intel Corporation
 *
 */

#ifndef _IPTS_SENSOR_REGS_H_
#define _IPTS_SENSOR_REGS_H_

#include <linux/build_bug.h>

#pragma pack(1)

// Define static_assert macro (which will be available after 5.1
// and not available on 4.19 yet) to check structure size and fail
// compile for unexpected mismatch.
// Taken from upstream commit 6bab69c65013bed5fce9f101a64a84d0385b3946.
#define static_assert(expr, ...) __static_assert(expr, ##__VA_ARGS__, #expr)
#define __static_assert(expr, msg, ...) _Static_assert(expr, msg)

/*
 * Compatibility versions for this header file
 */
#define TOUCH_EDS_REV_MINOR 0
#define TOUCH_EDS_REV_MAJOR 1
#define TOUCH_EDS_INTF_REV 1
#define TOUCH_PROTOCOL_VER 0

/*
 * Offset 00h: TOUCH_STS: Status Register
 * This register is read by the SPI Controller immediately following
 * an interrupt.
 */
#define TOUCH_STS_REG_OFFSET 0x00

#define TOUCH_SYNC_BYTE_VALUE 0x5A

/*
 * Offset 04h: TOUCH_FRAME_CHAR: Frame Characteristics Register
 * This registers describes the characteristics of each data frame read by the
 * SPI Controller in response to a touch interrupt.
 */
#define TOUCH_FRAME_CHAR_REG_OFFSET 0x04

/*
 * Offset 08h: Touch Error Register
 */
#define TOUCH_ERR_REG_OFFSET 0x08

/*
 * Offset 10h: Touch Identification Register
 */
#define TOUCH_ID_REG_OFFSET 0x10
#define TOUCH_ID_REG_VALUE  0x43495424

/*
 * Offset 14h: TOUCH_DATA_SZ: Touch Data Size Register
 * This register describes the maximum size of frames and feedback data
 */
#define TOUCH_DATA_SZ_REG_OFFSET 0x14

#define TOUCH_MAX_FRAME_SIZE_INCREMENT    64
#define TOUCH_MAX_FEEDBACK_SIZE_INCREMENT 64

/*
 * Max allowed frame size 32KB
 * Max allowed feedback size 16KB
 */
#define TOUCH_SENSOR_MAX_FRAME_SIZE    (32 * 1024)
#define TOUCH_SENSOR_MAX_FEEDBACK_SIZE (16 * 1024)

/*
 * Offset 18h: TOUCH_CAPABILITIES: Touch Capabilities Register
 * This register informs the host as to the capabilities of the touch IC.
 */
#define TOUCH_CAPS_REG_OFFSET 0x18

#define TOUCH_BULK_DATA_MAX_WRITE_INCREMENT 64

/*
 * Offset 1Ch: TOUCH_CFG: Touch Configuration Register
 * This register allows the SPI Controller to configure the touch sensor as
 * needed during touch operations.
 */
#define TOUCH_CFG_REG_OFFSET 0x1C

/*
 * Offset 20h: TOUCH_CMD: Touch Command Register
 * This register is used for sending commands to the Touch IC.
 */
#define TOUCH_CMD_REG_OFFSET 0x20

/*
 * Offset 24h: Power Management Control
 * This register is used for active power management. The Touch IC is allowed
 * to mover from Doze or Armed to Sensing after a touch has occurred. All other
 * transitions will be made at the request of the SPI Controller.
 */
#define TOUCH_PWR_MGMT_CTRL_REG_OFFSET 0x24

/*
 * Offset 28h: Vendor HW Information Register
 * This register is used to relay Intel-assigned vendor ID information to the
 * SPI Controller, which may be forwarded to SW running on the host CPU.
 */
#define TOUCH_VEN_HW_INFO_REG_OFFSET 0x28

/*
 * Offset 2Ch: HW Revision ID Register
 * This register is used to relay vendor HW revision information to the SPI
 * Controller which may be forwarded to SW running on the host CPU.
 */
#define TOUCH_HW_REV_REG_OFFSET 0x2C

/*
 * Offset 30h: FW Revision ID Register
 * This register is used to relay vendor FW revision information to the SPI
 * Controller which may be forwarded to SW running on the host CPU.
 */
#define TOUCH_FW_REV_REG_OFFSET 0x30

/*
 * Offset 34h: Compatibility Revision ID Register
 * This register is used to relay vendor compatibility information to the SPI
 * Controller which may be forwarded to SW running on the host CPU.
 * Compatibility Information is a numeric value given by Intel to the Touch IC
 * vendor based on the major and minor revision of the EDS supported. From a
 * nomenclature point of view in an x.y revision number of the EDS, the major
 * version is the value of x and the minor version is the value of y. For
 * example, a Touch IC supporting an EDS version of 0.61 would contain a major
 * version of 0 and a minor version of 61 in the register.
 */
#define TOUCH_COMPAT_REV_REG_OFFSET 0x34

/*
 * Touch Register Block is the full set of registers from offset 0x00h to 0x3F
 * This is the entire set of registers needed for normal touch operation. It
 * does not include test registers such as TOUCH_TEST_CTRL_REG
 */
#define TOUCH_REG_BLOCK_OFFSET TOUCH_STS_REG_OFFSET

/*
 * Offset 40h: Test Control Register
 * This register
 */
#define TOUCH_TEST_CTRL_REG_OFFSET 0x40

/*
 * Offsets 0x000 to 0xFFF are reserved for Intel-defined Registers
 */
#define TOUCH_REGISTER_LIMIT 0xFFF

/*
 * Data Window: Address 0x1000-0x1FFFF
 * The data window is reserved for writing and reading large quantities of
 * data to and from the sensor.
 */
#define TOUCH_DATA_WINDOW_OFFSET 0x1000
#define TOUCH_DATA_WINDOW_LIMIT  0x1FFFF

#define TOUCH_SENSOR_MAX_OFFSET TOUCH_DATA_WINDOW_LIMIT

enum touch_sts_reg_int_type {
	// Touch Data Available
	TOUCH_STS_REG_INT_TYPE_DATA_AVAIL = 0,

	// Reset Occurred
	TOUCH_STS_REG_INT_TYPE_RESET_OCCURRED,

	// Error Occurred
	TOUCH_STS_REG_INT_TYPE_ERROR_OCCURRED,

	// Vendor specific data, treated same as raw frame
	TOUCH_STS_REG_INT_TYPE_VENDOR_DATA,

	// Get Features response data available
	TOUCH_STS_REG_INT_TYPE_GET_FEATURES,

	TOUCH_STS_REG_INT_TYPE_MAX
};
static_assert(sizeof(enum touch_sts_reg_int_type) == 4);

enum touch_sts_reg_pwr_state {
	// Sleep
	TOUCH_STS_REG_PWR_STATE_SLEEP = 0,

	// Doze
	TOUCH_STS_REG_PWR_STATE_DOZE,

	// Armed
	TOUCH_STS_REG_PWR_STATE_ARMED,

	// Sensing
	TOUCH_STS_REG_PWR_STATE_SENSING,

	TOUCH_STS_REG_PWR_STATE_MAX
};
static_assert(sizeof(enum touch_sts_reg_pwr_state) == 4);

enum touch_sts_reg_init_state {
	// Ready for normal operation
	TOUCH_STS_REG_INIT_STATE_READY_FOR_OP = 0,

	// Touch IC needs its Firmware loaded
	TOUCH_STS_REG_INIT_STATE_FW_NEEDED,

	// Touch IC needs its Data loaded
	TOUCH_STS_REG_INIT_STATE_DATA_NEEDED,

	// Error info in TOUCH_ERR_REG
	TOUCH_STS_REG_INIT_STATE_INIT_ERROR,

	TOUCH_STS_REG_INIT_STATE_MAX
};
static_assert(sizeof(enum touch_sts_reg_init_state) == 4);

union touch_sts_reg {
	u32 reg_value;
	struct {
		// When set, this indicates the hardware has data
		// that needs to be read.
		u32 int_status:1;

		// see TOUCH_STS_REG_INT_TYPE
		u32 int_type:4;

		// see TOUCH_STS_REG_PWR_STATE
		u32 pwr_state:2;

		// see TOUCH_STS_REG_INIT_STATE
		u32 init_state:2;

		// Busy bit indicates that sensor cannot
		// accept writes at this time
		u32 busy:1;

		// Reserved
		u32 reserved:14;

		// Synchronization bit, should always be TOUCH_SYNC_BYTE_VALUE
		u32 sync_byte:8;
	} fields;
};
static_assert(sizeof(union touch_sts_reg) == 4);

union touch_frame_char_reg {
	u32  reg_value;
	struct {
		// Micro-Frame Size (MFS): Indicates the size of a touch
		// micro-frame in byte increments. When a micro-frame is to be
		// read for processing (in data mode), this is the total number
		// of bytes that must be read per interrupt, split into
		// multiple read commands no longer than RPS.
		// Maximum micro-frame size is 256KB.
		u32 microframe_size:18;

		// Micro-Frames per Frame (MFPF): Indicates the number of
		// micro-frames per frame. If a sensor's frame does not contain
		// micro-frames this value will be 1. Valid values are 1-31.
		u32 microframes_per_frame:5;

		// Micro-Frame Index (MFI): Indicates the index of the
		// micro-frame within a frame. This allows the SPI Controller
		// to maintain synchronization with the sensor and determine
		// when the final micro-frame has arrived.
		// Valid values are 1-31.
		u32 microframe_index:5;

		// HID/Raw Data: This bit describes whether the data from the
		// sensor is Raw data or a HID report. When set, the data
		// is a HID report.
		u32 hid_report:1;

		// Reserved
		u32 reserved:3;
	} fields;
};
static_assert(sizeof(union touch_frame_char_reg) == 4);

// bit definition is vendor specific
union touch_err_reg {
	u32  reg_value;
	struct {
		u32 invalid_fw:1;
		u32 invalid_data:1;
		u32 self_test_failed:1;
		u32 reserved:12;
		u32 fatal_error:1;
		u32 vendor_errors:16;
	} fields;
};
static_assert(sizeof(union touch_err_reg) == 4);

union touch_data_sz_reg {
	u32  reg_value;
	struct {
		// This value describes the maximum frame size in
		// 64byte increments.
		u32 max_frame_size:12;

		// This value describes the maximum feedback size in
		// 64byte increments.
		u32 max_feedback_size:8;

		// Reserved
		u32 reserved:12;
	} fields;
};
static_assert(sizeof(union touch_data_sz_reg) == 4);

enum touch_caps_reg_read_delay_time {
	TOUCH_CAPS_REG_READ_DELAY_TIME_0,
	TOUCH_CAPS_REG_READ_DELAY_TIME_10uS,
	TOUCH_CAPS_REG_READ_DELAY_TIME_50uS,
	TOUCH_CAPS_REG_READ_DELAY_TIME_100uS,
	TOUCH_CAPS_REG_READ_DELAY_TIME_150uS,
	TOUCH_CAPS_REG_READ_DELAY_TIME_250uS,
	TOUCH_CAPS_REG_READ_DELAY_TIME_500uS,
	TOUCH_CAPS_REG_READ_DELAY_TIME_1mS,
};
static_assert(sizeof(enum touch_caps_reg_read_delay_time) == 4);

union touch_caps_reg {
	u32  reg_value;
	struct {
		// Reserved for future frequency
		u32 reserved0:1;

		// 17 MHz (14 MHz on Atom) Supported
		// 0b - Not supported, 1b - Supported
		u32 supported_17Mhz:1;

		// 30 MHz (25MHz on Atom) Supported
		// 0b - Not supported, 1b - Supported
		u32 supported_30Mhz:1;

		// 50 MHz Supported
		// 0b - Not supported, 1b - Supported
		u32 supported_50Mhz:1;

		// Reserved
		u32 reserved1:4;

		// Single I/O Supported
		// 0b - Not supported, 1b - Supported
		u32 supported_single_io:1;

		// Dual I/O Supported
		// 0b - Not supported, 1b - Supported
		u32 supported_dual_io:1;

		// Quad I/O Supported
		// 0b - Not supported, 1b - Supported
		u32 supported_quad_io:1;

		// Bulk Data Area Max Write Size: The amount of data the SPI
		// Controller can write to the bulk data area before it has to
		// poll the busy bit. This field is in multiples of 64 bytes.
		// The SPI Controller will write the amount of data specified
		// in this field, then check and wait for the Status.Busy bit
		// to be zero before writing the next data chunk. This field is
		// 6 bits long, allowing for 4KB of contiguous writes w/o a
		// poll of the busy bit. If this field is 0x00 the Touch IC has
		// no limit in the amount of data the SPI Controller can write
		// to the bulk data area.
		u32 bulk_data_max_write:6;

		// Read Delay Timer Value: This field describes the delay the
		// SPI Controller will initiate when a read interrupt follows
		// a write data command. Uses values from
		// TOUCH_CAPS_REG_READ_DELAY_TIME
		u32 read_delay_timer_value:3;

		// Reserved
		u32 reserved2:4;

		// Maximum Touch Points: A byte value based on the
		// HID descriptor definition.
		u32 max_touch_points:8;
	} fields;
};
static_assert(sizeof(union touch_caps_reg) == 4);

enum touch_cfg_reg_bulk_xfer_size {
	// Bulk Data Transfer Size is 4 bytes
	TOUCH_CFG_REG_BULK_XFER_SIZE_4B  = 0,

	// Bulk Data Transfer Size is 8 bytes
	TOUCH_CFG_REG_BULK_XFER_SIZE_8B,

	// Bulk Data Transfer Size is 16 bytes
	TOUCH_CFG_REG_BULK_XFER_SIZE_16B,

	// Bulk Data Transfer Size is 32 bytes
	TOUCH_CFG_REG_BULK_XFER_SIZE_32B,

	// Bulk Data Transfer Size is 64 bytes
	TOUCH_CFG_REG_BULK_XFER_SIZE_64B,

	TOUCH_CFG_REG_BULK_XFER_SIZE_MAX
};
static_assert(sizeof(enum touch_cfg_reg_bulk_xfer_size) == 4);

/*
 * Frequency values used by TOUCH_CFG_REG
 * and TOUCH_SENSOR_GET_DEVICE_INFO_RSP_DATA.
 */
enum touch_freq {
	// Reserved value
	TOUCH_FREQ_RSVD = 0,

	// Sensor set for 17MHz operation (14MHz on Atom)
	TOUCH_FREQ_17MHZ,

	// Sensor set for 30MHz operation (25MHz on Atom)
	TOUCH_FREQ_30MHZ,

	// Invalid value
	TOUCH_FREQ_MAX
};
static_assert(sizeof(enum touch_freq) == 4);

union touch_cfg_reg {
	u32  reg_value;
	struct {
		// Touch Enable (TE): This bit is used as a HW semaphore for
		// the Touch IC to guarantee to the SPI Controller to that
		// (when 0) no sensing operations will occur and only the Reset
		// interrupt will be generated.
		//
		// When TE is cleared by the SPI
		// Controller:
		//     - TICs must flush all output buffers
		//     - TICs must De-assert any pending interrupt
		//     - ME must throw away any partial frame and pending
		//       interrupt must be cleared/not serviced.
		//
		// The SPI Controller will only modify the configuration of the
		// TIC when TE is cleared.
		// TE is defaulted to 0h on a power-on reset.
		u32 touch_enable:1;

		// Data/HID Packet Mode (DHPM)
		// Raw Data Mode: 0h, HID Packet Mode: 1h
		u32 dhpm:1;

		// Bulk Data Transfer Size: This field represents the amount
		// of data written to the Bulk Data Area
		// (SPI Offset 0x1000-0x2FFF) in a single SPI write protocol
		u32 bulk_xfer_size:4;

		// Frequency Select: Frequency for the TouchIC to run at.
		// Use values from TOUCH_FREQ
		u32 freq_select:3;

		// Reserved
		u32 reserved:23;
	} fields;
};
static_assert(sizeof(union touch_cfg_reg) == 4);

enum touch_cmd_reg_code {
	// No Operation
	TOUCH_CMD_REG_CODE_NOP = 0,

	// Soft Reset
	TOUCH_CMD_REG_CODE_SOFT_RESET,

	// Prepare All Registers for Read
	TOUCH_CMD_REG_CODE_PREP_4_READ,

	// Generate Test Packets according to value in TOUCH_TEST_CTRL_REG
	TOUCH_CMD_REG_CODE_GEN_TEST_PACKETS,

	TOUCH_CMD_REG_CODE_MAX
};
static_assert(sizeof(enum touch_cmd_reg_code) == 4);

union touch_cmd_reg {
	u32 reg_value;
	struct {
		// Command Code: See TOUCH_CMD_REG_CODE
		u32 command_code:8;

		// Reserved
		u32 reserved:24;
	} fields;
};
static_assert(sizeof(union touch_cmd_reg) == 4);

enum touch_pwr_mgmt_ctrl_reg_cmd {
	// No change to power state
	TOUCH_PWR_MGMT_CTRL_REG_CMD_NOP = 0,

	// Sleep - set when the system goes into connected standby
	TOUCH_PWR_MGMT_CTRL_REG_CMD_SLEEP,

	// Doze - set after 300 seconds of inactivity
	TOUCH_PWR_MGMT_CTRL_REG_CMD_DOZE,

	// Armed - Set by FW when a "finger off" message is
	// received from the EUs
	TOUCH_PWR_MGMT_CTRL_REG_CMD_ARMED,

	// Sensing - not typically set by FW
	TOUCH_PWR_MGMT_CTRL_REG_CMD_SENSING,

	// Values will result in no change to the power state of the Touch IC
	TOUCH_PWR_MGMT_CTRL_REG_CMD_MAX
};
static_assert(sizeof(enum touch_pwr_mgmt_ctrl_reg_cmd) == 4);

union touch_pwr_mgmt_ctrl_reg {
	u32  reg_value;
	struct {
		// Power State Command: See TOUCH_PWR_MGMT_CTRL_REG_CMD
		u32 pwr_state_cmd:3;

		// Reserved
		u32 reserved:29;
	} fields;
};
static_assert(sizeof(union touch_pwr_mgmt_ctrl_reg) == 4);

union touch_ven_hw_info_reg {
	u32  reg_value;
	struct {
		// Touch Sensor Vendor ID
		u32 vendor_id:16;

		// Touch Sensor Device ID
		u32 device_id:16;
	} fields;
};
static_assert(sizeof(union touch_ven_hw_info_reg) == 4);

union touch_compat_rev_reg {
	u32  reg_value;

	struct {
		// EDS Minor Revision
		u8 minor;

		// EDS Major Revision
		u8 major;

		// Interface Revision Number (from EDS)
		u8 intf_rev;

		// EU Kernel Compatibility Version - vendor specific value
		u8 kernel_compat_ver;
	} fields;
};
static_assert(sizeof(union touch_compat_rev_reg) == 4);

struct touch_reg_block {
	// 0x00
	union touch_sts_reg sts_reg;

	// 0x04
	union touch_frame_char_reg frame_char_reg;

	// 0x08
	union touch_err_reg error_reg;

	// 0x0C
	u32 reserved0;

	// 0x10 - expected value is "$TIC" or 0x43495424
	u32 id_reg;

	// 0x14
	union touch_data_sz_reg data_size_reg;

	// 0x18
	union touch_caps_reg caps_reg;

	// 0x1C
	union touch_cfg_reg cfg_reg;

	// 0x20
	union touch_cmd_reg cmd_reg;

	// 0x24
	union touch_pwr_mgmt_ctrl_reg pwm_mgme_ctrl_reg;

	// 0x28
	union touch_ven_hw_info_reg ven_hw_info_reg;

	// 0x2C
	u32 hw_rev_reg;

	// 0x30
	u32 fw_rev_reg;

	// 0x34
	union touch_compat_rev_reg compat_rev_reg;

	// 0x38
	u32 reserved1;

	// 0x3C
	u32 reserved2;
};
static_assert(sizeof(struct touch_reg_block) == 64);

union touch_test_ctrl_reg {
	u32  reg_value;
	struct {
		// Size of Test Frame in Raw Data Mode: This field specifies
		// the test frame size in raw data mode in multiple of 64 bytes.
		// For example, if this field value is 16, the test frame size
		// will be 16x64 = 1K.
		u32 raw_test_frame_size:16;

		// Number of Raw Data Frames or HID Report Packets Generation.
		// This field represents the number of test frames or HID
		// reports to be generated when test mode is enabled. When
		// multiple packets/frames are generated, they need be
		// generated at 100 Hz frequency, i.e. 10ms per packet/frame.
		u32 num_test_frames:16;
	} fields;
};
static_assert(sizeof(union touch_test_ctrl_reg) == 4);

/*
 * The following data structures represent the headers defined in the Data
 * Structures chapter of the Intel Integrated Touch EDS
 */

// Enumeration used in TOUCH_RAW_DATA_HDR
enum touch_raw_data_types {
	TOUCH_RAW_DATA_TYPE_FRAME = 0,

	// RawData will be the TOUCH_ERROR struct below
	TOUCH_RAW_DATA_TYPE_ERROR,

	// Set when InterruptType is Vendor Data
	TOUCH_RAW_DATA_TYPE_VENDOR_DATA,

	TOUCH_RAW_DATA_TYPE_HID_REPORT,
	TOUCH_RAW_DATA_TYPE_GET_FEATURES,
	TOUCH_RAW_DATA_TYPE_MAX
};
static_assert(sizeof(enum touch_raw_data_types) == 4);

// Private data structure. Kernels must copy to HID driver buffer
struct touch_hid_private_data {
	u32 transaction_id;
	u8 reserved[28];
};
static_assert(sizeof(struct touch_hid_private_data) == 32);

// This is the data structure sent from the PCH FW to the EU kernel
struct touch_raw_data_hdr {
	// use values from TOUCH_RAW_DATA_TYPES
	u32 data_type;

	// The size in bytes of the raw data read from the sensor, does not
	// include TOUCH_RAW_DATA_HDR. Will be the sum of all uFrames, or size
	// of TOUCH_ERROR for if DataType is TOUCH_RAW_DATA_TYPE_ERROR
	u32 raw_data_size_bytes;

	// An ID to qualify with the feedback data to track buffer usage
	u32 buffer_id;

	// Must match protocol version of the EDS
	u32 protocol_ver;

	// Copied from the Compatibility Revision ID Reg
	u8 kernel_compat_id;

	// Padding to extend header to full 64 bytes and allow for growth
	u8 reserved[15];

	// Private data structure. Kernels must copy to HID driver buffer
	struct touch_hid_private_data hid_private_data;
};
static_assert(sizeof(struct touch_raw_data_hdr) == 64);

struct touch_raw_data {
	struct touch_raw_data_hdr header;

	// used to access the raw data as an array and keep the compilers
	// happy. Actual size of this array is Header.RawDataSizeBytes
	u8 raw_data[1];
};

/*
 * The following section describes the data passed in TOUCH_RAW_DATA.RawData
 * when DataType equals TOUCH_RAW_DATA_TYPE_ERROR
 * Note: This data structure is also applied to HID mode
 */
enum touch_err_types {
	TOUCH_RAW_DATA_ERROR = 0,
	TOUCH_RAW_ERROR_MAX
};
static_assert(sizeof(enum touch_err_types) == 4);

union touch_me_fw_error {
	u32  value;
	struct {
		u32 invalid_frame_characteristics:1;
		u32 microframe_index_invalid:1;
		u32 reserved:30;
	} fields;
};
static_assert(sizeof(union touch_me_fw_error) == 4);

struct touch_error {
	// This must be a value from TOUCH_ERROR_TYPES
	u8 touch_error_type;
	u8 reserved[3];
	union touch_me_fw_error touch_me_fw_error;

	// Contains the value copied from the Touch Error Reg
	union touch_err_reg touch_error_register;
};
static_assert(sizeof(struct touch_error) == 12);

// Enumeration used in TOUCH_FEEDBACK_BUFFER
enum touch_feedback_cmd_types {
	TOUCH_FEEDBACK_CMD_TYPE_NONE = 0,
	TOUCH_FEEDBACK_CMD_TYPE_SOFT_RESET,
	TOUCH_FEEDBACK_CMD_TYPE_GOTO_ARMED,
	TOUCH_FEEDBACK_CMD_TYPE_GOTO_SENSING,
	TOUCH_FEEDBACK_CMD_TYPE_GOTO_SLEEP,
	TOUCH_FEEDBACK_CMD_TYPE_GOTO_DOZE,
	TOUCH_FEEDBACK_CMD_TYPE_HARD_RESET,
	TOUCH_FEEDBACK_CMD_TYPE_MAX
};
static_assert(sizeof(enum touch_feedback_cmd_types) == 4);

// Enumeration used in TOUCH_FEEDBACK_HDR
enum touch_feedback_data_types {
	// This is vendor specific feedback to be written to the sensor
	TOUCH_FEEDBACK_DATA_TYPE_FEEDBACK = 0,

	// This is a set features command to be written to the sensor
	TOUCH_FEEDBACK_DATA_TYPE_SET_FEATURES,

	// This is a get features command to be written to the sensor
	TOUCH_FEEDBACK_DATA_TYPE_GET_FEATURES,

	// This is a HID output report to be written to the sensor
	TOUCH_FEEDBACK_DATA_TYPE_OUTPUT_REPORT,

	// This is calibration data to be written to system flash
	TOUCH_FEEDBACK_DATA_TYPE_STORE_DATA,

	TOUCH_FEEDBACK_DATA_TYPE_MAX
};
static_assert(sizeof(enum touch_feedback_data_types) == 4);

/*
 * This is the data structure sent from the EU kernels back to the ME FW.
 * In addition to "feedback" data, the FW can execute a "command" described by
 * the command type parameter. Any payload data will always be sent to the TIC
 * first, then any command will be issued.
 */
struct touch_feedback_hdr {
	// use values from TOUCH_FEEDBACK_CMD_TYPES
	u32 feedback_cmd_type;

	// The amount of data to be written to the sensor,
	// not including the header
	u32 payload_size_bytes;

	// The ID of the raw data buffer that generated this feedback data
	u32 buffer_id;

	// Must match protocol version of the EDS
	u32 protocol_ver;

	// use values from TOUCH_FEEDBACK_DATA_TYPES. This is not relevant
	// if PayloadSizeBytes is 0
	u32 feedback_data_type;

	// The offset from TOUCH_DATA_WINDOW_OFFSET at which to write the
	// Payload data. Maximum offset is 0x1EFFF.
	u32 spi_offest;

	// Padding to extend header to full 64 bytes and allow for growth
	u8 reserved[40];
};
static_assert(sizeof(struct touch_feedback_hdr) == 64);

struct touch_feedback_buffer {
	struct touch_feedback_hdr Header;

	// used to access the feedback data as an array and keep the compilers
	// happy. Actual size of this array is Header.PayloadSizeBytes
	u8 feedback_data[1];
};

/*
 * This data structure describes the header prepended to all data
 * written to the touch IC at the bulk data write
 * (TOUCH_DATA_WINDOW_OFFSET + TOUCH_FEEDBACK_HDR.SpiOffest) address.
 */
enum touch_write_data_type {
	TOUCH_WRITE_DATA_TYPE_FW_LOAD = 0,
	TOUCH_WRITE_DATA_TYPE_DATA_LOAD,
	TOUCH_WRITE_DATA_TYPE_FEEDBACK,
	TOUCH_WRITE_DATA_TYPE_SET_FEATURES,
	TOUCH_WRITE_DATA_TYPE_GET_FEATURES,
	TOUCH_WRITE_DATA_TYPE_OUTPUT_REPORT,
	TOUCH_WRITE_DATA_TYPE_NO_DATA_USE_DEFAULTS,
	TOUCH_WRITE_DATA_TYPE_MAX
};
static_assert(sizeof(enum touch_write_data_type) == 4);

struct touch_write_hdr {
	// Use values from TOUCH_WRITE_DATA_TYPE
	u32 write_data_type;

	// This field designates the amount of data to follow
	u32 write_data_len;
};
static_assert(sizeof(struct touch_write_hdr) == 8);

struct touch_write_data {
	struct touch_write_hdr header;

	// used to access the write data as an array and keep the compilers
	// happy. Actual size of this array is Header.WriteDataLen
	u8 write_data[1];
};

#pragma pack()

#endif // _IPTS_SENSOR_REGS_H_
