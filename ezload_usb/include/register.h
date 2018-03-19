//------------------------------------------------------------------------------
// 파 일 명 : register.h
// 프로젝트 : ez-jtag
// 설    명 : AT91S 레지스터 정의
// 작 성 자 : 유영창(frog@falinux.com) ,이영민,박영리
// 작 성 일 : 2007년 4월 28일
// 수 정 일 : 
// 수 정 일 : 
// 주    의 : 
// 라이센스 : BSD
//------------------------------------------------------------------------------

#ifndef _REGISTER_HEADER_
#define _REGISTER_HEADER_

#ifndef __ASSEMBLY__
	#define __REG(x)       (*((volatile u32 *)x))
#else
	#define __REG(x)       (x)
#endif

#ifndef __ASSEMBLY__
	#define __REG_S(x)       (*((volatile s32 *)x))
#else
	#define __REG_S(x)       (x)
#endif

// SOFTWARE API DEFINITION  FOR Timer Counter Channel Interface
#define TC0_CCR 			__REG(0xFFFA0000)		// Channel Control Register
#define TC0_CMR 			__REG(0xFFFA0004)		// Channel Mode Register (Capture Mode / Waveform Mode)
#define TC0_CV 				__REG(0xFFFA0010)		// Counter Value
#define TC0_RA 				__REG(0xFFFA0014)		// Register A
#define TC0_RB 				__REG(0xFFFA0018)		// Register B
#define TC0_RC 				__REG(0xFFFA001C)		// Register C
#define TC0_SR 				__REG(0xFFFA0020)		// Status Register
#define TC0_IER 			__REG(0xFFFA0024)		// Interrupt Enable Register
#define TC0_IDR 			__REG(0xFFFA0028)		// Interrupt Disable Register
#define TC0_IMR 			__REG(0xFFFA002C)		// Interrupt Mask Register

#define TC1_CCR 			__REG(0xFFFA0040)		// Channel Control Register
#define TC1_CMR 			__REG(0xFFFA0044)		// Channel Mode Register (Capture Mode / Waveform Mode)
#define TC1_CV 				__REG(0xFFFA0050)		// Counter Value
#define TC1_RA 				__REG(0xFFFA0054)		// Register A
#define TC1_RB 				__REG(0xFFFA0058)		// Register B
#define TC1_RC 				__REG(0xFFFA005C)		// Register C
#define TC1_SR 				__REG(0xFFFA0060)		// Status Register
#define TC1_IER 			__REG(0xFFFA0064)		// Interrupt Enable Register
#define TC1_IDR 			__REG(0xFFFA0068)		// Interrupt Disable Register
#define TC1_IMR 			__REG(0xFFFA006C)		// Interrupt Mask Register

#define TC2_CCR 			__REG(0xFFFA0080)		// Channel Control Register
#define TC2_CMR 			__REG(0xFFFA0084)		// Channel Mode Register (Capture Mode / Waveform Mode)
#define TC2_CV 				__REG(0xFFFA0090)		// Counter Value
#define TC2_RA 				__REG(0xFFFA0094)		// Register A
#define TC2_RB 				__REG(0xFFFA0098)		// Register B
#define TC2_RC 				__REG(0xFFFA009C)		// Register C
#define TC2_SR 				__REG(0xFFFA00A0)		// Status Register
#define TC2_IER 			__REG(0xFFFA00A4)		// Interrupt Enable Register
#define TC2_IDR 			__REG(0xFFFA00A8)		// Interrupt Disable Register
#define TC2_IMR 			__REG(0xFFFA00AC)		// Interrupt Mask Register

#define TCB_BCR 			__REG(0xFFFA00C0)		// TC Block Control Register
#define TCB_BMR 			__REG(0xFFFA00C4)		// TC Block Mode Register

