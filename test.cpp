# 1 "test.c"
# 1 "/usr/local/qdos-gcc/include/stdio.h" 1















# 26 "/usr/local/qdos-gcc/include/stdio.h"


























typedef long fpos_t;



typedef unsigned long  size_t;




















typedef char __stdiobuf_t;
typedef size_t  __stdiosize_t;
typedef struct __iobuf {
__stdiobuf_t *__rptr;
__stdiobuf_t *__rend;
__stdiobuf_t *__wptr;
__stdiobuf_t *__wend;
__stdiobuf_t *__base;
__stdiosize_t __bufsiz;
short __flag;
char __file;
__stdiobuf_t __buf;
int (*__filbuf)  (struct __iobuf *)  ;
int (*__flsbuf)  (int,struct __iobuf *)  ;
int (*__flush)  (struct __iobuf *)  ;
struct __iobuf *__next;
} FILE;
extern FILE __stdin;
extern FILE __stdout;
extern FILE __stderr;



# 113 "/usr/local/qdos-gcc/include/stdio.h"











int getc  (FILE *)  ;

int getchar  (void)  ;

# 142 "/usr/local/qdos-gcc/include/stdio.h"











int putc  (int,FILE *)  ;

int putchar  (int)  ;


int feof  (FILE *)  ;


int ferror  (FILE *)  ;


void clearerr  (FILE *)  ;

FILE *fopen  (const char *,const char *)  ;
FILE *freopen  (const char *,const char *,FILE *)  ;
int fflush  (FILE *)  ;
int fclose  (FILE *)  ;
int fgetpos  (FILE *,fpos_t *)  ;
int fsetpos  (FILE *,const fpos_t *)  ;
long ftell  (FILE *)  ;
int fseek  (FILE *,long,int)  ;
void rewind  (FILE *)  ;
int fgetc  (FILE *)  ;
int fputc  (int,FILE *)  ;
__stdiosize_t fread  (void *,__stdiosize_t,
__stdiosize_t,FILE *)  ;
__stdiosize_t fwrite  (const void *,__stdiosize_t,
__stdiosize_t,FILE *)  ;
int getw  (FILE *)  ;
int putw  (int,FILE *)  ;
char *gets  (char *)  ;
char *fgets  (char *,int,FILE *)  ;
int puts  (const char *)  ;
int fputs  (const char *,FILE *)  ;
int ungetc  (int,FILE *)  ;
int printf  (const char * ,... )  ;
int fprintf  (FILE *,const char * ,... )  ;
int sprintf  (char *,const char * ,... )  ;
int vprintf  (const char *,char * )  ;
int vfprintf  (FILE *,const char *,char * )  ;
int vsprintf  (char *,const char *,char * )  ;
int scanf  (const char * ,... )  ;
int fscanf  (FILE *,const char * ,... )  ;
int sscanf  (const char *,const char * ,... )  ;
void setbuf  (FILE *,char *)  ;
int setvbuf  (FILE *,char *,int,__stdiosize_t)  ;
int rename  (const char *,const char *)  ;
int remove  (const char *)  ;
void perror  (const char *)  ;
char * tmpnam  (char *)  ;
FILE * tmpfile  (void)  ;



















char * ctermid  (char *s)  ;

char * cuserid  (char *s)  ;
FILE * fdopen  (int,const char *)  ;

int fileno  (FILE *)  ;



int pclose  (FILE *)  ;
FILE *popen  (const char *,const char *)  ;

FILE *fopene  (const char *,const char *,int)  ;
int getch  (void)  ;
int getche  (void)  ;
int kbhit  (void)  ;
int putch  (int)  ;
int ungetch  (int)  ;
void setnbf  (FILE *)  ;
long fgetchid  (FILE *)  ;
FILE *fusechid  (long)  ;








# 1 "test.c" 2

# 1 "/usr/local/qdos-gcc/include/stdlib.h" 1



# 1 "/usr/local/qdos-gcc/include/sys/types.h" 1








typedef long time_t;



typedef long clock_t;



typedef char wchar_t;

typedef unsigned long dev_t;
typedef unsigned char gid_t;
typedef unsigned int ino_t;
typedef int mode_t;
typedef unsigned char nlkink_t;
typedef long off_t;
typedef long pid_t;
typedef unsigned short uid_t;
typedef long ptrdiff_t;
typedef char * addreg_t;
typedef long datareg_t;
typedef long chanid_t;
typedef unsigned char event_t;
typedef long jobid_t;
typedef short timeout_t;
typedef unsigned char colour_t;



















# 105 "/usr/local/qdos-gcc/include/sys/types.h"


# 4 "/usr/local/qdos-gcc/include/stdlib.h" 2











extern char * optarg;
extern int optind,opterr,optopt;
typedef struct { int quot; int rem; } div_t;
typedef struct {long quot; long rem; } ldiv_t;







void * malloc  (size_t)  ;
void * _Calloc   (size_t,size_t)  ;
void * _Realloc   (void *,size_t)  ;
void free  (void *)  ;
char * alloca  (size_t)  ;
char * getmem  (int)  ;
char * getml  (long)  ;
int rlsmem  (char *,int)  ;
int rlsml  (char *,long)  ;

void *bsearch  (const void *,const void *,size_t,size_t,int (*)(const void *,const void *))  ;
void _Qsort   (void *,size_t,size_t,int (*)(const void *,const void *))  ;
void dqsort  (double *,int)  ;
void fqsort  (float *,int)  ;
void lqsort  (long *,int)  ;
void sqsort  (short *,int)  ;
void tqsort  (char **,int)  ;
int rand  (void)  ;
void srand  (unsigned)  ;
double drand48  (void)  ;
double erand48  (short *)  ;
long jrand48  (short *)  ;
void lcong48  (short *)  ;
long lrand48  (void)  ;
long mrand48  (void)  ;
long nrand48  (short *)  ;
short *seed48  (short *)  ;
void srand48  (long)  ;





