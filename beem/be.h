/*
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#ifndef BE_H_INCLUDED
#define BE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <errno.h>
#include <stddef.h>
#include <stdint.h>

/*  Handle DSO symbol visibility. */
#if !defined(BE_EXPORT)
#    if defined(_WIN32) && !defined(BE_STATIC_LIB)
#        if defined BE_SHARED_LIB
#            define BE_EXPORT __declspec(dllexport)
#        else
#            define BE_EXPORT __declspec(dllimport)
#        endif
#    else
#        define BE_EXPORT extern
#    endif
#endif

/******************************************************************************/
/*  ABI versioning support.                                                   */
/******************************************************************************/

/*  Don't change this unless you know exactly what you're doing and have      */
/*  read and understand the following documents:                              */
/*  www.gnu.org/software/libtool/manual/html_node/Libtool-versioning.html     */
/*  www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html  */

/*  The current interface version. */
#define BE_VERSION_CURRENT 5

/*  The latest revision of the current interface. */
#define BE_VERSION_REVISION 0

/*  How many past interface versions are still supported. */
#define BE_VERSION_AGE 0

/******************************************************************************/
/*  Errors.                                                                   */
/******************************************************************************/

/*  A number random enough not to collide with different errno ranges on      */
/*  different OSes. The assumption is that error_t is at least 32-bit type.   */
#define BE_HAUSNUMERO 156384712

/*  On some platforms some standard POSIX errnos are not defined.    */
#ifndef ENOTSUP
#define ENOTSUP (BE_HAUSNUMERO + 1)
#endif
#ifndef EPROTONOSUPPORT
#define EPROTONOSUPPORT (BE_HAUSNUMERO + 2)
#endif
#ifndef ENOBUFS
#define ENOBUFS (BE_HAUSNUMERO + 3)
#endif
#ifndef ENETDOWN
#define ENETDOWN (BE_HAUSNUMERO + 4)
#endif
#ifndef EADDRINUSE
#define EADDRINUSE (BE_HAUSNUMERO + 5)
#endif
#ifndef EADDRNOTAVAIL
#define EADDRNOTAVAIL (BE_HAUSNUMERO + 6)
#endif
#ifndef ECONNREFUSED
#define ECONNREFUSED (BE_HAUSNUMERO + 7)
#endif
#ifndef EINPROGRESS
#define EINPROGRESS (BE_HAUSNUMERO + 8)
#endif
#ifndef ENOTSOCK
#define ENOTSOCK (BE_HAUSNUMERO + 9)
#endif
#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT (BE_HAUSNUMERO + 10)
#endif
#ifndef EPROTO
#define EPROTO (BE_HAUSNUMERO + 11)
#endif
#ifndef EAGAIN
#define EAGAIN (BE_HAUSNUMERO + 12)
#endif
#ifndef EBADF
#define EBADF (BE_HAUSNUMERO + 13)
#endif
#ifndef EINVAL
#define EINVAL (BE_HAUSNUMERO + 14)
#endif
#ifndef EMFILE
#define EMFILE (BE_HAUSNUMERO + 15)
#endif
#ifndef EFAULT
#define EFAULT (BE_HAUSNUMERO + 16)
#endif
#ifndef EACCES
#define EACCES (BE_HAUSNUMERO + 17)
#endif
#ifndef EACCESS
#define EACCESS (EACCES)
#endif
#ifndef ENETRESET
#define ENETRESET (BE_HAUSNUMERO + 18)
#endif
#ifndef ENETUNREACH
#define ENETUNREACH (BE_HAUSNUMERO + 19)
#endif
#ifndef EHOSTUNREACH
#define EHOSTUNREACH (BE_HAUSNUMERO + 20)
#endif
#ifndef ENOTCONN
#define ENOTCONN (BE_HAUSNUMERO + 21)
#endif
#ifndef EMSGSIZE
#define EMSGSIZE (BE_HAUSNUMERO + 22)
#endif
#ifndef ETIMEDOUT
#define ETIMEDOUT (BE_HAUSNUMERO + 23)
#endif
#ifndef ECONNABORTED
#define ECONNABORTED (BE_HAUSNUMERO + 24)
#endif
#ifndef ECONNRESET
#define ECONNRESET (BE_HAUSNUMERO + 25)
#endif
#ifndef ENOPROTOOPT
#define ENOPROTOOPT (BE_HAUSNUMERO + 26)
#endif
#ifndef EISCONN
#define EISCONN (BE_HAUSNUMERO + 27)
#define BE_EISCOBE_DEFINED
#endif
#ifndef ESOCKTNOSUPPORT
#define ESOCKTNOSUPPORT (BE_HAUSNUMERO + 28)
#endif

