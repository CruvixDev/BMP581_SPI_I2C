/**
  ******************************************************************************
  * @file           : app_bmp581.h
  * @brief          : Header file for BMP581 app layer
  * initialisation
  * @author         : Julien Cruvieux
  * @date           : 2024/09/30
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _APP_BMP581_
#define _APP_BMP581_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/**
 * @brief Enumeration defining power modes of BMP581
 * 
 * To switch between power modes, write the enum value in the ODR_CONFIG
 * register in the pwr_mode bit.
 */
typedef enum {
  ceAPP_BMP581_STANDBY = 0,
  ceAPP_BMP581_NORMAL,
  ceAPP_BMP581_FORCED,
  ceAPP_BMP581_CONTINUOUS,
} eBMP581PwrMode_t;

/**
 * @brief Enumeration defining the different ODR values in Hz.
 * 
 * To set the expected ODR, write the enum value in the ODR_CONFIG
 * register in the odr bits.
 */
typedef enum {
  ceAPP_BMP581_240_000Hz = 0,
  ceAPP_BMP581_218_537Hz,
  ceAPP_BMP581_199_111Hz,
  ceAPP_BMP581_179_200Hz,
  ceAPP_BMP581_160_000Hz,
  ceAPP_BMP581_149_333Hz,
  ceAPP_BMP581_140_000Hz,
  ceAPP_BMP581_129_855Hz,
  ceAPP_BMP581_120_000Hz,
  ceAPP_BMP581_110_164Hz,
  ceAPP_BMP581_100_299Hz,
  ceAPP_BMP581_089_600Hz,
  ceAPP_BMP581_080_000Hz,
  ceAPP_BMP581_070_000Hz,
  ceAPP_BMP581_060_000Hz,
  ceAPP_BMP581_050_056Hz,
  ceAPP_BMP581_045_025Hz,
  ceAPP_BMP581_040_000Hz,
  ceAPP_BMP581_035_000Hz,
  ceAPP_BMP581_030_000Hz,
  ceAPP_BMP581_025_005Hz,
  ceAPP_BMP581_020_000Hz,
  ceAPP_BMP581_015_000Hz,
  ceAPP_BMP581_010_000Hz,
  ceAPP_BMP581_005_000Hz,
  ceAPP_BMP581_004_000Hz,
  ceAPP_BMP581_003_000Hz,
  ceAPP_BMP581_002_000Hz,
  ceAPP_BMP581_001_000Hz,
  ceAPP_BMP581_000_500Hz,
  ceAPP_BMP581_000_250Hz,
  ceAPP_BMP581_000_125Hz,
} eBMP581ODR_t;

/**
 * @brief Enumeration defining the different OSR values for
 * pressure and temperature
 * 
 * To set the expected OSR value, write the enum value in OSR_CONFIG
 * register in osr_p for pressure and osr_t for temperature.
 */
typedef enum {
  ceAPP_BMP581_OSR_1 = 0,
  ceAPP_BMP581_OSR_2,
  ceAPP_BMP581_OSR_4,
  ceAPP_BMP581_OSR_8,
  ceAPP_BMP581_OSR_16,
  ceAPP_BMP581_OSR_32,
  ceAPP_BMP581_OSR_64,
  ceAPP_BMP581_OSR_128,
} eBMP581OSR_t;

/**
 * @brief Enumeration defining the counter limit for OOR
 * 
 * To set the expected counter limit value, write the enum value in
 * OOR_CONFIG register in cnt_limit.
 */
typedef enum {
  ceAPP_BMP581_LIMIT_1 = 0,
  ceAPP_BMP581_LIMIT_3,
  ceAPP_BMP581_LIMIT_7,
  ceAPP_BMP581_LIMIT_15,
} eBMP581OORCntLim_t;

/**
 * @brief Enumeration defining compensation for pressure or temperature
 * 
 * To enable compensation for pressure, temperature or both, write the enum
 * value in the DSP_CONFIG register in comp_pt_en bit.
 */
typedef enum {
  ceAPP_BMP581_NO_COMP = 0,
  ceAPP_BMP581_T_COMP,
  ceAPP_BMP581_P_COMP,
  ceAPP_BMP581_PT_COMP,
} eBMP581PTComp_t;

/**
 * @brief Enumeration defining IIR filter coefficients
 * 
 * To set the coefficients of builtin IIR filter, write the enum value in
 * DRP_IIR register in set_iir_p for pressure and in set_iir_t for temperature.
 */