int abs  (int)  ;
void _Abort   (void)  ;
char * argopt  (int,char**,char *,int *,char *)  ;
int atexit  (void (*)(void))  ;
double atof  (const char *)  ;
int atoi  (const char *)  ;
long atol  (const char *)  ;
div_t div  (int,int)  ;
void exit  (int)  ;
char * getenv  (const char *)  ;
gid_t getegid  (void)  ;
uid_t geteuid  (void)  ;
int getfnl  (char *,char *,unsigned,int)  ;
gid_t getgid  (void)  ;
int getopt  (int,char **,char *)  ;
int isatty  (int)  ;
long labs  (long)  ;
ldiv_t ldiv  (long,long)  ;
char * mktemp  (char *)  ;
int onexit  (int(*)(void))  ;
int _Putenv   (char *)  ;
double _Strtod   (const char *,char **)  ;
long strtol  (const char *,char **,int)  ;
unsigned long _Strtoul   (const char *,char**,int)  ;
int system  (const char *)  ;
char * ttyname  (int)  ;
long utpack  (char *)  ;
void utunpk  (long,char *)  ;



int mblen  (const char * s,size_t n)  ;
int mbtowc  (wchar_t * pwc,const char *s,size_t n)  ;
size_t mbstowcs  (wchar_t * pwc,const char *s,size_t n)  ;
int wctomb  (char * s,wchar_t pwc)  ;
size_t wcstombs  (char * s,const wchar_t * pwc,size_t n)  ;
char * getpass  (char * prompt)  ;

int envunpk  (char *)  ;
char * itoa  (int,char *)  ;






# 2 "test.c" 2

# 1 "/usr/local/qdos-gcc/include/unistd.h" 1














































extern char ** _environ ;






void _exit  (int)  ;
int access  (char *,int)  ;
int alarm  (unsigned int)  ;
int _Chdir   (char *)  ;
int chown  (const char *,uid_t,gid_t)  ;
int _Close   (int)  ;
char * ctermid  (char *)  ;
char * cuserid  (char *)  ;
int dup  (int)  ;
int _Dup2   (int,int)  ;
int execl  (const char *,int *,const char *,...)  ;
int execlp  (const char *,int *,const char *,...)  ;
int execv  (const char *,int *,char * const * )  ;
int execvp  (const char *,int *,char * const * )  ;
pid_t forkl  (const char *,int *,const char *,...)  ;
pid_t forklp  (const char *,int *,const char *,...)  ;
pid_t forkv  (const char *,int *,char * const *)  ;
pid_t forkvp  (const char *,int *,char * const *)  ;
long fpathconf  (int,int)  ;
int fsync  (int)  ;
int ftruncate  (int,off_t)  ;
char * getcwd  (char *,int)  ;
gid_t getegid  (void)  ;
uid_t geteuid  (void)  ;
gid_t getgid  (void)  ;
int getgroups  (int,gid_t)  ;
char * getlogin  (void)  ;
pid_t getpgrp  (void)  ;
pid_t getpid  (void)  ;
pid_t getppid  (void)  ;
uid_t getuid  (void)  ;
int isatty  (int)  ;
int link  (const char *,const char *)  ;
off_t lseek  (int,off_t,int)  ;
long pathconf  (const char *,int)  ;
int pause  (void)  ;
int pipe  (int *)  ;
int _Read   (int,void *,unsigned int)  ;
int rmdir  (const char *)  ;
int seteuid  (int)  ;
int setgid  (int)  ;
int setpgid  (pid_t,pid_t)  ;
pid_t setsid  (void)  ;
int setuid  (int)  ;
unsigned sleep  (unsigned int)  ;
int stime  (const time_t *)  ;
void sync  (void)  ;
long sysconf  (int)  ;
int truncate  (char *,off_t)  ;
char * ttyname  (int)  ;
int _Unlink   (const char *)  ;
int _Write   (int,void *,unsigned int)  ;
void * sbrk  (int)  ;
void * lsbrk  (long)  ;
char * brk  (char *)  ;
char * mktemp  (char *)  ;
pid_t tcgetpgrp  (int)  ;
int tcsetpgrp  (int,pid_t)  ;
extern int (*_f_onexit)  (int)  ;




# 3 "test.c" 2

# 1 "/usr/local/qdos-gcc/include/string.h" 1




















void * memchr  (const void *,int,size_t)  ;
int _MemCmp   (const void *,const void *,size_t)  ;
void * _MemCpy   (void *,const void *,size_t)  ;
void * _MemMove   (void *,const void *,size_t)  ;
void * _MemSet   (void *,int,size_t)  ;
char * _StrCat   (char *,const char *)  ;
char * strchr  (const char *,int)  ;
int strcmp  (const char *,const char *)  ;
int strcoll  (const char *,const char *)  ;
char * _StrCpy   (char *,const char *)  ;
size_t strcspn  (const char *,const char *)  ;
char * strerror  (int)  ;
size_t _StrLen   (const char *)  ;
char * strncat  (char *,const char *,size_t)  ;
int strncmp  (const char *,const char *,size_t)  ;
char * strncpy  (char *,const char *,size_t)  ;
char * strpbrk  (const char *,const char *)  ;
char * strrchr  (const char *,int)  ;
size_t strspn  (const char *,const char *)  ;
char * strstr  (const char *,const char *)  ;
char * strtok  (char *,const char *)  ;
size_t strxfrm  (char *,const char *,size_t)  ;
char * index  (const char *,int)  ;
char * memccpy  (char *,char *,int,size_t)  ;
char * rindex  (const char *,int)  ;
int stricmp  (const char *,const char *)  ;
char * strdup  (char *)  ;
char * strlwr  (char *)  ;
void strmfe  (char *,const char *,const char *)  ;
void strmfn  (char *,const char *,const char *,const char *,const char *)  ;
void strmfp  (char *,const char *,const char *)  ;
int strnicmp  (const char *,const char *,size_t)  ;
char * strnset  (char *,int,int)  ;
int strpos  (const char *,int)  ;
char * strrev  (char *)  ;
int strrpos  (const char *,int)  ;
char * strrstr  (const char *,const char *)  ;
char * strset  (char *,int)  ;
void strsfn  (char *,char *,char *,char *,char *)  ;
char * strupr  (char *)  ;


int stccpy  (char *,char *,int)  ;
char * stpblk  (char *)  ;



char * stpcpy  (char *,const char *)  ;
int strbpl  (char **,int,char *)  ;


