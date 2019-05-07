
typedef unsigned int __pthread_size_t;

typedef struct { long __sig; char __opaque[8]; } pthread_attr_t;
typedef struct { long __sig; char __opaque[8]; } pthread_cond_t;
typedef struct { long __sig; char __opaque[8]; } pthread_condattr_t;
typedef struct { long __sig; char __opaque[8]; } pthread_key_t;
typedef struct { long __sig; char __opaque[8]; } pthread_mutex_t;
typedef struct { long __sig; char __opaque[8]; } pthread_mutexattr_t;
typedef struct { long __sig; char __opaque[8]; } pthread_once_t;
typedef struct { long __sig; char __opaque[8]; } pthread_rwlock_t;
typedef struct { long __sig; char __opaque[8]; } pthread_rwlockattr_t;
typedef unsigned long pthread_t;


#define __PTHREAD_STUB_OK           { return 0; }
#define __PTHREAD_STUB_FAIL         { return -1; }
#define __PTHREAD_STUB_NOOP         { }
#define __PTHREAD_STUB_IS_TRUE      { return 1; }


int pthread_attr_destroy(pthread_attr_t *attr) __PTHREAD_STUB_FAIL
int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate) __PTHREAD_STUB_FAIL
int pthread_attr_getguardsize(const pthread_attr_t *attr, __pthread_size_t *guardsize) __PTHREAD_STUB_FAIL
int pthread_attr_getinheritsched(const pthread_attr_t *attr, int *inheritsched) __PTHREAD_STUB_FAIL
int pthread_attr_getschedparam(const pthread_attr_t *attr, struct sched_param *param) __PTHREAD_STUB_FAIL
int pthread_attr_getschedpolicy(const pthread_attr_t *attr, int *policy) __PTHREAD_STUB_FAIL
int pthread_attr_getscope(const pthread_attr_t *attr, int *contentionscope) __PTHREAD_STUB_FAIL
int pthread_attr_getstackaddr(const pthread_attr_t *attr, void **stackaddr) __PTHREAD_STUB_FAIL
int pthread_attr_getstacksize(const pthread_attr_t *attr, __pthread_size_t *stacksize) __PTHREAD_STUB_FAIL
int pthread_attr_init(pthread_attr_t *attr) __PTHREAD_STUB_OK
int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate) __PTHREAD_STUB_OK
int pthread_attr_setguardsize(pthread_attr_t *attr, __pthread_size_t guardsize) __PTHREAD_STUB_OK
int pthread_attr_setinheritsched(pthread_attr_t *attr, int inheritsched) __PTHREAD_STUB_OK
int pthread_attr_setschedparam(pthread_attr_t *attr, const struct sched_param *param) __PTHREAD_STUB_OK
int pthread_attr_setschedpolicy(pthread_attr_t *attr, int policy) __PTHREAD_STUB_OK
int pthread_attr_setscope(pthread_attr_t *attr, int contentionscope) __PTHREAD_STUB_OK
int pthread_attr_setstackaddr(pthread_attr_t *attr, void *stackaddr) __PTHREAD_STUB_OK
int pthread_attr_setstacksize(pthread_attr_t *attr, __pthread_size_t stacksize) __PTHREAD_STUB_OK
int pthread_cancel(pthread_t thread) __PTHREAD_STUB_OK
void pthread_cleanup_push(void (*routine)(void*), void *arg) __PTHREAD_STUB_NOOP
void pthread_cleanup_pop(int execute) __PTHREAD_STUB_NOOP
int pthread_cond_broadcast(pthread_cond_t *cond) __PTHREAD_STUB_OK
int pthread_cond_destroy(pthread_cond_t *cond) __PTHREAD_STUB_OK
int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *condattr) __PTHREAD_STUB_OK
int pthread_cond_signal(pthread_cond_t *cond) __PTHREAD_STUB_OK
int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime) __PTHREAD_STUB_OK
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex) __PTHREAD_STUB_OK
int pthread_condattr_destroy(pthread_condattr_t *condattr) __PTHREAD_STUB_OK
int pthread_condattr_getpshared(const pthread_condattr_t *condattr, int *pshared) __PTHREAD_STUB_FAIL
int pthread_condattr_init(pthread_condattr_t *condattr) __PTHREAD_STUB_OK
int pthread_condattr_setpshared(pthread_condattr_t *condattr, int pshared) __PTHREAD_STUB_OK
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg) __PTHREAD_STUB_FAIL
int pthread_detach(pthread_t thread) __PTHREAD_STUB_OK
int pthread_equal(pthread_t t1, pthread_t t2) __PTHREAD_STUB_IS_TRUE
void pthread_exit(void *value_ptr) __PTHREAD_STUB_NOOP
int pthread_getconcurrency(void) __PTHREAD_STUB_OK
int pthread_getschedparam(pthread_t thread, int *policy, struct sched_param *param) __PTHREAD_STUB_FAIL
void *pthread_getspecific(pthread_key_t key) __PTHREAD_STUB_OK
int pthread_join(pthread_t thread, void **value_ptr) __PTHREAD_STUB_OK
int pthread_key_create(pthread_key_t *key, void (*destructor)(void *)) __PTHREAD_STUB_OK
int pthread_key_delete(pthread_key_t key) __PTHREAD_STUB_OK
int pthread_mutex_destroy(pthread_mutex_t *mutex) __PTHREAD_STUB_OK
int pthread_mutex_getprioceiling(const pthread_mutex_t *mutex, int *prioceiling) __PTHREAD_STUB_OK
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr) __PTHREAD_STUB_OK
int pthread_mutex_lock(pthread_mutex_t *mutex) __PTHREAD_STUB_OK
int pthread_mutex_setprioceiling(pthread_mutex_t *mutex, int prioceiling, int *old_ceiling) __PTHREAD_STUB_OK
int pthread_mutex_trylock(pthread_mutex_t *mutex) __PTHREAD_STUB_OK
int pthread_mutex_unlock(pthread_mutex_t *mutex) __PTHREAD_STUB_OK
int pthread_mutexattr_destroy(pthread_mutexattr_t *mutexattr) __PTHREAD_STUB_OK
int pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *mutexattr, int *prioceiling) __PTHREAD_STUB_FAIL
int pthread_mutexattr_getprotocol(const pthread_mutexattr_t *mutexattr, int *protocol) __PTHREAD_STUB_FAIL
int pthread_mutexattr_getpshared(const pthread_mutexattr_t *mutexattr, int *pshared) __PTHREAD_STUB_FAIL
int pthread_mutexattr_gettype(const pthread_mutexattr_t *mutexattr, int *type) __PTHREAD_STUB_FAIL
int pthread_mutexattr_init(pthread_mutexattr_t *mutexattr) __PTHREAD_STUB_OK
int pthread_mutexattr_setprioceiling(pthread_mutexattr_t *mutexattr, int prioceiling) __PTHREAD_STUB_OK
int pthread_mutexattr_setprotocol(pthread_mutexattr_t *mutexattr, int protocol) __PTHREAD_STUB_OK
int pthread_mutexattr_setpshared(pthread_mutexattr_t *mutexattr, int pshared) __PTHREAD_STUB_OK
int pthread_mutexattr_settype(pthread_mutexattr_t *mutexattr, int type) __PTHREAD_STUB_OK
int pthread_once(pthread_once_t *once_control, void (*init_routine)(void)) __PTHREAD_STUB_OK
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock) __PTHREAD_STUB_OK
int pthread_rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *rwlockattr) __PTHREAD_STUB_OK
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock) __PTHREAD_STUB_OK
int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock) __PTHREAD_STUB_OK
int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock) __PTHREAD_STUB_OK
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock) __PTHREAD_STUB_OK
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock) __PTHREAD_STUB_OK
int pthread_rwlockattr_destroy(pthread_rwlockattr_t *rwlockattr) __PTHREAD_STUB_OK
int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *rwlockattr, int *pshared) __PTHREAD_STUB_FAIL
int pthread_rwlockattr_init(pthread_rwlockattr_t *rwlockattr) __PTHREAD_STUB_OK
int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *rwlockattr, int pshared) __PTHREAD_STUB_OK
pthread_t pthread_self(void) { return 0; }
int pthread_setcancelstate(int state, int *oldstate) __PTHREAD_STUB_OK
int pthread_setcanceltype(int type, int *oldtype) __PTHREAD_STUB_OK
int pthread_setconcurrency(int new_level) __PTHREAD_STUB_OK
int pthread_setschedparam(pthread_t thread, int policy, const struct sched_param *param) __PTHREAD_STUB_OK
int pthread_setspecific(pthread_key_t key, const void *value) __PTHREAD_STUB_OK
void pthread_testcancel(void) __PTHREAD_STUB_NOOP

