/**
 * \file HelperMacros.cpp
 * \date Jun 21, 2010
 * \author samael
 */

#include <pthread.h>

pthread_mutex_t g_mxcout = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_mxcerr = PTHREAD_MUTEX_INITIALIZER;