void repmem  (char *,char *,int,int)  ;
void swmem  (char *,char *,unsigned)  ;
int stcarg  (char *,char *)  ;
int stcgfe  (char *,char *)  ;
int stcgfn  (char *,char *)  ;
int stcis  (char *,char *)  ;
int stcisn  (char *,char *)  ;
int stclen  (char *)  ;
int stcd_i  (char *,int *)  ;
int stcd_l  (char *,long *)  ;
int stch_i  (char *,int *)  ;
int stch_l  (char *,long *)  ;
int stci_d  (char *,int)  ;
int stci_h  (char *,int)  ;
int stci_o  (char *,int)  ;
int stcl_d  (char *,long)  ;
int stcl_h  (char *,long)  ;
int stcl_o  (char *,long)  ;
int stco_i  (char *,int *)  ;
int stco_l  (char *,long *)  ;
int stcpm  (char *,char *,char **)  ;
int stcpma  (char *,char *)  ;
int stcu_d  (char *,unsigned)  ;
int stcul_d  (char *,unsigned long)  ;
char * stpdate  (char *,int,char *)  ;
char * stpsym  (char *,char *,int)  ;
char * stptime  (char *,int,char *)  ;
char * stptok  (char *,char *,int,char *)  ;
int stscmp  (char *,char *)  ;
int stspfp  (char *,int *)  ;
char * strrpbrk  (const char *,const char *)  ;
int strfnd  (const char *,const char *)  ;
void strins  (char *,char *)  ;
char * strrstrip  (char *,int)  ;
char * strstrip  (char *,int)  ;


# 4 "test.c" 2

# 1 "/usr/local/qdos-gcc/include/math.h" 1





# 1 "/usr/local/qdos-gcc/include/sys/math.h" 1


extern const double _HUGE_VALUE;
extern const double _Infinity;

# 6 "/usr/local/qdos-gcc/include/math.h" 2



struct exception {
int type;
char * name;
double arg1,arg2;
double retval;
};



































extern int _fperr;
extern int errno;
extern int signgam;





double acos  (double)  ;
double asin  (double)  ;
double atan  (double)  ;
double atan2  (double,double)  ;
double ceil  (double)  ;
double cos  (double)  ;
double cosh  (double)  ;
double exp  (double)  ;
double fabs  (double)  ;
double floor  (double)  ;
double fmod  (double,double)  ;
double frexp  (double,int *)  ;
double ldexp  (double,int)  ;
double log  (double)  ;
double log10  (double)  ;
double modf  (double,double *)  ;
double pow  (double,double)  ;
double sin  (double)  ;
double sinh  (double)  ;
double sqrt  (double)  ;
double tan  (double)  ;
double tanh  (double)  ;
int matherr  (struct exception *)  ;
double acosh  (double)  ;
double asinh  (double)  ;
double atanh  (double)  ;
double cbrt  (double)  ;
double copysign  (double,double)  ;
double cot  (double)  ;
double erf  (double)  ;
double erfc  (double)  ;
double hypot  (double,double)  ;
double logb  (double)  ;
double nextafter  (double,double)  ;
double remainder  (double,double)  ;
double rint  (double)  ;
double scalb  (double,double)  ;
double j0  (double)  ;
double j1  (double)  ;
double jn  (int,double)  ;
double y0  (double)  ;
double y1  (double)  ;
double yn  (int,double)  ;
double gamma  (double)  ;
double lgamma  (double)  ;
int finite  (double)  ;
int isnan  (double)  ;
int unordered  (double,double)  ;




float ceilf  (float)  ;


float expf  (float)  ;
float fabsf  (float)  ;
float floorf  (float)  ;
float fmodf  (float,float)  ;
float logf  (float)  ;
float log10f  (float)  ;
float modff  (float,float *)  ;
float powf  (float,float)  ;


float sqrtf  (float)  ;



double except  (int,char *,double,double,double)  ;
char * ecvt  (double,int,int *,int *)  ;
char * fcvt  (double,int,int *,int *)  ;
char * gcvt  (double,int,char *)  ;











# 5 "test.c" 2

# 1 "/usr/local/qdos-gcc/include/qdos.h" 1



# 1 "/usr/local/qdos-gcc/include/sys/qlib.h" 1














# 1 "/usr/local/qdos-gcc/include/limits.h" 1








































































# 15 "/usr/local/qdos-gcc/include/sys/qlib.h" 2











typedef struct REGS {
datareg_t D0,D1,D2,D3;
addreg_t A0,A1,A2,A3;
} REGS_t;
extern int _oserr;
typedef struct QLSTR {
short qs_strlen;
char qs_str[1];
} QLSTR_t;






typedef struct QLFLOAT {
short qfp_exp;
long qfp_mant;
} QLFLOAT_t;
typedef struct QLHEAP {
long qh_size;
long qh_freeaddr;
jobid_t qh_job;
long qh_zero;
} QLHEAP_t;
typedef struct MELT {
long mp_size;
struct MELT *mp_next;
} MELT_t;

typedef struct QLVECTABLE {
long (*qv_adderr) (void)  ;
long (*qv_illegal) (void)  ;
long (*qv_divzero) (void)  ;
long (*qv_CHK) (void)  ;
long (*qv_TRAPV) (void)  ;
long (*qv_priviol) (void)  ;
long (*qv_tracexpt) (void)  ;
long (*qv_intlev7) (void)  ;
long (*qv_5trap) (void)  ;
long (*qv_6trap) (void)  ;
long (*qv_7trap) (void)  ;
long (*qv_8trap) (void)  ;
long (*qv_9trap) (void)  ;
long (*qv_10trap) (void)  ;
long (*qv_11trap) (void)  ;
long (*qv_12trap) (void)  ;
long (*qv_13trap) (void)  ;
long (*qv_14trap) (void)  ;
long (*qv_15trap) (void)  ;
} QLVECTABLE_t;
typedef struct FULLREGS {
datareg_t jb_D0,jb_D1,jb_D2,jb_D3,jb_D4,jb_D5,jb_D6,jb_D7;
addreg_t jb_A0,jb_A1,jb_A2,jb_A3,jb_A4,jb_A5,jb_A6,jb_A7;
short jb_SR;
addreg_t jb_PC;
} FULLREGS_t;
typedef struct JOBHEADER {
long jb_len;
long jb_start;
jobid_t jb_owner;
long jb_hold;
unsigned short jb_tag;
unsigned char jb_prior;
unsigned char jb_princ;
short jb_stat;
char jb_rela6;
char jb_wflag;
jobid_t jb_wjob;
QLVECTABLE_t * jb_trapv;
struct FULLREGS jb_regs;
short jb_resvd;
} JOBHEADER_t;
typedef struct QL_LINK {
struct QL_LINK *l_next;
void (*l_rtn) (void)  ;
} QL_LINK_t;
typedef struct QLD_LINK {
struct QLD_LINK *ld_next;
long (*ld_io) (void)  ;
long (*ld_open) (void)  ;
long (*ld_close) (void)  ;
} QLD_LINK_t;
typedef struct QLDDEV_LINK {
struct QLDDEV_LINK *ldd_next;
long (*ldd_io) (void)  ;
long (*ldd_open) (void)  ;
long (*ldd_close) (void)  ;
long (*ldd_slave) (void)  ;
long (*ldd_rename) (void)  ;
long (*ldd_trunc) (void)  ;
long (*ldd_format) (void)  ;
long ldd_plen;
QLSTR_t ldd_dname;
} QLDDEV_LINK_t;

