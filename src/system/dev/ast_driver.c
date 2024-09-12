/**
 * \file system/dev/ast_driver.c
 *
 * Contains the driver for writing files to the microSD card.
 *
 * \copyright Copyright (c) 2017-2023, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "common/set.h"
#include "common/string.h"
#include "kapi.h"
#include "system/dev/ast.h"
#include "system/dev/vfs.h"
#include "system/hot.h"
#include "system/optimizers.h"
#include "v5_api.h"

typedef struct ast_file_arg {
	void* asset_ptr;
    off_t offset;
} ast_file_arg_t;

/******************************************************************************/
/**                         newlib driver functions                          **/
/******************************************************************************/
int ast_read_r(struct _reent* r, void* const arg, uint8_t* buffer, const size_t len) {
	ast_file_arg_t* file_arg = (ast_file_arg_t*)arg;
	// TODO: implement
	return 0;
}

int ast_write_r(struct _reent* r, void* const arg, const uint8_t* buf, const size_t len) {
	ast_file_arg_t* file_arg = (ast_file_arg_t*)arg;
	// can't write to a static asset
    r->_errno = ENOTSUP;
	return -1;
}

int ast_close_r(struct _reent* r, void* const arg) {
	// Closing is a no-op for static assets
	return 0;
}

int ast_fstat_r(struct _reent* r, void* const arg, struct stat* st) {
	ast_file_arg_t* file_arg = (ast_file_arg_t*)arg;
	// TODO: implement
    st->st_size = 0;
	return 0;
}

int ast_isatty_r(struct _reent* r, void* const arg) {
	return 0;
}

off_t ast_lseek_r(struct _reent* r, void* const arg, off_t ptr, int dir) {
	ast_file_arg_t* file_arg = (ast_file_arg_t*)arg;
	switch (dir) {
        case SEEK_SET:
        file_arg->offset = ptr;
        break;
        case SEEK_CUR:
        file_arg->offset += ptr;
        break;
        case SEEK_END:
        // TODO: implement
        break;
        default:
        // TODO: implement

    }
	return file_arg->offset;
}

int ast_ctl(void* const arg, const uint32_t cmd, void* const extra_arg) {
	return 0;
}

/******************************************************************************/
/**                           Driver description                             **/
/******************************************************************************/

const struct fs_driver _ast_driver = {.close_r = ast_close_r,
                                      .fstat_r = ast_fstat_r,
                                      .isatty_r = ast_isatty_r,
                                      .lseek_r = ast_lseek_r,
                                      .read_r = ast_read_r,
                                      .write_r = ast_write_r,
                                      .ctl = ast_ctl};
const struct fs_driver* const ast_driver = &_ast_driver;

int ast_open_r(struct _reent* r, const char* path, int flags, int mode) {
	ast_file_arg_t* file_arg = kmalloc(sizeof(*file_arg));
    // TODO: implement
	return vfs_add_entry_r(r, ast_driver, file_arg);
}

void ast_initialize(void) {
    extern unsigned __assets_start;
    extern unsigned __assets_end;
    (void) HOT_TABLE->__assets_start;
    (void) HOT_TABLE->__assets_end;
    // TODO: implement
}