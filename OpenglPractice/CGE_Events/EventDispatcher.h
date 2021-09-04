#pragma once
#include <functional>
#include <vector>

namespace ComplementEngine {
	template <typename Ret, typename... Args>
	class EventDispatcher {
	private:
		std::vector<std::function<Ret(Args...)>> m_Delegates;
	public:
		void operator +=(const std::function<Ret(Args...)>& delegate) {
			m_Delegates.push_back(delegate);
		}

		void operator -=(const std::function<Ret(Args...)>& delegate) {
			m_Delegates.erase(std::remove_if(m_Delegates.begin(), m_Delegates.end(), [&delegate](std::function<Ret(Args...)>& val) { return delegate == val; }), m_Delegates.end());
		}

		void operator()(Args... args) {
			for (std::function<Ret(Args...)>& i : m_Delegates) {
				i(args...);
			}
		}

		void clear() {
			m_Delegates.erase(m_Delegates.begin(), m_Delegates.end());
		}
	};
}