typedef struct QLRECT {
unsigned short q_width;
unsigned short q_height;
unsigned short q_x;
unsigned short q_y;
} QLRECT_t;

typedef struct WINDOWDEF {
unsigned char border_colour;
unsigned char border_width;
unsigned char paper;
unsigned char ink;
unsigned short width;
unsigned short height;
unsigned short x_origin;
unsigned short y_origin;
} WINDOWDEF_t;























typedef struct qdirect {
unsigned long d_length;
unsigned char d_access;
unsigned char d_type;
unsigned long d_datalen;
long d_reserved;
unsigned short d_szname;
char d_name[36];
long d_update;
union {
long d_refdate;
struct {
unsigned short d_version;
unsigned short d_fileno;
} v2;
} u;
long d_backup;
} qdirect_t;
typedef struct DIR_LIST {
struct DIR_LIST *dl_next;
struct qdirect dl_dir;
char dl_cname[1];
} DIR_LIST_t;







typedef struct ext_mdinf {
union {
char m_size[22];
QLSTR_t m_name;
} xm_name;
union {
char m_dsize[6];
QLSTR_t m_dname;
} xm_dname;
unsigned char xm_dnum;
char xm_rdonly;
unsigned short xm_alloc;
unsigned long xm_total;
unsigned long xm_free;
unsigned long xm_hdrlen;
char xm_spare[20];
char xm_spare2[36];
} ext_mdinf_t;











extern WINDOWDEF_t _condetails;
extern char _copyright[];
extern long _def_priority;
extern char * _endmsg;
extern timeout_t _endtimeout;
extern long _Jobid;
extern long _memincr;
extern long _memmax;
extern long _memqdos;
extern long _mneed;
extern long _pipesize;
extern char _prog_name[];
extern char _SLASH;
extern char * _SPorig;
extern long _stack;
extern long _stackmargin;
extern char * _sys_var;
extern char _tmpdir_[];
extern char _tmpnam_[];
extern char _version[];
extern int os_nerr;
extern char *os_errlist[];
extern char _CPU;
extern char _FPU;
extern long (*_cmdchannels)  (long)  ;
extern int (*_cmdparams)  (const char *,char ***,int *,int (*) (char *,char ***,int *)   )  ;
extern int (*_cmdwildcard)  (char *,char ***,int *)  ;
extern void (*_consetup)  (chanid_t,WINDOWDEF_t *)  ;
extern void _initcon  (void)  ;
extern long (*_stackchannels)  (long)  ;
extern int (*_readkbd)  (chanid_t,timeout_t,char *)  ;
int cmdexpand  (char *,char ***,int*)  ;
void consetup_qpac  (chanid_t,WINDOWDEF_t *)  ;
void consetup_title  (chanid_t,WINDOWDEF_t *)  ;
int readkbd_move  (chanid_t,timeout_t,char *)  ;
int ioppick  (jobid_t)  ;


QLSTR_t * _cstr_to_ql   (QLSTR_t *,char *)  ;
QLFLOAT_t * _d_to_qlfp   (QLFLOAT_t *,double)  ;
char * qlstr_to_c  (char *,QLSTR_t *)  ;
QLFLOAT_t * i_to_qlfp  (QLFLOAT_t *,int)  ;
QLFLOAT_t * l_to_qlfp  (QLFLOAT_t *,long)  ;
QLFLOAT_t * w_to_qlfp  (QLFLOAT_t *,int)  ;
double qlfp_to_d  (QLFLOAT_t *)  ;
long qlfp_to_f  (QLFLOAT_t *)  ;
QLSTR_t * qstrcat  (QLSTR_t *,const QLSTR_t *)  ;
char * qstrchr  (const QLSTR_t *,int)  ;
int qstrcmp  (const QLSTR_t *,const QLSTR_t *)  ;
QLSTR_t * qstrcpy  (QLSTR_t *,const QLSTR_t *)  ;
int qstricmp  (QLSTR_t *,QLSTR_t *)  ;
size_t qstrlen  (const QLSTR_t *)  ;
QLSTR_t * qstrncat  (QLSTR_t *,const QLSTR_t *,short)  ;
int qstrncmp  (const QLSTR_t *,const QLSTR_t *,short)  ;
QLSTR_t * qstrncpy  (QLSTR_t *,const QLSTR_t *,short)  ;
int qstrnicmp  (QLSTR_t *,QLSTR_t *,short)  ;








void _super  (void)  ;
void _user  (void)  ;
void _argfree   (char ***)  ;
char * _argpack   (char * const *,int)  ;
int _argunpack   (const char *,char ***,int *,int (*) (char *,char ***,int*)   )  ;

void _beep   (unsigned short,unsigned char)  ;


int chddir  (char *)  ;
int _chpdir   (char *)  ;
void _do_sound   (unsigned short,unsigned char,unsigned char,unsigned char,unsigned short,unsigned char,unsigned char,unsigned char)  ;

