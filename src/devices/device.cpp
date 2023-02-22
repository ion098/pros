#include "pros/device.hpp"

#include "vdml/registry.h"

namespace pros {
inline namespace v5 {
class Device {
	public:
	/**
	 * Gets the port number of the Smart Device.
	 *
	 * \return The smart device's port number.
	 */
	std::uint8_t get_port(void) {
		return _port;
	}

	/**
	 * Gets the type of device.
	 *
	 * \return The device type as an enum.
	 */
	virtual pros::DeviceType get_type() {
        v5_smart_device_s_t device = registry_get_device_internal(_port);
        return device->device_type;
    }

	protected:
	/**
	 * Creates a Device object.
	 *
	 * \param port The V5 port number from 1-21
	 *
	 */
	explicit Device(const std::uint8_t port) : _port(port) {}

	protected:
	const std::uint8_t _port;
};
}  // namespace v5
}  // namespace p