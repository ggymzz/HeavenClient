/////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright � 2015 Daniel Allendorf                                        //
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
#include "Graphics\Textlabel.h"
#include <vector>

namespace IO
{
	using std::string;
	using std::vector;
	using Util::vector2d;
	using Graphics::Textlabel;

	struct StatusInfo
	{
		Textlabel::Textcolor color = Textlabel::TXC_WHITE;
		string text = "";
		float alpha = 1.0f;
		float lastalpha = 1.0f;

		float getalpha(float inter) const
		{
			return (1.0f - inter) * lastalpha + inter * alpha;
		}
	};

	class StatusMessenger
	{
	public:
		StatusMessenger();
		~StatusMessenger();

		void draw(vector2d<int16_t> position, float inter) const;
		void update();
		void showstatus(Textlabel::Textcolor color, string message);

	private:
		vector<StatusInfo> statusinfos;
	};
}