int fnmatch  (char *,char *)  ;
int fqstat  (int,struct qdirect *)  ;
char * getcdd  (char *,int)  ;
char * getcpd  (char *,int)  ;
long getchid  (int)  ;
char * getcname  (chanid_t,char *)  ;
int iscon  (chanid_t,timeout_t)  ;
int isdevice  (const char *,int *)  ;
struct QLDDEV_LINK * isdirchid  (chanid_t)  ;
int isdirdev  (const char *)  ;
int isnoclose  (int)  ;
int keyrow  (char)  ;
chanid_t open_qdir  (const char *)  ;
int poserr  (const char *)  ;
void qdir_delete  (DIR_LIST_t *)  ;
DIR_LIST_t * qdir_read  (char *,char *,int)  ;
DIR_LIST_t * qdir_sort  (DIR_LIST_t *,char *,int (*)(DIR_LIST_t *,DIR_LIST_t *,char *))  ;

long qdos1  (struct REGS *,struct REGS *)  ;
long qdos2  (struct REGS *,struct REGS *)  ;
long qdos3  (struct REGS *,struct REGS *)  ;
pid_t qforkl  (const jobid_t,const char *,int *,const char *,...)  ;
pid_t qforklp  (const jobid_t,const char *,int *,const char *,...)  ;
pid_t qforkv  (const jobid_t,const char *,int *,char * const *)  ;
pid_t qforkvp  (const jobid_t,const char *,int *,char * const *)  ;
int qinstrn  (char *,int)  ;
int read_qdir  (chanid_t,char *,char *,struct qdirect *,int)  ;
int qstat  (char *,struct qdirect *)  ;
long stackcheck  (void)  ;
long stackreport  (void)  ;
char * str_oserr  (int)  ;
int usechid  (chanid_t)  ;
int waitfor  (jobid_t,int *)  ;
# 386 "/usr/local/qdos-gcc/include/sys/qlib.h"



# 4 "/usr/local/qdos-gcc/include/qdos.h" 2

































































void _mt_aclck   (long)  ;
int _mt_activ   (jobid_t,unsigned char,timeout_t)  ;
char * _mt_alchp   (long,long *,jobid_t)  ;
char * _mt_alloc   (char **,long *)  ;
char * _mt_alres   (long)  ;
void _mt_baud   (long)  ;
jobid_t _mt_cjob   (long,long,char *,jobid_t,char **)  ;
void _mt_dmode   (short *,short *)  ;
long _mt_free   (void)  ;
int _mt_frjob   (jobid_t,int)  ;
jobid_t _mt_inf   (char **,long *)  ;
int _mt_ipcom   (void *)  ;
int _mt_jinf   (jobid_t *,jobid_t *,long *,char **)  ;
void _mt_lnkfr   (char *,char **,long)  ;
void _mt_lxint   (QL_LINK_t *)  ;
void _mt_rxint   (QL_LINK_t *)  ;
void _mt_lpoll   (QL_LINK_t *)  ;
void _mt_rpoll   (QL_LINK_t *)  ;
void _mt_lschd   (QL_LINK_t *)  ;
void _mt_rschd   (QL_LINK_t *)  ;
void _mt_liod   (QLD_LINK_t *)  ;
void _mt_riod   (QLD_LINK_t *)  ;
void _mt_ldd   (QLDDEV_LINK_t *)  ;
void _mt_rdd   (QLDDEV_LINK_t *)  ;
int _mt_prior   (jobid_t,unsigned char)  ;
long _mt_rclck   (void)  ;
void _mt_rechp   (void *)  ;
JOBHEADER_t * _mt_reljb   (jobid_t)  ;
int _mt_reres   (void *)  ;
int _mt_rjob   (jobid_t,int)  ;
void _mt_sclck   (long)  ;
int _mt_shrink   (void *,long)  ;
int _mt_susjb   (jobid_t,timeout_t,char *)  ;
int _mt_trans   (void *,void *)  ;
int _mt_trapv   (long,QLVECTABLE_t *)  ;





int _io_close   (chanid_t)  ;
int _io_delete   (const char *)  ;
int _io_format   (const char *,short *,short *)  ;
chanid_t _io_open   (const char *,long)  ;
chanid_t _io_open_qlstr   (QLSTR_t *,long)  ;























int _fs_check   (chanid_t,timeout_t)  ;
int _fs_date   (chanid_t,timeout_t,char,long *)  ;
int _fs_flush   (chanid_t,timeout_t)  ;
int _fs_headr   (chanid_t,timeout_t,void *,short)  ;
int _fs_heads   (chanid_t,timeout_t,void *,short)  ;
long _fs_load   (chanid_t,char *,unsigned long)  ;
int _fs_mdinf   (chanid_t,timeout_t,void *,short *,short *)  ;
int _fs_mkdir   (chanid_t)  ;
long _fs_pos   (chanid_t,long,int)  ;
int _fs_posab   (chanid_t,timeout_t,unsigned long *)  ;
int _fs_posre   (chanid_t,timeout_t,long *)  ;
int _fs_rename   (const void *,const void *)  ;
int _fs_save   (chanid_t,void *,unsigned long)  ;
int _fs_trunc   (chanid_t,timeout_t)  ;
int _fs_vers   (chanid_t,timeout_t,long *)  ;
int _fs_xinf   (chanid_t,timeout_t,struct ext_mdinf *)  ;
int _io_edlin   (chanid_t,timeout_t,char **,short,short,short *)  ;
int _io_fbyte   (chanid_t,timeout_t,char *)  ;
int _io_fline   (chanid_t,timeout_t,void *,short)  ;
int _io_fstrg   (chanid_t,timeout_t,void *,short)  ;
int _io_pend   (chanid_t,timeout_t)  ;
int _io_sbyte   (chanid_t,timeout_t,unsigned char)  ;
int _io_sstrg   (chanid_t,timeout_t,void *,short)  ;






int _io_fdate   (chanid_t,timeout_t,char,long *)  ;
int _io_fvers   (chanid_t,timeout_t,long *)  ;
int _io_fxinf   (chanid_t,timeout_t,struct ext_mdinf *)  ;
int _io_mkdir   (chanid_t)  ;
int _io_rename   (const char *,const char *)  ;
int _io_trunc   (chanid_t,timeout_t)  ;





































