#pragma once

/// вспомогательный класс для запрета присваивания
class NonAssignable
{
public:
	NonAssignable& operator=(const NonAssignable &) = delete;
	virtual ~NonAssignable() = default;
};
