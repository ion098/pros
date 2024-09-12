#pragma once

struct hot_table {
	char const* compile_timestamp;
	char const* compile_directory;

	void* __exidx_start;
	void* __exidx_end;

	struct {
#define FUNC(F) void (*F)();
#include "system/user_functions/list.h"
#undef FUNC
	} functions;

	void* __assets_start;
	void* __assets_end;
};

extern struct hot_table* const HOT_TABLE;
