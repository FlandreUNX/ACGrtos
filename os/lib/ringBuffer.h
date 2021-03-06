/**　　　　　　 ,-...　　　 　 　 　　　..-.
 *　　　　　 ./:::::＼　　　　 　 　  ／:::::ヽ
 *　　　　  /::::::::::::;ゝ--──-- .._/:::::::ヽ
 *　　　　 /,.-‐''"′                  ＼:::::::|
 *　　　  ／　 　　　　　　　　　　　　  ヽ.::|
 *　　　　/　　　　●　　　 　 　 　 　 　 ヽ|
 *　　 　 l　　　...　　 　 　 　  ●　      l
 *　　　 .|　　　 　　 (_人__丿   ...　    |
 *　 　 　l　　　　　　　　　　　　 　　  l
 *　　　　` .　　　　　　　　 　 　 　　 /
 *　　　　　　`. .__　　　 　 　 　　.／
 *　　　　　　　　　/`'''.‐‐──‐‐‐┬---
 * File      : ringBuffer.c
 * This file is part of aRTOS
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/**
 *  参考原理
 *  http://en.wikipedia.org/wiki/Circular_buffer#Mirroring 
 *  使用in/out相等状态以及标志位(mirror)来确定环形缓冲是否满或者是空
 */
 
#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

/**
 * @addtogroup OS Include
 */

/*@{*/

#include "../arch/platform.h"

/*@}*/

/**
 * @addtogroup 定义
 */
 
/*@{*/

/**
 *  buffer储存状态
 *  @note none
 */
enum BUFFER_STAGE {
  RBUFFER_EMPTY,
  RBUFFER_FULL,
  RBUFFER_HALFFULL
};


/**
 *  buffer对象结构体
 *  @note none
 */
typedef struct ring_buffer {
  uint16_t size;        /**< 缓冲器大小 */
  uint8_t *pBuffer;     /**< 缓冲器指针 */

  uint16_t in : 15;             /**< 进指标 */
  uint16_t out : 15;            /**< 出指标 */
  uint16_t in_Mirror : 1;       /**< 进指标_镜像 标记是否回绕 */
  uint16_t out_Mirror : 1;      /**< 出指标_镜像 标记是否回绕 */  
}osRBuffer_t;

/*@}*/

/**
 * @addtogroup 创建
 */
 
/*@{*/
       
extern osRBuffer_t* osRBuffer_Create(uint16_t size);
extern osRBuffer_t* osRBuffer_StaticCreate(void *pool, uint16_t size);

/*@}*/

/**
 * @addtogroup 查询
 */
 
/*@{*/

extern enum BUFFER_STAGE osRBuffer_GetState(osRBuffer_t *obj);
        
extern uint16_t osRBuffer_GetDataLen(osRBuffer_t *obj);
extern uint16_t osRBuffer_GetSpaceLen(osRBuffer_t *obj);

/*@}*/

/**
 * @addtogroup 操作
 */
 
/*@{*/
        
extern uint16_t osRBuffer_Put(osRBuffer_t *obj, const uint8_t *src, uint16_t len);
extern uint16_t osRBuffer_Get(osRBuffer_t *obj, uint8_t *dest, uint16_t len);
        
extern uint8_t osRBuffer_PutByte(osRBuffer_t *obj, uint8_t src);
extern uint8_t osRBuffer_GetByte(osRBuffer_t *obj, uint8_t *dest);

extern void osRBuffer_Clear(osRBuffer_t *obj);
        
/*@}*/    
#endif
