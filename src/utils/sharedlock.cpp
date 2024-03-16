#include "sharedlock.h"

#include <QSystemSemaphore>

SharedLock::SharedLock(const QString &id) : mutex_(id)
{
#ifndef Q_OS_WIN32
    QSystemSemaphore semaphore(id + "-mutex", 1);
    semaphore.acquire();

    // on linux/unix shared memory is not freed upon crash
    // so if there is any trash from previous instance, clean it
    QSharedMemory nix_fix(id);
    if (nix_fix.attach())
        nix_fix.detach();
#endif

    if (mutex_.attach())
    {
        hasLock_ = false;
    }
    else
    {
        mutex_.create(1);
        hasLock_ = true;
    }

#ifndef Q_OS_WIN32
    semaphore.release();
#endif
}