//SOFTWARE API DEFINITION  FOR USB Device Interface 
#define	 UDP_NUM 			__REG(0XFFFB0000)		// Frame Number Register                                     
#define	 UDP_GLBSTATE 		__REG(0XFFFB0004)		// Global State Register                                               		
#define	 UDP_FADDR 			__REG(0XFFFB0008)		// Function Address Register                                           		                                               
#define	 UDP_IER 			__REG(0XFFFB0010)		// Interrupt Enable Register                           
#define	 UDP_IDR 			__REG(0XFFFB0014)		// Interrupt Disable Register                          
#define	 UDP_IMR 			__REG(0XFFFB0018)		// Interrupt Mask Register                             
#define	 UDP_ISR 			__REG(0XFFFB001C)		// Interrupt Status Register                           
#define	 UDP_ICR 			__REG(0XFFFB0020)		// Interrupt Clear Register                                                                             
#define	 UDP_RSTEP 			__REG(0XFFFB0028)		// Reset Endpoint Register                                                                          
#define	 UDP_CSR0 			__REG(0XFFFB0030)		// Endpoint Control and Status Register0
#define	 UDP_CSR1 			__REG(0XFFFB0034)		// Endpoint Control and Status Register1 
#define	 UDP_CSR2 			__REG(0XFFFB0038)		// Endpoint Control and Status Register2
#define	 UDP_CSR3 			__REG(0XFFFB003C)		// Endpoint Control and Status Register3                                                            
#define	 UDP_FDR0 	 		__REG(0XFFFB0050)		// Endpoint FIFO Data Register0   
#define	 UDP_FDR1 	 		__REG(0XFFFB0054)		// Endpoint FIFO Data Register1 
#define	 UDP_FDR2 	 		__REG(0XFFFB0058)		// Endpoint FIFO Data Register2 
#define	 UDP_FDR3 	 		__REG(0XFFFB005C)		// Endpoint FIFO Data Register3                                                                  
#define	 UDP_TXVC 			__REG(0XFFFB0074)		// Transceiver Control Register                        

//SOFTWARE API DEFINITION  FOR Two-wire Interface
#define  TWI_CR 			__REG(0XFFFB8000)		// Control Register                      
#define  TWI_MMR 			__REG(0XFFFB8004)		// Master Mode Register                         
#define  TWI_IADR 			__REG(0XFFFB800C)		// Internal Address Register             
#define  TWI_CWGR 			__REG(0XFFFB8010)		// Clock Waveform Generator Register     
#define  TWI_SR 			__REG(0XFFFB8020)		// Status Register                       
#define  TWI_IER 			__REG(0XFFFB8024)		// Interrupt Enable Register             
#define  TWI_IDR 			__REG(0XFFFB8028)		// Interrupt Disable Register            
#define  TWI_IMR 			__REG(0XFFFB802C)		// Interrupt Mask Register               
#define  TWI_RHR 			__REG(0XFFFB8030)		// Receive Holding Register              
#define  TWI_THR 			__REG(0XFFFB8034)		// Transmit Holding Register     

// SOFTWARE API DEFINITION  FOR Usart
#define US0_CR 				__REG(0xFFFC0000)		// Control Register
#define US0_MR 				__REG(0xFFFC0004)		// Mode Register
#define US0_IER 			__REG(0xFFFC0008)		// Interrupt Enable Register
#define US0_IDR 			__REG(0xFFFC000C)		// Interrupt Disable Register
#define US0_IMR 			__REG(0xFFFC0010)		// Interrupt Mask Register
#define US0_CSR 			__REG(0xFFFC0014)		// Channel Status Register
#define US0_RHR 			__REG(0xFFFC0018)		// Receiver Holding Register
#define US0_THR 			__REG(0xFFFC001C)		// Transmitter Holding Register
#define US0_BRGR 			__REG(0xFFFC0020)		// Baud Rate Generator Register
#define US0_RTOR 			__REG(0xFFFC0024)		// Receiver Time-out Register
#define US0_TTGR 			__REG(0xFFFC0028)		// Transmitter Time-guard Register
#define US0_FIDI 			__REG(0xFFFC0040)		// FI_DI_Ratio Register
#define US0_NER 			__REG(0xFFFC0044)		// Nb Errors Register
#define US0_IF 				__REG(0xFFFC004C)		// IRDA_FILTER Register

// US0-dma
#define US0_RPR 			__REG(0xFFFC0100)		// Receive Pointer Register
#define US0_RCR 			__REG(0xFFFC0104)		// Receive Counter Register
#define US0_TPR 			__REG(0xFFFC0108)		// Transmit Pointer Register
#define US0_TCR 			__REG(0xFFFC010C)		// Transmit Counter Register
#define US0_RNPR 			__REG(0xFFFC0110)		// Receive Next Pointer Register
#define US0_RNCR 			__REG(0xFFFC0114)		// Receive Next Counter Register
#define US0_TNPR 			__REG(0xFFFC0118)		// Transmit Next Pointer Register
#define US0_TNCR 			__REG(0xFFFC011C)		// Transmit Next Counter Register
#define US0_PTCR 			__REG(0xFFFC0120)		// PDC Transfer Control Register
#define US0_PTSR 			__REG(0xFFFC0124)		// PDC Transfer Status Register

