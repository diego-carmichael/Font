#include "dbg/log.hpp"
#include "os/time.hpp"
#include "gfx/surface.hpp"
#include "create/create.hpp"
#include "create/logic/font.hpp"

int main(void) {
	gfx::surface surface = gfx::surface("Font", 800, 600);
	cr::creationScene scene(&surface);

	while (surface.active()) {
		surface.update();
	}

	dbg::log("Program executed successfully, sleeping for 3 seconds...\n");
	os::sleep(3);
	dbg::log("Exiting...\n");
	return 0;
}