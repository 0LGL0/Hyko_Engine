#pragma once

namespace Hyko {
	class Time {
		float m_time;
	public:
		Time(float time = 0.0f)  
			: m_time(time)
		{
		}
		float getDeltaSeconds() {
			return m_time;
		}
		float getDeltaMilliseconds() {
			return m_time * 1000.0f;
		}
	};
}