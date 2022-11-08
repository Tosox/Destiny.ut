#pragma once

#include "../sdk/CEntity.hpp"

namespace features
{
	namespace legit
	{
		void rcs();
		void triggerbot();
		void aimbot();
	}

	namespace visuals
	{
		void brightness();
		void loop();

		void glow(CEntity& entity);
		void chams(CEntity& entity);
		void radar(CEntity& entity);
	}

	namespace misc
	{
		void bunnyhop();
		void noflash();
		void fov();
		void autopistol();
	}

	inline void run()
	{
		legit::rcs();
		legit::triggerbot();
		legit::aimbot();

		visuals::brightness();
		visuals::loop();

		misc::bunnyhop();
		misc::noflash();
		misc::fov();
		misc::autopistol();
	}
}