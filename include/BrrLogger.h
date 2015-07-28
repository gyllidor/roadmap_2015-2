//! ************************************************************************************************
//! @file   BrrLogger.h
//! @brief  helpfull macroses for printf
//! @author gyllidor (gyllidor@ukr.net)
//! @date   24 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef BRR_LOGGER_H
#define BRR_LOGGER_H

// system
#include <string>
#include <cstdio>
#include <cstdlib>
#include <string.h>

namespace brr
{

//! ************************************************************************************************
//! @brief  Get description of system error, stored in errno or returned by soome function, for
//! example pthread_cancel.
//! @param  [in] error number (errno for example).
//! @return description of system error.
//! ************************************************************************************************
std::string StrErrno( int error );

//! ************************************************************************************************
//! @brief  Get description of system error, stored in errno.
//! @return description of errno;
//! ************************************************************************************************
std::string StrErrno();

} // namespace brr

//! ************************************************************************************************
//! @brief escape codes for font colors (FC_);
//! ************************************************************************************************
#define BRR_FC_CYAN     "\033[36m"
#define BRR_FC_YELLOW   "\033[33m"
#define BRR_FC_RED      "\033[31m"
#define BRR_FC_WHITE    "\033[37m"
#define BRR_FC_RESET    "\033[0m"

//! ************************************************************************************************
//! @brief cut file name from file path.
//! ************************************************************************************************
#ifdef __FILE_NAME__
#warning macros __FILE_NAME__ already defined, you should change macros name
#else // __FILE_NAME__
#define  __FILE_NAME__ ((strrchr(__FILE__, '/') + 1) ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif // __FILE_NAME__

//! ************************************************************************************************
//! @brief prepare prefix for log message - [I][FILE_NAME][FUNCTION][LINE_NUMBER]${message};\n.
//! ************************************************************************************************
#define PREPARE_FORMAT(prefix, format) \
prefix "[%s][%s][%d]: " BRR_FC_RESET format ";\n", __FILE_NAME__, __FUNCTION__, __LINE__

#ifdef DEBUG_BUILD

//! ************************************************************************************************
//! @brief Print message to stderr with helpfull tags (example [I][main.cpp][main][26]: test info;).
//! ************************************************************************************************
#define BRR_LOGI(format, arg...) fprintf(stderr, PREPARE_FORMAT(BRR_FC_CYAN   "[I]", format), ##arg)
#define BRR_LOGW(format, arg...) fprintf(stderr, PREPARE_FORMAT(BRR_FC_YELLOW "[W]", format), ##arg)
#define BRR_LOGE(format, arg...) fprintf(stderr, PREPARE_FORMAT(BRR_FC_RED    "[E]", format), ##arg)

//! ************************************************************************************************
//! @brief Print message to stderr without formating (_WF).
//! ************************************************************************************************
#define BRR_LOGI_WF(format, arg...) fprintf(stderr, format, ##arg)
#define BRR_LOGW_WF(format, arg...) fprintf(stderr, format, ##arg)
#define BRR_LOGE_WF(format, arg...) fprintf(stderr, format, ##arg)

#ifdef VERBOSE_LOGGER
#define BRR_LOGV(format, arg...) fprintf(stderr, PREPARE_FORMAT(BRR_FC_WHITE  "[V]", format), ##arg)
#define BRR_LOGV_WF(format, arg...) fprintf(stderr, format, ##arg)
#else
#define BRR_LOGV
#define BRR_LOGV_WF
#endif // VERBOSE_LOGGER

#else // DEBUG_BUILD

#define BRR_LOGI(format, arg...) fprintf(stdout, "[I] " format, ##arg)
#define BRR_LOGW(format, arg...) fprintf(stdout, "[W] " format, ##arg)
#define BRR_LOGE(format, arg...) fprintf(stderr, "[E] " format, ##arg)
#define BRR_LOGV(format, arg...)

#define BRR_LOGI_WF(format, arg...) fprintf(stderr, format, ##arg)
#define BRR_LOGW_WF(format, arg...) fprintf(stderr, format, ##arg)
#define BRR_LOGE_WF(format, arg...) fprintf(stderr, format, ##arg)
#define BRR_LOGV_WF

#endif // DEBUG_BUILD

#endif // BRR_LOGGER_H
