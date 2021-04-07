/*
 * MNT ZZ9000 Amiga Graphics and ARM Coprocessor SDK
 *            Code example: "blur"
 *
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

#define ZZ9K_ARM_CODE

#include <stdlib.h>
#include <unistd.h>

#include "lib/printf/printf.h"
#include "zz9k_env.h"

#include "../mandel.h"

struct ZZ9K_ENV* _zz9k_env;

void __aeabi_idiv0(int r) {
  printf("__aeabi_idiv0()!\n");
  while (1) {
  }
}
void __aeabi_ldiv0(int r) {
  printf("__aeabi_idiv0()!\n");
  while (1) {
  }
}

int errno_var = 0;

int* __errno() {
  return &errno_var;
}

void _putchar(char c) {
  _zz9k_env->putchar(c);
};

int __attribute__ ((section (".binstart"))) main(struct ZZ9K_ENV* env) {
  _zz9k_env = env;

  printf("Program started on the ARM side. Env: %x\n", env);

  if (!env) {
    _putchar('d');
    return 1;
  }
  
  // argv[0]: framebuffer pointer
  // argv[1]: screen width
  // argv[2]: screen height
  // argv[3]: bitmap format (assume it's always 24bits)
  int code = mandel(env->argc, env->argv);
  if (code != 0) {
    printf("Not enough arguments passed to Mandel. Aborting!\n");
  }
  printf("Program terminated on the ARM side\n");
  return code;
}