int _sd_bordr   (chanid_t,timeout_t,colour_t,short)  ;
int _sd_chenq   (chanid_t,timeout_t,QLRECT_t *)  ;
int _sd_clear   (chanid_t,timeout_t)  ;
int _sd_clrbt   (chanid_t,timeout_t)  ;
int _sd_clrln   (chanid_t,timeout_t)  ;
int _sd_clrrt   (chanid_t,timeout_t)  ;
int _sd_clrtp   (chanid_t,timeout_t)  ;
int _sd_cure   (chanid_t,timeout_t)  ;
int _sd_curs   (chanid_t,timeout_t)  ;
int _sd_donl   (chanid_t,timeout_t)  ;
int _sd_extop   (chanid_t,timeout_t,int (*)(void),long,long,void *)  ;
int _sd_fill   (chanid_t,timeout_t,colour_t,QLRECT_t *)  ;
int _sd_fount   (chanid_t,timeout_t,char *,char *)  ;
int _sd_ncol   (chanid_t,timeout_t)  ;
int _sd_nl   (chanid_t,timeout_t)  ;
int _sd_nrow   (chanid_t,timeout_t)  ;
int _sd_pan   (chanid_t,timeout_t,short)  ;
int _sd_panln   (chanid_t,timeout_t,short)  ;
int _sd_panrt   (chanid_t,timeout_t,short)  ;
int _sd_pcol   (chanid_t,timeout_t)  ;
int _sd_pixp   (chanid_t,timeout_t,short,short)  ;
int _sd_pos   (chanid_t,timeout_t,short,short)  ;
int _sd_prow   (chanid_t,timeout_t)  ;
int _sd_pxenq   (chanid_t,timeout_t,QLRECT_t *)  ;
int _sd_recol   (chanid_t,timeout_t,char *)  ;
int _sd_scrbt   (chanid_t,timeout_t,short)  ;
int _sd_scrol   (chanid_t,timeout_t,short)  ;
int _sd_scrtp   (chanid_t,timeout_t,short)  ;
int _sd_setfl   (chanid_t,timeout_t,char)  ;
int _sd_setin   (chanid_t,timeout_t,colour_t)  ;
int _sd_setmd   (chanid_t,timeout_t,short)  ;
int _sd_setpa   (chanid_t,timeout_t,colour_t)  ;
int _sd_setst   (chanid_t,timeout_t,colour_t)  ;
int _sd_setsz   (chanid_t,timeout_t,short,short)  ;
int _sd_setul   (chanid_t,timeout_t,char)  ;
int _sd_tab   (chanid_t,timeout_t,short)  ;
int _sd_wdef   (chanid_t,timeout_t,colour_t,short,QLRECT_t *)  ;













int _sd_arc   (chanid_t,timeout_t,double,double,double,double,double)  ;
int _sd_elipse   (chanid_t,timeout_t,double,double,double,double,double)  ;
int _sd_flood   (chanid_t,timeout_t,long)  ;
int _sd_gcur   (chanid_t,timeout_t,double,double,double,double)  ;
int _sd_line   (chanid_t,timeout_t,double,double,double,double)   ;
int _sd_point   (chanid_t,timeout_t,double,double)  ;
int _sd_scale   (chanid_t,timeout_t,double,double,double)  ;
int _sd_iarc   (chanid_t,timeout_t,long,long,long,long,long)  ;
int _sd_ielipse   (chanid_t,timeout_t,long,long,long,long,long)  ;
int _sd_igcur   (chanid_t,timeout_t,long,long,long,long)  ;
int _sd_iline   (chanid_t,timeout_t,long,long,long,long)  ;
int _sd_ipoint   (chanid_t,timeout_t,long,long)  ;
int _sd_iscale   (chanid_t,timeout_t,long,long,long)  ;






























char * _cn_date   (char *,long)  ;
char * _cn_day   (char *,long)  ;
void _cn_itobb   (char *,char *)  ;
void _cn_itobw   (char *,short *)  ;
void _cn_itobl   (char *,long *)  ;
int _cn_itod   (char *,short *)  ;
void _cn_itohb   (char *,char *)  ;
void _cn_itohw   (char *,short *)  ;
void _cn_itohl   (char *,long *)  ;
int _io_qeof   (char *)  ;
int _io_qin   (char *,int)  ;
int _io_qout   (char *,char *)  ;
void _io_qset   (char *,long)  ;
int _io_qtest   (char *,char *,long *)  ;
int _io_serio   (chanid_t,timeout_t,int,long *,long *,char **,int ** )  ;
int _io_serq   (chanid_t,timeout_t,int,long *,long *,char **)  ;
char * _mm_alchp   (long *)  ;
char * _mm_alloc   (char **,long *)  ;
void _mm_lnkfr   (char *,char **,long)  ;
void _mm_rechp   (char *)  ;
chanid_t _ut_con   (WINDOWDEF_t *)  ;
int _ut_cstr   (const QLSTR_t *,const QLSTR_t *,int)  ;
void _ut_err   (long,chanid_t)  ;
void _ut_err0   (long)  ;
void _ut_link   (void *,void *)  ;
int _ut_mint   (chanid_t,int)  ;
int _ut_mtext   (chanid_t,const QLSTR_t *)  ;
chanid_t _ut_scr   (WINDOWDEF_t *)  ;
void _ut_unlnk   (void *,void *)  ;
chanid_t _ut_window   (const char *,char *)  ;


# 6 "test.c" 2


# 1 "image.h" 1
# 1 "system_variables.h" 1
void sysBaseInit();
void setSysBase(unsigned char *a);
unsigned char *getSysBase();



























# 1 "image.h" 2


 


 










typedef void * screen;

extern screen SCREEN;
void init(unsigned int colours);
void* myMalloc(unsigned int i);
void *makeHigh(void *p,unsigned int size);










 

unsigned char scanKey();
unsigned char scanRawKey();

 

screen createScreen();
void closeScreen(screen s);
void copyScreen(screen from,screen to,unsigned int yLow,unsigned int yHigh);
void copyAllScreen(screen from,screen to);
void showAll(screen screen);
void show(screen screen,unsigned int lowy,unsigned int highy);

 

extern const unsigned short masks[];
extern const unsigned short colours[4][8];




