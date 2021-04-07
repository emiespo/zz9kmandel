/*
 * MNT ZZ9000 Amiga Graphics and ARM Coprocessor SDK
 * Copyright (C) 2019, Lukas F. Hartmann <lukas@mntre.com>
 *                     MNT Research GmbH, Berlin
 *                     https://mntre.com
 *
 * More Info: https://mntre.com/zz9000
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * GNU General Public License v3.0 or later
 *
 * https://spdx.org/licenses/GPL-3.0-or-later.html
 */

#ifndef ZZ9K_ENV_H
#define ZZ9K_ENV_H

struct ZZ9K_ENV {
  uint32_t api_version;
  uint32_t argv[8];
  uint32_t argc;

  int      (*putchar)(char);
  void     (*set_output_putchar_to_events)(char);
  void     (*set_output_events_blocking)(char);
  void     (*put_event_code)(uint16_t);
  uint16_t (*get_event_serial)();
  uint16_t (*get_event_code)();
  char     (*output_event_acked)();
};

#endif