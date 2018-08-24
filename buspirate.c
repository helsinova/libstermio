/***************************************************************************
 *   Copyright (C) 2017 by Michael Ambrus                                  *
 *   michael@helsinova.se                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
/*
 * Helpers for project EHWE's buspirate interface
 */

#include "config.h"
#include <stermio.h>
#include <log.h>
#include <assure.h>
#include <string.h>
#include "local.h"

/* Set terminal to as do as little as possible (raw) settings and known
 * to be good defaults for BusPirate */
void stio_bp_raw(int fd)
{
    struct termios c_termios;
    int rc;

    ASSURE(stio_tcgetattr(fd, &c_termios) == 0);
#ifdef HAVE_CYGWIN
    ASSURE(cfsetspeed(&c_termios, B115200) == 0);
#else
    ASSURE(cfsetspeed(&c_termios, 115200) == 0);
#endif
    rc = cfgetispeed(&c_termios);
    TCLOG("cfgetispeed: %d\n", rc);
    rc = cfgetospeed(&c_termios);
    TCLOG("cfgetospeed: %d\n", rc);

    /* Make it so... */
    ASSURE(stio_tcsetattr(fd, TCSANOW, &c_termios) == 0);

    /* Flush pending input.  */
    ASSURE(tcflush(fd, TCIFLUSH) == 0);
}

/* Set terminal settings known to be good defaults for BusPirate "terminal"*/
void stio_bp_terminal(int fd)
{
    struct termios c_termios;
    int rc;

    /* Read termios settings. We don't use them, but reading will put current
       values in log */
    ASSURE(stio_tcgetattr(fd, &c_termios) == 0);

    /* Clear all flags */
    c_termios.c_iflag = 0;
    c_termios.c_oflag = 0;
    c_termios.c_cflag = 0;
    c_termios.c_lflag = 0;

#ifdef NEVER
    /* Rewrite - Good host */
    c_termios.c_iflag = 0x1400;
    c_termios.c_oflag = 0x0000;
    c_termios.c_cflag = 0x14B2;
    c_termios.c_lflag = 0x0000;
#endif

    c_termios.c_cflag |= CS8;
    c_termios.c_cflag |= CREAD;
    c_termios.c_cflag |= HUPCL;

#ifdef NEVER
    //cSmin = 1;
    c_termios.c_cc[VMIN] = 1;   //cSmin;
    c_termios.c_cc[VTIME] = 1;
#endif
    /* Adjust in/out speeds using convenience API */
#ifdef HAVE_CYGWIN
    ASSURE(cfsetspeed(&c_termios, B115200) == 0);
#else
    ASSURE(cfsetspeed(&c_termios, 115200) == 0);
#endif
    rc = cfgetispeed(&c_termios);
    TCLOG("cfgetispeed: %d\n", rc);
    rc = cfgetospeed(&c_termios);
    TCLOG("cfgetospeed: %d\n", rc);

    /* Make it so... */
    ASSURE(stio_tcsetattr(fd, TCSANOW, &c_termios) == 0);

    /* Flush pending input.  */
    ASSURE(tcflush(fd, TCIFLUSH) == 0);

    ASSURE(stio_tcgetattr(fd, &c_termios) == 0);
}