void fill(screen screen,unsigned int xmin,unsigned int xmax,unsigned char c);
void plot(screen screen,unsigned int x,unsigned int y,unsigned char c);
void plot4(screen screen,unsigned int x,unsigned int y,unsigned char c);
unsigned int unplot(screen screen,unsigned short x,unsigned short y);
void box(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int c);
void fillBox(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int c);
void copyBox(screen screen,unsigned char **m,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int c);
void drawBox(screen screen,unsigned char **m,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int c);

void fillTriangle(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int x3,unsigned int y3,unsigned int c);
void triangle(screen screen,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int x3,unsigned int y3,unsigned int c);
void line(screen screen,unsigned int x,unsigned int y,unsigned int x2,unsigned int y2,unsigned int c);

void circle(screen screen,unsigned int x,unsigned int y,int radius,unsigned int colour);
void fillCircle(screen screen,unsigned int ox,unsigned int oy,int r,unsigned int colour);

 

typedef struct
{
	
	unsigned int magic;
	

	unsigned short y;
	unsigned short x;

	char *name;

	unsigned short *mask;
	unsigned short *data;

	unsigned short *datashifter[4],*maskshifter[4];
} image;

typedef struct
{
        unsigned int value,delta;
} timer;

struct sprite
{
	char name[32];
	unsigned int active;

	unsigned int images;
	image *image[10];

	int x,y,dx,dy,currentImage;
	unsigned int mask,draw;
	timer timer,timer2;

	struct sprite *next;

	void(*movement)(struct sprite *s);
	void(*boundsCheck)(struct sprite *s);
};

typedef struct sprite sprite;

typedef struct
{
	unsigned n;
	image *images;
} library;

void spriteSetup(sprite *s,char *name);
void spriteClearImages(sprite *s);
void spriteAddImage(sprite *s,library *lib,unsigned int i);
void spriteSetImage(sprite *s,unsigned int ci);

struct shifter
{
	union
	{
		unsigned char b[4];      
        	unsigned short w[2];     
       		unsigned int l;          
	} z;
};

void spritePlot(screen scr,sprite *sprite);
void spriteClear(screen scr,screen mask,sprite *sprite);

 

void loadLibrary(library *library,char *filename,int shift);
int bLoadLibrary(library *library,char *filename,int shift);
void bSaveLibrary(library *library,char *filename);

void cls(screen screen);	 
void clsColour(screen screen,unsigned int colour);  

unsigned short peek(screen screen,unsigned int y,unsigned int x);
unsigned short *screenAddress(screen screen,unsigned int y,unsigned int x);

 

void setFontMasking(unsigned int m);
void printCharAt(screen screen,library *font,unsigned int x,unsigned int y,char c);
void printAt(screen screen,library *font,unsigned int x,unsigned y,char *s);
int loadScreen(unsigned char *scr,char *dir,char *file);

void framesInit();
unsigned int getFrames();
void framesClose();
void frameActive(unsigned int a);
void msleep(unsigned int delay);

void multiDraw(screen screen,unsigned char *data);

 
 

 

# 8 "test.c" 2


void binPrint2(short i)
{
	int z;

	for(z=15;z>=0;z--)
		((  (&__stdout)   )->__wptr>=(  (&__stdout)   )->__wend?(*(  (&__stdout)   )->__flsbuf)((   i&(1<<z)?'1':'0'   ),(  (&__stdout)   )):(int)((unsigned char)(*(  (&__stdout)   )->__wptr++=(   i&(1<<z)?'1':'0'   ))))   ;
}

void benchmark()
{
	unsigned int s;
	screen background=createScreen();
	library lib;

	init(8);

	loadLibrary(&lib,"test_lib",1);
	copyAllScreen(background,SCREEN);

	for(s=0;s<4;s++)
	{
		const int n=10;

		unsigned long t,c=0,pass;
		unsigned int x=0,y=0;
		sprite sprite[8];

		for(c=0;c<8;c++)
		{
			spriteSetup(&sprite[c],"");
			spriteAddImage(&sprite[c],&lib,s);
			sprite[c].currentImage=0;
			sprite[c].x=x++;

			sprite[c].y=y;
			sprite[c].draw=1;

			y+=sprite[c].image[0]->y;
			if(y+sprite[c].image[0]->y>255)
			{
				y=0;
				x+=sprite[c].image[0]->x<<2;
			}
		}

		for(pass=0;pass<2;pass++)
		{
			for(c=0;c<8;c++) sprite[c].mask=pass;

			t=getFrames()+n*50;
	
			while(t>getFrames())
			{
				unsigned int i;

				for(i=0;i<8;i++) spritePlot(SCREEN,&sprite[i]);

				c+=8;
			}

			copyAllScreen(SCREEN,background);

			if(pass==0)
				printf("%d x %d\t-> %ld",lib.images[s].x<<2,lib.images[s].y,c);
			else printf("\tMasked %ld\n",c);

			copyAllScreen(background,SCREEN);
		}
	}

	exit(0);
}

static unsigned int g_seed;

 

void fastSrand(int seed)
{
        g_seed = seed;
}

 
 

inline unsigned int fastRand(void)
{
        g_seed = (214013*g_seed+2531011);
        return (g_seed>>16);
}





