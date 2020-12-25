#pragma once

#include <tuple>

/*
// создаем коллбек с такой сигнатурой
	struct callback
	{
		template<std::size_t, class T>
		void operator()( T&& element )
		{
			// действие над элементом кортежа
		}
	};
	foreachTuple(callback(), myTuple); // вызываем его
*/

class TupleHelper
{
public:
	template<class CallbackForeach, class ...Args>
	static void foreachTuple(CallbackForeach callback, const std::tuple<Args...>& tuple);
};

template<std::size_t IndexElement, class CallbackForeach, class ...Args>
class ForeachTuple
{
public:
	static void tupleForeach(CallbackForeach callback, const std::tuple<Args...>& tuple);
};

template<class CallbackForeach, class ...Args>
class ForeachTuple<0, CallbackForeach, Args...> // заглушка для выхода из рекурсии (по 0-му элементу кортежа)
{
public:
	static void tupleForeach(CallbackForeach, const std::tuple<Args...>&);
};

// -------------------------------------- //

template<class CallbackForeach, class ...Args>
inline void TupleHelper::foreachTuple(CallbackForeach callback, const std::tuple<Args...>& tuple)
{
	ForeachTuple<sizeof...(Args), CallbackForeach, Args...>::tupleForeach(callback, tuple);
}

template<std::size_t IndexElement, class CallbackForeach, class ...Args>
inline void ForeachTuple<IndexElement, CallbackForeach, Args...>::tupleForeach(CallbackForeach callback, const std::tuple<Args...>& tuple)
{
	// вызов коллбека для элемента кортежа по индексу
	const std::size_t index(sizeof...(Args) - IndexElement);
	callback.template operator()<index>(std::get<index>(tuple));
	ForeachTuple<IndexElement - 1, CallbackForeach, Args...>::tupleForeach(callback, tuple);
}

template<class CallbackForeach, class ...Args>
inline void ForeachTuple<0, CallbackForeach, Args...>::tupleForeach(CallbackForeach callback, const std::tuple<Args...>& tuple)
{
	// выход из рекурсии
	return;
}
