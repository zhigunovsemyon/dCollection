#pragma once
#include "object.h"

class Int : public Object {
public:
	~Int() override { delete n_; }

	Int(Int const & i) : n_{new int{*i.n_}} {}

	Int(int n = 0) : n_{new int{n}} {}

	Int & operator=(Int const & i);

	std::string_view type() const override { return "Int"; }

	Int const & print(std::ostream & ost) const override;

	Int & read(std::istream & ist) override;

	int compare(Object const & other) const noexcept(false) override;

	bool equal(Object const & i) const noexcept(false) override;

	Int & add(Object const & other) override;

	/*Перезапись данного файла*/
	Int const & save(std::FILE * src [[maybe_unused]]) const override
	{
		return *this;
	}

	/*Добавление объекта в данный файл*/
	Int const & append(std::FILE * src [[maybe_unused]]) const override
	{
		return *this;
	}

	/*Чтение из переданного файла*/
	Int & read(std::FILE * src [[maybe_unused]]) override { return *this; }

private:
	static char const type_id{0};
	int * n_;

	// Размер объекта при чтении или записи в бинарный файл
	virtual int rwSize() override { return sizeof(*n_) + sizeof(type_id); }
};