/*  Native beem error codes.                                               */
#ifndef ETERM
#define ETERM (BE_HAUSNUMERO + 53)
#endif
#ifndef EFSM
#define EFSM (BE_HAUSNUMERO + 54)
#endif

/*  This function retrieves the errno as it is known to the library.          */
/*  The goal of this function is to make the code 100% portable, including    */
/*  where the library is compiled with certain CRT library (on Windows) and   */
/*  linked to an application that uses different CRT library.                 */
BE_EXPORT int be_errno (void);

/*  Resolves system errors and native errors to human-readable string.        */
BE_EXPORT const char *be_strerror (int errnum);


/*  Returns the symbol name (e.g. "BE_REQ") and value at a specified index.   */
/*  If the index is out-of-range, returns NULL and sets errno to EINVAL       */
/*  General usage is to start at i=0 and iterate until NULL is returned.      */
BE_EXPORT const char *be_symbol (int i, int *value);

/*  Constants that are returned in `ns` member of be_symbol_properties        */
#define BE_NS_NAMESPACE 0
#define BE_NS_VERSION 1
#define BE_NS_DOMAIN 2
#define BE_NS_TRANSPORT 3
#define BE_NS_PROTOCOL 4
#define BE_NS_OPTION_LEVEL 5
#define BE_NS_SOCKET_OPTION 6
#define BE_NS_TRANSPORT_OPTION 7
#define BE_NS_OPTION_TYPE 8
#define BE_NS_OPTION_UNIT 9
#define BE_NS_FLAG 10
#define BE_NS_ERROR 11
#define BE_NS_LIMIT 12
#define BE_NS_EVENT 13
#define BE_NS_STATISTIC 14

/*  Constants that are returned in `type` member of be_symbol_properties      */
#define BE_TYPE_NONE 0
#define BE_TYPE_INT 1
#define BE_TYPE_STR 2

/*  Constants that are returned in the `unit` member of be_symbol_properties  */
#define BE_UNIT_NONE 0
#define BE_UNIT_BYTES 1
#define BE_UNIT_MILLISECONDS 2
#define BE_UNIT_PRIORITY 3
#define BE_UNIT_BOOLEAN 4
#define BE_UNIT_MESSAGES 5
#define BE_UNIT_COUNTER 6

/*  Structure that is returned from be_symbol  */
struct be_symbol_properties {

    /*  The constant value  */
    int value;

    /*  The constant name  */
    const char* name;

    /*  The constant namespace, or zero for namespaces themselves */
    int ns;

    /*  The option type for socket option constants  */
    int type;

    /*  The unit for the option value for socket option constants  */
    int unit;
};

/*  Fills in be_symbol_properties structure and returns it's length           */
/*  If the index is out-of-range, returns 0                                   */
/*  General usage is to start at i=0 and iterate until zero is returned.      */
BE_EXPORT int be_symbol_info (int i,
    struct be_symbol_properties *buf, int buflen);

/******************************************************************************/
/*  Helper function for shutting down multi-threaded applications.            */
/******************************************************************************/

BE_EXPORT void be_term (void);

/******************************************************************************/
/*  Zero-copy support.                                                        */
/******************************************************************************/

#define BE_MSG ((size_t) -1)

BE_EXPORT void *be_allocmsg (size_t size, int type);
BE_EXPORT void *be_reallocmsg (void *msg, size_t size);
BE_EXPORT int be_freemsg (void *msg);

/******************************************************************************/
/*  Socket definition.                                                        */
/******************************************************************************/

struct be_iovec {
    void *iov_base;
    size_t iov_len;
};

struct be_msghdr {
    struct be_iovec *msg_iov;
    int msg_iovlen;
    void *msg_control;
    size_t msg_controllen;
};

struct be_cmsghdr {
    size_t cmsg_len;
    int cmsg_level;
    int cmsg_type;
};

/*  Internal stuff. Not to be used directly.                                  */
BE_EXPORT  struct be_cmsghdr *be_cmsg_nxthdr_ (
    const struct be_msghdr *mhdr,
    const struct be_cmsghdr *cmsg);
#define BE_CMSG_ALIGN_(len) \
    (((len) + sizeof (size_t) - 1) & (size_t) ~(sizeof (size_t) - 1))

/* POSIX-defined msghdr manipulation. */

#define BE_CMSG_FIRSTHDR(mhdr) \
    be_cmsg_nxthdr_ ((struct be_msghdr*) (mhdr), NULL)

