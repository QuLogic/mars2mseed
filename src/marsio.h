/*
$Header: /usr/local/cvs/repository/mars2mseed/src/marsio.h,v 1.4 2006-07-27 17:28:00 chad Exp $
*/
#ifndef MARSIO_H_
 #define MARSIO_H_

 #include <stdio.h>
 #include <time.h>
 
 #include <libmseed.h>

 #include "mars.h"
 
 #define msStreamActive       0x00000001 
 #define msLongHeaders        0x00000100
 
 #define msCheckStatus(a,b)   ( (a)&(b) )
 
 #define mbHeaderMacros
 #define mbGetMagic(a)	      ((((m88Head *)(a))->format_id).magic)
 #define mbGetBlockFormat(a)  ((((m88Head *)(a))->format_id).block_format)
 #define mbGetDataFormat(a)   ((((m88Head *)(a))->format_id).data_format)
 
 #define mbGetChan(a)	      (((m88Head *)(a))->chno)
 #define mbGetSamp(a)	      (1<<(((m88Head *)(a))->samp_rate))
 #define mbGetSampRate(a)     (1000.0/mbGetSamp(a))
 #define mbGetMaxamp(a)	      (((m88Head *)(a))->maxamp)
 #define mbGetScale(a)	      (1<<((m88Head *)(a))->scale)
 #define mbGetTime(a)	      ( ((((m88Head *)(a))->format_id).data_format < LITE_BLOCK_FORMAT) ? (((m88Head *)(a))->time).time : ((mlHead *)(a))->time  )

 typedef struct
 {
  FILE	*hf;
  off_t	offset;
  char	block[marsBlockSize];
  
  size_t  status;
  
  /*	file info	*/
  off_t		size;
  time_t	time;
  char 		name[4096];
 
 } marsStream;
 
/*********************************************************
***   Function Prototypes
**********************************************************/
 #ifdef __cplusplus
  extern "C" {
 #endif
 
 marsStream *marsStreamOpen(char *name);
 marsStream *marsStreamGetNextBlock(int verbose);
 marsStream *marsStreamGetCurrent(void);
 
 void marsStreamClose(void);
 void m88SwapBlock(m88Block *blk);
 
 int *marsBlockDecodeData(char *block,int *scale);
 int marsStreamDumpBlock(marsStream *hMS);

 double marsBlockGetGain(char *blk);
 int marsBlockGetScaleFactor(char *blk);
 char *mbGetStationCode(char *blk);
 int mbGetStationSerial(char *blk);
 
 #ifdef __cplusplus
  }
 #endif
#endif
