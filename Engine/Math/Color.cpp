#include "Color.h"
#include <string>

namespace nc
{
	const Color Color::white{ 1, 1, 1 };
	const Color Color::red{ 1, 0, 0 };
	const Color Color::green{ 0, 1, 0 };
	const Color Color::blue{ 0, 0, 1 };
	const Color Color::purple{ 1, 0, 1 };
	const Color Color::cyan{ 0, 1, 1 };
	const Color Color::orange{ 1, 0.5f, 0 };
	const Color Color::yellow{ 1, 1, 0 };
	const Color Color::black{ 1, 1, 0 };

	std::istream& operator>>(std::istream& stream, Color& color)
	{
		std::string line;
		std::getline(stream, line);

		if (line.find("{") != std::string::npos)
		{
			// red
			std::string r = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
			color.r = std::stof(r);

			line = line.substr(line.find(",") + 1);

			// green
			std::string g = line.substr(0, line.find(","));
			color.g = std::stof(g);

			// blue
			std::string b = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);
			color.b = std::stof(b);
		}

		return stream;
	}

	Color Color::HSVToRGB(float h, float s, float v)
	{
		Color rgb;

		float chroma = s * v;
		float hdash = h / 60.0f;
		float x = chroma * (1.0f - std::abs(std::fmod(hdash, 2.0f) - 1.0f));

		if (hdash < 1.0)
		{
			rgb.r = chroma;
			rgb.g = x;
		}
		else if (hdash < 2.0)
		{
			rgb.r = x;
			rgb.g = chroma;
		}
		else if (hdash < 3.0)
		{
			rgb.g = chroma;
			rgb.b = x;
		}
		else if (hdash < 4.0)
		{
			rgb.g = x;
			rgb.b = chroma;
		}
		else if (hdash < 5.0)
		{
			rgb.r = x;
			rgb.b = chroma;
		}
		else if (hdash <= 6.0)
		{
			rgb.r = chroma;
			rgb.b = x;
		}

		float min = v - chroma;

		rgb.r += min;
		rgb.g += min;
		rgb.b += min;

		return rgb;
	}

	void Color::RGBToHSV(const Color& rgb, float& h, float& s, float& v)
	{
		float max = std::max(rgb.r, std::max(rgb.g, rgb.b));
		float min = std::min(rgb.r, std::min(rgb.g, rgb.b));
		float chroma = max - min;

		if (chroma != 0)
		{
			if (rgb.r == max)
			{
				h = (rgb.g - rgb.b) / chroma;

				if (h < 0.0)
				{
					h += 6.0f;
				}
			}
			else if (rgb.g == max)
			{
				h = ((rgb.b - rgb.r) / chroma) + 2.0f;
			}
			else // rgb.b == max
			{
				h = ((rgb.r - rgb.g) / chroma) + 4.0f;
			}

			h *= 60.0;
			s = chroma / max;
		}

		v = max;
	}

	std::ostream& operator<<(std::ostream& stream, Color& color)
	{
		stream << color.r << " " << color.g << " " << color.b;

		return stream;
	}

}