void test()
{
	const char *tests[9 +1]={"plot","line","tri","fil tri","box","fill box","circle","fill cir","unplot","mean"};

	unsigned int i;
	WINDOWDEF_t w;
	chanid_t cid;
	unsigned int counts[9 ],pass;
	unsigned char *r=myMalloc((13107* 10 ) );
	unsigned int ri=0;
	
	init(8);
	framesInit();

	 
	
	w.width=w.height=512;
	w.x_origin=w.y_origin=0;
	w.paper=0; w.ink=7;

	cid= _ut_con (&w);

	cls(SCREEN); fastSrand(0);

	for(i=0;i<120;i++)
	{
		box(SCREEN,i+4-1,i*2+4-1,200-i+1,i*2+4+1,7);
		line(SCREEN,i+4,i*2+4,200-i,i*2+4,(i/4)&7);
	}

	puts("Creating random numbers...");
	for(ri=0;ri< (13107* 10 ) ;ri++) r[ri]=fastRand()&255;

	cls(SCREEN);

	for(pass=0;pass<1;pass++)
	{
		unsigned int f=getFrames()+ 10 *50;

		counts[pass]=0;
		ri=0;

		if(pass==0)
		{
			while(getFrames()<f)
			{
				{ unsigned short *address= (((unsigned short *) ( SCREEN ) )+ ( r[ri+1] ) *64+ ( r[ri] ) /4) ; *address=(*address&masks[( r[ri] )&3])|colours[( r[ri] )&3][ r[ri+2]&7 ]; } ; ri++;
				{ unsigned short *address= (((unsigned short *) ( SCREEN ) )+ ( r[ri+1] ) *64+ ( r[ri] ) /4) ; *address=(*address&masks[( r[ri] )&3])|colours[( r[ri] )&3][ r[ri+2]&7 ]; } ; ri++;
				{ unsigned short *address= (((unsigned short *) ( SCREEN ) )+ ( r[ri+1] ) *64+ ( r[ri] ) /4) ; *address=(*address&masks[( r[ri] )&3])|colours[( r[ri] )&3][ r[ri+2]&7 ]; } ; ri++;
				{ unsigned short *address= (((unsigned short *) ( SCREEN ) )+ ( r[ri+1] ) *64+ ( r[ri] ) /4) ; *address=(*address&masks[( r[ri] )&3])|colours[( r[ri] )&3][ r[ri+2]&7 ]; } ; ri++;
				{ unsigned short *address= (((unsigned short *) ( SCREEN ) )+ ( r[ri+1] ) *64+ ( r[ri] ) /4) ; *address=(*address&masks[( r[ri] )&3])|colours[( r[ri] )&3][ r[ri+2]&7 ]; } ; ri++;
				{ unsigned short *address= (((unsigned short *) ( SCREEN ) )+ ( r[ri+1] ) *64+ ( r[ri] ) /4) ; *address=(*address&masks[( r[ri] )&3])|colours[( r[ri] )&3][ r[ri+2]&7 ]; } ; ri++;
				{ unsigned short *address= (((unsigned short *) ( SCREEN ) )+ ( r[ri+1] ) *64+ ( r[ri] ) /4) ; *address=(*address&masks[( r[ri] )&3])|colours[( r[ri] )&3][ r[ri+2]&7 ]; } ; ri++;
				{ unsigned short *address= (((unsigned short *) ( SCREEN ) )+ ( r[ri+1] ) *64+ ( r[ri] ) /4) ; *address=(*address&masks[( r[ri] )&3])|colours[( r[ri] )&3][ r[ri+2]&7 ]; } ; ri++;
				{ unsigned short *address= (((unsigned short *) ( SCREEN ) )+ ( r[ri+1] ) *64+ ( r[ri] ) /4) ; *address=(*address&masks[( r[ri] )&3])|colours[( r[ri] )&3][ r[ri+2]&7 ]; } ; ri++;
				{ unsigned short *address= (((unsigned short *) ( SCREEN ) )+ ( r[ri+1] ) *64+ ( r[ri] ) /4) ; *address=(*address&masks[( r[ri] )&3])|colours[( r[ri] )&3][ r[ri+2]&7 ]; } ; ri++;

				counts[0]+=10;
			}
		}
		else while(getFrames()<f)
		{
			switch(pass)
			{
				case 1: line(SCREEN,r[ri++],r[ri++],r[ri++],r[ri++],r[ri++]&7); break;
				case 2: triangle(SCREEN,r[ri++],r[ri++],r[ri++],r[ri++],r[ri++],r[ri++],r[ri++]&7); break;
				case 3:fillTriangle(SCREEN,r[ri++],r[ri++],r[ri++],r[ri++],r[ri++],r[ri++],r[ri++]&7); break;
				case 4:box(SCREEN,r[ri++],r[ri++],r[ri++],r[ri++],r[ri++]&7); break;
				case 5:fillBox(SCREEN,r[ri++],r[ri++],r[ri++],r[ri++],r[ri++]&7); break;
				case 6:circle(SCREEN,128,128,r[ri++]&127,r[ri++]&7); break;
				case 7:fillCircle(SCREEN,128,128,r[ri++]&127,r[ri++]&7); break;
				case 8:unplot(SCREEN,r[ri++],r[ri++]); break;
			}

			counts[pass]++;
		}

		if(pass!=7) cls(SCREEN);

		if(ri>= (13107* 10 ) )
		{
			printf("Random overflow! NEED MORE!!! %d\n",ri);
			 
		}
	}

	for(i=0;i< 9 ;i++)
		printf("%8s %8.1f p/s\n",tests[i],counts[i]/(double)10 );

	while(1)
	{
		fillTriangle(SCREEN,128+(fastRand()&127),fastRand()&127,128+(fastRand()&127),fastRand()&127,128+(fastRand()&127),fastRand()&127,fastRand()&7);
		line(SCREEN,128+(fastRand()&127),128+(fastRand()&127),128+(fastRand()&127),128+(fastRand()&127),fastRand()&7);
		circle(SCREEN,64,128+64,fastRand()&63,fastRand()&7);
	}
}

void testMode4()
{
	unsigned int i;

	init(4);

	while(1)
	{
		for(i=0;i<8;i++)
		{
			plot4(SCREEN,i,0,3);
			plot4(SCREEN,i,i,3); sleep(1);
		}

		while(1);
	}
}

void testKey()
{
	while(1)
	{
		unsigned char c=scanKey();

		if(c==8) printf("DEL");
		else if(c!=0) ((  (&__stdout)   )->__wptr>=(  (&__stdout)   )->__wend?(*(  (&__stdout)   )->__flsbuf)((   c   ),(  (&__stdout)   )):(int)((unsigned char)(*(  (&__stdout)   )->__wptr++=(   c   ))))   ;
	}
}

 
 
 

char *drive="MDV1_";

int main(int argc, char *argv[],char *argp[])
{
	unsigned int s;

	if(getenv("DRIVE")!= ((void *) 0) ) _StrCpy (drive,getenv("DRIVE"));

	printf("Default drive is '%s'\n",drive);

	 

	setSysBase((unsigned char *)0x28000);

	 
	 
	 

	for(s=1;s<argc;s++)
	{
		if(strcmp(argv[s],"-bm")==0) benchmark();
		else if(strcmp(argv[s],"-t")==0) test();
		else
		{
			printf("Unknown command line argument: %s\n",argv[s]);
			exit(4);	
		}
	}

	return 0;
}
