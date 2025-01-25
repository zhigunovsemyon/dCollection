#include "Double.h"
#include <vector>

Double const & Double::print(std::ostream & ost) const
{
	ost << *n_;
	return *this;
}

Double & Double::add(Object const & other)
{
	auto cmp{dynamic_cast<Double const *>(&other)};
	if (nullptr == cmp)
		throw Object::exceptions::NOT_MATCHING_TYPES;

	*n_ += *(cmp->n_);
	return *this;
}

Double & Double::read(std::istream & ist)
{
	ist >> *n_;
	return *this;
}

Double & Double::operator=(Double const & i)
{
	*n_ = *i.n_;
	return *this;
}

int Double::compare(Object const & other) const noexcept(false)
{
	auto cmp{dynamic_cast<Double const *>(&other)};
	if (nullptr == cmp)
		throw Object::exceptions::NOT_MATCHING_TYPES;

	auto diff{*n_ - *cmp->n_};
	return (diff > 0) ? 1 : (diff < 0) ? -1 : 0;
}

Double const & Double::save(std::FILE * src) const
{
	if (!std::fwrite(&type_id_, sizeof(type_id_), 1, src))
		throw Object::exceptions::FWRITE_FAIL;
	if (!std::fwrite(n_, sizeof(*n_), 1, src))
		throw Object::exceptions::FWRITE_FAIL;
	return *this;
}

/*Чтение из переданного файла*/
Double & Double::read(std::FILE * src)
{
	/*Буфер для хранения прочитанного*/
	std::vector<std::byte> buf;
	buf.reserve(rwSize_());

	/*Чтение файла в буфер*/
	if (!fread(buf.data(), rwSize_(), 1, src))
		throw Object::exceptions::FREAD_FAIL;

	/*Если идентификатор типа из буфера не соответствует таковому для
	 *данного объекта, выбрасывается соответствующее исключение*/
	if (static_cast<char>(*buf.data()) != type_id_)
		throw Object::exceptions::NOT_MATCHING_TYPES;

	/*Перезапись значения*/
	*n_ = *(double *)(buf.data() + 1);

	return *this;
}
