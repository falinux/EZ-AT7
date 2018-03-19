//------------------------------------------------------------------------------
// 파 일 명 : setup.h
// 프로젝트 : ez-jtag
// 설    명 : 레지스터 초기 설정 값에 대한 정의
// 작 성 자 : 유영창(frog@falinux.com), 이영민, 박영리
// 작 성 일 : 2007년 4월 28일
// 수 정 일 : 
// 수 정 일 : 
// 주    의 : 
// 라이센스 : BSD
//------------------------------------------------------------------------------

#ifndef _SETUP_HEADER_
#define _SETUP_HEADER_


//------------------------------------------------------------------------------
//              SOFTWARE API DEFINITION  FOR Real Time Timer Controller Interface
//------------------------------------------------------------------------------

// -------- RTTC_RTMR : (RTTC Offset: 0x0) Real-time Mode Register -------- 
#define RTTC_RTPRES     				( 0xFFFF 	<<  0) 				// (RTTC) Real-time Timer Prescaler Value
#define RTTC_ALMIEN     				( 0x1 	 	<< 16) 				// (RTTC) Alarm Interrupt Enable
#define RTTC_RTTINCIEN  				( 0x1    	<< 17) 				// (RTTC) Real Time Timer Increment Interrupt Enable
#define RTTC_RTTRST     				( 0x1    	<< 18) 				// (RTTC) Real Time Timer Restart

// -------- RTTC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- 
#define RTTC_ALMV       				( 0x0    	<<  0) 				// (RTTC) Alarm Value

// -------- RTTC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- 
#define RTTC_CRTV       				( 0x0   	<<  0) 				// (RTTC) Current Real-time Value
// -------- RTTC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- 
#define RTTC_ALMS       				( 0x1   	<<  0) 				// (RTTC) Real-time Alarm Status
#define RTTC_RTTINC     				( 0x1   	<<  1) 				// (RTTC) Real-time Timer Increment

//------------------------------------------------------------------------------
//              SOFTWARE API DEFINITION  FOR Advanced Interrupt Controller
//------------------------------------------------------------------------------

// -------- AIC_SMR : (AIC Offset: 0x0) Control Register -------- 
#define AIC_PRIOR       				( 0x7 		<<  0) 				// (AIC) Priority Level
#define AIC_PRIOR_LOWEST               	( 0x0 		<<  0) 				// (AIC) Lowest priority level
#define AIC_PRIOR_HIGHEST              	( 0x7 		<<  0) 				// (AIC) Highest priority level
#define AIC_SRCTYPE     				( 0x3 		<<  5) 				// (AIC) Interrupt Source Type
#define AIC_SRCTYPE_INT_HIGH_LEVEL      ( 0x0 		<<  5) 				// (AIC) Internal Sources Code Label High-level Sensitive
#define AIC_SRCTYPE_EXT_LOW_LEVEL       ( 0x0 		<<  5) 				// (AIC) External Sources Code Label Low-level Sensitive
#define AIC_SRCTYPE_INT_POSITIVE_EDGE   ( 0x1 		<<  5) 				// (AIC) Internal Sources Code Label Positive Edge triggered
#define AIC_SRCTYPE_EXT_NEGATIVE_EDGE   ( 0x1 		<<  5) 				// (AIC) External Sources Code Label Negative Edge triggered
#define AIC_SRCTYPE_HIGH_LEVEL          ( 0x2 		<<  5) 				// (AIC) Internal Or External Sources Code Label High-level Sensitive
#define AIC_SRCTYPE_POSITIVE_EDGE       ( 0x3 		<<  5) 				// (AIC) Internal Or External Sources Code Label Positive Edge triggered
// -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- 
#define AT91C_AIC_NFIQ        			( 0x1 		<<  0) 				// (AIC) NFIQ Status
#define AT91C_AIC_NIRQ        			( 0x1 		<<  1) 				// (AIC) NIRQ Status
// -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- 
#define AT91C_AIC_DCR_PROT    			( 0x1 		<<  0) 				// (AIC) Protection Mode
#define AT91C_AIC_DCR_GMSK    			( 0x1 		<<  1) 				// (AIC) General Mask


//------------------------------------------------------------------------------
//              SOFTWARE API DEFINITION  FOR Debug Unit
//------------------------------------------------------------------------------

// -------- DBGU_CR : (DBGU Offset: 0x0) Debug Unit Control Register -------- 
#define US_RSTRX        				( 0x1 		<<  2) 				// (DBGU) Reset Receiver
#define US_RSTTX        				( 0x1 		<<  3) 				// (DBGU) Reset Transmitter
#define US_RXEN         				( 0x1 		<<  4) 				// (DBGU) Receiver Enable
#define US_RXDIS        				( 0x1 		<<  5) 				// (DBGU) Receiver Disable
#define US_TXEN         				( 0x1 		<<  6) 				// (DBGU) Transmitter Enable
#define US_TXDIS        				( 0x1 		<<  7) 				// (DBGU) Transmitter Disable
#define US_RSTSTA       				( 0x1 		<<  8) 				// (DBGU) Reset Status Bits
// -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- 
#define US_PAR          				( 0x7 		<<  9) 				// (DBGU) Parity type
#define US_PAR_EVEN                 	( 0x0 		<<  9) 				// (DBGU) Even Parity
#define US_PAR_ODD                  	( 0x1 		<<  9) 				// (DBGU) Odd Parity
#define US_PAR_SPACE                	( 0x2 		<<  9) 				// (DBGU) Parity forced to 0 (Space)
#define US_PAR_MARK                 	( 0x3 		<<  9) 				// (DBGU) Parity forced to 1 (Mark)
#define US_PAR_NONE                 	( 0x4 		<<  9) 				// (DBGU) No Parity
#define US_PAR_MULTI_DROP           	( 0x6 		<<  9) 				// (DBGU) Multi-drop mode
#define US_CHMODE       				( 0x3 		<< 14) 				// (DBGU) Channel Mode
#define US_CHMODE_NORMAL               	( 0x0 		<< 14) 				// (DBGU) Normal Mode: The USART channel operates as an RX/TX USART.
#define US_CHMODE_AUTO                 	( 0x1 		<< 14) 				// (DBGU) Automatic Echo: Receiver Data Input is connected to the TXD pin.
#define US_CHMODE_LOCAL                	( 0x2 		<< 14) 				// (DBGU) Local Loopback: Transmitter Output Signal is connected to Receiver Input Signal.
#define US_CHMODE_REMOTE               	( 0x3 		<< 14) 				// (DBGU) Remote Loopback: RXD pin is internally connected to TXD pin.
// -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- 
#define US_RXRDY        				( 0x1 		<<  0) 				// (DBGU) RXRDY Interrupt
#define US_TXRDY        				( 0x1 		<<  1) 				// (DBGU) TXRDY Interrupt
#define US_ENDRX        				( 0x1 		<<  3) 				// (DBGU) End of Receive Transfer Interrupt
#define US_ENDTX        				( 0x1 		<<  4) 				// (DBGU) End of Transmit Interrupt
#define US_OVRE         				( 0x1 		<<  5) 				// (DBGU) Overrun Interrupt
#define US_FRAME        				( 0x1 		<<  6) 				// (DBGU) Framing Error Interrupt
#define US_PARE         				( 0x1 		<<  7) 				// (DBGU) Parity Error Interrupt
#define US_TXEMPTY      				( 0x1 		<<  9) 				// (DBGU) TXEMPTY Interrupt
#define US_TXBUFE       				( 0x1 		<< 11) 				// (DBGU) TXBUFE Interrupt
#define US_RXBUFF       				( 0x1 		<< 12) 				// (DBGU) RXBUFF Interrupt
#define US_COMM_TX      				( 0x1 		<< 30) 				// (DBGU) COMM_TX Interrupt
#define US_COMM_RX      				( 0x1 		<< 31) 				// (DBGU) COMM_RX Interrupt
// -------- DBGU_IDR : (DBGU Offset: 0xc) Debug Unit Interrupt Disable Register -------- 
// -------- DBGU_IMR : (DBGU Offset: 0x10) Debug Unit Interrupt Mask Register -------- 
// -------- DBGU_CSR : (DBGU Offset: 0x14) Debug Unit Channel Status Register -------- 
// -------- DBGU_FNTR : (DBGU Offset: 0x48) Debug Unit FORCE_NTRST Register -------- 
#define US_FORCE_NTRST  				( 0x1 		<<  0) 				// (DBGU) Force NTRST in JTAG

//------------------------------------------------------------------------------
//              SOFTWARE API DEFINITION  FOR Clock Generator Controler
//------------------------------------------------------------------------------
// -------- CKGR_MOR : (CKGR Offset: 0x0) Main Oscillator Register -------- 
#define CKGR_MOSCEN     				( 0x1 		<<  0) 				// (CKGR) Main Oscillator Enable
#define CKGR_OSCBYPASS  				( 0x1 		<<  1) 				// (CKGR) Main Oscillator Bypass
#define CKGR_OSCOUNT    				( 0xFF 		<<  8) 				// (CKGR) Main Oscillator Start-up Time
#define CKGR_OSCOUNT_VAL   				( 6 		<<  8) 				// (CKGR) Main Oscillator Start-up Time
// -------- CKGR_MCFR : (CKGR Offset: 0x4) Main Clock Frequency Register -------- 
#define CKGR_MAINF      				( 0xFFFF 	<<  0) 				// (CKGR) Main Clock Frequency
#define CKGR_MAINRDY    				( 0x1 		<< 16) 				// (CKGR) Main Clock Ready
// -------- CKGR_PLLR : (CKGR Offset: 0xc) PLL B Register -------- 
#define CKGR_DIV        				( 0xFF 		<<  0) 				// (CKGR) Divider Selected
#define CKGR_DIV_VAL     				( 5 		<<  0) 				// (CKGR) Divider Selected
#define CKGR_DIV_0      				( 0x0		<<  0) 				// (CKGR) Divider output is 0
#define CKGR_DIV_BYPASS 				( 0x1		<<  0) 				// (CKGR) Divider is bypassed
#define CKGR_PLLCOUNT   				( 0x3F 		<<  8) 				// (CKGR) PLL Counter
#define CKGR_PLLCOUNT_VAL  				( 28 		<<  8) 				// (CKGR) PLL Counter
#define CKGR_OUT        				( 0x3 		<< 14) 				// (CKGR) PLL Output Frequency Range
#define CKGR_OUT_0      				( 0x0 		<< 14) 				// (CKGR) Please refer to the PLL datasheet
#define CKGR_OUT_1      				( 0x1 		<< 14) 				// (CKGR) Please refer to the PLL datasheet
#define CKGR_OUT_2      				( 0x2 		<< 14) 				// (CKGR) Please refer to the PLL datasheet
#define CKGR_OUT_3      				( 0x3 		<< 14) 				// (CKGR) Please refer to the PLL datasheet
#define CKGR_MUL        				( 0x7FF 	<< 16) 				// (CKGR) PLL Multiplier
#define CKGR_MUL_VAL       				( 25 		<< 16) 				// (CKGR) PLL Multiplier
#define CKGR_USBDIV     				( 0x3 		<< 28) 				// (CKGR) Divider for USB Clocks
#define CKGR_USBDIV_0   				( 0x0 		<< 28) 				// (CKGR) Divider output is PLL clock output
#define CKGR_USBDIV_1   				( 0x1 		<< 28) 				// (CKGR) Divider output is PLL clock output divided by 2
#define CKGR_USBDIV_2   				( 0x2 		<< 28) 				// (CKGR) Divider output is PLL clock output divided by 4

//------------------------------------------------------------------------------
//              SOFTWARE API DEFINITION  FOR Power Management Controler
//------------------------------------------------------------------------------

