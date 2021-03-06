#if !defined( __WLAN_HDD_DP_UTILS_H )
#define __WLAN_HDD_DP_UTILS_H

/**=============================================================================
  wlan_hdd_dp_utils.h
  
  \brief      Utility functions for data path module
  
  Description...
               Copyright 2008 (c) Qualcomm, Incorporated.
               All Rights Reserved.
               Qualcomm Confidential and Proprietary.
  
  ==============================================================================**/
/* $HEADER$ */
  
/**-----------------------------------------------------------------------------
  Include files
  ----------------------------------------------------------------------------*/
#include <linux/list.h>
#include <vos_types.h>
#include <linux/kernel.h>
#include <i_vos_types.h>
#include <vos_status.h>
#include <linux/spinlock.h>
#include <vos_trace.h>
#ifdef WLAN_SOFTAP_FEATURE
#include <vos_list.h>
#endif

/**-----------------------------------------------------------------------------
  Preprocessor definitions and constants
 ----------------------------------------------------------------------------*/
  
/**-----------------------------------------------------------------------------
  Type declarations
 ----------------------------------------------------------------------------*/

typedef struct list_head hdd_list_node_t;

typedef struct hdd_list_s
{
   hdd_list_node_t anchor;
   v_SIZE_t count;
   v_SIZE_t max_size;
   spinlock_t lock; 
} hdd_list_t;

typedef struct
{
   hdd_list_node_t anchor;
   struct sk_buff *skb;
   int userPriority;
} skb_list_node_t;

//FIXME Need a helper function to cleanup skbs in a queue. Required for cleanup/shutdown
  
/**-----------------------------------------------------------------------------
  Function declarations and documenation
 ----------------------------------------------------------------------------*/
VOS_INLINE_FN v_VOID_t hdd_list_init( hdd_list_t *pList, v_SIZE_t max_size)
{
   INIT_LIST_HEAD( &pList->anchor );
   pList->count = 0;
   pList->max_size = max_size;
   spin_lock_init(&pList->lock);
}

VOS_INLINE_FN v_VOID_t hdd_list_destroy( hdd_list_t *pList )
{
   if ( pList->count !=0 )
   {
       VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO_HIGH, "%s: list length not equal to zero",__func__);
   }
}

VOS_INLINE_FN v_VOID_t hdd_list_size( hdd_list_t *pList, v_SIZE_t *pSize )
{
   *pSize = pList->count;
}

VOS_STATUS hdd_list_insert_front( hdd_list_t *pList, hdd_list_node_t *pNode );

VOS_STATUS hdd_list_insert_back( hdd_list_t *pList, hdd_list_node_t *pNode );

VOS_STATUS hdd_list_insert_back_size( hdd_list_t *pList, hdd_list_node_t *pNode, v_SIZE_t *pSize );

VOS_STATUS hdd_list_remove_front( hdd_list_t *pList, hdd_list_node_t **ppNode );

VOS_STATUS hdd_list_remove_back( hdd_list_t *pList, hdd_list_node_t **ppNode );

VOS_STATUS hdd_list_remove_node( hdd_list_t *pList, hdd_list_node_t *pNodeToRemove );
VOS_STATUS hdd_list_peek_front( hdd_list_t *pList, hdd_list_node_t **ppNode );
VOS_STATUS hdd_list_peek_next( hdd_list_t *pList, hdd_list_node_t *pNode,
                               hdd_list_node_t **ppNode );
VOS_STATUS hdd_string_to_hex( char *pSrcMac, int length, char *pDescMac );
#endif //__WLAN_HDD_DP_UTILS_H