#define US1_CR 				__REG(0xFFFC4000)		// Control Register
#define US1_MR 				__REG(0xFFFC4004)		// Mode Register
#define US1_IER 			__REG(0xFFFC4008)		// Interrupt Enable Register
#define US1_IDR 			__REG(0xFFFC400C)		// Interrupt Disable Register
#define US1_IMR 			__REG(0xFFFC4010)		// Interrupt Mask Register
#define US1_CSR 			__REG(0xFFFC4014)		// Channel Status Register
#define US1_RHR 			__REG(0xFFFC4018)		// Receiver Holding Register
#define US1_THR 			__REG(0xFFFC401C)		// Transmitter Holding Register
#define US1_BRGR 			__REG(0xFFFC4020)		// Baud Rate Generator Register
#define US1_RTOR 			__REG(0xFFFC4024)		// Receiver Time-out Register
#define US1_TTGR 			__REG(0xFFFC4028)		// Transmitter Time-guard Register
#define US1_FIDI 			__REG(0xFFFC4040)		// FI_DI_Ratio Register
#define US1_NER 			__REG(0xFFFC4044)		// Nb Errors Register
#define US1_IF 				__REG(0xFFFC404C)		// IRDA_FILTER Register

// US1-dma
#define US1_RPR 			__REG(0xFFFC4100)		// Receive Pointer Register
#define US1_RCR 			__REG(0xFFFC4104)		// Receive Counter Register
#define US1_TPR 			__REG(0xFFFC4108)		// Transmit Pointer Register
#define US1_TCR 			__REG(0xFFFC410C)		// Transmit Counter Register
#define US1_RNPR 			__REG(0xFFFC4110)		// Receive Next Pointer Register
#define US1_RNCR 			__REG(0xFFFC4114)		// Receive Next Counter Register
#define US1_TNPR 			__REG(0xFFFC4118)		// Transmit Next Pointer Register
#define US1_TNCR 			__REG(0xFFFC411C)		// Transmit Next Counter Register
#define US1_PTCR 			__REG(0xFFFC4120)		// PDC Transfer Control Register
#define US1_PTSR 			__REG(0xFFFC4124)		// PDC Transfer Status Register


// SOFTWARE API DEFINITION  FOR Pulse Width Modulation Controller Interface
#define PWMC_MR 			__REG(0xFFFCC000)		// PWMC Mode Register
#define PWMC_ENA 			__REG(0xFFFCC004)		// PWMC Enable Register
#define PWMC_DIS 			__REG(0xFFFCC008)		// PWMC Disable Register
#define PWMC_SR 			__REG(0xFFFCC00C)		// PWMC Status Register
#define PWMC_IER 			__REG(0xFFFCC010)		// PWMC Interrupt Enable Register
#define PWMC_IDR 			__REG(0xFFFCC014)		// PWMC Interrupt Disable Register
#define PWMC_IMR 			__REG(0xFFFCC018)		// PWMC Interrupt Mask Register
#define PWMC_ISR 			__REG(0xFFFCC01C)		// PWMC Interrupt Status Register
#define PWMC_VR 			__REG(0xFFFCC0FC)		// PWMC Version Register

#define PWMC_CH0_CMR 		__REG(0xFFFCC200) 		// (PWMC_CH0) Channel Mode Register
#define PWMC_CH0_CDTYR 		__REG(0xFFFCC204) 		// (PWMC_CH0) Channel Duty Cycle Register
#define PWMC_CH0_CPRDR 		__REG(0xFFFCC208) 		// (PWMC_CH0) Channel Period Register
#define PWMC_CH0_CCNTR 		__REG(0xFFFCC20C) 		// (PWMC_CH0) Channel Counter Register
#define PWMC_CH0_CUPDR 		__REG(0xFFFCC210) 		// (PWMC_CH0) Channel Update Register

#define PWMC_CH1_CMR 		__REG(0xFFFCC220) 		// (PWMC_CH0) Channel Mode Register
#define PWMC_CH1_CDTYR 		__REG(0xFFFCC224) 		// (PWMC_CH0) Channel Duty Cycle Register
#define PWMC_CH1_CPRDR 		__REG(0xFFFCC228) 		// (PWMC_CH0) Channel Period Register
#define PWMC_CH1_CCNTR 		__REG(0xFFFCC22C) 		// (PWMC_CH0) Channel Counter Register
#define PWMC_CH1_CUPDR 		__REG(0xFFFCC230) 		// (PWMC_CH0) Channel Update Register

