#pragma once
namespace dae
{
	template <typename T> //CRTP : curiously recurring template pattern 
	class Singleton
	{
	public:
		static T& GetInstance()
		{
			static T instance{};
			return instance;
		}

		virtual ~Singleton() = default;
		Singleton(const Singleton& other) = delete;
		Singleton(Singleton&& other) = delete;
		Singleton& operator=(const Singleton& other) = delete;
		Singleton& operator=(Singleton&& other) = delete;

	protected:
		Singleton() = default;
	};
}