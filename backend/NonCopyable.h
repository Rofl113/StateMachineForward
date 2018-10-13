#pragma once



/// вспомогательный класс для запрета копирования
class NonCopyable
{
public:
	NonCopyable() = default;
	NonCopyable(const NonCopyable &) = delete;
	virtual ~NonCopyable() = default;
};