#define PWMC_CH2_CMR 		__REG(0xFFFCC240) 		// (PWMC_CH0) Channel Mode Register
#define PWMC_CH2_CDTYR 		__REG(0xFFFCC244) 		// (PWMC_CH0) Channel Duty Cycle Register
#define PWMC_CH2_CPRDR 		__REG(0xFFFCC248) 		// (PWMC_CH0) Channel Period Register
#define PWMC_CH2_CCNTR 		__REG(0xFFFCC24C) 		// (PWMC_CH0) Channel Counter Register
#define PWMC_CH2_CUPDR 		__REG(0xFFFCC250) 		// (PWMC_CH0) Channel Update Register

#define PWMC_CH3_CMR 		__REG(0xFFFCC260) 		// (PWMC_CH0) Channel Mode Register
#define PWMC_CH3_CDTYR 		__REG(0xFFFCC264) 		// (PWMC_CH0) Channel Duty Cycle Register
#define PWMC_CH3_CPRDR 		__REG(0xFFFCC268) 		// (PWMC_CH0) Channel Period Register
#define PWMC_CH3_CCNTR 		__REG(0xFFFCC26C) 		// (PWMC_CH0) Channel Counter Register
#define PWMC_CH3_CUPDR 		__REG(0xFFFCC270) 		// (PWMC_CH0) Channel Update Register

// SOFTWARE API DEFINITION  FOR Synchronous Serial Controller Interface
#define SSC_CR 				__REG(0xFFFD4000)		// Control Register
#define SSC_CMR 			__REG(0xFFFD4004)		// Clock Mode Register
                    		
#define SSC_RCMR 			__REG(0xFFFD4010)		// Receive Clock ModeRegister
#define SSC_RFMR 			__REG(0xFFFD4014)		// Receive Frame Mode Register
#define SSC_TCMR 			__REG(0xFFFD4018)		// Transmit Clock Mode Register
#define SSC_TFMR 			__REG(0xFFFD401C)		// Transmit Frame Mode Register
#define SSC_RHR 			__REG(0xFFFD4020)		// Receive Holding Register
#define SSC_THR 			__REG(0xFFFD4024)		// Transmit Holding Register
                    		
#define SSC_RSHR 			__REG(0xFFFD4030)		// Receive Sync Holding Register
#define SSC_TSHR 			__REG(0xFFFD4034)		// Transmit Sync Holding Register
                    		
#define SSC_SR 				__REG(0xFFFD4040)		// Status Register
#define SSC_IER 			__REG(0xFFFD4044)		// Interrupt Enable Register
#define SSC_IDR 			__REG(0xFFFD4048)		// Interrupt Disable Register
#define SSC_IMR 			__REG(0xFFFD404C)		// Interrupt Mask Register
/* No Found Manual Offset
#define SSC_RPR 			__REG(0xFFFD4000)		// Receive Pointer Register
#define SSC_RCR 			__REG(0xFFFD4000)		// Receive Counter Register
#define SSC_TPR 			__REG(0xFFFD4000)		// Transmit Pointer Register
#define SSC_TCR 			__REG(0xFFFD4000)		// Transmit Counter Register
#define SSC_RNPR 			__REG(0xFFFD4000)		// Receive Next Pointer Register
#define SSC_RNCR 			__REG(0xFFFD4000)		// Receive Next Counter Register
#define SSC_TNPR 			__REG(0xFFFD4000)		// Transmit Next Pointer Register
#define SSC_TNCR 			__REG(0xFFFD4000)		// Transmit Next Counter Register
#define SSC_PTCR 			__REG(0xFFFD4000)		// PDC Transfer Control Register
#define SSC_PTSR 			__REG(0xFFFD4000)		// PDC Transfer Status Register
*/

