/*
 * File: threadimpl.cpp
 * --------------------
 * This file contains the implementation of the template functions,
 * which have to be compiled together with the header.
 */

#ifdef _thread_h

int forkForPlatform(void (*fn)(void *), void *dp);

struct StartWithVoid {
   void (*fn)();
};

template <typename ClientType>
struct StartWithClientData {
   void (*fn)(ClientType & data);
   ClientType *dp;
};

template <typename ClientType>
static void forkWithClientData(void *arg) {
   StartWithClientData<ClientType> *startup =
      (StartWithClientData<ClientType> *) arg;
   startup->fn(*startup->dp);
}

template <typename ClientType>
Thread fork(void (*fn)(ClientType & data), ClientType & data) {
   StartWithClientData<ClientType> startup = { fn, &data };
   Thread thread;
   thread.id = forkForPlatform(forkWithClientData<ClientType>, &startup);
   return thread;
}

#endif
