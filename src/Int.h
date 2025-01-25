#pragma once
#include "object.h"

class Int : public Object {
public:
	/*Деструктор*/
	~Int() override { delete n_; }

	/*Конструктор копирования*/
	Int(Int const & i) : n_{new int{*i.n_}} {}

	/*Конструктор из целочисленного типа*/
	Int(int n = 0) : n_{new int{n}} {}

	/*Присвоение*/
	Int & operator=(Int const & i);

	/*Название типа объекта*/
	std::string_view type() const override { return "Int"; }

	/*Вывод в текстовый поток*/
	Int const & print(std::ostream & ost) const override;

	/*Чтение из текстового потока*/
	Int & read(std::istream & ist) override;

	/*Сравнение текущего объекта с данным*/
	int compare(Object const & other) const noexcept(false) override;

	/*Сравнение на равенство текущего объекта с данным*/
	bool equal(Object const & i) const noexcept(false) override
	{
		return (compare(i) == 0);
	}

	/*Добавление к текущему объекту значения данного*/
	Int & add(Object const & other) override;

	/*Запись в данный бинарный файл*/
	Int const & save(std::FILE * src) const noexcept(false) override;

	/*Чтение из переданного бинарного файла*/
	Int & read(std::FILE * src) noexcept(false) override;

private:
	static char constexpr type_id_{0};
	int * n_;

	// Размер объекта при чтении или записи в бинарный файл
	size_t rwSize_() override { return sizeof(*n_) + sizeof(type_id_); }
};
