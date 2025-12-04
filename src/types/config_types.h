#ifndef CONFIG_TYPES_H
#define CONFIG_TYPES_H

#include <cstdint>

namespace FAN {
    enum SPEED : uint8_t {
        AUTO = 0,
        SLOW = 1,
        MEDIUM = 2,
        FAST = 3
    };
}

namespace CLIMATE {
    enum MODE : uint8_t {
        AUTO = 0,
        COOL = 1,
        DRY = 2,
        HEAT = 3,
        FAN = 4
    };
}

namespace SWING {
    enum MODE_V : uint8_t {
        AUTO = 0,
        OFF = 1,
        TOP = 2,
        FRONT = 3,
        BOTTOM = 4,
        DOWN = 5,
    };
}

#endif