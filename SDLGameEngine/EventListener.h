#pragma once
#include <iostream>
#include <functional>

//http://www.dannyb.me/posts/2014/02/creating_event_system_c++/

template <class T>
class EventListener
{
public:
	using function = std::function<void(const T&)>;

private:
	function handler;

public:
	EventListener(const function &_handler);

	~EventListener();

	void Handle(const T& t);
	void operator()(const T& t);

	bool IsNotNull();
	bool disabled =  false;
};

template <class T> EventListener<T>::EventListener(const function &_handler)
{
	handler = _handler;
}

template <class T> EventListener<T>::~EventListener()
{

}

template <class T> void EventListener<T>::Handle(const T& t)
{
	if (!disabled)
	{
		handler(t);
	}
}

template <class T> void EventListener<T>::operator()(const T& t)
{
	if (!disabled)
	{
		handler(t);
	}
}

template <class T> bool EventListener<T>::IsNotNull()
{
	return handler != nullptr;
}