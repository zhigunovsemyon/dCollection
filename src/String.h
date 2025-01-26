#pragma once
#include "object.h"
#include <string>

class String : public Object {
public:
	/*Деструктор*/
	~String() override {}

	/*Конструктор копирования*/
	String(String const & i) : str_{i.str_} {}

	/*Конструктор из C-строки*/
	String(char const * src = "") : str_{src} {}

	/*Длина строки*/
	auto length() const { return str_.length(); }

	/*Присвоение*/
	String & operator=(String const & i)
	{
		str_ = i.str_;
		return *this;
	}

	/*Название типа объекта*/
	std::string_view type() const override { return "String"; }

	/*Вывод в текстовый поток*/
	String const & print(std::ostream & ost) const override
	{
		ost << str_;
		return *this;
	}

	/*Добавление к текущему объекту значения данного*/
	String & add(Object const & other) override;

	/*Чтение из текстового потока*/
	String & read(std::istream & ist) override
	{
		ist >> str_;
		return *this;
	}

	/*Сравнение на равенство текущего объекта с данным*/
	bool equal(Object const & i) const noexcept(false) override
	{
		return (compare(i) == 0);
	}

	/*Сравнение текущего объекта с данным*/
	int compare(Object const & other) const noexcept(false) override;

	/*Перезапись данного файла*/
	String const & save(std::FILE * src) const noexcept(false) override;

	/*Чтение из переданного файла*/
	String & read(std::FILE * src) noexcept(false) override;

private:
	static char constexpr type_id_{2};
	std::string str_;

	// Размер объекта при чтении или записи в бинарный файл
	size_t rwSize_() override
	{
		return sizeof(str_.length()) + sizeof(char) * str_.length() +
		       sizeof(type_id_);
	}
};
