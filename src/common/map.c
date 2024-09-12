/**
 * \file common/map.c
 *
 * Contains an implementation of a thread-safe basic map in the kernel heap.
 * It's used to check which streams are enabled in ser_driver for the moment,
 * but also has list_contains which may be useful in other contexts.
 *
 * \copyright Copyright (c) 2017-2023, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

/*
#include <string.h>

#include "common/map.h"
#include "kapi.h"
#include "system/optimizers.h"

void map_initialize(struct map* const map) {
	map->arr = kmalloc(32 * sizeof(map_node));
	map->size = 32;
	map->mtx = mutex_create_static(&(map->mtx_buf));
}

bool map_add(struct map* const map, void* key, void* val) {
	size_t i = 0;
	if (!mutex_take(map->mtx, TIMEOUT_MAX)) {
		return false;
	}
    uint32_t hash = map->hash(key);
	for (i = 0; i < map->size; i++) {
        map_node* node = map->arr + i + hash % map->size;
		if
	}
	if (map->used == map->size) {
		
	}
	map->arr[map->used] = item;
	map->used++;
	mutex_give(map->mtx);
	return true;
}

bool map_rm(struct map* map, uint32_t item) {
	size_t i = 0;
	if (!mutex_take(map->mtx, TIMEOUT_MAX)) {
		return false;
	}
	for (i = 0; i < map->used - 1; i++) {
		if (map->arr[i] == item) {
			memcpy(map->arr + i, map->arr + i + 1, map->used - i - 1);
			map->used--;
			mutex_give(map->mtx);
			return true;
		}
	}
	if (map->arr[map->used] == item) {
		// this is the last item, no need to do memcpy, just decrement the counter
		map->used--;
	}
	mutex_give(map->mtx);
	return true;
}

bool map_contains(struct map* map, uint32_t item) {
	if (!mutex_take(map->mtx, TIMEOUT_MAX)) {
		return false;
	}
	bool ret = list_contains(map->arr, map->used, item);
	mutex_give(map->mtx);
	return ret;
}

static void grow_map(struct map* map) {
    map_node* temp = map->arr;
    size_t new_size = (map->size / 2 * 3);
    // Use 1.5 growth factor
    map->arr = kmalloc(new_size * sizeof(map_node));
    if (unlikely(map->arr == NULL)) {
        map->arr = temp;
        return false;
    }
    memcpy(map->arr, temp, map->size * sizeof(map_node));
    map->size = new_size;
    return true;
}
*/