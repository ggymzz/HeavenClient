//////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright � 2016 Daniel Allendorf                                        //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////
#include "SkillHitEffect.h"

#include "Util\Misc.h"

namespace Gameplay
{
	SingleHitEffect::SingleHitEffect(node src)
		: effect(src["hit"]["0"]) {}

	void SingleHitEffect::apply(const AttackUser& user, Mob& target) const
	{
		effect.apply(target, user.flip);
	}


	TwoHHitEffect::TwoHHitEffect(node src)
		: effects(src["hit"]["0"], src["hit"]["1"]) {}

	void TwoHHitEffect::apply(const AttackUser& user, Mob& target) const
	{
		effects[user.secondweapon].apply(target, user.flip);
	}


	ByLevelHitEffect::ByLevelHitEffect(node src)
	{
		for (node sub : src["CharLevel"])
		{
			uint16_t level = StringConversion<uint16_t>(sub.name()).orzero();
			effects.emplace(level, sub["hit"]["0"]);
		}
	}

	void ByLevelHitEffect::apply(const AttackUser& user, Mob& target) const
	{
		if (effects.size() == 0)
			return;

		auto iter = effects.begin();
		for (; iter != effects.end() && user.level > iter->first; ++iter) {}
		if (iter != effects.begin())
			iter--;

		iter->second.apply(target, user.flip);
	}


	ByLevelTwoHHitEffect::ByLevelTwoHHitEffect(node src)
	{
		for (node sub : src["CharLevel"])
		{
			auto level = StringConversion<uint16_t>(sub.name()).orzero();
			effects.emplace(std::piecewise_construct,
				std::forward_as_tuple(level), 
				std::forward_as_tuple(sub["hit"]["0"], sub["hit"]["1"])
				);
		}
	}

	void ByLevelTwoHHitEffect::apply(const AttackUser& user, Mob& target) const
	{
		if (effects.size() == 0)
			return;

		auto iter = effects.begin();
		for (; iter != effects.end() && user.level > iter->first; ++iter) {}
		if (iter != effects.begin())
			iter--;

		iter->second[user.secondweapon].apply(target, user.flip);
	}


	BySkillLevelHitEffect::BySkillLevelHitEffect(node src)
	{
		for (auto sub : src["level"])
		{
			auto level = StringConversion<int32_t>(sub.name()).orzero();
			effects.emplace(level, sub["hit"]["0"]);
		}
	}

	void BySkillLevelHitEffect::apply(const AttackUser& user, Mob& target) const
	{
		auto iter = effects.find(user.skilllevel);
		if (iter != effects.end())
		{
			iter->second.apply(target, user.flip);
		}
	}
}