// SOFTWARE API DEFINITION  FOR Analog to Digital Convertor
#define ADC_CR 				__REG(0xFFFD8000)		// ADC Control Register
#define ADC_MR 				__REG(0xFFFD8004)		// ADC Mode Register
#define ADC_CHER 			__REG(0xFFFD8010)		// ADC Channel Enable Register
#define ADC_CHDR 			__REG(0xFFFD8014)		// ADC Channel Disable Register
#define ADC_CHSR 			__REG(0xFFFD8018)		// ADC Channel Status Register
#define ADC_SR 				__REG(0xFFFD801C)		// ADC Status Register
#define ADC_LCDR 			__REG(0xFFFD8020)		// ADC Last Converted Data Register
#define ADC_IER 			__REG(0xFFFD8024)		// ADC Interrupt Enable Register
#define ADC_IDR 			__REG(0xFFFD8028)		// ADC Interrupt Disable Register
#define ADC_IMR 			__REG(0xFFFD802C)		// ADC Interrupt Mask Register
#define ADC_CDR0 			__REG(0xFFFD8030)		// ADC Channel Data Register 0
#define ADC_CDR1 			__REG(0xFFFD8034)		// ADC Channel Data Register 1
#define ADC_CDR2 			__REG(0xFFFD8038)		// ADC Channel Data Register 2
#define ADC_CDR3 			__REG(0xFFFD803C)		// ADC Channel Data Register 3
#define ADC_CDR4 			__REG(0xFFFD8040)		// ADC Channel Data Register 4
#define ADC_CDR5 			__REG(0xFFFD8044)		// ADC Channel Data Register 5
#define ADC_CDR6 			__REG(0xFFFD8048)		// ADC Channel Data Register 6
#define ADC_CDR7 			__REG(0xFFFD804C)		// ADC Channel Data Register 7
/* No Found Manual Offset
#define ADC_RPR 			__REG(0xFFFD8000)		// Receive Pointer Register
#define ADC_RCR 			__REG(0xFFFD8000)		// Receive Counter Register
#define ADC_TPR 			__REG(0xFFFD8000)		// Transmit Pointer Register
#define ADC_TCR 			__REG(0xFFFD8000)		// Transmit Counter Register
#define ADC_RNPR 			__REG(0xFFFD8000)		// Receive Next Pointer Register
#define ADC_RNCR 			__REG(0xFFFD8000)		// Receive Next Counter Register
#define ADC_TNPR 			__REG(0xFFFD8000)		// Transmit Next Pointer Register
#define ADC_TNCR 			__REG(0xFFFD8000)		// Transmit Next Counter Register
#define ADC_PTCR 			__REG(0xFFFD8000)		// PDC Transfer Control Register
#define ADC_PTSR 			__REG(0xFFFD8000)		// PDC Transfer Status Register
*/

//SOFTWARE API DEFINITION  FOR Serial Parallel Interface
#define	 SPI_CR 			__REG(0XFFFE0000)		// Control Register                
#define	 SPI_MR 			__REG(0XFFFE0004)		// Mode Register                   
#define	 SPI_RDR 			__REG(0XFFFE0008)		// Receive Data Register         
#define	 SPI_TDR 			__REG(0XFFFE000C)		// Transmit Data Register        
#define	 SPI_SR 			__REG(0XFFFE0010)		// Status Register                 
#define	 SPI_IER 			__REG(0XFFFE0014)		// Interrupt Enable Register     
#define	 SPI_IDR 			__REG(0XFFFE0018)		// Interrupt Disable Register    
#define	 SPI_IMR 			__REG(0XFFFE001C)		// Interrupt Mask Register                                
#define	 SPI_CSR0 			__REG(0XFFFE0030)		// Chip Select Register1 
#define	 SPI_CSR1         	__REG(0XFFFE0034)       // Chip Select Register2
#define	 SPI_CSR2         	__REG(0XFFFE0038)		// Chip Select Register3	
#define	 SPI_CSR3         	__REG(0XFFFE003C)		// Chip Select Register4
                                         
/* No Found Manual offset                           
#define	 SPI_RPR 			__REG					// Receive Pointer Register      
#define	 SPI_RCR 			__REG					// Receive Counter Register      
#define	 SPI_TPR 			__REG					// Transmit Pointer Register     
#define	 SPI_TCR 			__REG					// Transmit Counter Register     
#define	 SPI_RNPR 			__REG					// Receive Next Pointer Register 
#define	 SPI_RNCR 			__REG					// Receive Next Counter Register 
#define	 SPI_TNPR 			__REG					// Transmit Next Pointer Register
#define	 SPI_TNCR 			__REG					// Transmit Next Counter Register
#define	 SPI_PTCR 			__REG					// PDC Transfer Control Register 
#define	 SPI_PTSR 			__REG					// PDC Transfer Status Register  
*/

