#pragma once


namespace nc {

	const float Pi = 3.14159265359f; //180
	const float TwoPi = 6.28318530718f; //360
	const float HalfPi = 1.57079632679f; //90
	const float QuarterPi = 0.78539816339f; //45



	inline float RadToDeg(float radians) {

		return radians * 180.0f / Pi;
	}

	inline float DegToRad(float degrees) {

		return degrees * Pi / 180.0f;
	}

	template<typename T>
	T Clamp(T v, T min, T max) {
		if (v < min) return min;
		if (v > max) return max;

		return v;
	}

	template<typename T>
	T Wrap(T v, T min, T max) {
		if (v < min) return max;
		if (v > max) return min;

		return v;
	}

	template <typename T>
	T Lerp(T a, T b, float t) {

		t = Clamp(t, 0.0f, 1.0f);

		return a + ((b - a) * t);
	}
}