typedef enum {
  ceAPP_BMP581_FILTER_BYPASS = 0,
  ceAPP_BMP581_FILTER_COEFF_1,
  ceAPP_BMP581_FILTER_COEFF_3,
  ceAPP_BMP581_FILTER_COEFF_7,
  ceAPP_BMP581_FILTER_COEFF_15,
  ceAPP_BMP581_FILTER_COEFF_31,
  ceAPP_BMP581_FILTER_COEFF_63,
  ceAPP_BMP581_FILTER_COEFF_127,
} eBMP581IRRFilter_t;

/**
 * @brief Enumeration defining the FIFO selection mode
 * 
 * The BMP581 FIFO can contain temperature, pressure or both. To select
 * the expected mode, write the enum value in FIFO_SEL register in 
 * fifo_frame_sel bit.
 */
typedef enum {
  ceAPP_BMP581_FIFO_DISABLE = 0,
  ceAPP_BMP581_FIFO_TEMP_ONLY,
  ceAPP_BMP581_FIFO_PRESS_ONLY,
  ceAPP_BMP581_FIFO_PRESS_AND_TEMP,
} eBMP581FIFOSel_t;

/**
 * @brief Enumeration defining the different decimation for FIFO
 * 
 * To set the expected decimation factor for the FIFO, write the enum value
 * in the FIFO_SEL register in the fifo_dec_sel bit (for pressure and temperature).
 */
typedef enum {
  ceAPP_BMP581_DEC_1 = 0,
  ceAPP_BMP581_DEC_2,
  ceAPP_BMP581_DEC_4,
  ceAPP_BMP581_DEC_8,
  ceAPP_BMP581_DEC_16,
  ceAPP_BMP581_DEC_32,
  ceAPP_BMP581_DEC_64,
  ceAPP_BMP581_DEC_128,
} eBMP581FIFODec_t;

/**
 * @brief Enumeration defining the protocol used by ASIC
 * 
 * Read this bit in the read only CHIP_STATUS register in hif_mode bit.
 */
typedef enum {
  ceAPP_BMP581_I2C_ONLY = 0,
  ceAPP_BMP581_SPI_MODE1_MODE2,
  ceAPP_BMP581_SPI_MODE0_MODE3,
  ceAPP_BMP581_SPI_AUTOCONFIG,
} eBMP581HIFMode_t;

/**
 * @brief Struct to easily configure and read bits in ODR_CONFIG register
 * ODR_CONFIG : read-write register
 * 
 */
typedef struct {
  eBMP581PwrMode_t e_pwr_mode;
  eBMP581ODR_t e_odr;
  bool b_deep_stdy;
} sODRConfig_t;

/**
 * @brief Struct to easily configure and read bits in OSR_CONFIG register
 * OSR_CONFIG : read-write register 
 * 
 */
typedef struct {
  eBMP581OSR_t e_osr_t;
  eBMP581OSR_t e_osr_p;
  bool b_press_en;
} sOSRConfig_t;

/**
 * @brief Struct to easily configure and read bits in OOR_CONFIG, OOR_RANGE,
 * OOR_THR_P_MSB and OOR_THR_P_LSB registers
 * OOR_CONFIG : read-write register
 * OOR_RANGE : read-wrtie register
 * OOR_THR_P_MSB : read-write register
 * OOR_THR_P_LSB : read-write register
 * 
 */
typedef struct {
  bool b_oor_thr_p_16;
  eBMP581OORCntLim_t e_cnt_lim;
  uint8_t u8_oor_range_p;
  uint8_t u8_oor_thr_p_15_8;
  uint8_t u8_oor_thr_p_7_0;
} sOORConfig_t;

/**
 * @brief Struct to easily configure and read bits in DSP_CONFIG and
 * DSP_IIR registers
 * DSP_CONFIG : read-write register
 * DSP_IIR : read-write register
 * 
 */
typedef struct {
  eBMP581IRRFilter_t e_set_iir_t;
  eBMP581IRRFilter_t e_set_iir_p;
  eBMP581PTComp_t e_comp_pt_en;
  bool b_iir_flush_forced;
  bool b_shdw_sel_iir_t;
  bool b_fifo_sel_iir_t;
  bool b_shdw_sel_iir_p;
  bool b_fifo_sel_iir_p;
  bool b_oor_sel_iir_p;
} sDSPConfig_t;

/**
 * @brief Struct to easily configure and read bits in FIFO_SEL and
 * FIFO_CONFIG registers
 * FIFO_SEL : read-write register
 * FIFO_CONFIG : read-write register
 * 
 */