// -------- PMC_SCER : (PMC Offset: 0x0) System Clock Enable Register -------- 
#define PMC_PCK         				( 0x1 		<<  0) 				// (PMC) Processor Clock
#define PMC_UDP         				( 0x1 		<<  7) 				// (PMC) USB Device Port Clock
#define PMC_PCK0        				( 0x1 		<<  8) 				// (PMC) Programmable Clock Output
#define PMC_PCK1        				( 0x1 		<<  9) 				// (PMC) Programmable Clock Output
#define PMC_PCK2        				( 0x1 		<< 10) 				// (PMC) Programmable Clock Output
// -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- 
// -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- 
// -------- CKGR_MOR : (PMC Offset: 0x20) Main Oscillator Register -------- 
// -------- CKGR_MCFR : (PMC Offset: 0x24) Main Clock Frequency Register -------- 
// -------- CKGR_PLLR : (PMC Offset: 0x2c) PLL B Register -------- 
// -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- 
#define PMC_CSS         				( 0x3 		<<  0) 				// (PMC) Programmable Clock Selection
#define PMC_CSS_SLOW_CLK             	( 0x0 		<<  0) 				// (PMC) Slow Clock is selected
#define PMC_CSS_MAIN_CLK             	( 0x1 		<<  0) 				// (PMC) Main Clock is selected
#define PMC_CSS_PLL_CLK              	( 0x3 		<<  0) 				// (PMC) Clock from PLL is selected
#define PMC_PRES        				( 0x7 		<<  2) 				// (PMC) Programmable Clock Prescaler
#define PMC_PRES_CLK                  	( 0x0 		<<  2) 				// (PMC) Selected clock
#define PMC_PRES_CLK_2                	( 0x1 		<<  2) 				// (PMC) Selected clock divided by 2
#define PMC_PRES_CLK_4                	( 0x2 		<<  2) 				// (PMC) Selected clock divided by 4
#define PMC_PRES_CLK_8                	( 0x3 		<<  2) 				// (PMC) Selected clock divided by 8
#define PMC_PRES_CLK_16               	( 0x4 		<<  2) 				// (PMC) Selected clock divided by 16
#define PMC_PRES_CLK_32               	( 0x5 		<<  2) 				// (PMC) Selected clock divided by 32
#define PMC_PRES_CLK_64               	( 0x6 		<<  2) 				// (PMC) Selected clock divided by 64
// -------- PMC_PCKR : (PMC Offset: 0x40) Programmable Clock Register -------- 
// -------- PMC_IER : (PMC Offset: 0x60) PMC Interrupt Enable Register -------- 
#define PMC_MOSCS       				( 0x1 		<<  0) 				// (PMC) MOSC Status/Enable/Disable/Mask
#define PMC_LOCK        				( 0x1 		<<  2) 				// (PMC) PLL Status/Enable/Disable/Mask
#define PMC_MCKRDY      				( 0x1 		<<  3) 				// (PMC) MCK_RDY Status/Enable/Disable/Mask
#define PMC_PCK0RDY     				( 0x1 		<<  8) 				// (PMC) PCK0_RDY Status/Enable/Disable/Mask
#define PMC_PCK1RDY     				( 0x1 		<<  9) 				// (PMC) PCK1_RDY Status/Enable/Disable/Mask
#define PMC_PCK2RDY     				( 0x1 		<< 10) 				// (PMC) PCK2_RDY Status/Enable/Disable/Mask
// -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- 
// -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- 
// -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- 

//------------------------------------------------------------------------------
//              SOFTWARE API DEFINITION  FOR Voltage Regulator Mode Controller Interface
//------------------------------------------------------------------------------

// -------- VREG_MR : (VREG Offset: 0x0) Voltage Regulator Mode Register -------- 
#define VREG_PSTDBY     				( 0x1 		<<  0) 				// (VREG) Voltage Regulator Power Standby Mode

//------------------------------------------------------------------------------
//              SOFTWARE API DEFINITION  FOR Memory Controller Interface
//------------------------------------------------------------------------------

// -------- MC_RCR : (MC Offset: 0x0) MC Remap Control Register -------- 
#define MC_RCB          				( 0x1 		<<  0) 				// (MC) Remap Command Bit
// -------- MC_ASR : (MC Offset: 0x4) MC Abort Status Register -------- 
#define MC_UNDADD       				( 0x1 		<<  0) 				// (MC) Undefined Addess Abort Status
#define MC_MISADD       				( 0x1 		<<  1) 				// (MC) Misaligned Addess Abort Status
#define MC_ABTSZ        				( 0x3 		<<  8) 				// (MC) Abort Size Status
#define MC_ABTSZ_BYTE                 	( 0x0 		<<  8) 				// (MC) Byte
#define MC_ABTSZ_HWORD                	( 0x1 		<<  8) 				// (MC) Half-word
#define MC_ABTSZ_WORD                 	( 0x2 		<<  8) 				// (MC) Word
#define MC_ABTTYP       				( 0x3 		<< 10) 				// (MC) Abort Type Status
#define MC_ABTTYP_DATAR               	( 0x0 		<< 10) 				// (MC) Data Read
#define MC_ABTTYP_DATAW               	( 0x1 		<< 10) 				// (MC) Data Write
#define MC_ABTTYP_FETCH               	( 0x2 		<< 10) 				// (MC) Code Fetch
#define MC_MST0         				( 0x1 		<< 16) 				// (MC) Master 0 Abort Source
#define MC_MST1         				( 0x1 		<< 17) 				// (MC) Master 1 Abort Source
#define MC_SVMST0       				( 0x1 		<< 24) 				// (MC) Saved Master 0 Abort Source
#define MC_SVMST1       				( 0x1 		<< 25) 				// (MC) Saved Master 1 Abort Source
// -------- MC_FMR : (MC Offset: 0x60) MC Flash Mode Register -------- 
#define MC_FRDY         				( 0x1 		<<  0) 				// (MC) Flash Ready Interrupt Enable
#define MC_LOCKE        				( 0x1 		<<  2) 				// (MC) Lock Error Interrupt Enable
#define MC_PROGE        				( 0x1 		<<  3) 				// (MC) Programming Error Interrupt Enable
#define MC_NEBP         				( 0x1 		<<  7) 				// (MC) No Erase Before Programming
#define MC_FWS          				( 0x3 		<<  8) 				// (MC) Flash Wait State
#define MC_FWS_0FWS                 	( 0x0 		<<  8) 				// (MC) 1 cycle for Read, 2 for Write operations
#define MC_FWS_1FWS                 	( 0x1 		<<  8) 				// (MC) 2 cycles for Read, 3 for Write operations
#define MC_FWS_2FWS                 	( 0x2 		<<  8) 				// (MC) 3 cycles for Read, 4 for Write operations
#define MC_FWS_3FWS                 	( 0x3 		<<  8) 				// (MC) 4 cycles for Read, 4 for Write operations
#define MC_FMCN         				( 0xFF 		<< 16) 				// (MC) Flash Microsecond Cycle Number
#define MC_FMCN_VAL        				( 46 		<< 16) 				// (MC) Flash Microsecond Cycle Number
#define MC_FMCN_VAL72      				( 72 		<< 16) 				// (MC) Flash Microsecond Cycle Number
// -------- MC_FCR : (MC Offset: 0x64) MC Flash Command Register -------- 
#define MC_FCMD         				( 0xF		<<  0) 				// (MC) Flash Command
#define MC_FCMD_START_PROG           	( 0x1		<<  0) 				// (MC) Starts the programming of the page specified by PAGEN.
#define MC_FCMD_LOCK                 	( 0x2		<<  0) 				// (MC) Starts a lock sequence of the sector defined by the bits 4 to 7 of the field PAGEN.
#define MC_FCMD_PROG_AND_LOCK        	( 0x3		<<  0) 				// (MC) The lock sequence automatically happens after the programming sequence is completed.
#define MC_FCMD_UNLOCK               	( 0x4		<<  0) 				// (MC) Starts an unlock sequence of the sector defined by the bits 4 to 7 of the field PAGEN.
#define MC_FCMD_ERASE_ALL            	( 0x8		<<  0) 				// (MC) Starts the erase of the entire flash.If at least a page is locked, the command is cancelled.
#define MC_FCMD_SET_GP_NVM           	( 0xB		<<  0) 				// (MC) Set General Purpose NVM bits.
#define MC_FCMD_CLR_GP_NVM           	( 0xD		<<  0) 				// (MC) Clear General Purpose NVM bits.
#define MC_FCMD_SET_SECURITY         	( 0xF		<<  0) 				// (MC) Set Security Bit.
#define MC_PAGEN        				( 0x3FF 	<<  8) 				// (MC) Page Number
#define MC_KEY          				( 0xFF 		<< 24) 				// (MC) Writing Protect Key
// -------- MC_FSR : (MC Offset: 0x68) MC Flash Command Register -------- 
//MC_FMR 공통으로 사용
//#define MC_FRDY         				( 0x1 		<<  0) 				// (MC) Flash Ready
//#define MC_LOCKE        				( 0x1 		<<  2) 				// (MC) Lock Error
//#define MC_PROGE        				( 0x1 		<<  3) 				// (MC) Programming Error
#define MC_SECURITY     				( 0x1 		<<  4) 				// (MC) Security Bit Status
#define MC_GPNVM0       				( 0x1 		<<  8) 				// (MC) Sector 0 Lock Status
#define MC_GPNVM1       				( 0x1 		<<  9) 				// (MC) Sector 1 Lock Status
#define MC_GPNVM2       				( 0x1 		<< 10) 				// (MC) Sector 2 Lock Status
#define MC_GPNVM3       				( 0x1 		<< 11) 				// (MC) Sector 3 Lock Status
#define MC_GPNVM4       				( 0x1 		<< 12) 				// (MC) Sector 4 Lock Status
#define MC_GPNVM5       				( 0x1 		<< 13) 				// (MC) Sector 5 Lock Status
#define MC_GPNVM6       				( 0x1 		<< 14) 				// (MC) Sector 6 Lock Status
#define MC_GPNVM7       				( 0x1 		<< 15) 				// (MC) Sector 7 Lock Status
#define MC_LOCKS0       				( 0x1 		<< 16) 				// (MC) Sector 0 Lock Status
#define MC_LOCKS1       				( 0x1 		<< 17) 				// (MC) Sector 1 Lock Status
#define MC_LOCKS2       				( 0x1 		<< 18) 				// (MC) Sector 2 Lock Status
#define MC_LOCKS3       				( 0x1 		<< 19) 				// (MC) Sector 3 Lock Status
#define MC_LOCKS4       				( 0x1 		<< 20) 				// (MC) Sector 4 Lock Status
#define MC_LOCKS5       				( 0x1 		<< 21) 				// (MC) Sector 5 Lock Status
#define MC_LOCKS6       				( 0x1 		<< 22) 				// (MC) Sector 6 Lock Status
#define MC_LOCKS7       				( 0x1 		<< 23) 				// (MC) Sector 7 Lock Status
#define MC_LOCKS8       				( 0x1 		<< 24) 				// (MC) Sector 8 Lock Status
#define MC_LOCKS9       				( 0x1 		<< 25) 				// (MC) Sector 9 Lock Status
#define MC_LOCKS10      				( 0x1 		<< 26) 				// (MC) Sector 10 Lock Status
#define MC_LOCKS11      				( 0x1 		<< 27) 				// (MC) Sector 11 Lock Status
#define MC_LOCKS12      				( 0x1 		<< 28) 				// (MC) Sector 12 Lock Status
#define MC_LOCKS13      				( 0x1 		<< 29) 				// (MC) Sector 13 Lock Status
#define MC_LOCKS14      				( 0x1 		<< 30) 				// (MC) Sector 14 Lock Status
#define MC_LOCKS15      				( 0x1 		<< 31) 				// (MC) Sector 15 Lock Status

//------------------------------------------------------------------------------
//              SOFTWARE API DEFINITION  FOR Analog to Digital Convertor
//------------------------------------------------------------------------------

