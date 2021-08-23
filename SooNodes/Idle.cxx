// (c) Dominique Attali 2003 (LIS)

#include <FL/Fl.H>
#include "Idle.h"

static void (*cb)(void *) = 0;
static void * data;

static void CallIdle()
{
  cb(data);
}

void
SetIdle(void (*cb_user)(void *), void * data_user)
{
  cb = cb_user;
  data = data_user;
  Fl::set_idle(CallIdle);
}

void
SetNoIdle()
{
  Fl::set_idle(0);
}

void
SetIdle()
{
  if (cb) Fl::set_idle(CallIdle);
}