#define BE_CMSG_NXTHDR(mhdr, cmsg) \
    be_cmsg_nxthdr_ ((struct be_msghdr*) (mhdr), (struct be_cmsghdr*) (cmsg))

#define BE_CMSG_DATA(cmsg) \
    ((unsigned char*) (((struct be_cmsghdr*) (cmsg)) + 1))

/* Extensions to POSIX defined by RFC 3542.                                   */

#define BE_CMSG_SPACE(len) \
    (BE_CMSG_ALIGN_ (len) + BE_CMSG_ALIGN_ (sizeof (struct be_cmsghdr)))

#define BE_CMSG_LEN(len) \
    (BE_CMSG_ALIGN_ (sizeof (struct be_cmsghdr)) + (len))

/*  SP address families.                                                      */
#define AF_BEE 1
#define AF_BEE_RAW 2

/*  Max size of an SP address.                                                */
#define BE_SOCKADDR_MAX 128

/*  Socket option levels: Negative numbers are reserved for transports,
    positive for socket types. */
#define BE_SOL_SOCKET 0

/*  Generic socket options (BE_SOL_SOCKET level).                             */
#define BE_LINGER 1
#define BE_SNDBUF 2
#define BE_RCVBUF 3
#define BE_SNDTIMEO 4
#define BE_RCVTIMEO 5
#define BE_RECONNECT_IVL 6
#define BE_RECONNECT_IVL_MAX 7
#define BE_SNDPRIO 8
#define BE_RCVPRIO 9
#define BE_SNDFD 10
#define BE_RCVFD 11
#define BE_DOMAIN 12
#define BE_PROTOCOL 13
#define BE_IPV4ONLY 14
#define BE_SOCKET_NAME 15
#define BE_RCVMAXSIZE 16
#define BE_MAXTTL 17

/*  Send/recv options.                                                        */
#define BE_DONTWAIT 1

/*  Ancillary data.                                                           */
#define PROTO_SP 1
#define SP_HDR 1

BE_EXPORT int be_socket (int domain, int protocol);
BE_EXPORT int be_close (int s);
BE_EXPORT int be_setsockopt (int s, int level, int option, const void *optval,
    size_t optvallen);
BE_EXPORT int be_getsockopt (int s, int level, int option, void *optval,
    size_t *optvallen);
BE_EXPORT int be_bind (int s, const char *addr);
BE_EXPORT int be_connect (int s, const char *addr);
BE_EXPORT int be_shutdown (int s, int how);
BE_EXPORT int be_send (int s, const void *buf, size_t len, int flags);
BE_EXPORT int be_recv (int s, void *buf, size_t len, int flags);
BE_EXPORT int be_sendmsg (int s, const struct be_msghdr *msghdr, int flags);
BE_EXPORT int be_recvmsg (int s, struct be_msghdr *msghdr, int flags);

/******************************************************************************/
/*  Socket mutliplexing support.                                              */
/******************************************************************************/

#define BE_POLLIN 1
#define BE_POLLOUT 2

struct be_pollfd {
    int fd;
    short events;
    short revents;
};

BE_EXPORT int be_poll (struct be_pollfd *fds, int nfds, int timeout);

/******************************************************************************/
/*  Built-in support for switchers.                                             */
/******************************************************************************/

BE_EXPORT int be_switcher (int s1, int s2);

/******************************************************************************/
/*  Statistics.                                                               */
/******************************************************************************/

/*  Transport statistics  */
#define BE_STAT_ESTABLISHED_CONNECTIONS 101
#define BE_STAT_ACCEPTED_CONNECTIONS    102
#define BE_STAT_DROPPED_CONNECTIONS     103
#define BE_STAT_BROKEN_CONNECTIONS      104
#define BE_STAT_CONNECT_ERRORS          105
#define BE_STAT_BIND_ERRORS             106
#define BE_STAT_ACCEPT_ERRORS           107

#define BE_STAT_CURRENT_CONNECTIONS     201
#define BE_STAT_INPROGRESS_CONNECTIONS  202
#define BE_STAT_CURRENT_EP_ERRORS       203

/*  The socket-internal statistics  */
#define BE_STAT_MESSAGES_SENT           301
#define BE_STAT_MESSAGES_RECEIVED       302
#define BE_STAT_BYTES_SENT              303
#define BE_STAT_BYTES_RECEIVED          304
/*  Protocol statistics  */
#define	BE_STAT_CURRENT_SND_PRIORITY    401

BE_EXPORT uint64_t be_get_statistic (int s, int stat);

#ifdef __cplusplus
}
#endif

#endif