// SOFTWARE API DEFINITION  FOR Advanced Interrupt Controller
#define AIC_SMR 			__REG(0xFFFFF000)		// Source Mode Register     0 ~ 31
#define AIC_SVR 			__REG(0xFFFFF080)		// Source Vector Register   0 ~ 31
#define AIC_IVR 			__REG(0xFFFFF100)		// IRQ Vector Register
#define AIC_FVR 			__REG(0xFFFFF104)		// FIQ Vector Register
#define AIC_ISR 			__REG(0xFFFFF108)		// Interrupt Status Register
#define AIC_IPR 			__REG(0xFFFFF10C)		// Interrupt Pending Register
#define AIC_IMR 			__REG(0xFFFFF110)		// Interrupt Mask Register
#define AIC_CISR 			__REG(0xFFFFF114)		// Core Interrupt Status Register
#define AIC_IECR 			__REG(0xFFFFF120)		// Interrupt Enable Command Register
#define AIC_IDCR 			__REG(0xFFFFF124)		// Interrupt Disable Command Register
#define AIC_ICCR 			__REG(0xFFFFF128)		// Interrupt Clear Command Register
#define AIC_ISCR 			__REG(0xFFFFF12C)		// Interrupt Set Command Register
#define AIC_EOICR 			__REG(0xFFFFF130)		// End of Interrupt Command Register
#define AIC_SPU 			__REG(0xFFFFF134)		// Spurious Vector Register
#define AIC_DCR 			__REG(0xFFFFF138)		// Debug Control Register (Protect)
#define AIC_FFER 			__REG(0xFFFFF140)		// Fast Forcing Enable Register
#define AIC_FFDR 			__REG(0xFFFFF144)		// Fast Forcing Disable Register
#define AIC_FFSR 			__REG(0xFFFFF148)		// Fast Forcing Status Register

//SOFTWARE API DEFINITION  FOR Peripheral DMA Controller
//#define	PDC_RPR 			__REG(0XFFFFF100)		// Receive Pointer Register
//#define	PDC_RCR 			__REG(0XFFFFF104)		// Receive Counter Register
//#define	PDC_TPR 			__REG(0XFFFFF108)		// Transmit Pointer Register
//#define	PDC_TCR 			__REG(0XFFFFF10C)		// Transmit Counter Register
//#define	PDC_RNPR 			__REG(0XFFFFF110)		// Receive Next Pointer Register
//#define	PDC_RNCR 			__REG(0XFFFFF114)		// Receive Next Counter Register
//#define	PDC_TNPR 			__REG(0XFFFFF118)		// Transmit Next Pointer Register
//#define	PDC_TNCR 			__REG(0XFFFFF11C)		// Transmit Next Counter Register
//#define	PDC_PTCR 			__REG(0XFFFFF120)		// PDC Transfer Control Register
//#define	PDC_PTSR 			__REG(0XFFFFF124)		// PDC Transfer Status Register 

// SOFTWARE API DEFINITION  FOR Debug Unit
#define DBGU_CR 			__REG(0xFFFFF200)		// Control Register
#define DBGU_MR 			__REG(0xFFFFF204)		// Mode Register
#define DBGU_IER 			__REG(0xFFFFF208)		// Interrupt Enable Register
#define DBGU_IDR 			__REG(0xFFFFF20C)		// Interrupt Disable Register
#define DBGU_IMR 			__REG(0xFFFFF210)		// Interrupt Mask Register
#define DBGU_CSR 			__REG(0xFFFFF214)		// Channel Status Register
#define DBGU_RHR 			__REG(0xFFFFF218)		// Receiver Holding Register
#define DBGU_THR 			__REG(0xFFFFF21C)		// Transmitter Holding Register
#define DBGU_BRGR 			__REG(0xFFFFF220)		// Baud Rate Generator Register
#define DBGU_CIDR 			__REG(0xFFFFF240)		// Chip ID Register
#define DBGU_EXID 			__REG(0xFFFFF244)		// Chip ID Extension Register
#define DBGU_FNTR 			__REG(0xFFFFF248)		// Force NTRST Register

#define	DBGU_RPR 			__REG(0XFFFFF300)		// Receive Pointer Register
#define	DBGU_RCR 			__REG(0XFFFFF304)		// Receive Counter Register
#define	DBGU_TPR 			__REG(0XFFFFF308)		// Transmit Pointer Register
#define	DBGU_TCR 			__REG(0XFFFFF30C)		// Transmit Counter Register
#define	DBGU_RNPR 			__REG(0XFFFFF310)		// Receive Next Pointer Register
#define	DBGU_RNCR 			__REG(0XFFFFF314)		// Receive Next Counter Register
#define	DBGU_TNPR 			__REG(0XFFFFF318)		// Transmit Next Pointer Register
#define	DBGU_TNCR 			__REG(0XFFFFF31C)		// Transmit Next Counter Register
#define	DBGU_PTCR 			__REG(0XFFFFF320)		// PDC Transfer Control Register
#define	DBGU_PTSR 			__REG(0XFFFFF324)		// PDC Transfer Status Register 
        

