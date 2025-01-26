#pragma once
#include "object.h"

class Double : public Object {
public:
	/*Деструктор*/
	~Double() override { delete n_; }

	/*Конструктор копирования*/
	Double(Double const & i) : n_{new double{*i.n_}} {}

	/*Конструктор из вещественного числа*/
	Double(double n = 0) : n_{new double{n}} {}

	/*Присвоение*/
	Double & operator=(Double const & i);

	/*Извлечение содержимого в стандартной переменной*/
	double get() const { return *n_; }

	/*Название типа объекта*/
	std::string_view type() const override { return "Double"; }

	/*Вывод в текстовый поток*/
	Double const & print(std::ostream & ost) const override;

	/*Добавление к текущему объекту значения данного*/
	Double & add(Object const & other) override;

	/*Чтение из текстового потока*/
	Double & read(std::istream & ist) override;

	/*Сравнение на равенство текущего объекта с данным*/
	bool equal(Object const & i) const noexcept(false) override
	{
		return (compare(i) == 0);
	}

	/*Сравнение текущего объекта с данным*/
	int compare(Object const & other) const noexcept(false) override;

	/*Перезапись данного файла*/
	Double const & save(std::FILE * src) const noexcept(false) override;

	/*Чтение из переданного файла*/
	Double & read(std::FILE * src) noexcept(false) override;

private:
	static char constexpr type_id_{1};
	double * n_;

	// Размер объекта при чтении или записи в бинарный файл
	size_t rwSize_() override { return sizeof(*n_) + sizeof(type_id_); }
};