typedef struct {
  eBMP581FIFOSel_t e_fifo_frame_sel;
  eBMP581FIFODec_t e_fifo_dec_sel;
  uint8_t u8_fifo_threshold;
  bool b_fifo_mode;
} sFIFOConfig_t;

/**
 * @brief Struct to easily configure and read bits in INT_SOURCE and
 * INT_CONFIG registers
 * INT_SOURCE : read-write register
 * INT_CONFIG : read-write register
 * 
 */
typedef struct {
  bool b_drdy_data_reg_en;
  bool b_fifo_full_en;
  bool b_fifo_ths_en;
  bool b_oor_p_en;
  bool b_int_mode;
  bool b_int_pol;
  bool b_int_od;
  bool b_int_en;
  uint8_t u8_pad_int_drv;
} sIntConfig_t;

/**
 * @brief Struct to easily configure and read bits in DRIVE register
 * DRIVE : read-write register
 * 
 */
typedef struct {
  bool b_i2c_csb_pull_en;
  bool b_spi3_en;
  uint8_t u8_pad_if_drv;
} sDriveConfig_t;

/**
 * @brief Struct to easily read bits in OSR_EFF register
 * OSR_EFF : read only register
 * 
 */
typedef struct {
  eBMP581OSR_t e_osr_t_eff;
  eBMP581OSR_t e_osr_p_eff;
  bool b_odr_is_valid;
} sOSREff_t;

/**
 * @brief Struct to easily read bits in STATUS register
 * STATUS : read only register
 * 
 */
typedef struct {
  bool b_status_core_rdy;
  bool b_status_nvm_rdy;
  bool b_status_nvm_err;
  bool b_status_nvm_cmd_err;
  bool b_status_boot_err_corrected;
  bool b_st_crack_pass; 
} sStatus_t;

/**
 * @brief Struct to easily read bits in INT_STATUS register
 * INT_STATUS : read only register
 * 
 */
typedef struct {
  bool b_drdy_data_reg;
  bool b_fifo_full;
  bool b_fifo_ths;
  bool b_oor_p;
  bool b_por;
} sIntStatus_t;

/**
 * @brief Struct to easily read bits in PRESS_DATA register
 * PRESS_DATA : read only register
 * 
 */
typedef struct {
  /* Pressure data */
  uint8_t u8_press_7_0;
  uint8_t u8_press_15_8;
  uint8_t u8_press_23_16;
} sPressData_t;

/**
 * @brief Struct to easily read TEMP_DATA register
 * TEMP_DATA : read only register
 * 
 */
typedef struct {
  uint8_t u8_temp_7_0;
  uint8_t u8_temp_15_8;
  uint8_t u8_temp_23_16;
} sTempData_t;

/**
 * @brief Struct to easily read CHIP_STATUS register
 * CHIP_STATUS : read only register
 * 
 */
typedef struct {
  eBMP581HIFMode_t e_hif_mode;
  bool b_i3c_err_0;
  bool b_i3c_err_3;
} sChipStatus_t;

/* Exported constants --------------------------------------------------------*/
#define BMP581_I2C_ADDR_PRIM        (uint8_t)0x46
#define BMP581_I2C_ADDR_SEC         (uint8_t)0x47
#define BMP581_I2C_CHIP_ID          (uint8_t)0x50
#define BMP581_I2C_REV_ID           (uint8_t)0x32
#define BMP581_I2C_INT_STATUS_READY (uint8_t)0x10
#define BMP581_I2C_STATUS_READY     (uint8_t)0x06