// SOFTWARE API DEFINITION  FOR Parallel Input Output Controler

#define PIO_PER				__REG(0xFFFFF400)	 	// PIO Enable Register
#define PIO_PDR 			__REG(0xFFFFF404)		// PIO Disable Register
#define PIO_PSR 			__REG(0xFFFFF408)		// PIO Status Register
                                               
#define PIO_OER 			__REG(0xFFFFF410)		// Output Enable Register
#define PIO_ODR 			__REG(0xFFFFF414)		// Output Disable Registerr
#define PIO_OSR 			__REG(0xFFFFF418)		// Output Status Register
                                               
#define PIO_IFER 			__REG(0xFFFFF420)		// Input Filter Enable Register
#define PIO_IFDR 			__REG(0xFFFFF424)		// Input Filter Disable Register
#define PIO_IFSR 			__REG(0xFFFFF428)		// Input Filter Status Register
                                               
#define PIO_SODR  			__REG(0xFFFFF430)		// Set Output Data Register
#define PIO_CODR  			__REG(0xFFFFF434)		// Clear Output Data Register
#define PIO_ODSR  			__REG(0xFFFFF438)		// Output Data Status Register
#define PIO_PDSR  			__REG(0xFFFFF43C)		// Pin Data Status Register

#define PIO_PER_S				__REG_S(0xFFFFF400)	 	// PIO Enable Register
#define PIO_PDR_S 			__REG_S(0xFFFFF404)		// PIO Disable Register
#define PIO_PSR_S 			__REG_S(0xFFFFF408)		// PIO Status Register
                                               
#define PIO_OER_S 			__REG_S(0xFFFFF410)		// Output Enable Register
#define PIO_ODR_S 			__REG_S(0xFFFFF414)		// Output Disable Registerr
#define PIO_OSR_S 			__REG_S(0xFFFFF418)		// Output Status Register
                                               
#define PIO_IFER_S 			__REG_S(0xFFFFF420)		// Input Filter Enable Register
#define PIO_IFDR_S 			__REG_S(0xFFFFF424)		// Input Filter Disable Register
#define PIO_IFSR_S 			__REG_S(0xFFFFF428)		// Input Filter Status Register

#define PIO_SODR_S  			__REG_S(0xFFFFF430)		// Set Output Data Register
#define PIO_CODR_S  			__REG_S(0xFFFFF434)		// Clear Output Data Register
#define PIO_ODSR_S  			__REG_S(0xFFFFF438)		// Output Data Status Register
#define PIO_PDSR_S  			__REG_S(0xFFFFF43C)		// Pin Data Status Register

#define PIO_IER  			__REG(0xFFFFF440)		// Interrupt Enable Register
#define PIO_IDR  			__REG(0xFFFFF444)		// Interrupt Disable Register
#define PIO_IMR  			__REG(0xFFFFF448)		// Interrupt Mask Register
#define PIO_ISR  			__REG(0xFFFFF44C)		// Interrupt Status Register
#define PIO_MDER  			__REG(0xFFFFF450)		// Multi-driver Enable Register
#define PIO_MDDR  			__REG(0xFFFFF454)		// Multi-driver Disable Register
#define PIO_MDSR  			__REG(0xFFFFF458)		// Multi-driver Status Register
                                               
#define PIO_PUDR  			__REG(0xFFFFF460)		// Pull-up Disable Register
#define PIO_PUER  			__REG(0xFFFFF464)		// Pull-up Enable Register
#define PIO_PUSR  			__REG(0xFFFFF468)		// Pull-up Status Register
                                               
#define PIO_ASR  			__REG(0xFFFFF470)		// Select A Register
#define PIO_BSR  			__REG(0xFFFFF474)		// Select B Register
#define PIO_ABSR  			__REG(0xFFFFF478)		// AB Select Status Register
                                               
#define PIO_OWER  			__REG(0xFFFFF4A0)		// Output Write Enable Register
#define PIO_OWDR  			__REG(0xFFFFF4A4)		// Output Write Disable Register
#define PIO_OWSR  			__REG(0xFFFFF4A8)		// Output Write Status Register

