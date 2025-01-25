#pragma once
#include "object.h"

class Double : public Object {
public:
	~Double() override { delete n_; }

	Double(Double const & i) : n_{new double{*i.n_}} {}

	Double(double n = 0) : n_{new double{n}} {}

	Double & operator=(Double const & i)
	{
		*n_ = *i.n_;
		return *this;
	}

	std::string_view type() const override { return "Double"; }

	Double const & print(std::ostream & ost) const override;

	Double & add(Object const & other) override;

	Double & read(std::istream & ist) override;

	bool equal(Object const & i) const noexcept(false) override;

	int compare(Object const & other) const noexcept(false) override;

	/*Перезапись данного файла*/
	Double const & save(std::FILE *src[[maybe_unused]]) const override {return *this;};

	/*Добавление объекта в данный файл*/
	Double const & append(std::FILE *src[[maybe_unused]]) const override {return *this;};

	/*Чтение из переданного файла*/
	Double & read(std::FILE *src[[maybe_unused]]) override {return *this;};

private:
	static char const type_id {1};
	double * n_;
};
