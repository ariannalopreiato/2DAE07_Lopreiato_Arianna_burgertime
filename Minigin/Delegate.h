#pragma once
#include <algorithm>
#include <vector>
#include <functional>

namespace dae
{
	//https://www.cprogramming.com/tutorial/function-pointers.html
	template <typename T>
	class Delegate final 
	{
	public:

		using Callback = std::function<void(const T&)>; //callback function will be called when a particular event happens 

		void BindCallback(const Callback& callback)
		{
			//check if the callback has already been added to the callback vector 
			auto it = std::find_if(m_Callbacks.cbegin(), m_Callbacks.cend(), [&callback](const Callback& call) -> bool
				{ return call.target_type() == callback.target_type(); });

			if (it == m_Callbacks.cend())
				m_Callbacks.emplace_back(callback); //add it to callbacks
		}

		//will notify the code that the event has been fired
		void Notify(const T& data)
		{
			for (size_t i = 0; i < m_Callbacks.size(); ++i)
			{
				m_Callbacks[i](data);
			}
		}

	private:
		std::vector<Callback> m_Callbacks;
	};
}