// -------- ADC_CR : (ADC Offset: 0x0) ADC Control Register -------- 
#define ADC_SWRST       				( 0x1 		<<  0) 				// (ADC) Software Reset
#define ADC_START       				( 0x1 		<<  1) 				// (ADC) Start Conversion
// -------- ADC_MR : (ADC Offset: 0x4) ADC Mode Register -------- 
#define ADC_TRGEN       				( 0x1 		<<  0) 				// (ADC) Trigger Enable
#define ADC_TRGEN_DIS   				( 0x0		<<  0) 				// (ADC) Hradware triggers are disabled. Starting a conversion is only possible by software
#define ADC_TRGEN_EN    				( 0x1		<<  0) 				// (ADC) Hardware trigger selected by TRGSEL field is enabled.
#define ADC_TRGSEL      				( 0x7 		<<  1) 				// (ADC) Trigger Selection
#define ADC_TRGSEL_TIOA0                ( 0x0 		<<  1) 				// (ADC) Selected TRGSEL = TIAO0
#define ADC_TRGSEL_TIOA1                ( 0x1 		<<  1) 				// (ADC) Selected TRGSEL = TIAO1
#define ADC_TRGSEL_TIOA2                ( 0x2 		<<  1) 				// (ADC) Selected TRGSEL = TIAO2
#define ADC_TRGSEL_TIOA3                ( 0x3 		<<  1) 				// (ADC) Selected TRGSEL = TIAO3
#define ADC_TRGSEL_TIOA4                ( 0x4 		<<  1) 				// (ADC) Selected TRGSEL = TIAO4
#define ADC_TRGSEL_TIOA5                ( 0x5 		<<  1) 				// (ADC) Selected TRGSEL = TIAO5
#define ADC_TRGSEL_EXT                  ( 0x6 		<<  1) 				// (ADC) Selected TRGSEL = External Trigger
#define ADC_LOWRES      				( 0x1 		<<  4) 				// (ADC) Resolution.
#define ADC_LOWRES_10_BIT               ( 0x0 		<<  4) 				// (ADC) 10-bit resolution
#define ADC_LOWRES_8_BIT                ( 0x1 		<<  4) 				// (ADC) 8-bit resolution
#define ADC_SLEEP       				( 0x1 		<<  5) 				// (ADC) Sleep Mode
#define ADC_SLEEP_NORMAL_MODE          	( 0x0 		<<  5) 				// (ADC) Normal Mode
#define ADC_SLEEP_MODE                 	( 0x1 		<<  5) 				// (ADC) Sleep Mode
#define ADC_PRESCAL     				( 0x3F 		<<  8) 				// (ADC) Prescaler rate selection
#define ADC_STARTUP     				( 0x1F 		<< 16) 				// (ADC) Startup Time
#define ADC_SHTIM       				( 0xF 		<< 24) 				// (ADC) Sample & Hold Time
// -------- 	ADC_CHER : (ADC Offset: 0x10) ADC Channel Enable Register -------- 
#define ADC_CH0         				( 0x1 		<<  0) 				// (ADC) Channel 0
#define ADC_CH1         				( 0x1 		<<  1) 				// (ADC) Channel 1
#define ADC_CH2         				( 0x1 		<<  2) 				// (ADC) Channel 2
#define ADC_CH3         				( 0x1 		<<  3) 				// (ADC) Channel 3
#define ADC_CH4         				( 0x1 		<<  4) 				// (ADC) Channel 4
#define ADC_CH5         				( 0x1 		<<  5) 				// (ADC) Channel 5
#define ADC_CH6         				( 0x1 		<<  6) 				// (ADC) Channel 6
#define ADC_CH7         				( 0x1 		<<  7) 				// (ADC) Channel 7
// -------- 	ADC_CHDR : (ADC Offset: 0x14) ADC Channel Disable Register -------- 
// -------- 	ADC_CHSR : (ADC Offset: 0x18) ADC Channel Status Register -------- 
// -------- ADC_SR : (ADC Offset: 0x1c) ADC Status Register -------- 
#define ADC_EOC0        				( 0x1 		<<  0) 				// (ADC) End of Conversion
#define ADC_EOC1        				( 0x1 		<<  1) 				// (ADC) End of Conversion
#define ADC_EOC2        				( 0x1 		<<  2) 				// (ADC) End of Conversion
#define ADC_EOC3        				( 0x1 		<<  3) 				// (ADC) End of Conversion
#define ADC_EOC4        				( 0x1 		<<  4) 				// (ADC) End of Conversion
#define ADC_EOC5        				( 0x1 		<<  5) 				// (ADC) End of Conversion
#define ADC_EOC6        				( 0x1 		<<  6) 				// (ADC) End of Conversion
#define ADC_EOC7        				( 0x1 		<<  7) 				// (ADC) End of Conversion
#define ADC_OVRE0       				( 0x1 		<<  8) 				// (ADC) Overrun Error
#define ADC_OVRE1       				( 0x1 		<<  9) 				// (ADC) Overrun Error
#define ADC_OVRE2       				( 0x1 		<< 10) 				// (ADC) Overrun Error
#define ADC_OVRE3       				( 0x1 		<< 11) 				// (ADC) Overrun Error
#define ADC_OVRE4       				( 0x1 		<< 12) 				// (ADC) Overrun Error
#define ADC_OVRE5       				( 0x1 		<< 13) 				// (ADC) Overrun Error
#define ADC_OVRE6       				( 0x1 		<< 14) 				// (ADC) Overrun Error
#define ADC_OVRE7       				( 0x1 		<< 15) 				// (ADC) Overrun Error
#define ADC_DRDY        				( 0x1 		<< 16) 				// (ADC) Data Ready
#define ADC_GOVRE       				( 0x1 		<< 17) 				// (ADC) General Overrun
#define ADC_ENDRX       				( 0x1 		<< 18) 				// (ADC) End of Receiver Transfer
#define ADC_RXBUFF      				( 0x1 		<< 19) 				// (ADC) RXBUFF Interrupt
// -------- ADC_LCDR : (ADC Offset: 0x20) ADC Last Converted Data Register -------- 
#define ADC_LDATA       				( 0x3FF 	<<  0) 				// (ADC) Last Data Converted
// -------- ADC_IER : (ADC Offset: 0x24) ADC Interrupt Enable Register -------- 
// -------- ADC_IDR : (ADC Offset: 0x28) ADC Interrupt Disable Register -------- 
// -------- ADC_IMR : (ADC Offset: 0x2c) ADC Interrupt Mask Register -------- 
// -------- ADC_CDR0 : (ADC Offset: 0x30) ADC Channel Data Register 0 -------- 
#define AT91C_ADC_DATA        			( 0x3FF 	<<  0) 				// (ADC) Converted Data
// -------- ADC_CDR1 : (ADC Offset: 0x34) ADC Channel Data Register 1 -------- 
// -------- ADC_CDR2 : (ADC Offset: 0x38) ADC Channel Data Register 2 -------- 
// -------- ADC_CDR3 : (ADC Offset: 0x3c) ADC Channel Data Register 3 -------- 
// -------- ADC_CDR4 : (ADC Offset: 0x40) ADC Channel Data Register 4 -------- 
// -------- ADC_CDR5 : (ADC Offset: 0x44) ADC Channel Data Register 5 -------- 
// -------- ADC_CDR6 : (ADC Offset: 0x48) ADC Channel Data Register 6 -------- 
// -------- ADC_CDR7 : (ADC Offset: 0x4c) ADC Channel Data Register 7 -------- 

//------------------------------------------------------------------------------
//              SOFTWARE API DEFINITION  FOR Synchronous Serial Controller Interface
//------------------------------------------------------------------------------

// -------- SSC_CR : (SSC Offset: 0x0) SSC Control Register -------- 
#define SSC_RXEN        				( 0x1 		<<  0) 				// (SSC) Receive Enable
#define SSC_RXDIS       				( 0x1 		<<  1) 				// (SSC) Receive Disable
#define SSC_TXEN        				( 0x1 		<<  8) 				// (SSC) Transmit Enable
#define SSC_TXDIS       				( 0x1 		<<  9) 				// (SSC) Transmit Disable
#define SSC_SWRST       				( 0x1 		<< 15) 				// (SSC) Software Reset
// -------- SSC_RCMR : (SSC Offset: 0x10) SSC Receive Clock Mode Register -------- 
#define SSC_CKS         				( 0x3 		<<  0) 				// (SSC) Receive/Transmit Clock Selection
#define SSC_CKS_DIV                  	( 0x0 		<<  0) 				// (SSC) Divided Clock
#define SSC_CKS_TK                   	( 0x1 		<<  0) 				// (SSC) TK Clock signal
#define SSC_CKS_RK                   	( 0x2 		<<  0) 				// (SSC) RK pin
#define SSC_CKO         				( 0x7 		<<  2) 				// (SSC) Receive/Transmit Clock Output Mode Selection
#define SSC_CKO_NONE                 	( 0x0 		<<  2) 				// (SSC) Receive/Transmit Clock Output Mode: None RK pin: Input-only
#define SSC_CKO_CONTINOUS            	( 0x1 		<<  2) 				// (SSC) Continuous Receive/Transmit Clock RK pin: Output
#define SSC_CKO_DATA_TX              	( 0x2 		<<  2) 				// (SSC) Receive/Transmit Clock only during data transfers RK pin: Output
#define SSC_CKI         				( 0x1 		<<  5) 				// (SSC) Receive/Transmit Clock Inversion
#define SSC_START       				( 0xF 		<<  8) 				// (SSC) Receive/Transmit Start Selection
#define SSC_START_CONTINOUS            	( 0x0 		<<  8) 				// (SSC) Continuous, as soon as the receiver is enabled, and immediately after the end of transfer of the previous data.
#define SSC_START_TX                   	( 0x1 		<<  8) 				// (SSC) Transmit/Receive start
#define SSC_START_LOW_RF               	( 0x2 		<<  8) 				// (SSC) Detection of a low level on RF input
#define SSC_START_HIGH_RF              	( 0x3 		<<  8) 				// (SSC) Detection of a high level on RF input
#define SSC_START_FALL_RF              	( 0x4 		<<  8) 				// (SSC) Detection of a falling edge on RF input
#define SSC_START_RISE_RF              	( 0x5 		<<  8) 				// (SSC) Detection of a rising edge on RF input
#define SSC_START_LEVEL_RF             	( 0x6 		<<  8) 				// (SSC) Detection of any level change on RF input
#define SSC_START_EDGE_RF              	( 0x7 		<<  8) 				// (SSC) Detection of any edge on RF input
#define SSC_START_0                    	( 0x8 		<<  8) 				// (SSC) Compare 0
#define SSC_STTDLY      				( 0xFF 		<< 16) 				// (SSC) Receive/Transmit Start Delay
#define SSC_PERIOD      				( 0xFF 		<< 24) 				// (SSC) Receive/Transmit Period Divider Selection
// -------- SSC_RFMR : (SSC Offset: 0x14) SSC Receive Frame Mode Register -------- 
#define SSC_DATLEN      				( 0x1F 		<<  0) 				// (SSC) Data Length
#define SSC_LOOP        				( 0x1 		<<  5) 				// (SSC) Loop Mode
#define SSC_MSBF        				( 0x1 		<<  7) 				// (SSC) Most Significant Bit First
#define SSC_DATNB       				( 0xF 		<<  8) 				// (SSC) Data Number per Frame
#define SSC_FSLEN       				( 0xF 		<< 16) 				// (SSC) Receive/Transmit Frame Sync length
#define SSC_FSOS        				( 0x7 		<< 20) 				// (SSC) Receive/Transmit Frame Sync Output Selection
#define SSC_FSOS_NONE                 	( 0x0 		<< 20) 				// (SSC) Selected Receive/Transmit Frame Sync Signal: None RK pin Input-only
#define SSC_FSOS_NEGATIVE             	( 0x1 		<< 20) 				// (SSC) Selected Receive/Transmit Frame Sync Signal: Negative Pulse
#define SSC_FSOS_POSITIVE             	( 0x2 		<< 20) 				// (SSC) Selected Receive/Transmit Frame Sync Signal: Positive Pulse
#define SSC_FSOS_LOW                  	( 0x3 		<< 20) 				// (SSC) Selected Receive/Transmit Frame Sync Signal: Driver Low during data transfer
#define SSC_FSOS_HIGH                 	( 0x4 		<< 20) 				// (SSC) Selected Receive/Transmit Frame Sync Signal: Driver High during data transfer
#define SSC_FSOS_TOGGLE               	( 0x5 		<< 20) 				// (SSC) Selected Receive/Transmit Frame Sync Signal: Toggling at each start of data transfer
#define SSC_FSEDGE      				( 0x1 		<< 24) 				// (SSC) Frame Sync Edge Detection
// -------- SSC_TCMR : (SSC Offset: 0x18) SSC Transmit Clock Mode Register -------- 
// -------- SSC_TFMR : (SSC Offset: 0x1c) SSC Transmit Frame Mode Register -------- 
#define SSC_DATDEF      				( 0x1 		<<  5) 				// (SSC) Data Default Value
#define SSC_FSDEN       				( 0x1 		<< 23) 				// (SSC) Frame Sync Data Enable
// -------- SSC_SR : (SSC Offset: 0x40) SSC Status Register -------- 
#define SSC_TXRDY       				( 0x1 		<<  0) 				// (SSC) Transmit Ready
#define SSC_TXEMPTY     				( 0x1 		<<  1) 				// (SSC) Transmit Empty
#define SSC_ENDTX       				( 0x1 		<<  2) 				// (SSC) End Of Transmission
#define SSC_TXBUFE      				( 0x1 		<<  3) 				// (SSC) Transmit Buffer Empty
#define SSC_RXRDY       				( 0x1 		<<  4) 				// (SSC) Receive Ready
#define SSC_OVRUN       				( 0x1 		<<  5) 				// (SSC) Receive Overrun
#define SSC_ENDRX       				( 0x1 		<<  6) 				// (SSC) End of Reception
#define SSC_RXBUFF      				( 0x1 		<<  7) 				// (SSC) Receive Buffer Full
#define SSC_TXSYN       				( 0x1 		<< 10) 				// (SSC) Transmit Sync
#define SSC_RXSYN       				( 0x1 		<< 11) 				// (SSC) Receive Sync
#define SSC_TXENA       				( 0x1 		<< 16) 				// (SSC) Transmit Enable
#define SSC_RXENA       				( 0x1 		<< 17) 				// (SSC) Receive Enable
// -------- SSC_IER : (SSC Offset: 0x44) SSC Interrupt Enable Register -------- 
// -------- SSC_IDR : (SSC Offset: 0x48) SSC Interrupt Disable Register -------- 
// -------- SSC_IMR : (SSC Offset: 0x4c) SSC Interrupt Mask Register -------- 

