#pragma once
namespace dae
{
	class Observer //knows what other classes do
	{
	public:
		virtual ~Observer() {}
		virtual void onNotify(const std::string& message) = 0;
	};
}

