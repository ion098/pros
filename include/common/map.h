/**
 * \file common/map.h
 *
 * Kernel-allocated thread-safe hash map header
 *
 * See common/map.c for discussion
 *
 * \copyright Copyright (c) 2017-2023, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "kapi.h"

struct map_node {
    uint32_t hash;
    void* key;
    void* val;
}

struct map {
	map_node* arr;
	size_t size;
    int (*comparator)(void *, void *);
    uint32_t (*hash)(void *);
	static_sem_s_t mtx_buf;
	mutex_t mtx;
};

/**
 * Initializes a a map.
 *
 * \param map
 *        A pointer to a map structure
 * \param comparator
 *        A pointer to a function to compare two keys for eqaulity
 * \param hash
 *        A pointer to a function to hash a key
 */
void map_initialize(struct map* const map, bool (*comparator)(void *, void *), uint32_t (*hash)(void *));

/**
 * Add an item to the map if it didn't already exist
 *
 * \param map
 *        A pointer to the map structure
 * \param key
 *        key of the item to add to the map
 * \param val
 *        value of the item to add to the map
 *
 * \return true if the item was added to the map or false if it was already present
 */
bool map_add(struct map* const map, void* key, void* val);

/**
 * Removes a value from the map
 *
 * \param map
 *        A pointer to the map structure
 * \param key
 *        The key to remove
 *
 * \return A pointer to the data, or a null pointer if the key was not found
 */
void* map_rm(struct map* const map, void* key);

/**
 * Get a value from the map
 *
 * \param map
 *        A pointer to the map structure
 * \param key
 *        The key to check
 *
 * \return True if the item is in the map
 */
void* map_find(struct map* map, void* key);