//------------------------------------------------------------------------------
//              SOFTWARE API DEFINITION  FOR Usart
//------------------------------------------------------------------------------

// -------- US_CR : (USART Offset: 0x0) Debug Unit Control Register -------- 
#define US_STTBRK       				( 0x1 		<<  9) 				// (USART) Start Break
#define US_STPBRK       				( 0x1 		<< 10) 				// (USART) Stop Break
#define US_STTTO        				( 0x1 		<< 11) 				// (USART) Start Time-out
#define US_SENDA        				( 0x1 		<< 12) 				// (USART) Send Address
#define US_RSTIT        				( 0x1 		<< 13) 				// (USART) Reset Iterations
#define US_RSTNACK      				( 0x1 		<< 14) 				// (USART) Reset Non Acknowledge
#define US_RETTO        				( 0x1 		<< 15) 				// (USART) Rearm Time-out
#define US_DTREN        				( 0x1 		<< 16) 				// (USART) Data Terminal ready Enable
#define US_DTRDIS       				( 0x1 		<< 17) 				// (USART) Data Terminal ready Disable
#define US_RTSEN        				( 0x1 		<< 18) 				// (USART) Request to Send enable
#define US_RTSDIS       				( 0x1 		<< 19) 				// (USART) Request to Send Disable
// -------- US_MR : (USART Offset: 0x4) Debug Unit Mode Register -------- 
#define US_USMODE       				( 0xF 		<<  0) 				// (USART) Usart mode
#define US_USMODE_NORMAL               	( 0x0 		<<  0) 				// (USART) Normal
#define US_USMODE_RS485                	( 0x1 		<<  0) 				// (USART) RS485
#define US_USMODE_HWHSH                	( 0x2 		<<  0) 				// (USART) Hardware Handshaking
#define US_USMODE_MODEM                	( 0x3 		<<  0) 				// (USART) Modem
#define US_USMODE_ISO7816_0            	( 0x4 		<<  0) 				// (USART) ISO7816 protocol: T = 0
#define US_USMODE_ISO7816_1            	( 0x6 		<<  0) 				// (USART) ISO7816 protocol: T = 1
#define US_USMODE_IRDA                 	( 0x8 		<<  0) 				// (USART) IrDA
#define US_USMODE_SWHSH                	( 0xC 		<<  0) 				// (USART) Software Handshaking
#define US_CLKS         				( 0x3 		<<  4) 				// (USART) Clock Selection (Baud Rate generator Input Clock
#define US_CLKS_CLOCK                	( 0x0 		<<  4) 				// (USART) Clock
#define US_CLKS_FDIV1                	( 0x1 		<<  4) 				// (USART) fdiv1
#define US_CLKS_SLOW                 	( 0x2 		<<  4) 				// (USART) slow_clock (ARM)
#define US_CLKS_EXT                  	( 0x3 		<<  4) 				// (USART) External (SCK)
#define US_CHRL         				( 0x3 		<<  6) 				// (USART) Clock Selection (Baud Rate generator Input Clock
#define US_CHRL_5_BITS               	( 0x0 		<<  6) 				// (USART) Character Length: 5 bits
#define US_CHRL_6_BITS               	( 0x1 		<<  6) 				// (USART) Character Length: 6 bits
#define US_CHRL_7_BITS               	( 0x2 		<<  6) 				// (USART) Character Length: 7 bits
#define US_CHRL_8_BITS               	( 0x3 		<<  6) 				// (USART) Character Length: 8 bits
#define US_SYNC         				( 0x1 		<<  8) 				// (USART) Synchronous Mode Select
#define US_NBSTOP       				( 0x3 		<< 12) 				// (USART) Number of Stop bits
#define US_NBSTOP_1_BIT                	( 0x0 		<< 12) 				// (USART) 1 stop bit
#define US_NBSTOP_15_BIT               	( 0x1 		<< 12) 				// (USART) Asynchronous (SYNC=0) 2 stop bits Synchronous (SYNC=1) 2 stop bits
#define US_NBSTOP_2_BIT                	( 0x2 		<< 12) 				// (USART) 2 stop bits
#define US_MSBF         				( 0x1 		<< 16) 				// (USART) Bit Order
#define US_MODE9        				( 0x1 		<< 17) 				// (USART) 9-bit Character length
#define US_CKLO         				( 0x1 		<< 18) 				// (USART) Clock Output Select
#define US_OVER         				( 0x1 		<< 19) 				// (USART) Over Sampling Mode
#define US_INACK        				( 0x1 		<< 20) 				// (USART) Inhibit Non Acknowledge
#define US_DSNACK       				( 0x1 		<< 21) 				// (USART) Disable Successive NACK
#define US_MAX_ITER     				( 0x1 		<< 24) 				// (USART) Number of Repetitions
#define US_FILTER       				( 0x1 		<< 28) 				// (USART) Receive Line Filter
// -------- US_IER : (USART Offset: 0x8) Debug Unit Interrupt Enable Register -------- 
#define US_RXBRK        				( 0x1 		<<  2) 				// (USART) Break Received/End of Break
#define US_TIMEOUT      				( 0x1 		<<  8) 				// (USART) Receiver Time-out
#define US_ITERATION    				( 0x1 		<< 10) 				// (USART) Max number of Repetitions Reached
#define US_NACK         				( 0x1 		<< 13) 				// (USART) Non Acknowledge
#define US_RIIC         				( 0x1 		<< 16) 				// (USART) Ring INdicator Input Change Flag
#define US_DSRIC        				( 0x1 		<< 17) 				// (USART) Data Set Ready Input Change Flag
#define US_DCDIC        				( 0x1 		<< 18) 				// (USART) Data Carrier Flag
#define US_CTSIC        				( 0x1 		<< 19) 				// (USART) Clear To Send Input Change Flag
// -------- US_IDR : (USART Offset: 0xc) Debug Unit Interrupt Disable Register -------- 
// -------- US_IMR : (USART Offset: 0x10) Debug Unit Interrupt Mask Register -------- 
// -------- US_CSR : (USART Offset: 0x14) Debug Unit Channel Status Register -------- 
#define US_RI           				( 0x1 		<< 20) 				// (USART) Image of RI Input
#define US_DSR          				( 0x1 		<< 21) 				// (USART) Image of DSR Input
#define US_DCD          				( 0x1 		<< 22) 				// (USART) Image of DCD Input
#define US_CTS          				( 0x1 		<< 23) 				// (USART) Image of CTS Input

//------------------------------------------------------------------------------
//              SOFTWARE API DEFINITION  FOR Timer Counter Channel Interface
//------------------------------------------------------------------------------

