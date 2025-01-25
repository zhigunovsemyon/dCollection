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
	Int const & save(std::FILE * src) const noexcept(false) override;

	/*Чтение из переданного файла*/
	Int & read(std::FILE * src) noexcept(false) override;

private:
	static char constexpr type_id_{0};
	int * n_;

	// Размер объекта при чтении или записи в бинарный файл
	size_t rwSize_() override { return sizeof(*n_) + sizeof(type_id_); }
};