#define cAPP_BMP581_REG_CHIP_ID         (uint8_t)0x01
#define cAPP_BMP581_REG_REV_ID          (uint8_t)0x02
#define cAPP_BMP581_REG_CHIP_STATUS     (uint8_t)0x11
#define cAPP_BMP581_REG_DRIVE_CONFIG    (uint8_t)0x13
#define cAPP_BMP581_REG_INT_CONFIG      (uint8_t)0x14
#define cAPP_BMP581_REG_INT_SOURCE      (uint8_t)0x15
#define cAPP_BMP581_REG_FIFO_CONFIG     (uint8_t)0x16
#define cAPP_BMP581_REG_FIFO_COUNT      (uint8_t)0x17
#define cAPP_BMP581_REG_FIFO_SEL        (uint8_t)0x18
#define cAPP_BMP581_REG_TEMP_DATA_XLSB  (uint8_t)0x1D
#define cAPP_BMP581_REG_TEMP_DATA_LSB   (uint8_t)0x1E
#define cAPP_BMP581_REG_TEMP_DATA_MSB   (uint8_t)0x1F
#define cAPP_BMP581_REG_PRESS_DATA_XLSB (uint8_t)0x20
#define cAPP_BMP581_REG_PRESS_DATA_LSB  (uint8_t)0x21
#define cAPP_BMP581_REG_PRESS_DATA_MSB  (uint8_t)0x22
#define cAPP_BMP581_REG_INT_STATUS      (uint8_t)0x27
#define cAPP_BMP581_REG_STATUS          (uint8_t)0x28
#define cAPP_BMP581_REG_FIFO_DATA       (uint8_t)0x29
#define cAPP_BMP581_REG_NVM_ADDR        (uint8_t)0x2B
#define cAPP_BMP581_REG_NVM_DATA_LSB    (uint8_t)0x2C
#define cAPP_BMP581_REG_NVM_DATA_MSB    (uint8_t)0x2D
#define cAPP_BMP581_REG_DSP_CONFIG      (uint8_t)0x30
#define cAPP_BMP581_REG_DSP_IIR         (uint8_t)0x31
#define cAPP_BMP581_REG_OOR_THR_P_LSB   (uint8_t)0x32
#define cAPP_BMP581_REG_OOR_THR_P_MSB   (uint8_t)0x33
#define cAPP_BMP581_REG_OOR_RANGE       (uint8_t)0x34
#define cAPP_BMP581_REG_OOR_CONFIG      (uint8_t)0x35
#define cAPP_BMP581_REG_OSR_CONFIG      (uint8_t)0x36
#define cAPP_BMP581_REG_ODR_CONFIG      (uint8_t)0x37
#define cAPP_BMP581_REG_OSR_EFF         (uint8_t)0x38
#define cAPP_BMP581_REG_CMD             (uint8_t)0x7E

#define BMP581_REGISTER_SIZE (uint8_t)1

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void vAPP_BMP581_init(void);

/* Write functions for read / write registers */
void errAPP_BMP581_writeCommand(uint8_t p_u8Command);
void errAPP_BMP581_configureODR(sODRConfig_t p_sODRConfig);
void errAPP_BMP581_configureOSR(sOSRConfig_t p_sOSRConfig);
void errAPP_BMP581_configureOOR(sOORConfig_t p_sOORConfig);
void errAPP_BMP581_configureDSP(sDSPConfig_t p_sDSPConfig);
void errAPP_BMP581_writeNVM(uint8_t p_u8NVMAddress, uint8_t p_u8NVMData);
void errAPP_BMP581_readNVM(uint8_t p_u8NVMAddress, uint8_t p_u8NVMData);
void errAPP_BMP581_configureFIFO(sFIFOConfig_t p_sFIFOConfig);
void errAPP_BMP581_configureInterrupt(sIntConfig_t p_sIntConfig);
void errAPP_BMP581_configureDrive(sDriveConfig_t p_sDriveConfig);

/* Read functions for read / write registers */
void errAPP_BMP581_getCommand(uint8_t* p_u8Command);
void errAPP_BMP581_getODRConfig(sODRConfig_t* p_sODRConfig);
void errAPP_BMP581_getOSRConfig(sOSRConfig_t* p_sOSRConfig);
void errAPP_BMP581_getOORConfig(sOORConfig_t* p_sOORConfig);
void errAPP_BMP581_getDSPConfig(sDSPConfig_t* p_sDSPConfig);
void errAPP_BMP581_getFIFOConfig(sFIFOConfig_t* p_sFIFOConfig);
void errAPP_BMP581_getInterruptConfig(sIntConfig_t* p_sIntConfig);
void errAPP_BMP581_getDriveConfig(sDriveConfig_t* p_sDriveConfig);

/* Read functions for read only registers */
void errAPP_BMP581_getEffectiveOSR(sOSREff_t* p_sOSREff);
void errAPP_BMP581_getFIFOData(uint8_t* p_u8FIFOData);
void errAPP_BMP581_getStatus(sStatus_t* p_sStatus);
void errAPP_BMP581_getIntStatus(sIntStatus_t* p_sIntStatus);
void errAPP_BMP581_getPressData(sPressData_t* p_sPressData);
void errAPP_BMP581_getTempData(sTempData_t* p_sTempData);
void errAPP_BMP581_getFIFOCount(uint8_t* p_u8FIFOCount);
void errAPP_BMP581_getChipStatus(sChipStatus_t* p_sChipStatus);
void errAPP_BMP581_getChipID(uint8_t* p_u8ChipID);
void errAPP_BMP581_getRevID(uint8_t* p_u8RevID);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* _APP_BMP581_ */