// SOFTWARE API DEFINITION  FOR Clock Generator Controler
#define CKGR_MOR 			__REG(0xFFFFFC20)		// Main Oscillator Register
#define CKGR_MCFR 			__REG(0xFFFFFC24)		// Main Clock  Frequency Register
#define CKGR_PLLR 			__REG(0xFFFFFC2C)		// PLL Register

// SOFTWARE API DEFINITION  FOR Power Management Controler
#define PMC_SCER 			__REG(0xFFFFFC00)		// System Clock Enable Register
#define PMC_SCDR 			__REG(0xFFFFFC04)		// System Clock Disable Register
#define PMC_SCSR 			__REG(0xFFFFFC08)		// System Clock Status Register
#define PMC_PCER 			__REG(0xFFFFFC10)		// Peripheral Clock Enable Register
#define PMC_PCDR 			__REG(0xFFFFFC14)		// Peripheral Clock Disable Register
#define PMC_PCSR 			__REG(0xFFFFFC18)		// Peripheral Clock Status Register
#define PMC_MOR 			__REG(0xFFFFFC20)		// Main Oscillator Register
#define PMC_MCFR 			__REG(0xFFFFFC24)		// Main Clock  Frequency Register
#define PMC_PLLR 			__REG(0xFFFFFC2C)		// PLL Register
#define PMC_MCKR 			__REG(0xFFFFFC30)		// Master Clock Register
#define PMC_PCKR0 			__REG(0xFFFFFC40)		// Programmable Clock Register
#define PMC_PCKR1 			__REG(0xFFFFFC44)		// Programmable Clock Register
#define PMC_IER 			__REG(0xFFFFFC60)		// Interrupt Enable Register
#define PMC_IDR 			__REG(0xFFFFFC64)		// Interrupt Disable Register
#define PMC_SR 				__REG(0xFFFFFC68)		// Status Register
#define PMC_IMR 			__REG(0xFFFFFC6C)		// Interrupt Mask Register

//SOFTWARE API DEFINITION  FOR Reset Controller Interface
#define	RSTC_RCR			__REG(0XFFFFFD00) 		// Reset Control Register
#define	RSTC_RSR			__REG(0XFFFFFD04) 		// Reset Status Register 
#define	RSTC_RMR			__REG(0XFFFFFD08) 		// Reset Mode Register   

// SOFTWARE API DEFINITION  FOR Real Time Timer Controller Interface
#define RTTC_RTMR			__REG(0xFFFFFD20)	 	// Real-time Mode Register
#define RTTC_RTAR	 		__REG(0xFFFFFD24)		// Real-time Alarm Register
#define RTTC_RTVR	 		__REG(0xFFFFFD28)		// Real-time Value Register
#define RTTC_RTSR	 		__REG(0xFFFFFD2C)		// Real-time Status Register

//SOFTWARE API DEFINITION  FOR Periodic Interval Timer Controller Interface
#define PITC_PIMR 			__REG(0XFFFFFD30)		// Period Interval Mode Register  
#define PITC_PISR 			__REG(0XFFFFFD34)		// Period Interval Status Register                 
#define PITC_PIVR 			__REG(0XFFFFFD38)		// Period Interval Value Register #define#endif // _REGI__REGSTER_HEADER_
#define PITC_PIIR 			__REG(0XFFFFFD3C)		// Period Interval Image Register 
                        	
//SOFTWARE API DEFINITION  FOR Watchdog Timer Controller Interface 
#define	WDTC_WDCR 			__REG(0XFFFFFD40)		// Watchdog Control Register 
#define	WDTC_WDMR 			__REG(0XFFFFFD44)		// Watchdog Mode Register    
#define	WDTC_WDSR 			__REG(0XFFFFFD48)		// Watchdog Status Register  

// SOFTWARE API DEFINITION  FOR Voltage Regulator Mode Controller Interface
#define VREG_MR				__REG(0xFFFFFD60) 		// Voltage Regulator Mode Register

//              SOFTWARE API DEFINITION  FOR Memory Controller Interface
#define MC_RCR 				__REG(0xFFFFFF00)		// MC Remap Control Register
#define MC_ASR 				__REG(0xFFFFFF04)		// MC Abort Status Register
#define MC_AASR 			__REG(0xFFFFFF08)		// MC Abort Address Status Register
#define MC_FMR 				__REG(0xFFFFFF60)		// MC Flash Mode Register
#define MC_FCR 				__REG(0xFFFFFF64)		// MC Flash Command Register
#define MC_FSR 				__REG(0xFFFFFF68)		// MC Flash Status Register

 

#endif // _REGISTER_HEADER_