// -------- TC_CCR : (TC Offset: 0x0) TC Channel Control Register -------- 
#define TC_CLKEN        				( 0x1 		<<  0) 				// (TC) Counter Clock Enable Command
#define TC_CLKDIS       				( 0x1 		<<  1) 				// (TC) Counter Clock Disable Command
#define TC_SWTRG        				( 0x1 		<<  2) 				// (TC) Software Trigger Command
// -------- TC_CMR : (TC Offset: 0x4) TC Channel Mode Register: Capture Mode / Waveform Mode -------- 
#define TC_CLKS         				( 0x7 		<<  0) 				// (TC) Clock Selection
#define TC_CLKS_TIMER_DIV1_CLOCK     	( 0x0 		<<  0) 				// (TC) Clock selected: TIMER_DIV1_CLOCK
#define TC_CLKS_TIMER_DIV2_CLOCK     	( 0x1 		<<  0) 				// (TC) Clock selected: TIMER_DIV2_CLOCK
#define TC_CLKS_TIMER_DIV3_CLOCK     	( 0x2 		<<  0) 				// (TC) Clock selected: TIMER_DIV3_CLOCK
#define TC_CLKS_TIMER_DIV4_CLOCK     	( 0x3 		<<  0) 				// (TC) Clock selected: TIMER_DIV4_CLOCK
#define TC_CLKS_TIMER_DIV5_CLOCK     	( 0x4 		<<  0) 				// (TC) Clock selected: TIMER_DIV5_CLOCK
#define TC_CLKS_XC0                  	( 0x5 		<<  0) 				// (TC) Clock selected: XC0
#define TC_CLKS_XC1                  	( 0x6 		<<  0) 				// (TC) Clock selected: XC1
#define TC_CLKS_XC2                  	( 0x7 		<<  0) 				// (TC) Clock selected: XC2
#define TC_CLKI         				( 0x1 		<<  3) 				// (TC) Clock Invert
#define TC_BURST        				( 0x3 		<<  4) 				// (TC) Burst Signal Selection
#define TC_BURST_NONE                 	( 0x0 		<<  4) 				// (TC) The clock is not gated by an external signal
#define TC_BURST_XC0                  	( 0x1 		<<  4) 				// (TC) XC0 is ANDed with the selected clock
#define TC_BURST_XC1                  	( 0x2 		<<  4) 				// (TC) XC1 is ANDed with the selected clock
#define TC_BURST_XC2                  	( 0x3 		<<  4) 				// (TC) XC2 is ANDed with the selected clock
#define TC_CPCSTOP      				( 0x1 		<<  6) 				// (TC) Counter Clock Stopped with RC Compare
#define TC_LDBSTOP      				( 0x1 		<<  6) 				// (TC) Counter Clock Stopped with RB Loading
#define TC_CPCDIS       				( 0x1 		<<  7) 				// (TC) Counter Clock Disable with RC Compare
#define TC_LDBDIS       				( 0x1 		<<  7) 				// (TC) Counter Clock Disabled with RB Loading
#define TC_ETRGEDG      				( 0x3 		<<  8) 				// (TC) External Trigger Edge Selection
#define TC_ETRGEDG_NONE                 ( 0x0 		<<  8) 				// (TC) Edge: None
#define TC_ETRGEDG_RISING               ( 0x1 		<<  8) 				// (TC) Edge: rising edge
#define TC_ETRGEDG_FALLING              ( 0x2 		<<  8) 				// (TC) Edge: falling edge
#define TC_ETRGEDG_BOTH                 ( 0x3 		<<  8) 				// (TC) Edge: each edge
#define TC_EEVTEDG      				( 0x3 		<<  8) 				// (TC) External Event Edge Selection
#define TC_EEVTEDG_NONE                 ( 0x0 		<<  8) 				// (TC) Edge: None
#define TC_EEVTEDG_RISING               ( 0x1 		<<  8) 				// (TC) Edge: rising edge
#define TC_EEVTEDG_FALLING              ( 0x2 		<<  8) 				// (TC) Edge: falling edge
#define TC_EEVTEDG_BOTH                 ( 0x3 		<<  8) 				// (TC) Edge: each edge
#define TC_EEVT         				( 0x3 		<< 10) 				// (TC) External Event  Selection
#define TC_EEVT_TIOB                 	( 0x0 		<< 10) 				// (TC) Signal selected as external event: TIOB TIOB direction: input
#define TC_EEVT_XC0                  	( 0x1 		<< 10) 				// (TC) Signal selected as external event: XC0 TIOB direction: output
#define TC_EEVT_XC1                  	( 0x2 		<< 10) 				// (TC) Signal selected as external event: XC1 TIOB direction: output
#define TC_EEVT_XC2                  	( 0x3 		<< 10) 				// (TC) Signal selected as external event: XC2 TIOB direction: output
#define TC_ABETRG       				( 0x1 		<< 10) 				// (TC) TIOA or TIOB External Trigger Selection
#define TC_ENETRG       				( 0x1 		<< 12) 				// (TC) External Event Trigger enable
#define TC_WAVESEL      				( 0x3 		<< 13) 				// (TC) Waveform  Selection
#define TC_WAVESEL_UP                   ( 0x0 		<< 13) 				// (TC) UP mode without atomatic trigger on RC Compare
#define TC_WAVESEL_UPDOWN               ( 0x1 		<< 13) 				// (TC) UPDOWN mode without automatic trigger on RC Compare
#define TC_WAVESEL_UP_AUTO              ( 0x2 		<< 13) 				// (TC) UP mode with automatic trigger on RC Compare
#define TC_WAVESEL_UPDOWN_AUTO          ( 0x3 		<< 13) 				// (TC) UPDOWN mode with automatic trigger on RC Compare
#define TC_CPCTRG       				( 0x1 		<< 14) 				// (TC) RC Compare Trigger Enable
#define TC_WAVE         				( 0x1 		<< 15) 				// (TC) 
#define TC_ACPA         				( 0x3 		<< 16) 				// (TC) RA Compare Effect on TIOA
#define TC_ACPA_NONE                 	( 0x0 		<< 16) 				// (TC) Effect: none
#define TC_ACPA_SET                  	( 0x1 		<< 16) 				// (TC) Effect: set
#define TC_ACPA_CLEAR                	( 0x2 		<< 16) 				// (TC) Effect: clear
#define TC_ACPA_TOGGLE               	( 0x3 		<< 16) 				// (TC) Effect: toggle
#define TC_LDRA         				( 0x3 		<< 16) 				// (TC) RA Loading Selection
#define TC_LDRA_NONE                 	( 0x0 		<< 16) 				// (TC) Edge: None
#define TC_LDRA_RISING               	( 0x1 		<< 16) 				// (TC) Edge: rising edge of TIOA
#define TC_LDRA_FALLING              	( 0x2 		<< 16) 				// (TC) Edge: falling edge of TIOA
#define TC_LDRA_BOTH                 	( 0x3 		<< 16) 				// (TC) Edge: each edge of TIOA
#define TC_ACPC         				( 0x3 		<< 18) 				// (TC) RC Compare Effect on TIOA
#define TC_ACPC_NONE                 	( 0x0 		<< 18) 				// (TC) Effect: none
#define TC_ACPC_SET                  	( 0x1 		<< 18) 				// (TC) Effect: set
#define TC_ACPC_CLEAR                	( 0x2 		<< 18) 				// (TC) Effect: clear
#define TC_ACPC_TOGGLE               	( 0x3 		<< 18) 				// (TC) Effect: toggle
#define TC_LDRB         				( 0x3 		<< 18) 				// (TC) RB Loading Selection
#define TC_LDRB_NONE                 	( 0x0 		<< 18) 				// (TC) Edge: None
#define TC_LDRB_RISING               	( 0x1 		<< 18) 				// (TC) Edge: rising edge of TIOA
#define TC_LDRB_FALLING              	( 0x2 		<< 18) 				// (TC) Edge: falling edge of TIOA
#define TC_LDRB_BOTH                 	( 0x3 		<< 18) 				// (TC) Edge: each edge of TIOA
#define TC_AEEVT        				( 0x3 		<< 20) 				// (TC) External Event Effect on TIOA
#define TC_AEEVT_NONE                 	( 0x0 		<< 20) 				// (TC) Effect: none
#define TC_AEEVT_SET                  	( 0x1 		<< 20) 				// (TC) Effect: set
#define TC_AEEVT_CLEAR                	( 0x2 		<< 20) 				// (TC) Effect: clear
#define TC_AEEVT_TOGGLE               	( 0x3 		<< 20) 				// (TC) Effect: toggle
#define TC_ASWTRG       				( 0x3 		<< 22) 				// (TC) Software Trigger Effect on TIOA
#define TC_ASWTRG_NONE                 	( 0x0 		<< 22) 				// (TC) Effect: none
#define TC_ASWTRG_SET                  	( 0x1 		<< 22) 				// (TC) Effect: set
#define TC_ASWTRG_CLEAR                	( 0x2 		<< 22) 				// (TC) Effect: clear
#define TC_ASWTRG_TOGGLE               	( 0x3 		<< 22) 				// (TC) Effect: toggle
#define TC_BCPB         				( 0x3 		<< 24) 				// (TC) RB Compare Effect on TIOB
#define TC_BCPB_NONE                 	( 0x0 		<< 24) 				// (TC) Effect: none
#define TC_BCPB_SET                  	( 0x1 		<< 24) 				// (TC) Effect: set
#define TC_BCPB_CLEAR                	( 0x2 		<< 24) 				// (TC) Effect: clear
#define TC_BCPB_TOGGLE               	( 0x3 		<< 24) 				// (TC) Effect: toggle
#define TC_BCPC         				( 0x3 		<< 26) 				// (TC) RC Compare Effect on TIOB
#define TC_BCPC_NONE                 	( 0x0 		<< 26) 				// (TC) Effect: none
#define TC_BCPC_SET                  	( 0x1 		<< 26) 				// (TC) Effect: set
#define TC_BCPC_CLEAR                	( 0x2 		<< 26) 				// (TC) Effect: clear
#define TC_BCPC_TOGGLE               	( 0x3 		<< 26) 				// (TC) Effect: toggle
#define TC_BEEVT        				( 0x3 		<< 28) 				// (TC) External Event Effect on TIOB
#define TC_BEEVT_NONE                 	( 0x0 		<< 28) 				// (TC) Effect: none
#define TC_BEEVT_SET                  	( 0x1 		<< 28) 				// (TC) Effect: set
#define TC_BEEVT_CLEAR                	( 0x2 		<< 28) 				// (TC) Effect: clear
#define TC_BEEVT_TOGGLE               	( 0x3 		<< 28) 				// (TC) Effect: toggle
#define TC_BSWTRG       				( 0x3 		<< 30) 				// (TC) Software Trigger Effect on TIOB
#define TC_BSWTRG_NONE                 	( 0x0 		<< 30) 				// (TC) Effect: none
#define TC_BSWTRG_SET                  	( 0x1 		<< 30) 				// (TC) Effect: set
#define TC_BSWTRG_CLEAR                	( 0x2 		<< 30) 				// (TC) Effect: clear
#define TC_BSWTRG_TOGGLE               	( 0x3 		<< 30) 				// (TC) Effect: toggle
// -------- TC_SR : (TC Offset: 0x20) TC Channel Status Register -------- 
#define TC_COVFS        				( 0x1 		<<  0) 				// (TC) Counter Overflow
#define TC_LOVRS        				( 0x1 		<<  1) 				// (TC) Load Overrun
#define TC_CPAS         				( 0x1 		<<  2) 				// (TC) RA Compare
#define TC_CPBS         				( 0x1 		<<  3) 				// (TC) RB Compare
#define TC_CPCS         				( 0x1 		<<  4) 				// (TC) RC Compare
#define TC_LDRAS        				( 0x1 		<<  5) 				// (TC) RA Loading
#define TC_LDRBS        				( 0x1 		<<  6) 				// (TC) RB Loading
#define TC_ETRGS        				( 0x1 		<<  7) 				// (TC) External Trigger
#define TC_CLKSTA       				( 0x1 		<< 16) 				// (TC) Clock Enabling
#define TC_MTIOA        				( 0x1 		<< 17) 				// (TC) TIOA Mirror
#define TC_MTIOB        				( 0x1 		<< 18) 				// (TC) TIOA Mirror
// -------- TC_IER : (TC Offset: 0x24) TC Channel Interrupt Enable Register -------- 
// -------- TC_IDR : (TC Offset: 0x28) TC Channel Interrupt Disable Register -------- 
// -------- TC_IMR : (TC Offset: 0x2c) TC Channel Interrupt Mask Register -------- 

//------------------------------------------------------------------------------
//              SOFTWARE API DEFINITION  FOR Timer Counter Interface
//------------------------------------------------------------------------------

// -------- TCB_BCR : (TCB Offset: 0xc0) TC Block Control Register -------- 
#define TCB_SYNC        				( 0x1 		<<  0) 				// (TCB) Synchro Command
// -------- TCB_BMR : (TCB Offset: 0xc4) TC Block Mode Register -------- 
#define TCB_TC0XC0S     				( 0x3 		<<  0) 				// (TCB) External Clock Signal 0 Selection
#define TCB_TC0XC0S_TCLK0               ( 0x0 		<<  0) 				// (TCB) TCLK0 connected to XC0
#define TCB_TC0XC0S_NONE                ( 0x1 		<<  0) 				// (TCB) None signal connected to XC0
#define TCB_TC0XC0S_TIOA1               ( 0x2 		<<  0) 				// (TCB) TIOA1 connected to XC0
#define TCB_TC0XC0S_TIOA2               ( 0x3 		<<  0) 				// (TCB) TIOA2 connected to XC0
#define TCB_TC1XC1S     				( 0x3 		<<  2) 				// (TCB) External Clock Signal 1 Selection
#define TCB_TC1XC1S_TCLK1               ( 0x0 		<<  2) 				// (TCB) TCLK1 connected to XC1
#define TCB_TC1XC1S_NONE                ( 0x1 		<<  2) 				// (TCB) None signal connected to XC1
#define TCB_TC1XC1S_TIOA0               ( 0x2 		<<  2) 				// (TCB) TIOA0 connected to XC1
#define TCB_TC1XC1S_TIOA2               ( 0x3 		<<  2) 				// (TCB) TIOA2 connected to XC1
#define TCB_TC2XC2S     				( 0x3 		<<  4) 				// (TCB) External Clock Signal 2 Selection
#define TCB_TC2XC2S_TCLK2               ( 0x0 		<<  4) 				// (TCB) TCLK2 connected to XC2
#define TCB_TC2XC2S_NONE                ( 0x1 		<<  4) 				// (TCB) None signal connected to XC2
#define TCB_TC2XC2S_TIOA0               ( 0x2 		<<  4) 				// (TCB) TIOA0 connected to XC2
#define TCB_TC2XC2S_TIOA1               ( 0x3 		<<  4) 				// (TCB) TIOA2 connected to XC2


//------------------------------------------------------------------------------
//              SOFTWARE API DEFINITION  FOR Pulse Width Modulation Controller Interface
//------------------------------------------------------------------------------

// -------- PWMC_MR : (PWMC Offset: 0x0) PWMC Mode Register -------- 
#define PWMC_DIVA       				( 0xFF 		<<  0) 				// (PWMC) CLKA divide factor.
#define PWMC_PREA       				( 0xF 		<<  8) 				// (PWMC) Divider Input Clock Prescaler A
#define PWMC_PREA_MCK   				( 0x0 		<<  8) 				// (PWMC) 
#define PWMC_DIVB       				( 0xFF 		<< 16) 				// (PWMC) CLKB divide factor.
#define PWMC_PREB       				( 0xF 		<< 24) 				// (PWMC) Divider Input Clock Prescaler B
#define PWMC_PREB_MCK   				( 0x0 		<< 24) 				// (PWMC) 
// -------- PWMC_ENA : (PWMC Offset: 0x4) PWMC Enable Register -------- 
#define PWMC_CHID0      				( 0x1 		<<  0) 				// (PWMC) Channel ID 0
#define PWMC_CHID1      				( 0x1 		<<  1) 				// (PWMC) Channel ID 1
#define PWMC_CHID2      				( 0x1 		<<  2) 				// (PWMC) Channel ID 2
#define PWMC_CHID3      				( 0x1 		<<  3) 				// (PWMC) Channel ID 3
// -------- PWMC_DIS : (PWMC Offset: 0x8) PWMC Disable Register -------- 
// -------- PWMC_SR : (PWMC Offset: 0xc) PWMC Status Register -------- 
// -------- PWMC_IER : (PWMC Offset: 0x10) PWMC Interrupt Enable Register -------- 
// -------- PWMC_IDR : (PWMC Offset: 0x14) PWMC Interrupt Disable Register -------- 
// -------- PWMC_IMR : (PWMC Offset: 0x18) PWMC Interrupt Mask Register -------- 
// -------- PWMC_ISR : (PWMC Offset: 0x1c) PWMC Interrupt Status Register -------- 


//------------------------------------------------------------------------------
//              SOFTWARE API DEFINITION  FOR PWMC Channel Interface
//------------------------------------------------------------------------------

