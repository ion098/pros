#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "v5_api.h"


static inline uint8_t vex_read_char() {
	int32_t b = vexSerialReadChar(1);
	while (b == -1L) {
		task_delay(1);
		b = vexSerialReadChar(1);
	}
	// Don't get rid of the literal type suffix, it ensures optimiziations don't
	// break this condition
	return (uint8_t)b;
}

static inline bool write_response(const char* data) {
    vexSerialWriteBuffer(1, data, strlen(data));
    return true;
}

static inline uint32_t read_data(void) {
    static char buf[16] = {};
    for (size_t i = 0; i < 16; i++) {
        buf[i] = vex_read_char();
    }
    return strtol(buf, NULL, 16);
}

static inline void expect(uint8_t c) {
    if(vex_read_char() != c) exit(1);
}

void gdbParse() {
    uint8_t chr = vex_read_char();
    switch (chr) {
        case 'm': {
            uint32_t addr_start = read_data();
            expect(',');
            uint32_t len = read_data();
        }
        default:
            write_response("$#00");
    }
}
