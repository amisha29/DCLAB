/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _FILE_H_RPCGEN
#define _FILE_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


#define HEXOCT 1
#define HEXOCT_1 1

#if defined(__STDC__) || defined(__cplusplus)
#define toHex 1
extern  int * tohex_1(int *, CLIENT *);
extern  int * tohex_1_svc(int *, struct svc_req *);
#define toOct 2
extern  int * tooct_1(int *, CLIENT *);
extern  int * tooct_1_svc(int *, struct svc_req *);
extern int hexoct_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define toHex 1
extern  int * tohex_1();
extern  int * tohex_1_svc();
#define toOct 2
extern  int * tooct_1();
extern  int * tooct_1_svc();
extern int hexoct_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_FILE_H_RPCGEN */