// -------- PWMC_CMR : (PWMC_CH Offset: 0x0) PWMC Channel Mode Register -------- 
#define PWMC_CPRE       				( 0xF 		<<  0) 				// (PWMC_CH) Channel Pre-scaler : PWMC_CLKx
#define PWMC_CPRE_MCK   				( 0x0 		<<  0) 				// (PWMC_CH) 
#define PWMC_CPRE_MCKA  				( 0xB 		<<  0) 				// (PWMC_CH) 
#define PWMC_CPRE_MCKB  				( 0xC 		<<  0) 				// (PWMC_CH) 
#define PWMC_CALG       				( 0x1 		<<  8) 				// (PWMC_CH) Channel Alignment
#define PWMC_CPOL       				( 0x1 		<<  9) 				// (PWMC_CH) Channel Polarity
#define PWMC_CPD        				( 0x1 		<< 10) 				// (PWMC_CH) Channel Update Period
// -------- PWMC_CDTYR : (PWMC_CH Offset: 0x4) PWMC Channel Duty Cycle Register -------- 
#define PWMC_CDTY       				( 0x0 		<<  0) 				// (PWMC_CH) Channel Duty Cycle
// -------- PWMC_CPRDR : (PWMC_CH Offset: 0x8) PWMC Channel Period Register -------- 
#define PWMC_CPRD       				( 0x0 		<<  0) 				// (PWMC_CH) Channel Period
// -------- PWMC_CCNTR : (PWMC_CH Offset: 0xc) PWMC Channel Counter Register -------- 
#define PWMC_CCNT       				( 0x0 		<<  0) 				// (PWMC_CH) Channel Counter
// -------- PWMC_CUPDR : (PWMC_CH Offset: 0x10) PWMC Channel Update Register -------- 
#define PWMC_CUPD       				( 0x0 		<<  0) 				// (PWMC_CH) Channel Update


//------------------------------------------------------------------------------ 
//              SOFTWARE API DEFINITION  FOR Reset Controller Interface          
//------------------------------------------------------------------------------  

// -------- RSTC_RCR : (RSTC Offset: 0x0) Reset Control Register --------           
#define RSTC_PROCRST    				( 0x1	 	<<	0) 				// (RSTC) Processor Reset                                                                               
#define RSTC_PERRST     				( 0x1		<<  2) 				// (RSTC) Peripheral Reset                                                                              
#define RSTC_EXTRST     				( 0x1 		<<  3) 				// (RSTC) External Reset                                                                                
#define RSTC_KEY        				( 0xFF 		<< 24) 				// (RSTC) Password                                                                                      

// -------- RSTC_RSR : (RSTC Offset: 0x4) Reset Status Register --------                                                                                  
#define RSTC_URSTS      				( 0x1 		<<  0) 				// (RSTC) User Reset Status                                                                             
#define RSTC_BODSTS     				( 0x1 		<<  1) 				// (RSTC) Brownout Detection Status                                                                     
#define RSTC_RSTTYP     				( 0x7 		<<  8) 				// (RSTC) Reset Type                                                                                    
#define RSTC_RSTTYP_POWERUP     		( 0x0 		<< 	8) 				// (RSTC) Power-up Reset. VDDCORE rising.                                     
#define RSTC_RSTTYP_WAKEUP      		( 0x1 		<< 	8) 				// (RSTC) WakeUp Reset. VDDCORE rising.                                       
#define RSTC_RSTTYP_WATCHDOG    		( 0x2 		<< 	8) 				// (RSTC) Watchdog Reset. Watchdog overflow occured.                          
#define RSTC_RSTTYP_SOFTWARE    		( 0x3 		<< 	8) 				// (RSTC) Software Reset. Processor reset required by the software.           
#define RSTC_RSTTYP_USER        		( 0x4 		<< 	8) 				// (RSTC) User Reset. NRST pin detected low.                                  
#define RSTC_RSTTYP_BROWNOUT    		( 0x5 		<< 	8) 				// (RSTC) Brownout Reset occured.                                       
#define RSTC_NRSTL      				( 0x1 		<< 	6) 				// (RSTC) NRST pin level                                                                   
#define RSTC_SRCMP      				( 0x1 		<< 	7) 				// (RSTC) Software Reset Command in Progress.                                                    

// -------- RSTC_RMR : (RSTC Offset: 0x8) Reset Mode Register --------                                                                                                                                                                    
#define RSTC_URSTEN     				( 0x1 		<< 	0) 				// (RSTC) User Reset Enable                                                                                                                                                      
#define RSTC_URSTIEN    				( 0x1 		<< 	4) 				// (RSTC) User Reset Interrupt Enable                                                                                                                                            
#define RSTC_ERSTL      				( 0xF 		<< 	8) 				// (RSTC) User Reset Length                                                                                                                                                      
#define RSTC_BODIEN     				( 0x1 		<< 16) 				// (RSTC) Brownout Detection Interrupt Enable                                                                                                                                    
                                                           
//------------------------------------------------------------------------------  
//              SOFTWARE API DEFINITION  FOR Peripheral DMA Controller           
//------------------------------------------------------------------------------  

// -------- PDC_PTCR : (PDC Offset: 0x20) PDC Transfer Control Register --------              
#define PDC_RXTEN       				( 0x1 		<<  0) 				// (PDC) Receiver Transfer Enable    
#define PDC_RXTDIS      				( 0x1 		<<  1) 				// (PDC) Receiver Transfer Disable   
#define PDC_TXTEN       				( 0x1 		<<  8) 				// (PDC) Transmitter Transfer Enable 
#define PDC_TXTDIS      				( 0x1 		<<  9) 				// (PDC) Transmitter Transfer Disable
                                                  				
// -------- PDC_PTSR : (PDC Offset: 0x24) PDC Transfer Status Register --------               

                                                                                  
//------------------------------------------------------------------------------  
//       				SOFTWARE API DEFINITION  FOR Periodic Interval Timer Controller Interface   
//------------------------------------------------------------------------------  

// -------- PITC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register --------                          
#define PITC_PIV       					( 0xFFFFF 	<<  0) 				// (PITC) Periodic Interval Value               
#define PITC_PITEN     					( 0x1 		<< 24) 		 		// (PITC) Periodic Interval Timer Enabled           
#define PITC_PITIEN    					( 0x1 		<< 25) 		 		// (PITC) Periodic Interval Timer Interrupt Enable  
                                    	
// -------- PITC_PISR :				 (PITC Offset		: 0x					eriodic Interval Status Register --------                        
#define PITC_PITS       			 	( 0x1 		<<  0) 				// (PITC) Periodic Interval Timer Status            
                               
// -------- PITC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register --------                         
#define PITC_CPIV       			 	( 0xFFFFF 	<<  0) 				// (PITC) Current Periodic Interval Value       
#define PITC_PICNT      			 	( 0xFFF 	<< 20) 				// (PITC) Periodic Interval Counter               
                                     	             					
// -------- PITC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register --------  
  
//------------------------------------------------------------------------------                     
//              SOFTWARE API DEFINITION  FOR Watchdog Timer Controller Interface
//------------------------------------------------------------------------------

// -------- WDTC_WDCR : (WDTC Offset: 0x0) Periodic Interval Image Register --------               
#define WDTC_WDRSTT     				( 0x1 		<<  0) 				// (WDTC) Watchdog Restart                
#define WDTC_KEY        				( 0xFF 		<< 24) 				// (WDTC) Watchdog KEY Password          

// -------- WDTC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register --------                         
#define WDTC_WDV        				( 0xFFF 	<< 	0) 				// (WDTC) Watchdog Timer Restart        
#define WDTC_WDFIEN     				( 0x1 		<< 12) 				// (WDTC) Watchdog Fault Interrupt Enable 
#define WDTC_WDRSTEN    				( 0x1 		<< 13) 				// (WDTC) Watchdog Reset Enable           
#define WDTC_WDRPROC    				( 0x1 		<< 14) 				// (WDTC) Watchdog Timer Restart          
#define WDTC_WDDIS      				( 0x1 		<< 15) 				// (WDTC) Watchdog Disable                
#define WDTC_WDD        				( 0xFFF 	<< 16) 				// (WDTC) Watchdog Delta Value          
#define WDTC_WDDBGHLT   				( 0x1 		<< 28) 				// (WDTC) Watchdog Debug Halt             
#define WDTC_WDIDLEHLT  				( 0x1 		<< 29) 				// (WDTC) Watchdog Idle Halt              

// -------- WDTC_WDSR : (WDTC Offset: 0x8) Watchdog Status Register --------                       
#define WDTC_WDUNF      				( 0x1 		<< 0) 				// (WDTC) Watchdog Underflow              
#define WDTC_WDERR      			    ( 0x1 		<< 1) 				// (WDTC) Watchdog Error                  
                                                                                                                
//------------------------------------------------------------------------------  
//              SOFTWARE API DEFINITION  FOR Serial Parallel Interface          
//------------------------------------------------------------------------------ 

// -------- SPI_CR : (SPI Offset: 0x0) SPI Control Register --------                                                                                                                                                                                                                                                                         
#define SPI_SPIEN       				( 0x1 		<<  0) 				// (SPI) SPI Enable                                                                                                          
#define SPI_SPIDIS      				( 0x1 		<<  1) 				// (SPI) SPI Disable                                                                                                         
#define SPI_SWRST       				( 0x1 		<<  7) 				// (SPI) SPI Software reset                                                                                                  
#define SPI_LASTXFER    				( 0x1 		<< 24) 				// (SPI) SPI Last Transfer                                                                                                   

// -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register --------                                                                                                                     
#define SPI_MSTR        				( 0x1 		<<  0) 				// (SPI) Master/Slave Mode                                                                                                   
#define SPI_PS          				( 0x1 		<<  1) 				// (SPI) Peripheral Select                                                                                                   
#define SPI_PS_FIXED    				( 0x0 		<<  1) 				// (SPI) Fixed Peripheral Sel                                                                                
#define SPI_PS_VARIABLE 				( 0x1 		<<  1) 				// (SPI) Variable Peripheral                                                                                 
#define SPI_PCSDEC      				( 0x1 		<<  2) 				// (SPI) Chip Select Decode                                                                                                  
#define SPI_FDIV        				( 0x1 		<<  3) 				// (SPI) Clock Selection                                                                                                     
#define SPI_MODFDIS     				( 0x1 		<<  4) 				// (SPI) Mode Fault Detection                                                                                                
#define SPI_LLB         				( 0x1 		<<  7) 				// (SPI) Clock Selection                                                                                                     
#define SPI_PCS         				( 0xF 		<< 16) 				// (SPI) Peripheral Chip Select                                                                                              
#define SPI_DLYBCS(x)      				((x & 0xFF)	<< 24) 				// (SPI) Delay Between Chip Selects
// b4 modify - gemini
//#define SPI_DLYBCS      				( 0xFF		<< 24) 				// (SPI) Delay Between Chip Selects

// -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register --------                                                                                                                
#define SPI_RD          				( 0xFFFF 	<<  0) 				// (SPI) Receive Data                                                                                                     
#define SPI_RPCS        				( 0xF 		<< 16) 				// (SPI) Peripheral Chip Select Status                                                                                       

// -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register --------                                                                                                               
#define SPI_TD          				( 0xFFFF 	<<  0) 				// (SPI) Transmit Data                                                                                                    
#define SPI_TPCS        				( 0xF 		<< 16) 				// (SPI) Peripheral Chip Select Status                                                                                       

// -------- SPI_SR : (SPI Offset: 0x10) Status Register --------                                                                                                                      
#define SPI_RDRF        				( 0x1 		<<  0) 				// (SPI) Receive Data Register Full                                                                                          
#define SPI_TDRE        				( 0x1 		<<  1) 				// (SPI) Transmit Data Register Empty                                                                                        
#define SPI_MODF        				( 0x1 		<<  2) 				// (SPI) Mode Fault Error                                                                                                    
#define SPI_OVRES       				( 0x1 		<<  3) 				// (SPI) Overrun Error Status                                                                                                
#define SPI_ENDRX       				( 0x1 		<<  4) 				// (SPI) End of Receiver Transfer                                                                                            
#define SPI_ENDTX       				( 0x1 		<<  5) 				// (SPI) End of Receiver Transfer                                                                                            
#define SPI_RXBUFF      				( 0x1 		<<  6) 				// (SPI) RXBUFF Interrupt                                                                                                    
#define SPI_TXBUFE      				( 0x1 		<<  7) 				// (SPI) TXBUFE Interrupt                                                                                                    
#define SPI_NSSR        				( 0x1 		<<  8) 				// (SPI) NSSR Interrupt                                                                                                      
#define SPI_TXEMPTY     				( 0x1 		<<  9) 				// (SPI) TXEMPTY Interrupt                                                                                                   
#define SPI_SPIENS      				( 0x1 		<< 16) 				// (SPI) Enable Status                                                                                                       

