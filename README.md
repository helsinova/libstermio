# libstermio

Manage serial ports (i.e. serial terminals) using termio (library)

## Motivation for project existence

Serial lines in UN*X are "terminals", i.e. they have a lot more intelligence
than for example COM ports under Windows in matters like LF, cannonical
in-/out-put, line-buffering e.t.c.

But for simple use-cases where serial ports are meant to be used with very
dumb HW and/or the programmer has full control over speed and buffering,
they are actually obscure to control.

Under UN*X this control is best done via the termio API. However this is not
a rigid standard and OS differences exists. This project attempts to
overcome these differences.