// -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register --------                                                                                                           
// -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register --------                                                                                                          
// -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register --------                                                                                                             
// -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register --------                                                                                                                
#define SPI_CPOL        				( 0x1 		<<  0) 				// (SPI) Clock Polarity                                                                                                      
#define SPI_NCPHA       				( 0x1 		<<  1) 				// (SPI) Clock Phase                                                                                                         
#define SPI_CSAAT       				( 0x1 		<<  3) 				// (SPI) Chip Select Active After Transfer                                                                                   
#define SPI_BITS        				( 0xF 		<<  4) 				// (SPI) Bits Per Transfer                                                                                                   
#define SPI_BITS_8                    	( 0x0 		<<  4) 				// (SPI) 8 Bits Per transfe                                                                                
#define SPI_BITS_9                    	( 0x1 		<<  4) 				// (SPI) 9 Bits Per transfe                                                                                
#define SPI_BITS_10                   	( 0x2 		<<  4) 				// (SPI) 10 Bits Per transf                                                                                
#define SPI_BITS_11                   	( 0x3 		<<  4) 				// (SPI) 11 Bits Per transf                                                                                
#define SPI_BITS_12                   	( 0x4 		<<  4) 				// (SPI) 12 Bits Per transf                                                                                
#define SPI_BITS_13                   	( 0x5 		<<  4) 				// (SPI) 13 Bits Per transf                                                                                
#define SPI_BITS_14                   	( 0x6 		<<  4) 				// (SPI) 14 Bits Per transf                                                                                
#define SPI_BITS_15                   	( 0x7 		<<  4) 				// (SPI) 15 Bits Per transf                                                                                
#define SPI_BITS_16                   	( 0x8 		<<  4) 				// (SPI) 16 Bits Per transf                                                                                
#define SPI_SCBR(x)        				((x & 0xFF)	<<  8) 				// (SPI) Serial Clock Baud Rate                                                                                             
#define SPI_DLYBS(x)       				((x & 0xFF) << 16) 				// (SPI) Delay Before SPCK                                                                                                  
#define SPI_DLYBCT(x)      				((x & 0xFF)	<< 24) 				// (SPI) Delay Between Consecutive Transfers   
// b4 modify - gemini
//#define SPI_SCBR        				( 0xFF 		<<  8) 				// (SPI) Serial Clock Baud Rate                                                                                             
//#define SPI_DLYBS       				( 0xFF 		<< 16) 				// (SPI) Delay Before SPCK                                                                                                  
//#define SPI_DLYBCT      				( 0xFF 		<< 24) 				// (SPI) Delay Between Consecutive Transfers   

//------------------------------------------------------------------------------ 
//              SOFTWARE API DEFINITION  FOR Two-wire Interface    
//------------------------------------------------------------------------------ 

// -------- TWI_CR : (TWI Offset: 0x0) TWI Control Register --------                                                                                                                                 
#define TWI_START       				( 0x1 		<< 	0) 				// (TWI) Send a START Condition                                
#define TWI_STOP        				( 0x1 		<< 	1) 				// (TWI) Send a STOP Condition                                 
#define TWI_MSEN        				( 0x1 		<< 	2) 				// (TWI) TWI Master Transfer Enabled                           
#define TWI_MSDIS       				( 0x1 		<< 	3) 				// (TWI) TWI Master Transfer Disabled                          
#define TWI_SWRST       				( 0x1 		<< 	7) 				// (TWI) Software Reset                                        

// -------- TWI_MMR : (TWI Offset: 0x4) TWI Master Mode Register --------                                               
#define TWI_IADRSZ      				( 0x3 		<< 	8) 				// (TWI) Internal Device Address Size                          
#define TWI_IADRSZ_NO                   ( 0x0 		<< 	8) 				// (TWI) No internal device address        
#define TWI_IADRSZ_1_BYTE               ( 0x1 		<< 	8) 				// (TWI) One-byte internal device address  
#define TWI_IADRSZ_2_BYTE               ( 0x2 		<< 	8) 				// (TWI) Two-byte internal device address  
#define TWI_IADRSZ_3_BYTE               ( 0x3 		<< 	8) 				// (TWI) Three-byte internal device address
#define TWI_MREAD       				( 0x1 		<< 12) 				// (TWI) Master Read Direction                                 
#define TWI_DADR(x)        				( ((x)&0x7F)<< 16) 				// (TWI) Device Address                                       

// -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register --------                                
#define TWI_CLDIV(x)       				( ((x)&0xFF)<<  0) 				// (TWI) Clock Low Divider                                    
#define TWI_CHDIV(x)       				( ((x)&0xFF)<<  8) 				// (TWI) Clock High Divider                                   
#define TWI_CKDIV(x)       				( ((x)&0x7 )<< 16) 				// (TWI) Clock Divider                                         

// -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register --------                                                    
#define TWI_TXCOMP      				( 0x1 		<<  0) 				// (TWI) Transmission Completed                                
#define TWI_RXRDY       				( 0x1 		<<  1) 				// (TWI) Receive holding register ReaDY                        
#define TWI_TXRDY       				( 0x1 		<<  2) 				// (TWI) Transmit holding register ReaDY                       
#define TWI_OVRE        				( 0x1 		<<  6) 				// (TWI) Overrun Error                                         
#define TWI_UNRE        				( 0x1 		<<  7) 				// (TWI) Underrun Error                                        
#define TWI_NACK        				( 0x1 		<<  8) 				// (TWI) Not Acknowledged                                      

// -------- TWI_IER : (TWI Offset: 0x24) TWI Interrupt Enable Register --------                                         
// -------- TWI_IDR : (TWI Offset: 0x28) TWI Interrupt Disable Register --------                                        
// -------- TWI_IMR : (TWI Offset: 0x2c) TWI Interrupt Mask Register --------                                           
                                                                                
//------------------------------------------------------------------------------   
//              SOFTWARE API DEFINITION  FOR USB Device Interface                    
//------------------------------------------------------------------------------   

// -------- UDP_FRM_NUM : (UDP Offset: 0x0) USB Frame Number Register --------                                                                                                

#define UDP_FRM_NUM     				( 0x7FF 	<<  0)				 	// (UDP) Frame Number as Defined in the Packet Field Formats               
#define UDP_FRM_ERR     				( 0x1 		<< 16)				 	// (UDP) Frame Error                                                         
#define UDP_FRM_OK      				( 0x1 		<< 17)				 	// (UDP) Frame OK                                                            

// -------- UDP_GLB_STATE : (UDP Offset: 0x4) USB Global State Register --------                                                      
#define UDP_FADDEN      				( 0x1 		<<  0)				 	// (UDP) Function Address Enable                                             
#define UDP_CONFG       				( 0x1 		<<  1)				 	// (UDP) Configured                                                          
#define UDP_ESR         				( 0x1 		<<  2)				 	// (UDP) Enable Send Resume                                                  
#define UDP_RSMINPR     				( 0x1 		<<  3)				 	// (UDP) A Resume Has Been Sent to the Host                                  
#define UDP_RMWUPE      				( 0x1 		<<  4)				 	// (UDP) Remote Wake Up Enable                                               

// -------- UDP_FADDR : (UDP Offset: 0x8) USB Function Address Register --------                                                      
#define UDP_FADD        				( 0xFF 		<<  0)				 	// (UDP) Function Address Value                                             
#define UDP_FEN         				( 0x1  		<<  8)				 	// (UDP) Function Enable                                                     

// -------- UDP_IER : (UDP Offset: 0x10) USB Interrupt Enable Register --------                                                       
#define UDP_EPINT0      				( 0x1 		<<  0)					// (UDP) Endpoint 0 Interrupt                                                
#define UDP_EPINT1      				( 0x1 		<<  1)					// (UDP) Endpoint 0 Interrupt                                                
#define UDP_EPINT2      				( 0x1 		<<  2)					// (UDP) Endpoint 2 Interrupt                                                
#define UDP_EPINT3      				( 0x1 		<<  3)					// (UDP) Endpoint 3 Interrupt                                                
#define UDP_RXSUSP      				( 0x1 		<<  8)					// (UDP) USB Suspend Interrupt                                               
#define UDP_RXRSM       				( 0x1 		<<  9)					// (UDP) USB Resume Interrupt                                                
#define UDP_EXTRSM      				( 0x1 		<< 10)					// (UDP) USB External Resume Interrupt                                       
#define UDP_SOFINT      				( 0x1 		<< 11)					// (UDP) USB Start Of frame Interrupt                                        
#define UDP_WAKEUP      				( 0x1 		<< 13)					// (UDP) USB Resume Interrupt                                                

// -------- UDP_IDR : (UDP Offset: 0x14) USB Interrupt Disable Register --------                                                      
// -------- UDP_IMR : (UDP Offset: 0x18) USB Interrupt Mask Register --------                                                         

// -------- UDP_ISR : (UDP Offset: 0x1c) USB Interrupt Status Register --------                                                       
#define UDP_ENDBUSRES   				( 0x1		 << 12)				// (UDP) USB End Of Bus Reset Interrupt                                      

// -------- UDP_ICR : (UDP Offset: 0x20) USB Interrupt Clear Register --------                                                        

// -------- UDP_RST_EP : (UDP Offset: 0x28) USB Reset Endpoint Register --------                                                      
#define UDP_EP0         				( 0x1		 << 0)				 	// (UDP) Reset Endpoint 0                                                    
#define UDP_EP1         				( 0x1		 << 1)				 	// (UDP) Reset Endpoint 1                                                    
#define UDP_EP2         				( 0x1		 << 2)				 	// (UDP) Reset Endpoint 2                                                    
#define UDP_EP3         				( 0x1		 << 3)				 	// (UDP) Reset Endpoint 3                                                    

// -------- UDP_CSR : (UDP Offset: 0x30) USB Endpoint Control and Status Register --------                                            
#define UDP_TXCOMP      				( 0x1 		<<  0)				 	// (UDP) Generates an IN packet with data previously written in the DPR      
#define UDP_RX_DATA_BK0 				( 0x1 		<<  1)				 	// (UDP) Receive Data Bank 0                                                 
#define UDP_RXSETUP     				( 0x1 		<<  2)				 	// (UDP) Sends STALL to the Host (Control endpoints)                         
#define UDP_ISOERROR    				( 0x1 		<<  3)				 	// (UDP) Isochronous error (Isochronous endpoints)                           
#define UDP_TXPKTRDY    				( 0x1 		<<  4)				 	// (UDP) Transmit Packet Ready                                               
#define UDP_FORCESTALL  				( 0x1 		<<  5)				 	// (UDP) Force Stall (used by Control, Bulk and Isochronous endpoints).      
#define UDP_RX_DATA_BK1 				( 0x1 		<<  6)				 	// (UDP) Receive Data Bank 1 (only used by endpoints with ping-pong attribute
#define UDP_DIR         				( 0x1 		<<  7)				 	// (UDP) Transfer Direction                                                  
#define UDP_EPTYPE      				( 0x7 		<<  8)				 	// (UDP) Endpoint type                                                       
#define UDP_EPTYPE_CTRL                 ( 0x0 		<<  8)				 	// (UDP) Control                                         
#define UDP_EPTYPE_ISO_OUT              ( 0x1 		<<  8)				 	// (UDP) Isochronous OUT                                 
#define UDP_EPTYPE_BULK_OUT             ( 0x2 		<<  8)				 	// (UDP) Bulk OUT                                        
#define UDP_EPTYPE_INT_OUT              ( 0x3 		<<  8)				 	// (UDP) Interrupt OUT                                   
#define UDP_EPTYPE_ISO_IN               ( 0x5 		<<  8)				 	// (UDP) Isochronous IN                                  
#define UDP_EPTYPE_BULK_IN              ( 0x6 		<<  8)				 	// (UDP) Bulk IN                                         
#define UDP_EPTYPE_INT_IN               ( 0x7 		<<  8)				 	// (UDP) Interrupt IN                                    
#define UDP_DTGLE       				( 0x1 		<< 11)				 	// (UDP) Data Toggle                                                         
#define UDP_EPEDS       				( 0x1 		<< 15)				 	// (UDP) Endpoint Enable Disable                                             
#define UDP_RXBYTECNT   				( 0x7FF 	<< 16)				 	// (UDP) Number Of Bytes Available in the FIFO                             

// -------- UDP_TXVC : (UDP Offset: 0x74) Transceiver Control Register --------                                                       
#define UDP_TXVDIS      				( 0x1		<<  8) 				    // (UDP)                                                                     


// PERIPHERAL ID DEFINITIONS FOR AT91SAM7S64

#define ID_FIQ    						((u32)  0) 							// Advanced Interrupt Controller (FIQ)
#define ID_SYS    						((u32)  1) 							// System Peripheral
#define ID_PIOA   						((u32)  2) 							// Parallel IO Controller
#define ID_3_Reserved 					((u32)  3) 							// Reserved
#define ID_ADC    						((u32)  4) 							// Analog-to-Digital Converter
#define ID_SPI    						((u32)  5) 							// Serial Peripheral Interface
#define ID_US0    						((u32)  6) 							// USART 0
#define ID_US1    						((u32)  7) 							// USART 1
#define ID_SSC    						((u32)  8) 							// Serial Synchronous Controller
#define ID_TWI    						((u32)  9) 							// Two-Wire Interface
#define ID_PWMC   						((u32) 10) 							// PWM Controller
#define ID_UDP    						((u32) 11) 							// USB Device Port
#define ID_TC0    						((u32) 12) 							// Timer Counter 0
#define ID_TC1    						((u32) 13) 							// Timer Counter 1
#define ID_TC2    						((u32) 14) 							// Timer Counter 2
#define ID_15_Reserved 					((u32) 15) 							// Reserved
#define ID_16_Reserved 					((u32) 16) 							// Reserved
#define ID_17_Reserved 					((u32) 17) 							// Reserved
#define ID_18_Reserved 					((u32) 18) 							// Reserved
#define ID_19_Reserved 					((u32) 19) 							// Reserved
#define ID_20_Reserved 					((u32) 20) 							// Reserved
#define ID_21_Reserved 					((u32) 21) 							// Reserved
#define ID_22_Reserved 					((u32) 22) 							// Reserved
#define ID_23_Reserved 					((u32) 23) 							// Reserved
#define ID_24_Reserved 					((u32) 24) 							// Reserved
#define ID_25_Reserved 					((u32) 25) 							// Reserved
#define ID_26_Reserved 					((u32) 26) 							// Reserved
#define ID_27_Reserved 					((u32) 27) 							// Reserved
#define ID_28_Reserved 					((u32) 28) 							// Reserved
#define ID_29_Reserved 					((u32) 29) 							// Reserved
#define ID_IRQ0   						((u32) 30) 							// Advanced Interrupt Controller (IRQ0)
#define ID_IRQ1   						((u32) 31) 							// Advanced Interrupt Controller (IRQ1)
#define ALL_INT   						((u32) 0xC0007FF7) 					// ALL VALID INTERRUPTS

// *****************************************************************************
//               PIO DEFINITIONS FOR AT91SAM7S64
// *****************************************************************************
#define PIO_PA0        					((u32) 1 <<  0) 					// Pin Controlled by PA0
#define PA0_PWM0     					((u32) PIO_PA0) 					//  PWM Channel 0
#define PA0_TIOA0    					((u32) PIO_PA0) 					//  Timer Counter 0 Multipurpose Timer I/O Pin A
#define PIO_PA1        					((u32) 1 <<  1) 					// Pin Controlled by PA1
#define PA1_PWM1     					((u32) PIO_PA1) 					//  PWM Channel 1
#define PA1_TIOB0    					((u32) PIO_PA1) 					//  Timer Counter 0 Multipurpose Timer I/O Pin B
#define PIO_PA10       					((u32) 1 << 10) 					// Pin Controlled by PA10
#define PA10_DTXD     					((u32) PIO_PA10) 					//  DBGU Debug Transmit Data
#define PA10_NPCS2    					((u32) PIO_PA10) 					//  SPI Peripheral Chip Select 2
#define PIO_PA11       					((u32) 1 << 11) 					// Pin Controlled by PA11
#define PA11_NPCS0    					((u32) PIO_PA11) 					//  SPI Peripheral Chip Select 0
#define PA11_PWM0     					((u32) PIO_PA11) 					//  PWM Channel 0
#define PIO_PA12       					((u32) 1 << 12) 					// Pin Controlled by PA12
#define PA12_MISO     					((u32) PIO_PA12) 					//  SPI Master In Slave
#define PA12_PWM1     					((u32) PIO_PA12) 					//  PWM Channel 1
#define PIO_PA13       					((u32) 1 << 13) 					// Pin Controlled by PA13
#define PA13_MOSI     					((u32) PIO_PA13) 					//  SPI Master Out Slave
#define PA13_PWM2     					((u32) PIO_PA13) 					//  PWM Channel 2
#define PIO_PA14       					((u32) 1 << 14) 					// Pin Controlled by PA14
#define PA14_SPCK     					((u32) PIO_PA14) 					//  SPI Serial Clock
#define PA14_PWM3     					((u32) PIO_PA14) 					//  PWM Channel 3
#define PIO_PA15       					((u32) 1 << 15) 					// Pin Controlled by PA15
#define PA15_TF       					((u32) PIO_PA15) 					//  SSC Transmit Frame Sync
#define PA15_TIOA1    					((u32) PIO_PA15) 					//  Timer Counter 1 Multipurpose Timer I/O Pin A
#define PIO_PA16       					((u32) 1 << 16) 					// Pin Controlled by PA16
#define PA16_TK       					((u32) PIO_PA16) 					//  SSC Transmit Clock
#define PA16_TIOB1    					((u32) PIO_PA16) 					//  Timer Counter 1 Multipurpose Timer I/O Pin B
#define PIO_PA17       					((u32) 1 << 17) 					// Pin Controlled by PA17
#define PA17_TD       					((u32) PIO_PA17) 					//  SSC Transmit data
#define PA17_PCK1     					((u32) PIO_PA17) 					//  PMC Programmable Clock Output 1
#define PIO_PA18       					((u32) 1 << 18) 					// Pin Controlled by PA18
#define PA18_RD       					((u32) PIO_PA18) 					//  SSC Receive Data
#define PA18_PCK2     					((u32) PIO_PA18) 					//  PMC Programmable Clock Output 2
#define PIO_PA19       					((u32) 1 << 19) 					// Pin Controlled by PA19
#define PA19_RK       					((u32) PIO_PA19) 					//  SSC Receive Clock
#define PA19_FIQ      					((u32) PIO_PA19) 					//  AIC Fast Interrupt Input
#define PIO_PA2        					((u32) 1 <<  2) 					// Pin Controlled by PA2
#define PA2_PWM2     					((u32) PIO_PA2) 					//  PWM Channel 2
#define PA2_SCK0     					((u32) PIO_PA2) 					//  USART 0 Serial Clock
#define PIO_PA20       					((u32) 1 << 20) 					// Pin Controlled by PA20
#define PA20_RF       					((u32) PIO_PA20) 					//  SSC Receive Frame Sync
#define PA20_IRQ0     					((u32) PIO_PA20) 					//  External Interrupt 0
#define PIO_PA21       					((u32) 1 << 21) 					// Pin Controlled by PA21
#define PA21_RXD1     					((u32) PIO_PA21) 					//  USART 1 Receive Data
#define PA21_PCK1     					((u32) PIO_PA21) 					//  PMC Programmable Clock Output 1
#define PIO_PA22       					((u32) 1 << 22) 					// Pin Controlled by PA22
#define PA22_TXD1     					((u32) PIO_PA22) 					//  USART 1 Transmit Data
#define PA22_NPCS3    					((u32) PIO_PA22) 					//  SPI Peripheral Chip Select 3
#define PIO_PA23       					((u32) 1 << 23) 					// Pin Controlled by PA23
#define PA23_SCK1     					((u32) PIO_PA23) 					//  USART 1 Serial Clock
#define PA23_PWM0     					((u32) PIO_PA23) 					//  PWM Channel 0
#define PIO_PA24      					((u32) 1 << 24) 					// Pin Controlled by PA24
#define PA24_RTS1     					((u32) PIO_PA24) 					//  USART 1 Ready To Send
#define PA24_PWM1     					((u32) PIO_PA24) 					//  PWM Channel 1
#define PIO_PA25       					((u32) 1 << 25) 					// Pin Controlled by PA25
#define PA25_CTS1     					((u32) PIO_PA25) 					//  USART 1 Clear To Send
#define PA25_PWM2     					((u32) PIO_PA25) 					//  PWM Channel 2
#define PIO_PA26       					((u32) 1 << 26) 					// Pin Controlled by PA26
#define PA26_DCD1     					((u32) PIO_PA26) 					//  USART 1 Data Carrier Detect
#define PA26_TIOA2    					((u32) PIO_PA26) 					//  Timer Counter 2 Multipurpose Timer I/O Pin A
#define PIO_PA27       					((u32) 1 << 27) 					// Pin Controlled by PA27
#define PA27_DTR1     					((u32) PIO_PA27) 					//  USART 1 Data Terminal ready
#define PA27_TIOB2    					((u32) PIO_PA27) 					//  Timer Counter 2 Multipurpose Timer I/O Pin B
#define PIO_PA28       					((u32) 1 << 28) 					// Pin Controlled by PA28
#define PA28_DSR1     					((u32) PIO_PA28) 					//  USART 1 Data Set ready
#define PA28_TCLK1    					((u32) PIO_PA28) 					//  Timer Counter 1 external clock input
#define PIO_PA29       					((u32) 1 << 29) 					// Pin Controlled by PA29
#define PA29_RI1      					((u32) PIO_PA29) 					//  USART 1 Ring Indicator
#define PA29_TCLK2    					((u32) PIO_PA29) 					//  Timer Counter 2 external clock input
#define PIO_PA3        					((u32) 1 <<  3) 					// Pin Controlled by PA3
#define PA3_TWD      					((u32) PIO_PA3) 					//  TWI Two-wire Serial Data
#define PA3_NPCS3    					((u32) PIO_PA3) 					//  SPI Peripheral Chip Select 3
#define PIO_PA30       					((u32) 1 << 30) 					// Pin Controlled by PA30
#define PA30_IRQ1     					((u32) PIO_PA30) 					//  External Interrupt 1
#define PA30_NPCS2    					((u32) PIO_PA30) 					//  SPI Peripheral Chip Select 2
#define PIO_PA31       					((u32) 1 << 31) 					// Pin Controlled by PA31
#define PA31_NPCS1    					((u32) PIO_PA31) 					//  SPI Peripheral Chip Select 1
#define PA31_PCK2     					((u32) PIO_PA31) 					//  PMC Programmable Clock Output 2
#define PIO_PA4        					((u32) 1 <<  4) 					// Pin Controlled by PA4
#define PA4_TWCK     					((u32) PIO_PA4) 					//  TWI Two-wire Serial Clock
#define PA4_TCLK0    					((u32) PIO_PA4) 					//  Timer Counter 0 external clock input
#define PIO_PA5        					((u32) 1 <<  5) 					// Pin Controlled by PA5
#define PA5_RXD0     					((u32) PIO_PA5) 					//  USART 0 Receive Data
#define PA5_NPCS3    					((u32) PIO_PA5) 					//  SPI Peripheral Chip Select 3
#define PIO_PA6        					((u32) 1 <<  6) 					// Pin Controlled by PA6
#define PA6_TXD0     					((u32) PIO_PA6) 					//  USART 0 Transmit Data
#define PA6_PCK0     					((u32) PIO_PA6) 					//  PMC Programmable Clock Output 0
#define PIO_PA7        					((u32) 1 <<  7) 					// Pin Controlled by PA7
#define PA7_RTS0     					((u32) PIO_PA7) 					//  USART 0 Ready To Send
#define PA7_PWM3     					((u32) PIO_PA7) 					//  PWM Channel 3
#define PIO_PA8        					((u32) 1 <<  8) 					// Pin Controlled by PA8
#define PA8_CTS0     					((u32) PIO_PA8) 					//  USART 0 Clear To Send
#define PA8_ADTRG    					((u32) PIO_PA8) 					//  ADC External Trigger
#define PIO_PA9        					((u32) 1 <<  9) 					// Pin Controlled by PA9
#define PA9_DRXD     					((u32) PIO_PA9) 					//  DBGU Debug Receive Data
#define PA9_NPCS1    					((u32) PIO_PA9) 					//  SPI Peripheral Chip Select 1


//
//  Memory Map
//

#define ADDR_FLASH              0x00100000
#define ADDR_FLASH_END          0x00140000	//256Kbyte
#define ADDR_SRAM               0x00200000
#define ADDR_SRAM_END           0x00210000	//64Kbyte

#define MCLK					(48054857)	  // MCLK (PLLRC div by 2)

//
//  User Define 
//
#define ADDR_STACK          	(ADDR_SRAM_END-4)
#define LED_DS1					(1<<0)
#define LED_DS2					(1<<1)
#define LED_DS3					(1<<2)
#define LED_DS4					(1<<3)

#endif  // _SETUP_HEADER_

